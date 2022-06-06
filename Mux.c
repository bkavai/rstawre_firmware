/*
 * Mux.c
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
#include "Mux.h"

void Mux_init(char mux_id){
    I2C_Transaction m_i2c;
    char txBuffer[2];

        if(mux_id == 0){
            m_i2c.slaveAddress = RST_MUX_1_ADDRESS;
        }
        else{
            m_i2c.slaveAddress = RST_MUX_2_ADDRESS;
        }

        m_i2c.writeBuf = txBuffer;
        m_i2c.writeCount = 2;
        m_i2c.readBuf = NULL;
        m_i2c.readCount = 0;

           // Set IO DIR
        txBuffer[0] = IODIR_ADDRESS;
        txBuffer[1] = 0;
        RST_I2C_Transaction(m_i2c);
           // Write all zeros to GPIO
        txBuffer[0] = GPIO_ADDRESS;
        txBuffer[1] = 0;
        RST_I2C_Transaction(m_i2c);
}

void Mux_set(char mux_value, char mux_id){
    I2C_Transaction m_i2c;
    char txBuffer[2];

        if(mux_id == 0){
            m_i2c.slaveAddress = RST_MUX_1_ADDRESS;
        }
        else{
            m_i2c.slaveAddress = RST_MUX_2_ADDRESS;
        }

        m_i2c.writeBuf = txBuffer;
        m_i2c.writeCount = 2;
        m_i2c.readBuf = NULL;
        m_i2c.readCount = 0;

              // Set IO DIR
        txBuffer[0] = GPIO_ADDRESS;
        txBuffer[1] = mux_value;
        RST_I2C_Transaction(m_i2c);
}

char Mux_get(char mux_id){
    I2C_Transaction m_i2c;
    char txBuffer[2];
    char rxBuffer[2];
        if(mux_id == 0){
            m_i2c.slaveAddress = RST_MUX_1_ADDRESS;
        }
        else{
            m_i2c.slaveAddress = RST_MUX_2_ADDRESS;
        }
        m_i2c.writeBuf = txBuffer;
        m_i2c.writeCount = 1;
        m_i2c.readBuf = rxBuffer;
        m_i2c.readCount = 1;

              // Set IO DIR
        txBuffer[0] = GPIO_ADDRESS;
        RST_I2C_Transaction(m_i2c);

        return(rxBuffer[0]);
}
