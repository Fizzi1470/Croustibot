#include <gui/robot_en_match_screen/Robot_en_matchView.hpp>
#include "main.h"
#include <gui_generated/robot_en_match_screen/Robot_en_matchViewBase.hpp>
#include "../../../../../STM32CubeIDE/CM7/Application/User/Core/user.h"

extern uint8_t *tab_coord_point_A;
extern uint8_t *tab_coord_point_B;
extern uint8_t *tab_coord_point_C;

//T_CAN_trame_rx trame_rx_lidar_avant;


Robot_en_matchView::Robot_en_matchView()
{

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
	int32_t fifo = read_fifo();

	if(fifo != -1)
	{
		switch (tab_recep_trames_can[fifo].header.Identifier)
		{
			default:
				break;

			case 210:
				tab_coord_point_A = tab_recep_trames_can[fifo].data;
				NVIC_SystemReset();
				break;

			case 220:
				tab_coord_point_B = tab_recep_trames_can[fifo].data;
				break;

			case 230:
				tab_coord_point_C = tab_recep_trames_can[fifo].data;
				break;
		}
	}
}
