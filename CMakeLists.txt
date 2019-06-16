
FIND_PACKAGE("msp430-driverlib" REQUIRED)
FIND_PACKAGE("ds" REQUIRED)
FIND_PACKAGE("printf" REQUIRED)

ADD_PLATFORM_LIBRARY(hal-uc-core STATIC "msp430-driverlib" core_impl.c)
ADD_PLATFORM_LIBRARY(hal-uc-gpio STATIC "msp430-driverlib" gpio_impl.c)
ADD_PLATFORM_LIBRARY(hal-uc-timer STATIC "msp430-driverlib" timer_impl.c timer_handlers.c)
ADD_PLATFORM_LIBRARY(hal-uc-uart STATIC "msp430-driverlib ds printf" uart_impl.c uart_handlers.c)
ADD_PLATFORM_LIBRARY(hal-uc-spi STATIC "msp430-driverlib ds" spi_impl.c spi_handlers.c)
ADD_PLATFORM_LIBRARY(hal-uc-id STATIC "msp430-driverlib" id_impl.c)
ADD_PLATFORM_LIBRARY(hal-uc-entropy STATIC "msp430-driverlib hal-uc-timer" entropy_impl.c)
ADD_PLATFORM_LIBRARY(hal-uc-usb STATIC "msp430-usbapi" usbcdc_impl.c)

ADD_SUBDIRECTORY(usb-impl)
