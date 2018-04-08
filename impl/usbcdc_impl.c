/* 
 * Copyright (c)
 *   (c) 2015-2016 Chintalagiri Shashank, Quazar Technologies Pvt. Ltd.
 *  
 * This file is part of
 * Embedded bootstraps : Peripheral driver implementations : MSP430
 * 
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 */


#include "../usbcdc.h"

#ifdef uC_INCLUDE_USB_IFACE
#if uC_USBCDC_ENABLED


static void _usbcdc_init(uint8_t intfnum){
    ;
}


static uint8_t _usbcdc_reqlock(uint8_t intfnum, uint8_t len, uint8_t token){
    // TODO Implement locking mechanism
    uint8_t avail = USBCDC_getInterfaceStatus_SendAvailable(intfnum);
    if (len){
        if (avail >= len){
            return 0x01;
        }
        else{
            return 0x00;
        }
    }
    else {
        return avail;
    }
}

static uint8_t _usbcdc_rellock(uint8_t intfnum, uint8_t token){
    return 1;
}

static uint8_t _usbcdc_write(uint8_t intfnum, uint8_t *buffer, uint8_t len, uint8_t token){
    uint8_t rval;
    rval = USBCDC_sendBuffer(intfnum, buffer, len);
    usbcdc_send_trigger(intfnum);
    return rval;
}


const pluggable_transport_t ptransport_usbcdc = {
    &_usbcdc_init,
    &USBCDC_getInterfaceStatus_RecieveWaiting,
    &USBCDC_recieveBuffer,
    &_usbcdc_reqlock,
    &_usbcdc_rellock,
    &_usbcdc_write,
    &USBCDC_sendFlush
};

#endif

#endif
