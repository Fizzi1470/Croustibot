#ifndef ROBOT_PRETVIEW_HPP
#define ROBOT_PRETVIEW_HPP

#include <gui_generated/robot_pret_screen/Robot_pretViewBase.hpp>
#include <gui/robot_pret_screen/Robot_pretPresenter.hpp>

class Robot_pretView : public Robot_pretViewBase
{
public:
    Robot_pretView();
    virtual ~Robot_pretView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // ROBOT_PRETVIEW_HPP
