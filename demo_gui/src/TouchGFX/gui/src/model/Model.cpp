#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

using namespace touchgfx_msrtos;

Model::Model() : modelListener(0)
{
    System::system_service_init();

    currentTemperature = 0;
    currentHumidity = 0;
    currentLight = 0;

    System::system_service_channel_query(SYSTEM_SERVICE_TYPE_LED, &ledsNumber);
    System::system_service_channel_query(SYSTEM_SERVICE_TYPE_KEYBOARD, &keysNumber);

    currentKeysState = (uint32_t *)malloc(keysNumber * sizeof(uint32_t));
    if (currentKeysState) {
        uint32_t i;
        for (i = 0; i < keysNumber; i++) {
            System::system_service_val_get(SYSTEM_SERVICE_TYPE_KEYBOARD, i, &currentKeysState[i]);
        }
    }
}

Model::~Model()
{
    System::system_service_deinit();

    if (currentKeysState) {
        free(currentKeysState);
    }
}

void Model::tick()
{
    if (modelListener != 0) {
        uint32_t temp;
        uint32_t humi;
        uint32_t light;

        System::system_service_val_get(SYSTEM_SERVICE_TYPE_TEMPERATURE, 0, &temp);
        System::system_service_val_get(SYSTEM_SERVICE_TYPE_HUMIDITY, 0, &humi);
        System::system_service_val_get(SYSTEM_SERVICE_TYPE_LIGHT, 0, &light);

        if (temp != currentTemperature) {
            currentTemperature = temp;
            modelListener->notifyTemperatureChanged(currentTemperature);
            System::system_sddc_notify(SYSTEM_NOTIFY_TYPE_TEMPERATURE, 0, currentTemperature);
        }

        if (humi != currentHumidity) {
            currentHumidity = humi;
            modelListener->notifyHumidityChanged(currentHumidity);
        }

        if (light != currentLight) {
            currentLight = light;
            modelListener->notifyLightChanged(currentLight);
        }

        if (currentKeysState) {
            uint32_t state;
            uint32_t i;
            for (i = 0; i < keysNumber; i++) {
                System::system_service_val_get(SYSTEM_SERVICE_TYPE_KEYBOARD, i, &state);
                if (currentKeysState[i] == 1 && state == 0) {
                    modelListener->notifyKeysPressDown((i + 1));
                }
                currentKeysState[i] = state;
            }
        }
    }
}

void Model::setLedState(uint16_t index, bool state)
{
    index = index - 1;
    if (index < ledsNumber) {
        System::system_service_val_set(SYSTEM_SERVICE_TYPE_LED, index, state);
        System::system_sddc_notify(SYSTEM_NOTIFY_TYPE_LED, index, state);
    }
}

void Model::getLedState(uint16_t index, bool &state)
{
    index = index - 1;
    if (index < ledsNumber) {
        uint32_t value;
        System::system_service_val_get(SYSTEM_SERVICE_TYPE_LED, index, &value);
        state = (value == 0) ? 0 : 1;
    }
}
