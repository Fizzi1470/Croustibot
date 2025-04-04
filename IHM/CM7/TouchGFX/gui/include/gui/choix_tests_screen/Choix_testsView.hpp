#ifndef CHOIX_TESTSVIEW_HPP
#define CHOIX_TESTSVIEW_HPP

#include <gui_generated/choix_tests_screen/Choix_testsViewBase.hpp>
#include <gui/choix_tests_screen/Choix_testsPresenter.hpp>

class Choix_testsView : public Choix_testsViewBase
{
public:
    Choix_testsView();
    virtual ~Choix_testsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // CHOIX_TESTSVIEW_HPP
