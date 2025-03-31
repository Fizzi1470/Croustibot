#include <gui/test_lidar_bas_screen/Test_lidar_basView.hpp>
#include "main.h"
#include <gui_generated/test_lidar_bas_screen/Test_lidar_basViewBase.hpp>
#include "../../../../../STM32CubeIDE/CM7/Application/User/Core/user.h"

extern uint32_t *tab_coord_point_A;

uin16_t x, y;

#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>

touchgfx::MoveAnimator< touchgfx::Circle > points[800];
touchgfx::PainterRGB888 pointPainters[800];

Test_lidar_basView::Test_lidar_basView()
{

}

void Test_lidar_basView::setupScreen()
{
    Test_lidar_basViewBase::setupScreen();

    uint16_t buffer_amnt = 100;

    for(uint16_t i = 0; i < buffer_amnt; i++)
    {
        //points[i].setPosition(i + 20, i + 20, 800, 480);
    	points[i].setPosition(i + 20, i + 20, 800, 480);
        points[i].setCenter(i + 20, i + 20);
        points[i].setRadius(2);
        points[i].setLineWidth(0);
        points[i].setArc(0, 360);
        pointPainters[i].setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        points[i].setPainter(pointPainters[i]);
        add(points[i]);
    }
}

void Test_lidar_basView::tearDownScreen()
{
    Test_lidar_basViewBase::tearDownScreen();
}

void Test_lidar_basView::reception_can_lidars_test_lidar_bas_avant()
{
	int32_t fifo = read_fifo();

	if (fifo != -1)
	{
		switch (tab_recep_trames_can[fifo].header.Identifier)
		{
		default:
			break;

		case 200:
			tab_coord_point_A = tab_recep_trames_can[fifo].data;

			x = tab_coord_point_A[0];
			y = tab_coord_point_A[1];

			NVIC_SystemReset();
			break;
		}
	}
}

void Test_lidar_basView::donnees_lidar_bas_avant()
{
	// point A obstacle 1
	//point1.setXY(tab[0], tab[1]);
	//point1.invalidate();
}

void Test_lidar_basView::donnees_lidar_bas_arriere()
{

}
