/*
 * Measurement.c
 *
 *  Created on: Jun 3, 2022
 *      Author: kavaipatti
 */

#include <stdint.h>
#include <stdbool.h>
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/drivers/GPIO.h>

#include "Measurement.h"
#include "Utility.h"
#include "RST_I2C.h"
#include "Mux.h"
#include "Pot.h"
#include "Board.h"
static float measurementSetting[MAX_MEASUREMENT_SETTING_COUNT];

void Measurement_rtn_en(char state){
    GPIO_write(RTN_ENA, state);
}

void Measurement_dischrg_en(char state){
    GPIO_write(DISCHARGE_ENA, state);
}

void Measurement_gain_en(char state){
    GPIO_write(GAIN_ENA, state);
}


char Measurement_config_set(char *pDataptr){

    float flt_value, tmp_config[3];
    char error = 0, i;

        for(i=0;i<3;++i){
            Convert2Float(pDataptr, (char*) &flt_value);
            tmp_config[i] = flt_value;
        }

        // Verify tmp config
        if((tmp_config[0] >= MIN_MUX_SETTING) && (tmp_config[0] <= MAX_MUX_SETTING))
                measurementSetting[0] = tmp_config[0];
        else
                error+=1;
        if((tmp_config[1] >= MIN_CHASSIS_SETTING) && (tmp_config[1] <= MAX_CHASSIS_SETTING))
                measurementSetting[1] = tmp_config[1];
        else
            error+=1;

        if((tmp_config[2] >= MIN_POT_SETTING) && (tmp_config[2] <= MAX_POT_SETTING))
                measurementSetting[2] = tmp_config[0];
        else
            error+=1;

        return(error);
}

char Measurement_resistance(char *pDataptr, float acq_time){

    uint16_t pot_scale;

        // Set mux
        Mux_set(pDataptr[0], 0);

        // Set pot
        pot_scale = (pDataptr[1] << 8) + pDataptr[2];

        Pot_set_scale(pot_scale);

        // Set chassis
        Measurement_rtn_en(1);

        // Start sampling ADC for time period

        return(0);
}

void Measurement_init(void){


        // Set Mux to 0
        Mux_init(0);
        Mux_init(1);

        Pot_init();

        Measurement_rtn_en(0);
        Measurement_dischrg_en(0);
        Measurement_gain_en(0);
}
