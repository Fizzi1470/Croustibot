#include <gui/robot_en_match_screen/Robot_en_matchView.hpp>
#include "main.h"
#include <gui_generated/robot_en_match_screen/Robot_en_matchViewBase.hpp>
#include "../../../../../STM32CubeIDE/CM7/Application/User/Core/user.h"

#include "../../../../../STM32CubeIDE/CM7/Application/User/Core/pathfinder.h"

float curr_x = 0, curr_y = 0, curr_t = 0;

#define MARGINS_RADIUS 2

instructions_t previous_0 = {0}, previous_1 = {0};

pathfinder_t p = {
	.curr_x = 0,
	.curr_y = 0,

	.dest_x = MAP_X_SIZE -1,
	.dest_y = MAP_Y_SIZE -1,
};

void process_point(uint16_t x, uint16_t y, uint16_t i){
	float pt_x_abs = curr_x + (float)x * cos(curr_t) - (float)y * sin(curr_t);
	float pt_y_abs = curr_y + (float)y * sin(curr_t) + (float)x * cos(curr_t);

	path_addObstacle(&p, pt_x_abs, pt_y_abs, MARGINS_RADIUS);

#warning : TODO : ajouter un garde fou pour arreter le robot s'il s'apprete a rentrer dans un obstacle directement devant lui


}





Robot_en_matchView::Robot_en_matchView() {
    if(path_process(&p)){ // if there is a path available

    	if( // conditions de renvoi de l'instruction
    			p.instructions[1].x != previous_1.x || // position cible de l'instruction en cours a changé
				p.instructions[1].y != previous_1.y
			) {
    			uint16_t distance = p.instructions[0].dist;
    		    uint16_t angle = p.instructions[0].angle;

    		    FDCAN_TxHeaderTypeDef header = {
    		    		.Identifier = 0x101,
						.IdType = FDCAN_STANDARD_ID,
						.TxFrameType = FDCAN_DATA_FRAME,
						.DataLength = 4,
						.ErrorStateIndicator = FDCAN_ESI_ACTIVE,
						.BitRateSwitch = FDCAN_BRS_OFF,
						.FDFormat = FDCAN_CLASSIC_CAN,
						.TxEventFifoControl = FDCAN_NO_TX_EVENTS,
						.MessageMarker = 0,
    		    };

    		    uint8_t data[] = {
    		    		(uint8_t)distance,
						(uint8_t)(distance >> 8),
						(uint8_t)angle,
						(uint8_t)(angle >> 8),
    		    };

    		    HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &header, data);

    	}

    	previous_0 = p.instructions[0];
    	previous_1 = p.instructions[1];
    }
}

void Robot_en_matchView::setupScreen()
{
    Robot_en_matchViewBase::setupScreen();
}

void Robot_en_matchView::tearDownScreen()
{
    Robot_en_matchViewBase::tearDownScreen();
}

void Robot_en_matchView::reception_can_lidars_en_match()
{
	int16_t pt_x = 0, pt_y = 0, i = 0;

	int32_t to_read = read_fifo();

	//if (fifo != -1)
	for(uint16_t fifo = 0; fifo < to_read; fifo++)
	{
		switch (tab_recep_trames_can[fifo].header.Identifier)
		{
			default:break;

			case 0x200 :

				i = tab_recep_trames_can[fifo].data[5] << 8 | tab_recep_trames_can[fifo].data[4];

				pt_x = tab_recep_trames_can[fifo].data[1] << 8 | tab_recep_trames_can[fifo].data[0];
				pt_y = tab_recep_trames_can[fifo].data[3] << 8 | tab_recep_trames_can[fifo].data[2];

#warning ajouter l'écart du lidar au centre

				process_point(pt_x, pt_y, i);
				break;

			case 0x201 :

				i = tab_recep_trames_can[fifo].data[5] << 8 | tab_recep_trames_can[fifo].data[4];

				pt_x = tab_recep_trames_can[fifo].data[1] << 8 | tab_recep_trames_can[fifo].data[0];
				pt_y = tab_recep_trames_can[fifo].data[3] << 8 | tab_recep_trames_can[fifo].data[2];

				process_point(pt_x, pt_y, i);
				break;
		}
	}
}
