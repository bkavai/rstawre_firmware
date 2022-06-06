#include <stdint.h>
#include <stdbool.h>

#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/family/arm/m3/Hwi.h>
#include <inc/hw_ints.h>
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <inc/hw_gpio.h>
#include <driverlib/uart.h>
#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>
#include <driverlib/pin_map.h>
#include <RST_TM4C1230.h>

#include <ti/drivers/uart/UARTTiva.h>

#if defined(__TI_COMPILER_VERSION__)
#pragma DATA_SECTION(UART_config, ".const:UART_config")
#pragma DATA_SECTION(uartTivaHWAttrs, ".const:uartTivaHWAttrs")
#endif
#define MAX_UART_BUFFER_SIZE  256
UARTTiva_Object uartTivaObjects[RST_TM4C1230_UARTCOUNT];
unsigned char uartTivaRingBuffer[RST_TM4C1230_UARTCOUNT][MAX_UART_BUFFER_SIZE];

/* UART configuration structure */
const UARTTiva_HWAttrs uartTivaHWAttrs[RST_TM4C1230_UARTCOUNT] = {
    {
        .baseAddr = UART0_BASE,
        .intNum = INT_UART0,
        .intPriority = (~0),
        .flowControl = UART_FLOWCONTROL_NONE,
        .ringBufPtr  = uartTivaRingBuffer[0],
        .ringBufSize = sizeof(uartTivaRingBuffer[0])
    },

    {
         .baseAddr = UART1_BASE,
         .intNum = INT_UART1,
         .intPriority = (~0),
         .flowControl = UART_FLOWCONTROL_NONE,
         .ringBufPtr  = uartTivaRingBuffer[1],
         .ringBufSize = sizeof(uartTivaRingBuffer[1])
    }

};

const UART_Config UART_config[] = {
    {
     .fxnTablePtr = &UARTTiva_fxnTable,
     .object = &uartTivaObjects[0],
     .hwAttrs = &uartTivaHWAttrs[0]
    },
    {
     .fxnTablePtr = &UARTTiva_fxnTable,
     .object = &uartTivaObjects[1],
     .hwAttrs = &uartTivaHWAttrs[1]
    }
}; /* TI_DRIVERS_UART_DMA */



UART_Handle uart0;
UART_Handle uart1;
UART_Params uart0Params;
UART_Params uart1Params;

static volatile char Uarta_tx_buffer[MAX_UART_BUFFER_SIZE];
static volatile uint16_t Uarta_tx_counter;
static volatile int16_t Uarta_tx_byte_count;

void RST_TM4C1230_initUART(char index)
{

        if(index == 0){
            /* Enable and configure the peripherals used by the uart. */
            SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

            GPIOPinConfigure(GPIO_PA0_U0RX);
            GPIOPinConfigure(GPIO_PA1_U0TX);
            GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

                     /* Create a UART with data processing off. */
            UART_Params_init(&uart0Params);
            uart0Params.writeDataMode = UART_DATA_BINARY;
            uart0Params.readDataMode = UART_DATA_BINARY;
            uart0Params.readReturnMode = UART_RETURN_FULL;
            uart0Params.readEcho = UART_ECHO_OFF;
            uart0Params.baudRate = 9600;
            uart0 = UART_open(0, &uart0Params);

            if (uart0 == NULL) {
                System_abort("Error opening the UART");
            }
        }
        if(index == 1){
            /* Enable and configure the peripherals used by the uart. */
            SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

            GPIOPinConfigure(GPIO_PB0_U1RX);
            GPIOPinConfigure(GPIO_PB1_U1TX);
            GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

                     /* Create a UART with data processing off. */
            UART_Params_init(&uart1Params);
            uart1Params.writeDataMode = UART_DATA_BINARY;
            uart1Params.readDataMode = UART_DATA_BINARY;
            uart1Params.readReturnMode = UART_RETURN_FULL;
            uart1Params.readEcho = UART_ECHO_OFF;
            uart1Params.baudRate = 115200;
            uart1 = UART_open(1, &uart1Params);

            if (uart1 == NULL) {
                System_abort("Error opening the UART");
            }
        }
}

void Uart_Test(char index){

    char test_char;

        test_char = 0x41;
        if(index == 0)
            UART_write(uart0, &test_char, 1);
}

char uarta_load_tx_buffer(char *ptxData, uint16_t tx_count, char index){

    uint16_t i;
    char ret_val = TRUE;
        if(index == 0){
            if(tx_count < MAX_UART_BUFFER_SIZE){
                 for(i=0;i<tx_count;++i){
                     uartTivaRingBuffer[0][i] = *(ptxData+i);
                 }
                 UART_write(uart0, &uartTivaRingBuffer[0][0], 1);
             }
        }

        return(ret_val);
}

char Uart_get_char(char *pDataptr, char size, char index){

    char i, uart_status;

        if(index == 0)
            uart_status = UART_read(uart0,pDataptr,size);

        return(uart_status);

}
