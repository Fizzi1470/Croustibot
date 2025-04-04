#ifndef CHOIX_TESTSPRESENTER_HPP
#define CHOIX_TESTSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Choix_testsView;

class Choix_testsPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Choix_testsPresenter(Choix_testsView& v);

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

    virtual ~Choix_testsPresenter() {}

private:
    Choix_testsPresenter();

    Choix_testsView& view;
};

#endif // CHOIX_TESTSPRESENTER_HPP
