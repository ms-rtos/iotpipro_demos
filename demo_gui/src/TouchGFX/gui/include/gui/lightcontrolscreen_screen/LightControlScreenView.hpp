#ifndef LIGHTCONTROLSCREENVIEW_HPP
#define LIGHTCONTROLSCREENVIEW_HPP

#include <gui_generated/lightcontrolscreen_screen/LightControlScreenViewBase.hpp>
#include <gui/lightcontrolscreen_screen/LightControlScreenPresenter.hpp>

class LightControlScreenView : public LightControlScreenViewBase
{
public:
    LightControlScreenView();
    virtual ~LightControlScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void notifyLightViewChanged(int id, bool state);
protected:
    virtual void actionLedClicked(uint32_t value);
};

#endif // LIGHTCONTROLSCREENVIEW_HPP
