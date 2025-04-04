#include <gui/test_lidar_haut_screen/Test_lidar_hautView.hpp>

#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>

#define POINTS_AMOUNT 2400

touchgfx::Circle points[POINTS_AMOUNT];
touchgfx::PainterRGB888 pointPainters[POINTS_AMOUNT];

Test_lidar_hautView::Test_lidar_hautView()
{
	/*
	points[0].setPosition(0, 0, 81, 80);
	points[0].setCenter(40, 40);
	points[0].setRadius(8);
	points[0].setLineWidth(0);
	points[0].setArc(0, 360);
	pointPainters[0].setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	points[0].setPainter(pointPainters[0]);
	add(points[0]);*/

}

void Test_lidar_hautView::setupScreen()
{
    Test_lidar_hautViewBase::setupScreen();
}

void Test_lidar_hautView::tearDownScreen()
{
    Test_lidar_hautViewBase::tearDownScreen();
}

void Test_lidar_hautView::donnees_lidar_haut(){
	/*
	for(uint32_t i = 0; i < POINTS_AMOUNT/2; i++){
		points[i].setPosition(i, i%10, 81, 80);
		points[i].setCenter(40, 40);
		points[i].setRadius(8);
		points[i].setLineWidth(0);
		points[i].setArc(0, 360);
		pointPainters[i].setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
		points[i].setPainter(pointPainters[i]);
		add(points[i]);
	}
	*/
}

void Test_lidar_hautView::lidar_loop(){
	//points[0].setPosition(30, 30, 81, 80);
}

