/*
 * user.h
 *
 *  Created on: Mar 24, 2025
 *      Author: lisaf
 */

#ifndef APPLICATION_USER_CORE_USER_H_
#define APPLICATION_USER_CORE_USER_H_

#include "main.h"

#define FIFO_SIZE 32

extern T_CAN_trame_rx tab_recep_trames_can[FIFO_SIZE];

int32_t read_fifo();


#endif /* APPLICATION_USER_CORE_USER_H_ */
