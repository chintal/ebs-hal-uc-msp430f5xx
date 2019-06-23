/* 
   Copyright (c) 
     (c) 2015-2016 Chintalagiri Shashank, Quazar Technologies Pvt. Ltd.
   
   This file is part of
   Embedded bootstraps : uC Support Package : MSP430F5529
   
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

/**
 * @file uc_msp430f5529.h
 * @brief uC PUM for MSP430F5529
 *
 * This file contains the peripheral usage map for the MSP430F5529.
 */

#ifndef uC_PUM_SPECIFIC_H
#define uC_PUM_SPECIFIC_H

/**
 * @name Watchdog Configuration
 */
/**@{*/ 
#define uC_HAS_WDT             1
#define uC_WDT_PROVIDER        MSP_WDT_A
/**@}*/ 


/**
 * @name Clock System Configuration
 */
/**@{*/ 
    /**
    * @name System Clock Configuration
    */
    /**@{*/ 
    
    #ifndef uC_FLL_FRQ_HZ
        #define uC_FLL_FRQ_HZ        24000000UL
    #endif
    #define uC_FLL_FRQ_KHZ       (uC_FLL_FRQ_HZ / 1000)
    #define uC_FLL_MULT          (uC_FLL_FRQ_HZ / uC_HF_EXT_CLK_FRQ)
    
    #ifndef uC_MCLK_FRQ_HZ
        #define uC_MCLK_FRQ_HZ       24000000UL
    #endif
    #define uC_MCLK_FRQ_KHZ      (uC_MCLK_FRQ_HZ / 1000)
    #define uC_MCLK_FRQ_MHZ      (uC_MCLK_FRQ_KHZ / 1000)
    
    #ifndef uC_SMCLK_FRQ_HZ
        #define uC_SMCLK_FRQ_HZ      24000000UL
    #endif
    #define uC_SMCLK_FRQ_KHZ     (uC_SMCLK_FRQ_HZ / 1000)
    #define uC_SMCLK_FRQ_MHZ     (uC_SMCLK_FRQ_KHZ / 1000)
    
    #ifndef uC_ACLK_FRQ_HZ
        #define uC_ACLK_FRQ_HZ       32768UL
    #endif
    #define uC_ACLK_FRQ_KHZ      (uC_ACLK_FRQ_HZ / 1000)
    
    
    #define CLKSOURCE_MCLK          0
    #define CLKSOURCE_SMCLK         1
    #define CLKSOURCE_ACLK          2
    
    /**@}*/ 
    
/**@}*/ 


/**
 * @name UART Configuration
 */
/**@{*/ 

    #define uC_AVAILABLE_UARTS     2

    /**
    * @name UART 0 Configuration
    */
    /**@{*/ 
    #define uC_HAS_UART0               1
    #ifndef uC_UART0_BAUD          
        #define uC_UART0_BAUD          19200
    #endif
    #ifndef uC_UART0_TXBUF_LEN
        #define uC_UART0_TXBUF_LEN     10
    #endif
    #ifndef uC_UART0_RXBUF_LEN
        #define uC_UART0_RXBUF_LEN     10
    #endif
    
    #ifndef uC_UART0_CLKSOURCE
        #define uC_UART0_CLKSOURCE     CLKSOURCE_SMCLK
    #endif
    
    #if (uC_UART0_CLKSOURCE == CLKSOURCE_SMCLK)
        #define uC_UART0_BASECLK_FREQ  uC_SMCLK_FRQ_HZ
    #elif (uC_UART0_CLKSOURCE == CLKSOURCE_ACLK)
        #define uC_UART0_BASECLK_FREQ  uC_ACLK_FRQ_HZ
    #endif
    
    #define uC_UART0_TYPE          UART_HWIF_USCI_A
    #define uC_UART0_BASE          USCI_A0_BASE
    #define uC_UART0_VECTOR        USCI_A0_VECTOR

    #define uC_PORTSEL_UART0       GPIO_PORT_P3
    #define uC_PINSEL_UART0_TX     GPIO_PIN3
    #define uC_PINSEL_UART0_RX     GPIO_PIN4

    /**@}*/ 
    
    /**
    * @name UART 1 Configuration
    */
    /**@{*/ 
    #define uC_HAS_UART1               1
    #ifndef uC_UART1_BAUD          
        #define uC_UART1_BAUD          19200
    #endif
    #ifndef uC_UART1_TXBUF_LEN
        #define uC_UART1_TXBUF_LEN     10
    #endif
    #ifndef uC_UART1_RXBUF_LEN
        #define uC_UART1_RXBUF_LEN     10
    #endif
    
    #ifndef uC_UART1_CLKSOURCE
        #define uC_UART1_CLKSOURCE     CLKSOURCE_SMCLK
    #endif
    
    #if (uC_UART1_CLKSOURCE == CLKSOURCE_SMCLK)
        #define uC_UART1_BASECLK_FREQ  uC_SMCLK_FRQ_HZ
    #elif (uC_UART1_CLKSOURCE == CLKSOURCE_ACLK)
        #define uC_UART1_BASECLK_FREQ  uC_ACLK_FRQ_HZ
    #endif
    
    #define uC_UART1_TYPE          UART_HWIF_USCI_A
    #define uC_UART1_BASE          USCI_A1_BASE
    #define uC_UART1_VECTOR        USCI_A1_VECTOR

    #define uC_PORTSEL_UART1       GPIO_PORT_P4
    #define uC_PINSEL_UART1_TX     GPIO_PIN4
    #define uC_PINSEL_UART1_RX     GPIO_PIN5

    /**@}*/ 
    
/**@}*/ 


/**
 * @name SPI Configuration
 */
/**@{*/ 

    #define uC_AVAILABLE_SPIS     4

    /**
    * @name SPI 0 Configuration (UCA0)
    */
    /**@{*/
    #define uC_HAS_SPI0             1
    #ifndef uC_SPI0_TXBUF_LEN
        #define uC_SPI0_TXBUF_LEN     10
    #endif
    #ifndef uC_SPI0_RXBUF_LEN
        #define uC_SPI0_RXBUF_LEN     10
    #endif

    #ifndef uC_SPI0_CLKSOURCE
        #define uC_SPI0_CLKSOURCE       CLKSOURCE_SMCLK
    #endif
    
    #if (uC_SPI0_CLKSOURCE == CLKSOURCE_SMCLK)
        #define uC_SPI0_SCLK_BASE_FREQ  uC_SMCLK_FRQ_HZ
    #elif (uC_SPI0_CLKSOURCE == CLKSOURCE_ACLK)
        #define uC_SPI0_SCLK_BASE_FREQ  uC_ACLK_FRQ_HZ
    #endif
    
    #ifndef APP_SPI0_SCLK_FREQ_DEFAULT
        #define APP_SPI0_SCLK_FREQ_DEFAULT  4000000UL
    #endif
    
    #define uC_SPI0_TYPE            SPI_HWIF_USCI_A
    #define uC_SPI0_BASE            USCI_A0_BASE
    #define uC_SPI0_VECTOR          USCI_A0_VECTOR

    #define uC_PORTSEL_SPI0_MISO    GPIO_PORT_P3
    #define uC_PINSEL_SPI0_MISO     GPIO_PIN4
    
    #define uC_PORTSEL_SPI0_MOSI    GPIO_PORT_P3
    #define uC_PINSEL_SPI0_MOSI     GPIO_PIN3
    
    #define uC_PORTSEL_SPI0_SCLK    GPIO_PORT_P2
    #define uC_PINSEL_SPI0_SCLK     GPIO_PIN7
    /**@}*/ 
    
    /**
    * @name SPI 1 Configuration (UCB0)
    */
    /**@{*/ 
    #define uC_HAS_SPI1             1
    #ifndef uC_SPI1_TXBUF_LEN
        #define uC_SPI1_TXBUF_LEN     10
    #endif
    #ifndef uC_SPI1_RXBUF_LEN
        #define uC_SPI1_RXBUF_LEN     10
    #endif
    
    #ifndef uC_SPI1_CLKSOURCE
        #define uC_SPI1_CLKSOURCE       CLKSOURCE_SMCLK
    #endif
    
    #if (uC_SPI1_CLKSOURCE == CLKSOURCE_SMCLK)
        #define uC_SPI1_SCLK_BASE_FREQ  uC_SMCLK_FRQ_HZ
    #elif (uC_SPI1_CLKSOURCE == CLKSOURCE_ACLK)
        #define uC_SPI1_SCLK_BASE_FREQ  uC_ACLK_FRQ_HZ
    #endif
    
    #ifndef APP_SPI1_SCLK_FREQ_DEFAULT
        #define APP_SPI1_SCLK_FREQ_DEFAULT  4000000UL
    #endif
    
    #define uC_SPI1_TYPE            SPI_HWIF_USCI_B
    #define uC_SPI1_BASE            USCI_B0_BASE
    #define uC_SPI1_VECTOR          USCI_B0_VECTOR

    #define uC_PORTSEL_SPI1_MISO    GPIO_PORT_P3
    #define uC_PINSEL_SPI1_MISO     GPIO_PIN1
    
    #define uC_PORTSEL_SPI1_MOSI    GPIO_PORT_P3
    #define uC_PINSEL_SPI1_MOSI     GPIO_PIN0
    
    #define uC_PORTSEL_SPI1_SCLK    GPIO_PORT_P3
    #define uC_PINSEL_SPI1_SCLK     GPIO_PIN2
    /**@}*/ 
    
    /**
    * @name SPI 2 Configuration (UCA1)
    */
    /**@{*/ 
    #define uC_HAS_SPI2             1
    #ifndef uC_SPI2_TXBUF_LEN
        #define uC_SPI2_TXBUF_LEN     10
    #endif
    #ifndef uC_SPI2_RXBUF_LEN
        #define uC_SPI2_RXBUF_LEN     10
    #endif
    
    #ifndef uC_SPI2_CLKSOURCE
        #define uC_SPI2_CLKSOURCE       CLKSOURCE_SMCLK
    #endif
    
    #if (uC_SPI2_CLKSOURCE == CLKSOURCE_SMCLK)
        #define uC_SPI2_SCLK_BASE_FREQ  uC_SMCLK_FRQ_HZ
    #elif (uC_SPI2_CLKSOURCE == CLKSOURCE_ACLK)
        #define uC_SPI2_SCLK_BASE_FREQ  uC_ACLK_FRQ_HZ
    #endif
    
    #ifndef APP_SPI2_SCLK_FREQ_DEFAULT
        #define APP_SPI2_SCLK_FREQ_DEFAULT  4000000UL
    #endif
    
    #define uC_SPI2_TYPE            SPI_HWIF_USCI_A
    #define uC_SPI2_BASE            USCI_A1_BASE
    #define uC_SPI2_VECTOR          USCI_A1_VECTOR

    #define uC_PORTSEL_SPI2_MISO    GPIO_PORT_P4
    #define uC_PINSEL_SPI2_MISO     GPIO_PIN5
    
    #define uC_PORTSEL_SPI2_MOSI    GPIO_PORT_P4
    #define uC_PINSEL_SPI2_MOSI     GPIO_PIN4
    
    #define uC_PORTSEL_SPI2_SCLK    GPIO_PORT_P4
    #define uC_PINSEL_SPI2_SCLK     GPIO_PIN0
    /**@}*/ 
    
    /**
    * @name SPI 3 Configuration (UCB1)
    */
    /**@{*/ 
    #define uC_HAS_SPI3             1
    #ifndef uC_SPI3_TXBUF_LEN
        #define uC_SPI3_TXBUF_LEN     10
    #endif
    #ifndef uC_SPI3_RXBUF_LEN
        #define uC_SPI3_RXBUF_LEN     10
    #endif
    
    #ifndef uC_SPI3_CLKSOURCE
        #define uC_SPI3_CLKSOURCE       CLKSOURCE_SMCLK
    #endif
    
    #if (uC_SPI3_CLKSOURCE == CLKSOURCE_SMCLK)
        #define uC_SPI3_SCLK_BASE_FREQ  uC_SMCLK_FRQ_HZ
    #elif (uC_SPI3_CLKSOURCE == CLKSOURCE_ACLK)
        #define uC_SPI3_SCLK_BASE_FREQ  uC_ACLK_FRQ_HZ
    #endif
    
    #ifndef APP_SPI3_SCLK_FREQ_DEFAULT
        #define APP_SPI3_SCLK_FREQ_DEFAULT  4000000UL
    #endif
    
    #define uC_SPI3_TYPE            SPI_HWIF_USCI_B
    #define uC_SPI3_BASE            USCI_B1_BASE
    #define uC_SPI3_VECTOR          USCI_B1_VECTOR

    #define uC_PORTSEL_SPI3_MISO    GPIO_PORT_P4
    #define uC_PINSEL_SPI3_MISO     GPIO_PIN2
    
    #define uC_PORTSEL_SPI3_MOSI    GPIO_PORT_P4
    #define uC_PINSEL_SPI3_MOSI     GPIO_PIN1
    
    #define uC_PORTSEL_SPI3_SCLK    GPIO_PORT_P4
    #define uC_PINSEL_SPI3_SCLK     GPIO_PIN3
    /**@}*/ 
    
/**@}*/ 


/**
 * @name Timer Configuration
 */
/**@{*/ 

    #define uC_AVAILABLE_TIMERS               4

    #ifndef uC_TIMER_DEFAULT_CLKSOURCE
        #define uC_TIMER_DEFAULT_CLKSOURCE    CLKSOURCE_SMCLK
    #endif
    
    #if (uC_TIMER_DEFAULT_CLKSOURCE == CLKSOURCE_SMCLK)
        #define uC_TIMER_DEFAULT_CLKSOURCE_FREQ  uC_SMCLK_FRQ_HZ
    #elif (uC_TIMER_DEFAULT_CLKSOURCE == CLKSOURCE_ACLK)
        #define uC_TIMER_DEFAULT_CLKSOURCE_FREQ  uC_ACLK_FRQ_HZ
    #endif
    
    /**
    * @name TIMER 0 Configuration
    */
    /**@{*/ 
    #define uC_HAS_TIMER0              1
    
    #define uC_TIMER0_TYPE             TIMER_HWIF_TIMER_A
    #define uC_TIMER0_BASE             TIMER_A0_BASE
    #define uC_TIMER0_PRIMARY_VECTOR   TIMER0_A0_VECTOR
    #define uC_TIMER0_SECONDARY_VECTOR TIMER0_A1_VECTOR
    #define uC_TIMER0_CHANNELS         5
    
    #ifndef uC_TIMER0_CLKSOURCE
        #define uC_TIMER0_CLKSOURCE         uC_TIMER_DEFAULT_CLKSOURCE
    #endif
    #if (uC_TIMER0_CLKSOURCE == CLKSOURCE_SMCLK)
        #define uC_TIMER0_CLKSOURCE_FREQ  uC_SMCLK_FRQ_HZ
    #elif (uC_TIMER0_CLKSOURCE == CLKSOURCE_ACLK)
        #define uC_TIMER0_CLKSOURCE_FREQ  uC_ACLK_FRQ_HZ
    #endif
    /**@}*/
    
    /**
    * @name TIMER 1 Configuration
    */
    /**@{*/ 
    #define uC_HAS_TIMER1              1
    
    #define uC_TIMER1_TYPE             TIMER_HWIF_TIMER_A
    #define uC_TIMER1_BASE             TIMER_A1_BASE
    #define uC_TIMER1_PRIMARY_VECTOR   TIMER1_A0_VECTOR
    #define uC_TIMER1_SECONDARY_VECTOR TIMER1_A1_VECTOR
    #define uC_TIMER1_CHANNELS         3
    
    #ifndef uC_TIMER1_CLKSOURCE
        #define uC_TIMER1_CLKSOURCE         uC_TIMER_DEFAULT_CLKSOURCE
    #endif
    #if (uC_TIMER1_CLKSOURCE == CLKSOURCE_SMCLK)
        #define uC_TIMER1_CLKSOURCE_FREQ  uC_SMCLK_FRQ_HZ
    #elif (uC_TIMER1_CLKSOURCE == CLKSOURCE_ACLK)
        #define uC_TIMER1_CLKSOURCE_FREQ  uC_ACLK_FRQ_HZ
    #endif
    /**@}*/ 
    
    /**
    * @name TIMER 2 Configuration
    */
    /**@{*/ 
    #define uC_HAS_TIMER2              1
    
    #define uC_TIMER2_TYPE             TIMER_HWIF_TIMER_A
    #define uC_TIMER2_BASE             TIMER_A2_BASE
    #define uC_TIMER2_PRIMARY_VECTOR   TIMER2_A0_VECTOR
    #define uC_TIMER2_SECONDARY_VECTOR TIMER2_A1_VECTOR
    #define uC_TIMER2_CHANNELS         3
    
    #ifndef uC_TIMER2_CLKSOURCE
        #define uC_TIMER2_CLKSOURCE         uC_TIMER_DEFAULT_CLKSOURCE
    #endif
    #if (uC_TIMER2_CLKSOURCE == CLKSOURCE_SMCLK)
        #define uC_TIMER2_CLKSOURCE_FREQ  uC_SMCLK_FRQ_HZ
    #elif (uC_TIMER2_CLKSOURCE == CLKSOURCE_ACLK)
        #define uC_TIMER2_CLKSOURCE_FREQ  uC_ACLK_FRQ_HZ
    #endif
    /**@}*/ 
    
    /**
    * @name TIMER 3 Configuration
    */
    /**@{*/ 
    #define uC_HAS_TIMER3              1
    
    #define uC_TIMER3_TYPE             TIMER_HWIF_TIMER_B
    #define uC_TIMER3_BASE             TIMER_B0_BASE
    #define uC_TIMER3_PRIMARY_VECTOR   TIMER0_B0_VECTOR
    #define uC_TIMER3_SECONDARY_VECTOR TIMER0_B1_VECTOR
    #define uC_TIMER3_CHANNELS         7
    
    #ifndef uC_TIMER3_CLKSOURCE
        #define uC_TIMER3_CLKSOURCE    CLKSOURCE_SMCLK
    #endif
    #if (uC_TIMER3_CLKSOURCE == CLKSOURCE_SMCLK)
        #define uC_TIMER3_CLKSOURCE_FREQ  uC_SMCLK_FRQ_HZ
    #elif (uC_TIMER3_CLKSOURCE == CLKSOURCE_ACLK)
        #define uC_TIMER3_CLKSOURCE_FREQ  uC_ACLK_FRQ_HZ
    #endif
    /**@}*/ 
        
/**@}*/ 

#endif
