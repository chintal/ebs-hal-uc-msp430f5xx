/* 
   Copyright (c)
     (c) 2015-2016 Chintalagiri Shashank, Quazar Technologies Pvt. Ltd.
   
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

#ifndef SPI_IMPL_H
#define SPI_IMPL_H

#include <stddef.h>
#include "hal/uc/spi.h"
#include <msp430-driverlib/MSP430F5xx_6xx/driverlib.h>
#include <ds/fifoq.h>

#ifdef uC_INCLUDE_SPI_IFACE

typedef enum {
    SPI_HWIF_USCI_A, 
    SPI_HWIF_USCI_B
} SPI_HWIF_TYPE;

typedef struct _SPI_HWIF_t{
    const SPI_HWIF_TYPE type;
    const HAL_ADDRESS_t base;
    const HAL_BASE_t vector;
}_spi_hwif_t;

typedef struct _SPI_STATE_t{
    volatile uint8_t done;
    spi_transaction_t * ctrans;
    spi_slave_t * slave;
    #if SPI_SUPPORT_SCLK_CTL
    spi_sclk_conf sclk;
    #endif
}spi_state_t;

typedef struct SPI_IF_t{
    const _spi_hwif_t *const hwif;
    spi_state_t *const state;
    fifoq_t *const queue;
}spi_if_t;

extern const spi_if_t *const spi_if[];

#if uC_SPI0_ENABLED
    extern const spi_if_t spi0_if;
    extern spi_transaction_t * spi0_ctrans;
#endif
#if uC_SPI1_ENABLED
    extern const spi_if_t spi1_if;
    extern spi_transaction_t * spi1_ctrans;
#endif
#if uC_SPI2_ENABLED
    extern const spi_if_t spi2_if;
    extern spi_transaction_t * spi2_ctrans;
#endif
#if uC_SPI3_ENABLED
    extern const spi_if_t spi3_if;
    extern spi_transaction_t * spi3_ctrans;
#endif
    
static inline void spi_enqueue_transaction(uint8_t intfnum, spi_transaction_t * transaction){
    fifoq_enqueue(spi_if[intfnum]->queue, (_fifoq_item_stub_t *) transaction);
}

static inline void spi_enqueue_pirority_transaction(uint8_t intfnum, spi_transaction_t * transaction){
    fifoq_enqueue_priority(spi_if[intfnum]->queue, (_fifoq_item_stub_t *) transaction);
}

static inline void spi_cancel_transaction(uint8_t intfnum, spi_transaction_t * transaction){
    fifoq_cancel(spi_if[intfnum]->queue, (_fifoq_item_stub_t *) transaction);
}

static inline uint8_t spi_queue_empty(uint8_t intfnum){
   return fifoq_empty(spi_if[intfnum]->queue);
}

static inline uint8_t spi_txrx_bare(uint8_t intfnum, uint8_t byte){
    return 0xFF;
}

#endif

#endif
