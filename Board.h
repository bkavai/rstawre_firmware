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

#ifndef __BOARD_H
#define __BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <RST_TM4C1230.h>



#define Board_initGeneral           RST_TM4C1230_initGeneral
#define Board_initGPIO              RST_TM4C1230_initGPIO
#if 0
#define Board_initEMAC              RST_TM4C1230_initEMAC
#define Board_initI2C               RST_TM4C1230_initI2C
#define Board_initPWM               RST_TM4C1230_initPWM
#define Board_initSDSPI             RST_TM4C1230_initSDSPI
#define Board_initSPI               RST_TM4C1230_initSPI
#define Board_initUART              RST_TM4C1230_initUART
#define Board_initUSB               RST_TM4C1230_initUSB
#define Board_initUSBMSCHFatFs      RST_TM4C1230_initUSBMSCHFatFs
#define Board_initWatchdog          RST_TM4C1230_initWatchdog
#define Board_initWiFi              RST_TM4C1230_initWiFi
#endif

#define Board_LED_ON                RST_TM4C1230_LED_ON
#define Board_LED_OFF               RST_TM4C1230_LED_OFF
#define Board_LED_R                 RST_TM4C1230_PF1
#define Board_LED_B                 RST_TM4C1230_PF2
#define Board_LED_G                 RST_TM4C1230_PF3

#define RTN_ENA                     RST_TM4C1230_PB7
#define DISCHARGE_ENA               RST_TM4C1230_PG5
#define GAIN_ENA                    RST_TM4C1230_PD0

#define BLE_MODE                    RST_TM4C1230_PF2

#if 0
#define Board_LED1                  RST_TM4C1230_LED_B
#define Board_LED2                  RST_TM4C1230_LED_R
#define Board_BUTTON0               RST_TM4C1230_BUTTON_SELECT
#define Board_BUTTON1               RST_TM4C1230_BUTTON_UP
#define Board_BUTTON2               RST_TM4C1230_BUTTON_DOWN

#define Board_I2C0                  RST_TM4C1230_I2C3
#define Board_I2C_TMP               RST_TM4C1230_I2C3
#define Board_I2C_NFC               RST_TM4C1230_I2C3
#define Board_I2C_TPL0401           RST_TM4C1230_I2C3

#define Board_PWM0                  RST_TM4C1230_PWM1
#define Board_PWM1                  RST_TM4C1230_PWM6

#define Board_SDSPI0                RST_TM4C1230_SDSPI0

#define Board_SPI0                  RST_TM4C1230_SPI3
#define Board_SPI1                  RST_TM4C1230_SPI2

#define Board_USBMSCHFatFs0         RST_TM4C1230_USBMSCHFatFs0

#define Board_USBHOST               RST_TM4C1230_USBHOST
#define Board_USBDEVICE             RST_TM4C1230_USBDEVICE

#define Board_UART0                 RST_TM4C1230_UART0

#define Board_WATCHDOG0             RST_TM4C1230_WATCHDOG0

#define Board_WIFI                  RST_TM4C1230_WIFI
#define Board_WIFI_SPI              RST_TM4C1230_SPI2

/* Board specific I2C addresses */
#define Board_TMP006_ADDR           (0x40)
#define Board_RF430CL330_ADDR       (0x28)
#define Board_TPL0401_ADDR          (0x40)
#endif

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H */
