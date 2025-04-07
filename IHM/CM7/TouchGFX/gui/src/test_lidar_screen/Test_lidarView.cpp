#include <gui/test_lidar_screen/Test_lidarView.hpp>
#include "main.h"
#include <gui_generated/test_lidar_screen/Test_lidarViewBase.hpp>
#include "../../../../../STM32CubeIDE/CM7/Application/User/Core/user.h"

//bonjour

uint16_t x, y;

#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>

touchgfx::MoveAnimator< touchgfx::Circle > points[100];
touchgfx::PainterRGB888 pointPainters[1];
touchgfx::PainterRGB888 lignePainters[1];

touchgfx::Line lignes[10];

struct {
	int16_t x;
	int16_t y;
	int16_t i;
} points_lidar_bas[360] = {0};

#warning chelou un peu
Test_lidarView::Test_lidarView(){}


void Test_lidarView::setupScreen()
{
	Test_lidarViewBase::setupScreen();

    uint16_t buffer_amnt = 100;
    for(uint16_t i = 0; i < buffer_amnt; i++)
    {
        //points[i].setPosition(i + 20, i + 20, 800, 480);
    	points[i].setPosition(points_lidar_bas[i].x, points_lidar_bas[i].y, 5, 5);
        points[i].setCenter(2, 2);
        points[i].setRadius(2);
        points[i].setLineWidth(0);
        points[i].setArc(0, 360);
        pointPainters[0].setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        points[i].setPainter(pointPainters[0]);
        add(points[i]);
    }
}

void Test_lidarView::tearDownScreen()
{
    Test_lidarViewBase::tearDownScreen();
}

void Test_lidarView::reception_can_lidars_test_lidar_bas_avant()
{
	int32_t to_read = read_fifo();

	//if (fifo != -1)
	for(uint16_t fifo = 0; fifo < to_read; fifo++)
	{

		switch (tab_recep_trames_can[fifo].header.Identifier)
		{
		default:
			break;

		case 0x200:
		{
			int16_t i = tab_recep_trames_can[fifo].data[5] << 8 | tab_recep_trames_can[fifo].data[4];

			points_lidar_bas[i].x = tab_recep_trames_can[fifo].data[1] << 8 | tab_recep_trames_can[fifo].data[0];
			points_lidar_bas[i].y = tab_recep_trames_can[fifo].data[3] << 8 | tab_recep_trames_can[fifo].data[2];


			for (uint16_t i = 0; i < 100; i++)
			{
#warning le 400 et 240 sont a modifier (c est censé être la position du robot)
				points[i].setXY(points_lidar_bas[i].x + 400, points_lidar_bas[i].y + 240);
				points[i].invalidate();
			}
/*

Dans setPosition : (x du point 1, y du point 1, x du point 2 + coordonnées du robot, y du point 2 + coordonnées du robot)
Dans setEnd : (x du point 2, y du point 2)

*/
			//lignes[i].setPosition(points_lidar_bas[i].x, points_lidar_bas[i].y, 400, 400);
				//lignes[i].setPosition(300, 300, 400, 400);
				//lignes[i].setEnd(400, 400);
				//lignePainter[0].setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
				//lignes[i].setPainter(lignePainters[0]);
				//lignes[i].invalidate();

			break;
		}
		case 0x201:
		{
			int16_t i = tab_recep_trames_can[fifo].data[5] << 8
					| tab_recep_trames_can[fifo].data[4];

			points_lidar_bas[i].x = tab_recep_trames_can[fifo].data[1] << 8
					| tab_recep_trames_can[fifo].data[0];
			points_lidar_bas[i].y = tab_recep_trames_can[fifo].data[3] << 8
					| tab_recep_trames_can[fifo].data[2];

			for (uint16_t i = 0; i < 100; i++) {
#warning le 400 et 240 sont a modifier (c est censé être la position du robot)
				points[i].setXY(points_lidar_bas[i].x + 400,
						points_lidar_bas[i].y + 240);
				points[i].invalidate();
			}
			break;
		}
		}
	}
}

void Test_lidarView::donnees_lidar_bas_avant()
{
	// point A obstacle 1
	//point1.setXY(tab[0], tab[1]);
	//point1.invalidate();
}
void Test_lidarView::donnees_lidar_bas_arriere()
{

}
