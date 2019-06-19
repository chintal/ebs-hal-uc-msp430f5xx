/* 
   Copyright 2015 Quazar Technologies Pvt. Ltd.
   Copyright 2015 Chintalagiri Shashank
   
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


#include "hal/uc/spi.h"
#include "hal/uc/gpio.h"

#include <msp430-driverlib/MSP430F5xx_6xx/usci_a_spi.h>
#include <msp430-driverlib/MSP430F5xx_6xx/usci_b_spi.h>

#ifdef uC_INCLUDE_SPI_IFACE

#if uC_SPI0_ENABLED
    static const _spi_hwif_t _spi0_hwif = {uC_SPI0_TYPE, uC_SPI0_BASE, uC_SPI0_VECTOR};
        
    spi_state_t spi0_state = {0, NULL, NULL};
    fifoq_t spi0_queue;
        
    const spi_if_t spi0_if = {
        &_spi0_hwif,
        &spi0_state,
        &spi0_queue
    };  
#endif
    
#if uC_SPI1_ENABLED
    static const _spi_hwif_t _spi1_hwif = {uC_SPI1_TYPE, uC_SPI1_BASE, uC_SPI1_VECTOR};
        
    spi_state_t spi1_state = {0, NULL, NULL};
    fifoq_t spi1_queue;
        
    const spi_if_t spi1_if = {
        &_spi1_hwif,
        &spi1_state,
        &spi1_queue
    };  
#endif
    
#if uC_SPI2_ENABLED
    static const _spi_hwif_t _spi2_hwif = {uC_SPI2_TYPE, uC_SPI2_BASE, uC_SPI2_VECTOR};
        
    spi_state_t spi2_state = {0, NULL, NULL};
    fifoq_t spi2_queue;
        
    const spi_if_t spi2_if = {
        &_spi2_hwif,
        &spi2_state,
        &spi2_queue
    };  
#endif

#if uC_SPI3_ENABLED
    static const _spi_hwif_t _spi3_hwif = {uC_SPI3_TYPE, uC_SPI3_BASE, uC_SPI3_VECTOR};
        
    spi_state_t spi3_state = {0, NULL, NULL};
    fifoq_t spi3_queue;
        
    const spi_if_t spi3_if = {
        &_spi3_hwif,
        &spi3_state,
        &spi3_queue
    };  
#endif



const spi_if_t *const spi_if[4] = {
    #if uC_SPI0_ENABLED
        &spi0_if
    #else
        NULL
    #endif
    ,
    #if uC_SPI1_ENABLED
        &spi1_if
    #else
        NULL
    #endif
    ,
    #if uC_SPI2_ENABLED
        &spi2_if
    #else
        NULL
    #endif
    ,
    #if uC_SPI3_ENABLED
        &spi3_if
    #else
        NULL
    #endif
};


static void _spi_reset(uint8_t intfnum){
    switch(spi_if[intfnum]->hwif->type){
        case SPI_HWIF_USCI_A:
            HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxCTL1) |= UCSWRST;
            break;
        case SPI_HWIF_USCI_B:
            HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxCTL1) |= UCSWRST;
            break;
    }
}

static void _spi_enable(uint8_t intfnum){
    switch(spi_if[intfnum]->hwif->type){
        case SPI_HWIF_USCI_A:
            HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxCTL1) &= ~UCSWRST;
            break;
        case SPI_HWIF_USCI_B:
            HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxCTL1) &= ~UCSWRST;
            break;
    }
}

static void _spi_gpio_init(uint8_t intfnum){
    switch (intfnum){
        case 0:
            gpio_conf_periph(uC_PORTSEL_SPI0_MISO, uC_PINSEL_SPI0_MISO, 0);
            gpio_conf_periph(uC_PORTSEL_SPI0_MOSI, uC_PINSEL_SPI0_MOSI, 0x80);
            gpio_conf_periph(uC_PORTSEL_SPI0_SCLK, uC_PINSEL_SPI0_SCLK, 0x80);
            break;
        case 1:
            gpio_conf_periph(uC_PORTSEL_SPI1_MISO, uC_PINSEL_SPI1_MISO, 0);
            gpio_conf_periph(uC_PORTSEL_SPI1_MOSI, uC_PINSEL_SPI1_MOSI, 0x80);
            gpio_conf_periph(uC_PORTSEL_SPI1_SCLK, uC_PINSEL_SPI1_SCLK, 0x80);
            break;
        case 2:
            gpio_conf_periph(uC_PORTSEL_SPI2_MISO, uC_PINSEL_SPI2_MISO, 0);
            gpio_conf_periph(uC_PORTSEL_SPI2_MOSI, uC_PINSEL_SPI2_MOSI, 0x80);
            gpio_conf_periph(uC_PORTSEL_SPI2_SCLK, uC_PINSEL_SPI2_SCLK, 0x80);
            break;
        case 3:
            gpio_conf_periph(uC_PORTSEL_SPI3_MISO, uC_PINSEL_SPI3_MISO, 0);
            gpio_conf_periph(uC_PORTSEL_SPI3_MOSI, uC_PINSEL_SPI3_MOSI, 0x80);
            gpio_conf_periph(uC_PORTSEL_SPI3_SCLK, uC_PINSEL_SPI3_SCLK, 0x80);
            break;
    }
}

static void _spi_conf_sclk(uint8_t intfnum, spi_sclk_conf sclk){
    uint16_t offset;
    if (sclk & SPI_CLKSHAP_DEFINED){
        
        switch(spi_if[intfnum]->hwif->type){
            case SPI_HWIF_USCI_A:
                offset = OFS_UCAxCTL0;
                break;
            case SPI_HWIF_USCI_B:
                offset = OFS_UCBxCTL0;
                break;
        }
        
        switch(sclk & SPI_CLKPHA_MASK){
            case SPI_CLKPHA_CAP_CHG:
                HWREG8(spi_if[intfnum]->hwif->base + offset) |= UCCKPH;
                break;
            case SPI_CLKPHA_CHG_CAP:
                HWREG8(spi_if[intfnum]->hwif->base + offset) &= ~UCCKPH;
                break;
        }
    
        switch(sclk & SPI_CLKPOL_MASK){
            case SPI_CLKPOL_AH:
                HWREG8(spi_if[intfnum]->hwif->base + offset) &= ~UCCKPL;
                break;
            case SPI_CLKPOL_AL:
                HWREG8(spi_if[intfnum]->hwif->base + offset) |= UCCKPL;
                break;
        }
    }
    
    if (sclk & SPI_CLKFREQ_DEFINED){
        switch(spi_if[intfnum]->hwif->type){
            case SPI_HWIF_USCI_A:
                HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxBR0) = (sclk & SPI_CLKFREQ_MASK) * 2;
                break;
            case SPI_HWIF_USCI_B:
                HWREG8(spi_if[intfnum]->hwif->base + OFS_UCBxBR0) = (sclk & SPI_CLKFREQ_MASK) * 2;
                break;
        }
    }
        
    spi_if[intfnum]->state->sclk = sclk;
}

static void _spi_init(uint8_t intfnum){
    _spi_reset(intfnum);
    _spi_gpio_init(intfnum);
    fifoq_init(spi_if[intfnum]->queue);
 
    uint8_t clk_default;
    uint8_t clk_source;
    switch(intfnum){
        case 0:
            clk_source = uC_SPI0_CLKSOURCE;
            clk_default = SPI_CLKFREQ_DEFINED | ((APP_SPI0_SCLK_FREQ_DEFAULT * 2 / uC_SPI0_SCLK_BASE_FREQ)  & SPI_CLKFREQ_MASK);
            break;
        case 1:
            clk_source = uC_SPI1_CLKSOURCE;
            clk_default = SPI_CLKFREQ_DEFINED | ((APP_SPI1_SCLK_FREQ_DEFAULT * 2 / uC_SPI1_SCLK_BASE_FREQ) & SPI_CLKFREQ_MASK);
            break;
        case 2:
            clk_source = uC_SPI2_CLKSOURCE;
            clk_default = SPI_CLKFREQ_DEFINED | ((APP_SPI2_SCLK_FREQ_DEFAULT * 2 / uC_SPI2_SCLK_BASE_FREQ) & SPI_CLKFREQ_MASK);
            break;
        case 3:
            clk_source = uC_SPI3_CLKSOURCE;
            clk_default = SPI_CLKFREQ_DEFINED | ((APP_SPI3_SCLK_FREQ_DEFAULT * 2 / uC_SPI3_SCLK_BASE_FREQ) & SPI_CLKFREQ_MASK);
            break;
    }
    
    switch(spi_if[intfnum]->hwif->type){
        case SPI_HWIF_USCI_A:
            HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxCTL0) = 0x00;
            HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxCTL0) |= UCMST;
            HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxCTL1) &= ~(UCSSEL0 | UCSSEL1);
            switch(clk_source){
                case CLKSOURCE_SMCLK:
                    HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxCTL1) |= UCSSEL__SMCLK;
                    break;
                case CLKSOURCE_ACLK:
                    HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxCTL1) |= UCSSEL__ACLK;
                    break;
            }
            break;
        case SPI_HWIF_USCI_B:
            HWREG8(spi_if[intfnum]->hwif->base + OFS_UCBxCTL0) = 0x00;
            HWREG8(spi_if[intfnum]->hwif->base + OFS_UCBxCTL0) |= UCMST;
            HWREG8(spi_if[intfnum]->hwif->base + OFS_UCBxCTL1) &= ~(UCSSEL0 | UCSSEL1);
            switch(clk_source){
                case CLKSOURCE_SMCLK:
                    HWREG8(spi_if[intfnum]->hwif->base + OFS_UCBxCTL1) |= UCSSEL__SMCLK;
                    break;
                case CLKSOURCE_ACLK:
                    HWREG8(spi_if[intfnum]->hwif->base + OFS_UCBxCTL1) |= UCSSEL__ACLK;
                    break;
            }
            break;
    }
    
    _spi_conf_sclk(intfnum, (SPI_CLKSHAP_DEFINED | SPI_CLKPOL_AL | SPI_CLKPHA_CHG_CAP | clk_default));
    _spi_enable(intfnum);
}

void spi_init(void){
    #if uC_SPI0_ENABLED
        _spi_init(0);
    #endif
    #if uC_SPI1_ENABLED
        _spi_init(1);
    #endif
    #if uC_SPI2_ENABLED
        _spi_init(2);
    #endif
    #if uC_SPI3_ENABLED
        _spi_init(3);
    #endif
}

void spi_init_slave(uint8_t intfnum, spi_slave_t * slave){
    switch(slave->sst){
        #if APP_SUPPORT_SPI_SELECT_PIO
        case SPI_SELECTOR_PIO:
            gpio_conf_output(slave->ss.pio.port, slave->ss.pio.pin);
            gpio_set_output_high(slave->ss.pio.port, slave->ss.pio.pin);
            break;
        #endif
        case SPI_SELECTOR_FUNC:
        default:
            break;
    }
}

void spi_select_slave(uint8_t intfnum, spi_slave_t * slave){
    #if SPI_SUPPORT_SCLK_CTL 
    if (spi_if[intfnum]->state->sclk != slave->sclk){
        _spi_reset(intfnum);
        _spi_conf_sclk(intfnum, slave->sclk);
        _spi_enable(intfnum);
    }
    #endif
    switch(slave->sst){
        #if APP_SUPPORT_SPI_SELECT_PIO
        case SPI_SELECTOR_PIO:
            gpio_set_output_low(slave->ss.pio.port, slave->ss.pio.pin);
            break;
        #endif
        case SPI_SELECTOR_FUNC:
            slave->ss.func.select();
            break;
        default:
            break;
    }
    spi_if[intfnum]->state->slave = slave;
}

void spi_deselect_slave(uint8_t intfnum, spi_slave_t * slave){
    switch(slave->sst){
        #if APP_SUPPORT_SPI_SELECT_PIO
        case SPI_SELECTOR_PIO:
            gpio_set_output_high(slave->ss.pio.port, slave->ss.pio.pin);
            break;
        #endif
        case SPI_SELECTOR_FUNC:
            slave->ss.func.deselect();
            break;
        default:
            break;
    }
    spi_if[intfnum]->state->slave = NULL;
}


static void _spi_trigger(uint8_t intfnum){
    if (!spi_queue_empty(intfnum) && !spi_if[intfnum]->state->ctrans){
        spi_if[intfnum]->state->ctrans = (spi_transaction_t * )(fifoq_pop_next(spi_if[intfnum]->queue));
        if (spi_if[intfnum]->state->ctrans->slave){
            spi_select_slave(intfnum, spi_if[intfnum]->state->ctrans->slave);
        }
        switch(spi_if[intfnum]->hwif->type){
            case SPI_HWIF_USCI_A:
                HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxIE) |= UCTXIE;
                break;
            case SPI_HWIF_USCI_B:
                HWREG8(spi_if[intfnum]->hwif->base + OFS_UCBxIE) |= UCTXIE;
                break;
        }
    }
}

static void _spi_wait_busy(uint8_t intfnum){
    switch(spi_if[intfnum]->hwif->type){
        case SPI_HWIF_USCI_A:
            while ( HWREG8(spi_if[intfnum]->hwif->base + OFS_UCAxSTAT) & UCBUSY );
            break;
        case SPI_HWIF_USCI_B:
            while ( HWREG8(spi_if[intfnum]->hwif->base + OFS_UCBxSTAT) & UCBUSY );
            break;
    }
}

// The reactor is to run in the main thread. This ensures that there is no 
// undue exposure to risks of long running callbacks and more inportantly, bypasses
// the problem of implementing concurrency for fifoq primitives. 
static void _spi_reactor(uint8_t intfnum){
    spi_transaction_t * transaction = NULL;
    if (spi_if[intfnum]->state->done){
        transaction = spi_if[intfnum]->state->ctrans;
        spi_if[intfnum]->state->ctrans = NULL;
        spi_if[intfnum]->state->done = 0;
        if (transaction->slave){
            _spi_wait_busy(intfnum);
            spi_deselect_slave(intfnum, transaction->slave);
        }
    }
    
    _spi_trigger(intfnum);
    
    if (transaction && transaction->callback){
        transaction->callback(transaction);
    }
}

void spi_reactor(void){
    #if uC_SPI0_ENABLED
        _spi_reactor(0);
    #endif
    #if uC_SPI1_ENABLED
        _spi_reactor(1);
    #endif
    #if uC_SPI2_ENABLED
        _spi_reactor(2);
    #endif
    #if uC_SPI3_ENABLED
        _spi_reactor(3);
    #endif
}



#endif
