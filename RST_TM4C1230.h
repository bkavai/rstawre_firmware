/*
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/** ============================================================================
 *  @file       DK_TM4C129X.h
 *
 *  @brief      DK_TM4C129X Board Specific APIs
 *
 *  The DK_TM4C129X header file should be included in an application as follows:
 *  @code
 *  #include <DK_TM4C129X.h>
 *  @endcode
 *
 *  ============================================================================
 */

#ifndef __RST_TM4C1230_H
#define __RST_TM4C1230_H

#ifdef __cplusplus
extern "C" {
#endif

/* LEDs on DK_TM4C129X are active high. */
#define RST_TM4C1230_LED_OFF (0)
#define RST_TM4C1230_LED_ON  (1)

/*!
 *  @def    RST_TM4C1230_EMACName
 *  @brief  Enum of EMAC names on the DK_TM4C129X dev board
 */
typedef enum RST_TM4C1230_EMACName {
    RST_TM4C1230_EMAC0 = 0,

    RST_TM4C1230_EMACCOUNT
} RST_TM4C1230_EMACName;

/*!
 *  @def    RST_TM4C1230_GPIOName
 *  @brief  Enum of LED names on the DK_TM4C129X dev board
 */
typedef enum RST_TM4C1230_GPIOName {
    RST_TM4C1230_PF1 = 0,
    RST_TM4C1230_PF2 = 1,
    RST_TM4C1230_PF3 = 2,
    RST_TM4C1230_PB2 = 3,
    RST_TM4C1230_PB6 = 4,
    RST_TM4C1230_PB7 = 5,
    RST_TM4C1230_PC6 = 6,
    RST_TM4C1230_PD0 = 7,
    RST_TM4C1230_PD1 = 8,
    RST_TM4C1230_PD3 = 9,
    RST_TM4C1230_PD6 = 10,
    RST_TM4C1230_PD7 = 11,
    RST_TM4C1230_PE0 = 12,
    RST_TM4C1230_PG5 = 13,
    RST_TM4C1230_GPIOCOUNT
} RST_TM4C1230_GPIOName;

/*!
 *  @def    RST_TM4C1230_I2CName
 *  @brief  Enum of I2C names on the DK_TM4C129X dev board
 */
typedef enum RST_TM4C1230_I2CName {
    RST_TM4C1230_I2C3 = 0,
    RST_TM4C1230_I2C6,
    RST_TM4C1230_I2C7,

    RST_TM4C1230_I2CCOUNT
} RST_TM4C1230_I2CName;

/*!
 *  @def    RST_TM4C1230_PWMName
 *  @brief  Enum of PWM names on the DK_TM4C129X dev board
 */
typedef enum RST_TM4C1230_PWMName {
    RST_TM4C1230_PWM1 = 0,
    RST_TM4C1230_PWM6,

    RST_TM4C1230_PWMCOUNT
} RST_TM4C1230_PWMName;

/*!
 *  @def    RST_TM4C1230_SDSPIName
 *  @brief  Enum of SDSPI names on the DK_TM4C129X dev board
 */
typedef enum RST_TM4C1230_SDSPIName {
    RST_TM4C1230_SDSPI0 = 0,

    RST_TM4C1230_SDSPICOUNT
} RST_TM4C1230_SDSPIName;

/*!
 *  @def    RST_TM4C1230_SPIName
 *  @brief  Enum of SPI names on the DK_TM4C129X dev board
 */
typedef enum RST_TM4C1230_SPIName {
    RST_TM4C1230_SPI0 = 0,
    RST_TM4C1230_SPI2,
    RST_TM4C1230_SPI3,

    RST_TM4C1230_SPICOUNT
} RST_TM4C1230_SPIName;

/*!
 *  @def    RST_TM4C1230_UARTName
 *  @brief  Enum of UARTs on the DK_TM4C129X dev board
 */
typedef enum RST_TM4C1230_UARTName {
    RST_TM4C1230_UART0 = 0,
    RST_TM4C1230_UART1 = 1,
    RST_TM4C1230_UARTCOUNT
} RST_TM4C1230_UARTName;

/*!
 *  @def    RST_TM4C1230_USBMode
 *  @brief  Enum of USB setup function on the DK_TM4C129X dev board
 */
typedef enum RST_TM4C1230_USBMode {
    RST_TM4C1230_USBDEVICE,
    RST_TM4C1230_USBHOST
} RST_TM4C1230_USBMode;

/*!
 *  @def    RST_TM4C1230_USBMSCHFatFsName
 *  @brief  Enum of USBMSCHFatFs names on the DK_TM4C129X dev board
 */
typedef enum RST_TM4C1230_USBMSCHFatFsName {
    RST_TM4C1230_USBMSCHFatFs0 = 0,

    RST_TM4C1230_USBMSCHFatFsCOUNT
} RST_TM4C1230_USBMSCHFatFsName;

/*
 *  @def    RST_TM4C1230_WatchdogName
 *  @brief  Enum of Watchdogs on the DK_TM4C129X dev board
 */
typedef enum RST_TM4C1230_WatchdogName {
    RST_TM4C1230_WATCHDOG0 = 0,

    RST_TM4C1230_WATCHDOGCOUNT
} RST_TM4C1230_WatchdogName;

/*!
 *  @def    RST_TM4C1230_WiFiName
 *  @brief  Enum of WiFi names on the DK_TM4C129X dev board
 */
typedef enum RST_TM4C1230_WiFiName {
    RST_TM4C1230_WIFI = 0,

    RST_TM4C1230_WIFICOUNT
} RST_TM4C1230_WiFiName;

/*!
 *  @brief  Initialize the general board specific settings
 *
 *  This function initializes the general board specific settings.
 *  This includes:
 *     - Enable clock sources for peripherals
 */
extern void RST_TM4C1230_initGeneral(void);

/*!
 *  @brief Initialize board specific EMAC settings
 *
 *  This function initializes the board specific EMAC settings and
 *  then calls the EMAC_init API to initialize the EMAC module.
 *
 *  The EMAC address is programmed as part of this call.
 *
 */
extern void RST_TM4C1230_initEMAC(void);

/*!
 *  @brief  Initialize board specific GPIO settings
 *
 *  This function initializes the board specific GPIO settings and
 *  then calls the GPIO_init API to initialize the GPIO module.
 *
 *  The GPIOs controlled by the GPIO module are determined by the GPIO_PinConfig
 *  variable.
 */
extern void RST_TM4C1230_initGPIO(void);

/*!
 *  @brief  Initialize board specific I2C settings
 *
 *  This function initializes the board specific I2C settings and then calls
 *  the I2C_init API to initialize the I2C module.
 *
 *  The I2C peripherals controlled by the I2C module are determined by the
 *  I2C_config variable.
 */
extern void RST_TM4C1230_initI2C(void);

/*!
 *  @brief  Initialize board specific PWM settings
 *
 *  This function initializes the board specific PWM settings and then calls
 *  the PWM_init API to initialize the PWM module.
 *
 *  The PWM peripherals controlled by the PWM module are determined by the
 *  PWM_config variable.
 */
extern void RST_TM4C1230_initPWM(void);

/*!
 *  @brief  Initialize board specific SDSPI settings
 *
 *  This function initializes the board specific SDSPI settings and then calls
 *  the SDSPI_init API to initialize the SDSPI module.
 *
 *  The SDSPI peripherals controlled by the SDSPI module are determined by the
 *  SDSPI_config variable.
 */
extern void RST_TM4C1230_initSDSPI(void);

/*!
 *  @brief  Initialize board specific SPI settings
 *
 *  This function initializes the board specific SPI settings and then calls
 *  the SPI_init API to initialize the SPI module.
 *
 *  The SPI peripherals controlled by the SPI module are determined by the
 *  SPI_config variable.
 */
extern void RST_TM4C1230_initSPI(void);

/*!
 *  @brief  Initialize board specific UART settings
 *
 *  This function initializes the board specific UART settings and then calls
 *  the UART_init API to initialize the UART module.
 *
 *  The UART peripherals controlled by the UART module are determined by the
 *  UART_config variable.
 */
extern void RST_TM4C1230_initUART(char);

/*!
 *  @brief  Initialize board specific USB settings
 *
 *  This function initializes the board specific USB settings and pins based on
 *  the USB mode of operation.
 *
 *  @param      usbMode    USB mode of operation
 */
extern void RST_TM4C1230_initUSB(RST_TM4C1230_USBMode usbMode);

/*!
 *  @brief  Initialize board specific USBMSCHFatFs settings
 *
 *  This function initializes the board specific USBMSCHFatFs settings and then
 *  calls the USBMSCHFatFs_init API to initialize the USBMSCHFatFs module.
 *
 *  The USBMSCHFatFs peripherals controlled by the USBMSCHFatFs module are
 *  determined by the USBMSCHFatFs_config variable.
 */
extern void RST_TM4C1230_initUSBMSCHFatFs(void);

/*!
 *  @brief  Initialize board specific Watchdog settings
 *
 *  This function initializes the board specific Watchdog settings and then
 *  calls the Watchdog_init API to initialize the Watchdog module.
 *
 *  The Watchdog peripherals controlled by the Watchdog module are determined
 *  by the Watchdog_config variable.
 */
extern void RST_TM4C1230_initWatchdog(void);

/*!
 *  @brief  Initialize board specific WiFi settings
 *
 *  This function initializes the board specific WiFi settings and then calls
 *  the WiFi_init API to initialize the WiFi module.
 *
 *  The hardware resources controlled by the WiFi module are determined by the
 *  WiFi_config variable.
 *
 *  A SimpleLink CC3100 device or module is required and must be connected to
 *  use the WiFi driver.
 */
extern void RST_TM4C1230_initWiFi(void);

#ifdef __cplusplus
}
#endif

#endif /* __RST_TM4C1230_H */
