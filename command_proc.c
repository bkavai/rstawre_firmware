/*
 * Command_Proc.c
 *
 *  Created on: Jun 3, 2022
 *      Author: kavaipatti
 */


#include <stdint.h>
#include <stdbool.h>
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/knl/Mailbox.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/family/arm/m3/Hwi.h>
#include <inc/hw_ints.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <inc/hw_gpio.h>
#include <driverlib/uart.h>
#include <driverlib/gpio.h>
#include <ti/drivers/uart/UARTTiva.h>
#include <driverlib/sysctl.h>
#include <driverlib/pin_map.h>

#include <RST_TM4C1230.h>
#include "RST_Commands.h"
#include "RSTaWRE_Mailbox.h"
#include "Version.h"
#include "Measurement.h"
#include "Utility.h"

#define MAX_COMMS_BUFFER_SIZE   256

static char comms_buffer[MAX_COMMS_BUFFER_SIZE];
static uartOutMsgObj commsOutMsg;

uint16_t Build_id_string(char *pDataPtr){

    uint16_t id_size = 0;
        id_size = System_sprintf(pDataPtr,"%s;%s;%s", MODULE_TYPE, HW_SERIAL_NUMBER, FIRMWARE_VERSION );
        return(id_size);
}

void Process_command(char command, char *pPayload, uint16_t byte_count){

    uint16_t size;
    char error;
    float tmp_float;

        switch(command){
        case SOFT_RESET:

            break;
        case GET_FIRMWARE_VERSION:
            comms_buffer[0] = command;
            size = Build_id_string(&comms_buffer[1]);
            commsOutMsg.puartOutPtr = comms_buffer;
            commsOutMsg.uartOutCount = size+1;
            Mailbox_post(uartOutMbx,&commsOutMsg, BIOS_WAIT_FOREVER);
            break;

        case SET_MEASUREMENT_SETTINGS:
            error = Measurement_config_set(pPayload);
            comms_buffer[0] = command;
            if(error == 0)
                comms_buffer[1] = ACK;
            else
                comms_buffer[1] = NACK;
            commsOutMsg.puartOutPtr = comms_buffer;
            commsOutMsg.uartOutCount = 2;
            Mailbox_post(uartOutMbx,&commsOutMsg, BIOS_WAIT_FOREVER);
            break;

        case PERFORM_RESISTANCE_MEASUREMENT:
            Convert2Float(pPayload, (char*) &tmp_float);
            size = Measurement_resistance(&comms_buffer[1],tmp_float);
            comms_buffer[0] = command;
            if(size == 0)
                comms_buffer[1] = ACK;
            else
                comms_buffer[1] = NACK;
            commsOutMsg.puartOutPtr = comms_buffer;
            commsOutMsg.uartOutCount = size+1;
            Mailbox_post(uartOutMbx,&commsOutMsg, BIOS_WAIT_FOREVER);
            break;

        default:
            break;
        }
}
