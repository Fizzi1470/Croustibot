#include <gui/robot_pret_screen/Robot_pretView.hpp>
#include "main.h"
#include <gui_generated/robot_pret_screen/Robot_pretViewBase.hpp>
#include "../../../../../STM32CubeIDE/CM7/Application/User/Core/user.h"

int tirette = 0;

extern int16_t x_rob, y_rob;
extern float t_rob;
int16_t t_rob_dix = 0;

Robot_pretView::Robot_pretView()
{

}

void Robot_pretView::setupScreen()
{
    Robot_pretViewBase::setupScreen();
}

void Robot_pretView::tearDownScreen()
{
    Robot_pretViewBase::tearDownScreen();
}

void Robot_pretView::attente_tirette()
{
 	fifo_params_t fifo = read_fifo();

	if(fifo.mess_avail){
	for(uint16_t i_fifo = 0; i_fifo < fifo.mess_amnt; i_fifo++)
	{
		uint16_t read_index = (fifo.first_read + i_fifo) % FIFO_SIZE;

		switch (tab_recep_trames_can[read_index].header.Identifier)
		{
			default: break;

			case 0x150: // telemetrie
							x_rob = tab_recep_trames_can[read_index].data[1] << 8
									| tab_recep_trames_can[read_index].data[0];
							y_rob = tab_recep_trames_can[read_index].data[3] << 8
									| tab_recep_trames_can[read_index].data[2];
							t_rob_dix = tab_recep_trames_can[read_index].data[5] << 8
									| tab_recep_trames_can[read_index].data[4];

							t_rob = (float) t_rob_dix / 100.0;
							break;

			case 0x211:
			{
				tirette = 0;
			}

			case 0x212:
			{
				tirette = 1;
				changeToRobot_en_match();
			}
		}
	}
	}
}
