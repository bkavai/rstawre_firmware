/*
 * tasks.h
 *
 *  Created on: May 13th, 2022
 *      Author: kavaipatti
 */

#ifndef UART_TASKS_H_
#define UART_TASKS_H_

void Uart_in_task(UArg a0, UArg a1);
void Uart_in_task_init(void);
void Uart_out_task(UArg a0, UArg a1);

typedef enum{
    IN_TASK_INIT,
    WAIT_FOR_UART_IN_SOM_MSG,
    WAIT_FOR_UART_BYTE_COUNT,
    WAIT_REST_DATA_IN,
    WAIT_FOR_CHKSUM_IN,
    ERROR_UART_IN
}  uartin_t;

#define UART_IN_TIMEOUT                10      // 10ms
#define MAX_UARTOUT_PAYLOAD_SIZE       264
#define UART_TX_TIMEOUT                1000      // 1s
#define MAX_UARTIN_PAYLOAD_SIZE        257
typedef struct{
    char som;
    char size;
    char command;
    char payload[MAX_UARTIN_PAYLOAD_SIZE];      // 1 status plus 256 bytes of payload
    char chksum;
} UARTDATA;

typedef struct{
    char cmd;
    char* pArg;
    uint16_t arg_len;
    char* pResp;
    uint16_t resp_len;
} cmdExe_Params;


#define SOM     0xE7
#define SPACE   0x32        // ''


#endif /* UART_COMMS_H */
