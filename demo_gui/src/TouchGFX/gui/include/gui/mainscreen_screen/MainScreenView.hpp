#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui_generated/mainscreen_screen/MainScreenViewBase.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class MainScreenView : public MainScreenViewBase
{
public:
    MainScreenView();
    virtual ~MainScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void updateTemperatureUI(int val);
    void updateHumidityUI(int val);
    void updateLightUI(int val);
protected:
    int data_temp, data_humi, data_light;
};

#endif // MAINSCREENVIEW_HPP
