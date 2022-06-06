/*
 * Pot.c
 *
 *  Created on: Jun 5, 2022
 *      Author: kavaipatti
 */

#include <stdint.h>
#include <stdbool.h>
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include "Measurement.h"
#include "Utility.h"
#include "RST_I2C.h"
#include "Pot.h"

void Pot_set_scale(uint16_t scale){

    I2C_Transaction m_i2c;
    char txBuffer[3];

        m_i2c.slaveAddress = RST_POT_ADDRESS;
        m_i2c.writeBuf = txBuffer;
        m_i2c.writeCount = 2;
        m_i2c.readBuf = NULL;
        m_i2c.readCount = 0;

        txBuffer[0] = POT_WRITE_DATA | ((scale >> 8) & 0x03);
        txBuffer[1] = (scale & 0xFF);

        RST_I2C_Transaction(m_i2c);
}

uint16_t Pot_read_scale(void){

    I2C_Transaction m_i2c;
    char txBuffer[2];
    char rxBuffer[3];
    uint16_t scale;

        m_i2c.slaveAddress = RST_POT_ADDRESS;
        m_i2c.writeBuf = txBuffer;
        m_i2c.writeCount = 1;
        m_i2c.readBuf = rxBuffer;
        m_i2c.readCount = 2;

        txBuffer[0] = POT_READ_DATA;

        RST_I2C_Transaction(m_i2c);
        scale = rxBuffer[0];
        return((scale << 8) | rxBuffer[1]);
}

void Pot_init(void){

        Pot_set_scale(POT_FULL_SCALE);
}

