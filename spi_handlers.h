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

#ifndef SPI_HANDLERS_H
#define SPI_HANDLERS_H

extern volatile uint8_t __spi_handler_inclusion;

/**
 * @name SPI Interrupt Handlers
 */
/**@{*/ 

#if uC_SPI0_ENABLED
/**
 * @brief SPI0 interrupt handler
 * 
 * Interrupt handler function for SPI0.
 * 
 * This function dispatches interrupts to the correct handler function. This will
 * usually not need to be changed.  
 * 
 */
void _spi0_irqhandler(void);
#endif

#if uC_SPI1_ENABLED
/**
 * @brief SPI1 interrupt handler
 * 
 * Interrupt handler function for SPI1.
 * 
 * This function dispatches interrupts to the correct handler function. This will
 * usually not need to be changed.  
 * 
 */
void _spi1_irqhandler(void);
#endif

#if uC_SPI2_ENABLED
/**
 * @brief SPI2 interrupt handler
 * 
 * Interrupt handler function for SPI2.
 * 
 * This function dispatches interrupts to the correct handler function. This will
 * usually not need to be changed.  
 * 
 */
void _spi2_irqhandler(void);
#endif

#if uC_SPI3_ENABLED
/**
 * @brief SPI3 interrupt handler
 * 
 * Interrupt handler function for SPI3.
 * 
 * This function dispatches interrupts to the correct handler function. This will
 * usually not need to be changed.  
 * 
 */
void _spi3_irqhandler(void);
#endif



/**@}*/ 
#endif
