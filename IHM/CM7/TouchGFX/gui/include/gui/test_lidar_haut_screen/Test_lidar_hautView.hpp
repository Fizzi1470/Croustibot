#ifndef TEST_LIDAR_HAUTVIEW_HPP
#define TEST_LIDAR_HAUTVIEW_HPP

#include <gui_generated/test_lidar_haut_screen/Test_lidar_hautViewBase.hpp>
#include <gui/test_lidar_haut_screen/Test_lidar_hautPresenter.hpp>

class Test_lidar_hautView : public Test_lidar_hautViewBase
{
public:
    Test_lidar_hautView();
    virtual ~Test_lidar_hautView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void donnees_lidar_haut();
    virtual void lidar_loop();

protected:
};

#endif // TEST_LIDAR_HAUTVIEW_HPP
