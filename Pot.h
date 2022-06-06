/*
 * Pot.h
 *
 *  Created on: Jun 5, 2022
 *      Author: kavaipatti
 */
// MCP4561 (Res code: 103)

#ifndef POT_H_
#define POT_H_


void Pot_set_scale(uint16_t scale);
uint16_t Pot_read_scale(void);
void Pot_init(void);

#define RST_POT_ADDRESS     0       // b0

#define POT_WRITE_DATA      0
#define POT_INC_DATA        1
#define POT_DEC_DATA        2
#define POT_READ_DATA       3
#define POT_TCON_REG        4
#define POT_STATUS_REG      5

#define POT_FULL_SCALE      256

#endif /* POT_H_ */
