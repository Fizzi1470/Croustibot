#include "../Core/user.h"

#include "main.h"


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

int32_t read_fifo()
{
	if(index_ecriture - index_lecture != 0)
	{
		index_lecture = index_lecture + 1;

		if(index_lecture > FIFO_SIZE -1)
		{
			index_lecture = 0;
		}

		return index_lecture;
	}
	else
	{
		return -1;
	}
}
