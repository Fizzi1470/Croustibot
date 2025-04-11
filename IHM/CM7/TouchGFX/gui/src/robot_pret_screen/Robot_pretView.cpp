#include <gui/robot_pret_screen/Robot_pretView.hpp>
#include "main.h"
#include <gui_generated/robot_pret_screen/Robot_pretViewBase.hpp>
#include "../../../../../STM32CubeIDE/CM7/Application/User/Core/user.h"

int tirette = 0;

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
