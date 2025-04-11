/*
 * user.h
 *
 *  Created on: Mar 24, 2025
 *      Author: lisaf
 */

#ifndef APPLICATION_USER_CORE_USER_H_
#define APPLICATION_USER_CORE_USER_H_

#include "main.h"

#define FIFO_SIZE 256

typedef struct  {
	uint16_t first_read;
	uint16_t mess_amnt;
	bool mess_avail;
} fifo_params_t;

extern T_CAN_trame_rx tab_recep_trames_can[FIFO_SIZE];

fifo_params_t read_fifo();

#endif /* APPLICATION_USER_CORE_USER_H_ */
