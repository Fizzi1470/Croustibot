#include <gui/test_lidar_screen/Test_lidarView.hpp>
#include "main.h"
#include <gui_generated/test_lidar_screen/Test_lidarViewBase.hpp>
#include "../../../../../STM32CubeIDE/CM7/Application/User/Core/user.h"

#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>

uint16_t x, y;
float pos_rob_x = 0.0f;
float pos_rob_y = 0.0f;
float pos_rob_t = 0.0f;
float pos_abs_rob_x;
float pos_abs_rob_y;

touchgfx::MoveAnimator< touchgfx::Circle > points[100];
touchgfx::PainterRGB888 pointPainters[1];
touchgfx::PainterRGB888 lignePainters[1];
touchgfx::Line lignes[10];

typedef struct {
	int16_t x;
	int16_t y;
	int16_t i;
} lidar_pt_t;

lidar_pt_t points_lidar[360] = {0}, discontinuites[360] = {0};

#warning chelou un peu
Test_lidarView::Test_lidarView(){}

static int16_t map(int16_t x, int16_t in_min, int16_t in_max, int16_t out_min, int16_t out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Test_lidarView::setupScreen()
{
	Test_lidarViewBase::setupScreen();

    uint16_t buffer_amnt = 100;
    for(uint16_t i = 0; i < buffer_amnt; i++)
    {
        //points[i].setPosition(i + 20, i + 20, 800, 480);
    	points[i].setPosition(points_lidar[i*2].x, points_lidar[i*2].y, 5, 5);
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
 	fifo_params_t fifo = read_fifo();

	if(fifo.mess_avail){
	for(uint16_t i_fifo = fifo.first_read; i_fifo < fifo.mess_amnt; i_fifo++){

		uint16_t read_index = i_fifo % FIFO_SIZE;

		switch (tab_recep_trames_can[read_index].header.Identifier){

		default: break;

		case 0x601:
		case 0x600:
			int16_t pt_i = tab_recep_trames_can[read_index].data[5] << 8 | tab_recep_trames_can[read_index].data[4];

			int16_t pt_x = tab_recep_trames_can[read_index].data[1] << 8 | tab_recep_trames_can[read_index].data[0];
			int16_t pt_y = tab_recep_trames_can[read_index].data[3] << 8 | tab_recep_trames_can[read_index].data[2];

			points_lidar[pt_i].x = pos_rob_x + pt_x * cos(pos_rob_t) - pt_y * sin(pos_rob_t);
			points_lidar[pt_i].y = pos_rob_y + pt_y * sin(pos_rob_t) + pt_x * cos(pos_rob_t);

			break;
		}
	}
	}
	for (uint16_t i = 0; i < 100; i++)
	{

		int16_t pt_x_ecran = map(points_lidar[i].x, 0, 8000, 181, 610);
		int16_t pt_y_ecran = map(points_lidar[i].y, 0, 8000, 31, 437);

		//points[i].setXY(points_lidar_bas[i].x + 400, points_lidar_bas[i].y + 240);
		points[i].setXY(pt_x_ecran, pt_y_ecran);
		points[i].invalidate();
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
