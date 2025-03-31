#ifndef ROBOT_EN_MATCHVIEW_HPP
#define ROBOT_EN_MATCHVIEW_HPP

#include <gui_generated/robot_en_match_screen/Robot_en_matchViewBase.hpp>
#include <gui/robot_en_match_screen/Robot_en_matchPresenter.hpp>

class Robot_en_matchView : public Robot_en_matchViewBase
{
public:
    Robot_en_matchView();
    virtual ~Robot_en_matchView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void reception_can_lidars_en_match();

protected:
};

#endif // ROBOT_EN_MATCHVIEW_HPP
