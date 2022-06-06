/*
 * Measurement.h
 *
 *  Created on: Jun 3, 2022
 *      Author: kavaipatti
 */

#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_


#define MIN_MUX_SETTING         0
#define MAX_MUX_SETTING         10
#define MIN_CHASSIS_SETTING     0
#define MAX_CHASSIS_SETTING     1
#define MIN_POT_SETTING         0
#define MAX_POT_SETTING         1023

#define MAX_MEASUREMENT_SETTING_COUNT   3

char Measurement_config_set(char *pDataptr);
char Measurement_resistance(char *pDataptr, float acq_time);
void Measurement_init(void);


#endif /* MEASUREMENT_H_ */
