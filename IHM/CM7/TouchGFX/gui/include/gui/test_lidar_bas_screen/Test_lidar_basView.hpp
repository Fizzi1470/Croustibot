#ifndef TEST_LIDAR_BASVIEW_HPP
#define TEST_LIDAR_BASVIEW_HPP

#include <gui_generated/test_lidar_bas_screen/Test_lidar_basViewBase.hpp>
#include <gui/test_lidar_bas_screen/Test_lidar_basPresenter.hpp>
//#include <gui/common/CustomPoint.h>
#include "../../../../../STM32CubeIDE/CM7/Application/User/Core/point.h"

class Test_lidar_basView : public Test_lidar_basViewBase
{
public:
    Test_lidar_basView();
    virtual ~Test_lidar_basView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void donnees_lidar_bas_avant();
    virtual void donnees_lidar_bas_arriere();
    virtual void reception_can_lidars_test_lidar_bas_avant();

// DEBUT TEST POUR AFFICHAGE POINTS

    void updatePointPosition(int x, int y); // Déplacer le point

private:
    CustomPoint myPoint;

// FIN TEST POUR AFFICHAGE POINTS

protected:
};

#endif // TEST_LIDAR_BASVIEW_HPP
