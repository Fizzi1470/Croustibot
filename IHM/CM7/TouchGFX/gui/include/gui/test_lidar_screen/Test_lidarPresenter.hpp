#ifndef TEST_LIDARPRESENTER_HPP
#define TEST_LIDARPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Test_lidarView;

class Test_lidarPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Test_lidarPresenter(Test_lidarView& v);

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

    virtual ~Test_lidarPresenter() {}

private:
    Test_lidarPresenter();

    Test_lidarView& view;
};

#endif // TEST_LIDARPRESENTER_HPP
