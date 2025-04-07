#ifndef ROBOT_EN_MATCHPRESENTER_HPP
#define ROBOT_EN_MATCHPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Robot_en_matchView;

class Robot_en_matchPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Robot_en_matchPresenter(Robot_en_matchView& v);

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

    virtual ~Robot_en_matchPresenter() {}

private:
    Robot_en_matchPresenter();

    Robot_en_matchView& view;
};

#endif // ROBOT_EN_MATCHPRESENTER_HPP
