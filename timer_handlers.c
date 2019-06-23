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

#include "app/application.h"
#include "app/application_handlers.h"
#include "hal/uc/timer.h"


volatile uint8_t __timer_handler_inclusion;

#if uC_TIMER0_ENABLED
#ifdef uC_TIMER0_TOP_IRQ_HANDLER
__attribute__((interrupt(uC_TIMER0_PRIMARY_VECTOR)))
void _timer0_primary_irqhandler(void){
    uC_TIMER0_TOP_IRQ_HANDLER();
}
#endif
#endif

#if uC_TIMER1_ENABLED
#ifdef uC_TIMER1_TOP_IRQ_HANDLER
__attribute__((interrupt(uC_TIMER1_PRIMARY_VECTOR)))
void _timer1_primary_irqhandler(void){
    uC_TIMER1_TOP_IRQ_HANDLER();
}
#endif
#endif

#if uC_TIMER2_ENABLED
#ifdef uC_TIMER2_TOP_IRQ_HANDLER
__attribute__((interrupt(uC_TIMER2_PRIMARY_VECTOR)))
void _timer2_primary_irqhandler(void){
    uC_TIMER2_TOP_IRQ_HANDLER();
}
#endif
#endif

#if uC_TIMER3_ENABLED
#ifdef uC_TIMER3_TOP_IRQ_HANDLER
__attribute__((interrupt(uC_TIMER3_PRIMARY_VECTOR)))
void _timer3_primary_irqhandler(void){
    uC_TIMER3_TOP_IRQ_HANDLER();
}
#endif
#endif


