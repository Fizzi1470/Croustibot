#ifndef TESTS_MOTEURSPRESENTER_HPP
#define TESTS_MOTEURSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Tests_moteursView;

class Tests_moteursPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Tests_moteursPresenter(Tests_moteursView& v);

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

    virtual ~Tests_moteursPresenter() {}

private:
    Tests_moteursPresenter();

    Tests_moteursView& view;
};

#endif // TESTS_MOTEURSPRESENTER_HPP
