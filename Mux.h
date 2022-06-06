/*
 * Mux.h
 *
 *  Created on: Jun 5, 2022
 *      Author: kavaipatti
 */

#ifndef MUX_H_
#define MUX_H_

#define RST_MUX_1_ADDRESS     0       // b000
#define RST_MUX_2_ADDRESS     4       // b100

#define IODIR_ADDRESS       0
#define IPOL_ADDRESS        1
#define GPINTEN_ADDRESS     2
#define DEFVAL_ADDRESS      3
#define INTCON_ADDRESS      4
#define IOCON_ADDRESS       5
#define GPPU_ADDRESS        6
#define INTF_ADDRESS        7
#define INTCAP_ADDRESS      8
#define GPIO_ADDRESS        9
#define OLAT_ADDRESS        10

void Mux_init(char mux_id);
void Mux_set(char mux_value, char mux_id);
char Mux_get(char mux_id);

#endif /* MUX_H_ */
