/* 
   Copyright (c)
    (c) 2016 Chintalagiri Shashank, Quazar Technologies Pvt. Ltd.
      
   This file is part of
   Embedded bootstraps : Peripheral driver implementations : MSP430
   
   This library is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/

#include <ds/bytebuf.h>
#include "hal/uc/spi.h"

#ifdef uC_INCLUDE_SPI_IFACE

volatile uint8_t __spi_handler_inclusion;

/**
 * @brief SPI TX interrupt handler
 * 
 * Interrupt handler function for TX Complete on SPI.
 * 
 * Called when SPI transmission is complete. Application code may need to change
 * this function.
 * 
 */
static inline void spi_handler_tx(uint8_t intfnum);

/**
 * @brief SPI RX interrupt handler
 * 
 * Interrupt handler function for RX Complete on SPI.
 * 
 * Called when SPI reception is complete. Application code may need to change
 * this function.
 * 
 */
static inline void spi_handler_rx(uint8_t intfnum);

// TODO Using spi_if[] doesn't seem to produce the best output. It might be necessary
//      to change to individual handler functions for each SPIn, and change to use 
//      the preprocessor declarations instead. This would work best with some kind of
//      C code generator.

static inline void spi_handler_tx(uint8_t intfnum){
    spi_transaction_t * ctrans = spi_if[intfnum]->state->ctrans;
    if (spi_if[intfnum]->hwif->type == SPI_HWIF_USCI_A){
        if (ctrans->txlen){
                HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxTXBUF) = *(ctrans->txdata);
                ctrans->txdata ++;
                ctrans->txlen -= 1;
        }
        else{
            HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxIE) &= ~UCTXIE;
            if (ctrans->rxlen){
                HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxRXBUF);
                HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxIE) |= UCRXIE;
                HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxTXBUF) = 0xFF;
            }
            else{
                spi_if[intfnum]->state->done = 1;
            }
        }
    }
    else if (spi_if[intfnum]->hwif->type == SPI_HWIF_USCI_B){
        if (ctrans->txlen){
                HWREG8(spi_if[intfnum]->hwif->base + OFS_UCBxTXBUF) = *(ctrans->txdata);
                ctrans->txdata ++;
                ctrans->txlen --;
        }
        else{
            HWREG8(spi_if[intfnum]->hwif->base + OFS_UCBxIE) &= ~UCTXIE;
            if (ctrans->rxlen){
                HWREG8(spi_if[intfnum]->hwif->base + OFS_UCBxRXBUF);
                HWREG8(spi_if[intfnum]->hwif->base + OFS_UCBxIE) |= UCRXIE;
                HWREG8(spi_if[intfnum]->hwif->base + OFS_UCBxTXBUF) = 0xFF;
            }
            else{
                spi_if[intfnum]->state->done = 1;
            }
        }
    }
}

static inline void spi_handler_rx(uint8_t intfnum){
    spi_transaction_t * ctrans = spi_if[intfnum]->state->ctrans;
    if (spi_if[intfnum]->hwif->type == SPI_HWIF_USCI_A){
        *(ctrans->rxdata) = HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxRXBUF);
        ctrans->rxlen --;
        ctrans->rxdata ++;
        if (ctrans->rxlen){
            HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxTXBUF) = 0xFF;
        }
        else{
            HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxIE) &= ~UCRXIE;
            spi_if[intfnum]->state->done = 1;
        }
    }
    else if (spi_if[intfnum]->hwif->type == SPI_HWIF_USCI_B){
        *(ctrans->rxdata) = HWREG8(spi_if[intfnum]->hwif->base + OFS_UCBxRXBUF);
        ctrans->rxlen --;
        ctrans->rxdata ++;
        if (ctrans->rxlen){
            HWREG8(spi_if[intfnum]->hwif->base + OFS_UCBxTXBUF) = 0xFF;
        }
        else{
            HWREG8(spi_if[intfnum]->hwif->base + OFS_UCBxIE) &= ~UCRXIE;
            spi_if[intfnum]->state->done = 1;
        }
    }
}


#if uC_SPI0_ENABLED
    __attribute__((interrupt(uC_SPI0_VECTOR)))
    void _spi0_irqhandler(void){
        uint8_t flagreg = HWREG8(uC_SPI0_BASE + OFS_UCAxIFG);
        if ( flagreg & UCTXIFG ){
            spi_handler_tx(0);
        }
        else if ( flagreg & UCRXIFG ){
            spi_handler_rx(0);
        }
    }
#endif

#if uC_SPI1_ENABLED
    __attribute__((interrupt(uC_SPI1_VECTOR)))
    void _spi1_irqhandler(void){
        uint8_t flagreg = HWREG8(uC_SPI1_BASE + OFS_UCBxIFG);
        if ( flagreg & UCTXIFG ){
            spi_handler_tx(1);
        }
        else if ( flagreg & UCRXIFG ){
            spi_handler_rx(1);
        }
    }
#endif

#if uC_SPI2_ENABLED
    __attribute__((interrupt(uC_SPI2_VECTOR)))
    void _spi2_irqhandler(void){
        uint8_t flagreg = HWREG8(uC_SPI2_BASE + OFS_UCAxIFG);
        if ( flagreg & UCTXIFG ){
            spi_handler_tx(2);
        }
        else if ( flagreg & UCRXIFG ){
            spi_handler_rx(2);
        }
    }
#endif

#if uC_SPI3_ENABLED
    __attribute__((interrupt(uC_SPI3_VECTOR)))
    void _spi3_irqhandler(void){
        uint8_t flagreg = HWREG8(uC_SPI3_BASE + OFS_UCBxIFG);
        if ( flagreg & UCTXIFG ){
            spi_handler_tx(3);
        }
        else if ( flagreg & UCRXIFG ){
            spi_handler_rx(3);
        }
    }
#endif

#endif
