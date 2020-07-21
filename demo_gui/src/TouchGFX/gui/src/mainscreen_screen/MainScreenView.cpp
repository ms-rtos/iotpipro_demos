#include <gui/mainscreen_screen/MainScreenView.hpp>

MainScreenView::MainScreenView()
{

}

void MainScreenView::setupScreen()
{
    /*
     * These three button cannot be clicked.
     */
    buttonWithIconTemp.setTouchable(0);
    buttonWithIconHum.setTouchable(0);
    buttonWithIconLight.setTouchable(0);

    /*
     * Read data from model with presenter.
     */
    presenter->getTemperature(data_temp);
    presenter->getHumidity(data_humi);
    presenter->getLight(data_light);

    /*
     * Update desktop screen
     */
    Unicode::snprintf(textAreaTempValueBuffer, TEXTAREATEMPVALUE_SIZE, "%d", data_temp);
    Unicode::snprintf(textAreaHumValueBuffer, TEXTAREAHUMVALUE_SIZE, "%d", data_humi);
    Unicode::snprintf(textAreaLightValueBuffer, TEXTAREALIGHTVALUE_SIZE, "%d", data_light);
}

void MainScreenView::tearDownScreen()
{
    MainScreenViewBase::tearDownScreen();
}

void MainScreenView::updateTemperatureUI(int val)
{
    data_temp = val;
    Unicode::snprintf(textAreaTempValueBuffer, TEXTAREATEMPVALUE_SIZE, "%d", val);
    textAreaTempValue.invalidate();
}

void MainScreenView::updateHumidityUI(int val)
{
    data_humi = val;
    Unicode::snprintf(textAreaHumValueBuffer, TEXTAREAHUMVALUE_SIZE, "%d", val);
    textAreaHumValue.invalidate();
}

void MainScreenView::updateLightUI(int val)
{
    data_light = val;
    Unicode::snprintf(textAreaLightValueBuffer, TEXTAREALIGHTVALUE_SIZE, "%d", val);
    textAreaLightValue.invalidate();
}
