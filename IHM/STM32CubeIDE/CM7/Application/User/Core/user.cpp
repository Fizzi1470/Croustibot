#include "../Core/user.h"

#include "main.h"

#include "common.h"
#include "ringbuff.h"
volatile void* rb_cm4_to_cm7 = (void *)BUFF_CM4_TO_CM7_ADDR;
volatile void* rb_cm7_to_cm4 = (void *)BUFF_CM7_TO_CM4_ADDR;
//volatile ringbuff_t* rb_cm4_to_cm7 = (void *)BUFF_CM4_TO_CM7_ADDR;
//volatile ringbuff_t* rb_cm7_to_cm4 = (void *)BUFF_CM7_TO_CM4_ADDR;
#include "../../../../../STM32CubeIDE/CM7/Application/User/Core/user.h"


void coms_read(void (*callback)(buff_point_t* addr)){
    size_t len;
    void* addr;

	while ((len = ringbuff_get_linear_block_read_length((ringbuff_t*)rb_cm4_to_cm7)) > 0) {
		addr = ringbuff_get_linear_block_read_address((ringbuff_t*)rb_cm4_to_cm7);

		/* Transmit data */
		if(callback != NULL) callback((buff_point_t*) addr);

		/* Mark buffer as read */
		ringbuff_skip((ringbuff_t*)rb_cm4_to_cm7, sizeof(buff_point_t));
	}
}


int32_t index_lecture = 0;
int32_t index_ecriture = 0;

T_CAN_trame_rx tab_recep_trames_can[FIFO_SIZE];

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hdfcan, uint32_t RxFifo0ITs)
{
	HAL_FDCAN_GetRxMessage(&hfdcan1, FDCAN_RX_FIFO0, &tab_recep_trames_can[index_ecriture].header, tab_recep_trames_can[index_ecriture].data);

	index_ecriture = index_ecriture + 1;

	if (index_ecriture > FIFO_SIZE -1)
	{
		index_ecriture = 0;
	}
}

fifo_params_t read_fifo(){
	fifo_params_t params = {0};

	if(index_ecriture == index_lecture){
		// nothing to do, params is already init at 0 for bool avail
	} else {
		params.mess_avail = true;
		params.first_read = index_lecture;

		while(index_lecture != index_ecriture){
			params.mess_amnt++;
			index_lecture ++;
			if(index_lecture > FIFO_SIZE -1) index_lecture = 0;
		}
	}

	return params;
}
