#include <gui/lightcontrolscreen_screen/LightControlScreenView.hpp>
#include "BitmapDatabase.hpp"

LightControlScreenView::LightControlScreenView()
{

}

void LightControlScreenView::setupScreen()
{
    bool state;

    presenter->lightStateGet(1, state);
    toggleButtonLED1.forceState(state);
    if (state) {
        imageLED1.setBitmap(touchgfx::Bitmap(BITMAP_ICON_LED_LIGHT_ID));
    } else {
        imageLED1.setBitmap(touchgfx::Bitmap(BITMAP_ICON_LED_DARK_ID));
    }

    presenter->lightStateGet(2, state);
    toggleButtonLED2.forceState(state);
    if (state) {
        imageLED2.setBitmap(touchgfx::Bitmap(BITMAP_ICON_LED_LIGHT_ID));
    } else {
        imageLED2.setBitmap(touchgfx::Bitmap(BITMAP_ICON_LED_DARK_ID));
    }

    presenter->lightStateGet(3, state);
    toggleButtonLED3.forceState(state);
    if (state) {
        imageLED3.setBitmap(touchgfx::Bitmap(BITMAP_ICON_LED_LIGHT_ID));
    } else {
        imageLED3.setBitmap(touchgfx::Bitmap(BITMAP_ICON_LED_DARK_ID));
    }
}

void LightControlScreenView::tearDownScreen()
{
    LightControlScreenViewBase::tearDownScreen();
}

void LightControlScreenView::actionLedClicked(uint32_t value)
{
    bool state;
    uint32_t button_id = value;
    touchgfx::ToggleButton *button;
    touchgfx::Image *image;

    switch (button_id) {
    case 1:
        button = &toggleButtonLED1;
        image = &imageLED1;
        break;
    case 2:
        button = &toggleButtonLED2;
        image = &imageLED2;
        break;
    case 3:
        button = &toggleButtonLED3;
        image = &imageLED3;
        break;
    default:
        return;
    }

    presenter->lightStateGet(button_id, state);
    state = !state;

    button->forceState(state);
    if (state) {
        image->setBitmap(touchgfx::Bitmap(BITMAP_ICON_LED_LIGHT_ID));
    } else {
        image->setBitmap(touchgfx::Bitmap(BITMAP_ICON_LED_DARK_ID));
    }

    presenter->lightButtonClicked(button_id, state);

    image->invalidate();
}

void LightControlScreenView::notifyLightViewChanged(int id, bool state)
{
    uint32_t button_id = id;
    touchgfx::ToggleButton *button;
    touchgfx::Image *image;

    switch (button_id) {
    case 1:
        button = &toggleButtonLED1;
        image = &imageLED1;
        break;
    case 2:
        button = &toggleButtonLED2;
        image = &imageLED2;
        break;
    case 3:
        button = &toggleButtonLED3;
        image = &imageLED3;
        break;
    default:
        return;
    }

    button->forceState(state);
    if (state) {
        image->setBitmap(touchgfx::Bitmap(BITMAP_ICON_LED_LIGHT_ID));
    } else {
        image->setBitmap(touchgfx::Bitmap(BITMAP_ICON_LED_DARK_ID));
    }

    button->invalidate();
    image->invalidate();
}
