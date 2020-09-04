#ifndef MODEL_HPP
#define MODEL_HPP

#include "System.hpp"

class ModelListener;

class Model
{
public:
    Model();
    virtual ~Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    // Function that allow your Presenter to control the led on/off state.
    void setLedState(uint16_t index, bool state);

    // Function that allow your Presenter to control the led on/off state.
    void getLedState(uint16_t index, bool &state);

    // Function that allow your Presenters to read current temperature.
    int getCurrentTemperature() const { return currentTemperature; }

    // Function that allow your Presenters to read current temperature.
    int getCurrentHumidity() const { return currentHumidity; }

    // Function that allow your Presenters to read current temperature.
    int getCurrentLight() const { return currentLight; }

    // Function that allow your Presenter to get the number of LED.
    int getLedsNumber() const { return ledsNumber; }

    // Function that allow your Presenter to get the number of KEY.
    int getKeysNumber() const { return keysNumber; }

public:
    void ledStateChanged(uint32_t channel, uint32_t state);

protected:
    ModelListener* modelListener;

private:
    // Variable storing last received temperature;
    uint32_t currentTemperature;

    // Variable storing last received humidity;
    uint32_t currentHumidity;

    // Variable storing last received light;
    uint32_t currentLight;

    // Variable storing the leds number.
    uint32_t ledsNumber;

    // Variable storing the keys number.
    uint32_t keysNumber;
    uint32_t *currentKeysState;
};

#endif // MODEL_HPP
