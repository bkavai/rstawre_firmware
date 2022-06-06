/*
 * RST_I2C.h
 *
 *  Created on: Jun 4, 2022
 *      Author: kavaipatti
 */

#ifndef RST_I2C_H_
#define RST_I2C_H_

#include <ti/drivers/I2C.h>
#include <ti/drivers/i2c/I2CTiva.h>


void RST_initI2C(void);
bool RST_I2C_Transaction(I2C_Transaction I2C_access);


#endif /* RST_I2C_H_ */
