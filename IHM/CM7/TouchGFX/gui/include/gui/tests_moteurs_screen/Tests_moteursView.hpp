#ifndef TESTS_MOTEURSVIEW_HPP
#define TESTS_MOTEURSVIEW_HPP

#include <gui_generated/tests_moteurs_screen/Tests_moteursViewBase.hpp>
#include <gui/tests_moteurs_screen/Tests_moteursPresenter.hpp>
#include "main.h"

class Tests_moteursView : public Tests_moteursViewBase
{
public:
    Tests_moteursView();
    virtual ~Tests_moteursView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void moteurs_avancer();
    void moteurs_tourner_90();
    void moteurs_aller_la_bas();
    virtual void stop();
    void active_tout_le_tps();

protected:
};

#endif // TESTS_MOTEURSVIEW_HPP
