#ifndef CHOIX_STRATEGIEVIEW_HPP
#define CHOIX_STRATEGIEVIEW_HPP

#include <gui_generated/choix_strategie_screen/Choix_strategieViewBase.hpp>
#include <gui/choix_strategie_screen/Choix_strategiePresenter.hpp>

class Choix_strategieView : public Choix_strategieViewBase
{
public:
    Choix_strategieView();
    virtual ~Choix_strategieView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void strategie_1();
    virtual void strategie_2();
    virtual void strategie_3();
    virtual void strategie_4();
    virtual void strategie_5();
    virtual void strategie_6();

    virtual void valider_strat();

protected:
};

#endif // CHOIX_STRATEGIEVIEW_HPP
