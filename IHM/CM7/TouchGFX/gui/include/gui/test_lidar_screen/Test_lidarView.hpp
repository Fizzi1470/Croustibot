#ifndef TEST_LIDARVIEW_HPP
#define TEST_LIDARVIEW_HPP

#include <gui_generated/test_lidar_screen/Test_lidarViewBase.hpp>
#include <gui/test_lidar_screen/Test_lidarPresenter.hpp>

class Test_lidarView : public Test_lidarViewBase
{
public:
    Test_lidarView();
    virtual ~Test_lidarView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void donnees_lidar_bas_avant();
    virtual void donnees_lidar_bas_arriere();
    virtual void reception_can_lidars_test_lidar_bas_avant();
protected:
};

#endif // TEST_LIDARVIEW_HPP
