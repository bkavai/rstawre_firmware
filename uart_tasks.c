/*
 * tasks.c
 *
 *  Created on: Aug 29, 2021
 *      Author: kavaipatti
 */

#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Mailbox.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>

#include <inc/hw_ints.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <inc/hw_gpio.h>
#include <stdbool.h>
#include <driverlib/uart.h>
#include <driverlib/gpio.h>
#include <ti/drivers/uart/UARTTiva.h>
#include <driverlib/sysctl.h>
#include <driverlib/pin_map.h>
#include <RST_TM4C1230.h>

#include "Utility.h"
#include "RSTaWRE_Semaphores.h"
#include "RSTaWRE_Mailbox.h"
#include "command_proc.h"

extern char uarta_load_tx_buffer(char *ptxData, uint16_t tx_count, char index);
extern char Uart_get_char(char *pDataptr, char size, char index);

Mailbox_Handle uartInMbx;
Mailbox_Handle uartOutMbx;
Mailbox_Params uartInMbxParams;
Mailbox_Params uartOutMbxParams;



static uint16_t uartInTimeout = 0;
static uartin_t UartInTaskIndex = WAIT_FOR_UART_IN_SOM_MSG;
//static uartin_t uartSPreviousState;


void Uart_in_task_init(void){
    Error_Block eb;

        UartInTaskIndex = WAIT_FOR_UART_IN_SOM_MSG;
#if 0
        Mailbox_Params_init(&uartInMbxParams);
         //Mailbox_Instance_init(&uartInMbx, sizeof(uartInMsgObj), MAX_IN_MAIL_COUNT, &uartInMbxParams, &eb);
        uartInMbx = Mailbox_create(sizeof(uartInMsgObj), MAX_IN_MAIL_COUNT, &uartInMbxParams, &eb);

        if(uartInMbx == NULL){
            System_printf("Cannot Create uart IN Mbox\n");
        }else{
            uartInTimeout = BIOS_WAIT_FOREVER;
        }
#endif
        Mailbox_Params_init(&uartOutMbxParams);
        uartOutMbx = Mailbox_create(sizeof(uartOutMsgObj), MAX_OUT_MAIL_COUNT, &uartOutMbxParams, &eb);

        if(uartOutMbx == NULL){
            System_printf("Cannot Create uart IN Mbox\n");
        }else{
            uartInTimeout = BIOS_WAIT_FOREVER;
        }
}
/* RS 485In Task */

void Uart_in_task(UArg a0, UArg a1)
{
    static UARTDATA  uartInData;
    static uint16_t expectedByteCount = 0;
    static uint16_t dataInCounter = 0;
    uartInMsgObj uartInMsg;
    uint16_t total_size = 0;

        while(1){
            switch(UartInTaskIndex){
                case WAIT_FOR_UART_IN_SOM_MSG:
                    //Mailbox_pend(uartInMbx,&uartInMsg,uartInTimeout);
                    Uart_get_char(&uartInMsg.rxChar, 1, 0);
                    // Check if it is SOM?
                    if(uartInMsg.rxChar==SOM){
                        //GpioDataRegs.GPBTOGGLE.bit.GPIO57 = 1;
                        uartInData.som =uartInMsg.rxChar;
                        UartInTaskIndex = WAIT_FOR_UART_BYTE_COUNT;
                        uartInTimeout = UART_IN_TIMEOUT;        // change timeout to 10ms?
                    }
                    break;

                case WAIT_FOR_UART_BYTE_COUNT:
                    Uart_get_char(&uartInData.size, 1, 0);
                    UartInTaskIndex = WAIT_REST_DATA_IN;
                    expectedByteCount = uartInData.size-2;
#if 0
                     if(Mailbox_pend(uartInMbx,&uartInMsg,uartInTimeout)){
                         uartInData.size_msb = uartInMsg.rxChar;
                         UartInTaskIndex = WAIT_FOR_UART_BYTE_LSB;
                     }
                     else{
                         uartInTimeout = BIOS_WAIT_FOREVER;
                         //uartSPreviousState = WAIT_FOR_UART_BYTE_MSB;
                         UartInTaskIndex = ERROR_UART_IN;
                     }
#endif
                     break;

                 case WAIT_REST_DATA_IN:
                     Uart_get_char(&uartInMsg.rxChar, 1, 0);
                     if(dataInCounter == 0){ // First entry is command
                         uartInData.command = uartInMsg.rxChar;

                     }
                     else{
                         uartInData.payload[dataInCounter-1] = uartInMsg.rxChar;
                     }
                     dataInCounter++;
                     if(dataInCounter > expectedByteCount){
                         UartInTaskIndex = WAIT_FOR_CHKSUM_IN;
                     }
                    break;

                 case WAIT_FOR_CHKSUM_IN:

                     Uart_get_char(&uartInData.chksum, 1, 0);

                        // Verify CRC
                     if(calculateCheckSum((char*)&uartInData,expectedByteCount) == uartInData.chksum){
                            // Process command
                         Process_command(uartInData.command, &uartInData.payload[0], expectedByteCount);
                     }
                        // Restart

                     UartInTaskIndex = WAIT_FOR_UART_IN_SOM_MSG;

                    break;

                 case ERROR_UART_IN:
                     UartInTaskIndex = WAIT_FOR_UART_IN_SOM_MSG;
                     break;

                 default:
                    UartInTaskIndex = WAIT_FOR_UART_IN_SOM_MSG;
            }

        }
}

void Uart_out_task(UArg a0, UArg a1)
{
    uartOutMsgObj uartOutMsg;
    UARTDATA uartOutData;
    uint16_t i, pay_load_size;


        while(1){
             Mailbox_pend(uartOutMbx,&uartOutMsg,BIOS_WAIT_FOREVER);
#if 1
             // Prepare data to be shipped out
             pay_load_size = uartOutMsg.uartOutCount;
             if(pay_load_size < MAX_UARTOUT_PAYLOAD_SIZE){
                uartOutData.som = SOM;
                uartOutData.size = ((pay_load_size + 3) >> 8)&0xFF;      // +4 for SIZE, CRC
                uartOutData.command = *(uartOutMsg.puartOutPtr);
                for(i=0;i<pay_load_size-1;++i){       // command already loaded, hence -1
                    uartOutData.payload[i] = *(uartOutMsg.puartOutPtr + i + 3);
                 }
                 //uartOutData.crc = calculateCheckSum((char*)&uartOutData, pay_load_size + 3); // 3 for Not including CRC
                 uartOutData.chksum = calculateCheckSum((char*)&uartOutData, pay_load_size + 3); // 3 for Not including CRC
                 // Append it to the last entry of the payload
                 //uartOutData.crc = 0xBC;
                 uartOutData.payload[i] = uartOutData.chksum;
            }

            uarta_load_tx_buffer((char*)&uartOutData, pay_load_size + 4, 0);
            //Semaphore_pend(uart_tx_done, UART_TX_TIMEOUT);
              // DISABLE TX DRIVER
#endif
        }
}
