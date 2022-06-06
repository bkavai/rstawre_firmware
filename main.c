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

/*
 *  ======== empty.c ========
 */
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/BIOS.h>
/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
// #include <ti/drivers/EMAC.h>
#include <ti/drivers/GPIO.h>
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SDSPI.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/USBMSCHFatFs.h>
// #include <ti/drivers/Watchdog.h>
// #include <ti/drivers/WiFi.h>

/* Board Header file */
#include "Board.h"
#include "uart_tasks.h"
#include "RST_I2C.h"
#include "Measurement.h"
#include "BLE.h"

#define TASKSTACKSIZE   512

Task_Struct task0Struct;
Char task0Stack[TASKSTACKSIZE];

extern void Uart_Test(void);
static char led_index = 0;

/*
 *  ======== heartBeatFxn ========
 *  Toggle the Board_LED0. The Task_sleep is determined by arg0 which
 *  is configured for the heartBeat Task instance.
 */
Void heartBeatFxn(UArg arg0, UArg arg1)
{
    while (1) {
        Task_sleep((unsigned int)arg0);
        switch(led_index){
            case 0:
                GPIO_write(Board_LED_R, Board_LED_ON);
                GPIO_write(Board_LED_B, Board_LED_OFF);
                GPIO_write(Board_LED_G, Board_LED_OFF);
                break;
            case 1:
                GPIO_write(Board_LED_R, Board_LED_OFF);
                GPIO_write(Board_LED_B, Board_LED_ON);
                GPIO_write(Board_LED_G, Board_LED_OFF);
                break;
            case 2:
                GPIO_write(Board_LED_R, Board_LED_OFF);
                GPIO_write(Board_LED_B, Board_LED_OFF);
                GPIO_write(Board_LED_G, Board_LED_ON);
                break;
        }
        if(led_index++ > 2)
            led_index = 0;
    }
}

/*
 *  ======== main ========
 */
int main(void)
{
    //UART_Handle

    Task_Params taskParams;
    Task_Handle UartInTask;        // Task 1
    Task_Handle UartOutTask;       // Task 2
    Task_Params UartInParams;
    Task_Params UartOutParams;
    Error_Block eb;

    /* Call board init functions */
        Board_initGeneral();            // Running at 80Mhz
        // Board_initEMAC();
        Board_initGPIO();
        RST_initI2C();
        RST_TM4C1230_initUART(0);       // UART TEST
        BLE_init();

        // Board_initI2C();
        // Board_initSDSPI();
        // Board_initSPI();
        // Board_initUART();
        // Board_initUSB(Board_USBDEVICE);
        // Board_initUSBMSCHFatFs();
        // Board_initWatchdog();
        // Board_initWiFi();
       // UARTTiva_init()
        // Set up tasks

        Error_init(&eb);
             // Task: UART IN
        Task_Params_init(&UartInParams); // Task: rs485In
        UartInParams.priority = 2;
        UartInParams.stackSize = 512;
        UartInParams.instance->name = "UARTIn";
        UartInTask = Task_create(Uart_in_task, &UartInParams, &eb);
        if (UartInTask == NULL){
            System_printf("Task UART In failed!\n");
            BIOS_exit(0);
         }
        Uart_in_task_init();

        // Task: UART OUT
        Task_Params_init(&UartOutParams); // Task: rs485In
        UartOutParams.priority = 2;
        UartOutParams.stackSize = 512;
        UartOutParams.instance->name = "UARTOut";
        UartOutTask = Task_create(Uart_out_task, &UartOutParams, &eb);
        if (UartOutTask == NULL){
            System_printf("Task UART Out failed!\n");
            BIOS_exit(0);
        }

    /* Construct heartBeat Task  thread */
        Task_Params_init(&taskParams);
        taskParams.arg0 = 100;
        taskParams.stackSize = TASKSTACKSIZE;
        taskParams.stack = &task0Stack;
        Task_construct(&task0Struct, (Task_FuncPtr)heartBeatFxn, &taskParams, NULL);
        led_index = 0;
         /* Turn on user LED */
        GPIO_write(Board_LED_R, Board_LED_ON);

        Measurement_init();

        System_printf("Starting the example\nSystem provider is set to SysMin. "
                      "Halt the target to view any SysMin contents in ROV.\n");
        /* SysMin will only print to the console when you call flush or exit */
        System_flush();

        /* Start BIOS */
        BIOS_start();

        return (0);
}
