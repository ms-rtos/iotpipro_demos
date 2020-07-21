#include <gui/mainscreen_screen/MainScreenView.hpp>
#include <gui/mainscreen_screen/MainScreenPresenter.hpp>

MainScreenPresenter::MainScreenPresenter(MainScreenView& v)
    : view(v)
{

}

void MainScreenPresenter::activate()
{

}

void MainScreenPresenter::deactivate()
{

}

void MainScreenPresenter::notifyTemperatureChanged(int newTemperature)
{
    view.updateTemperatureUI(newTemperature);
}

void MainScreenPresenter::notifyHumidityChanged(int newHumidity)
{
    view.updateHumidityUI(newHumidity);
}

void MainScreenPresenter::notifyLightChanged(int newLight)
{
    view.updateLightUI(newLight);
}

void MainScreenPresenter::getTemperature(int &temperature)
{
    temperature = model->getCurrentTemperature();
}

void MainScreenPresenter::getHumidity(int &humidity)
{
    humidity = model->getCurrentHumidity();
}

void MainScreenPresenter::getLight(int &light)
{
    light = model->getCurrentLight();
}
