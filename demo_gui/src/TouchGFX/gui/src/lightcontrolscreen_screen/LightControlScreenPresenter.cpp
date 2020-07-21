#include <gui/lightcontrolscreen_screen/LightControlScreenView.hpp>
#include <gui/lightcontrolscreen_screen/LightControlScreenPresenter.hpp>

LightControlScreenPresenter::LightControlScreenPresenter(LightControlScreenView& v)
    : view(v)
{

}

void LightControlScreenPresenter::activate()
{

}

void LightControlScreenPresenter::deactivate()
{

}

void LightControlScreenPresenter::lightButtonClicked(uint16_t index, bool state)
{
    model->setLedState(index, state);
}

void LightControlScreenPresenter::lightStateGet(uint16_t index, bool &state)
{
    model->getLedState(index, state);
}

void LightControlScreenPresenter::notifyKeysPressDown(int id)
{
    bool state;

    model->getLedState(id, state);
    state = (state) ? 0 : 1;

    view.notifyLightViewChanged(id, state);
}
