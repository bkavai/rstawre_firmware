/*
 * BLE.c
 *
 *  Created on: Jun 6, 2022
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
#include <ti/drivers/GPIO.h>
#include <RST_TM4C1230.h>
#include "Board.h"

extern char uarta_load_tx_buffer(char *ptxData, uint16_t tx_count, char index);
extern char Uart_get_char(char *pDataptr, char size, char index);

#define BLE_COMMAND_MODE        1
#define BLE_DATA_MODE           0

#define FACTORY_RESET
void BLE_mode(char mode){

    GPIO_write(BLE_MODE, mode);
}

bool BLE_send_command(char *pDataptr, char len){
    char resp[2];

        uarta_load_tx_buffer(pDataptr, len, 1);
        Uart_get_char(&resp[0], 2, 1);

        if (resp == "OK"){
            return(1);
        }
        else{
            return(0);
        }
}

void BLE_init(void){

        RST_TM4C1230_initUART(1);       // BLE

        // Set Mode to command
        BLE_mode(BLE_COMMAND_MODE);

        // Check AT
        BLE_send_command("AT", 2);

}
