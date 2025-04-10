#include <gui/robot_en_match_screen/Robot_en_matchView.hpp>
#include "main.h"
#include <gui_generated/robot_en_match_screen/Robot_en_matchViewBase.hpp>
#include "../../../../../STM32CubeIDE/CM7/Application/User/Core/user.h"

#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>

extern int tirette;

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

