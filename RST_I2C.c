/*
 * RST_I2C.c
 *
 *  Created on: Jun 3, 2022
 *      Author: kavaipatti
 */
#if defined(__TI_COMPILER_VERSION__)
#pragma DATA_SECTION(I2C_config, ".const:I2C_config")
#pragma DATA_SECTION(i2cTivaHWAttrs, ".const:i2cTivaHWAttrs")
#endif
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
#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>
#include <driverlib/pin_map.h>
#include <RST_TM4C1230.h>

#include <ti/drivers/I2C.h>
#include <ti/drivers/i2c/I2CTiva.h>

#define RST_TM4C123GXL_I2CCOUNT      1

I2CTiva_Object i2cTivaObjects[RST_TM4C123GXL_I2CCOUNT];
I2C_Handle      i2c;
I2C_Params      i2cParams;
I2C_Transaction i2cTransaction;


const I2CTiva_HWAttrs i2cTivaHWAttrs[RST_TM4C123GXL_I2CCOUNT] = {
    {
        .baseAddr = I2C2_BASE,
        .intNum = INT_I2C2,
        .intPriority = (~0)
    }
};

const I2C_Config I2C_config[] = {
    {
        .fxnTablePtr = &I2CTiva_fxnTable,
        .object = &i2cTivaObjects[0],
        .hwAttrs = &i2cTivaHWAttrs[0]
    },
};



/*
 *
 *  ======== EK_TM4C123GXL_initI2C ========
 */
void RST_initI2C(void)
{
    /* I2C1 Init */
    /* Enable the peripheral */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C2);

    /* Configure the appropriate pins to be I2C instead of GPIO. */
    GPIOPinConfigure(GPIO_PE4_I2C2SCL);
    GPIOPinConfigure(GPIO_PE5_I2C2SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTE_BASE, GPIO_PIN_4);
    GPIOPinTypeI2C(GPIO_PORTE_BASE, GPIO_PIN_5);

    I2C_init();

    /* Create I2C for usage */
     I2C_Params_init(&i2cParams);
     i2cParams.bitRate = I2C_400kHz;
     i2c = I2C_open(0, &i2cParams);
     if (i2c == NULL) {
         System_abort("Error Initializing I2C\n");
     }
     else {
         System_printf("I2C Initialized!\n");
     }
}

bool RST_I2C_Transaction(I2C_Transaction I2C_access)
{
    bool status;

    status = I2C_transfer(i2c, &I2C_access);

    return(status);
}
