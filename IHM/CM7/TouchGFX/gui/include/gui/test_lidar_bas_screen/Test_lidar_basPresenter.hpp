#ifndef TEST_LIDAR_BASPRESENTER_HPP
#define TEST_LIDAR_BASPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Test_lidar_basView;

class Test_lidar_basPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Test_lidar_basPresenter(Test_lidar_basView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~Test_lidar_basPresenter() {}

private:
    Test_lidar_basPresenter();

    Test_lidar_basView& view;
};

#endif // TEST_LIDAR_BASPRESENTER_HPP
