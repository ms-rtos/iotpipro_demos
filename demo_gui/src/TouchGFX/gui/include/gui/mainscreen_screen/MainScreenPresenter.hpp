#ifndef MAINSCREENPRESENTER_HPP
#define MAINSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class MainScreenView;

class MainScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    MainScreenPresenter(MainScreenView& v);

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

    virtual ~MainScreenPresenter() {};

public:
    // Override the event notify function.
    virtual void notifyTemperatureChanged(int newTemperature);
    virtual void notifyHumidityChanged(int newHumidity);
    virtual void notifyLightChanged(int newLight);

    // Get the model data.
    void getTemperature(int &temperature);
    void getHumidity(int &humidity);
    void getLight(int &light);

private:
    MainScreenPresenter();

    MainScreenView& view;
};

#endif // MAINSCREENPRESENTER_HPP
