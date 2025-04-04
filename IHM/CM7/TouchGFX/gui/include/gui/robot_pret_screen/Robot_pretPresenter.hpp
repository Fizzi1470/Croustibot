#ifndef ROBOT_PRETPRESENTER_HPP
#define ROBOT_PRETPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Robot_pretView;

class Robot_pretPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Robot_pretPresenter(Robot_pretView& v);

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

    virtual ~Robot_pretPresenter() {}

private:
    Robot_pretPresenter();

    Robot_pretView& view;
};

#endif // ROBOT_PRETPRESENTER_HPP
