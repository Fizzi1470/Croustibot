#ifndef TEST_LIDAR_BASVIEW_HPP
#define TEST_LIDAR_BASVIEW_HPP

#include <gui_generated/test_lidar_bas_screen/Test_lidar_basViewBase.hpp>
#include <gui/test_lidar_bas_screen/Test_lidar_basPresenter.hpp>

class Test_lidar_basView : public Test_lidar_basViewBase
{
public:
    Test_lidar_basView();
    virtual ~Test_lidar_basView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void donnees_lidar_bas_avant();
    virtual void donnees_lidar_bas_arriere();
protected:
};

#endif // TEST_LIDAR_BASVIEW_HPP
