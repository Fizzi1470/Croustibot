#include <gui/robot_pret_screen/Robot_pretView.hpp>
#include "main.h"
#include <gui_generated/robot_pret_screen/Robot_pretViewBase.hpp>

extern int tirette;

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
	// mettre la variable "tirette" à 1 lorsqu'elle est retirée
}
