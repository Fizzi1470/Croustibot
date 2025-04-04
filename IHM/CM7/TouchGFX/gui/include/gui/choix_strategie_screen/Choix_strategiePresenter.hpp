#ifndef CHOIX_STRATEGIEPRESENTER_HPP
#define CHOIX_STRATEGIEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Choix_strategieView;

class Choix_strategiePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Choix_strategiePresenter(Choix_strategieView& v);

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

    virtual ~Choix_strategiePresenter() {}

private:
    Choix_strategiePresenter();

    Choix_strategieView& view;
};

#endif // CHOIX_STRATEGIEPRESENTER_HPP
