#ifndef LIGHTCONTROLSCREENPRESENTER_HPP
#define LIGHTCONTROLSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class LightControlScreenView;

class LightControlScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    LightControlScreenPresenter(LightControlScreenView& v);

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

    virtual ~LightControlScreenPresenter() {};

    /**
     * The function in order to control LED.
     */
    void lightButtonClicked(uint16_t index, bool state);

public:
    // Override the event notify function.
    virtual void notifyKeysPressDown(int id);

    // Get LED state
    void lightStateGet(uint16_t index, bool &state);

private:
    LightControlScreenPresenter();

    LightControlScreenView& view;
};

#endif // LIGHTCONTROLSCREENPRESENTER_HPP
