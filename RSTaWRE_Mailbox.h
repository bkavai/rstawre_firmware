/*
 * Mailbox.h
 *
 *  Created on: May 13th, 2022
 *      Author: kavaipatti
 */

#ifndef RSTaWRE_MAILBOX_H_
#define RSTaWRE_MAILBOX_H_


#include <ti/sysbios/knl/Mailbox.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <uart_tasks.h>

#define MAX_IN_MAIL_COUNT               8
#define MAX_OUT_MAIL_COUNT              2


typedef struct uartInMsgObj{
    char rxChar;
} uartInMsgObj;

typedef struct uartOutMsgObj{
    uint16_t uartOutCount;
    char* puartOutPtr;
} uartOutMsgObj;

extern Mailbox_Handle uartInMbx;
extern Mailbox_Handle uartOutMbx;
extern Mailbox_Params uartInMbxParams;
extern Mailbox_Params uartOutMbxParams;


#endif /* RSTaWRE_MAILBOX_H_ */
