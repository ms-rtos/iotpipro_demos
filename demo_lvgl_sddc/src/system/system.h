
#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>
#include "generated/gui_guider.h"

#define SYSTEM_BOARD_LED_NUM    (3)
#define SYSTEM_BOARD_KEY_NUM    (3)

typedef enum {
    SYSTEM_SERVICE_TYPE_TEMPERATURE,
    SYSTEM_SERVICE_TYPE_HUMIDITY,
    SYSTEM_SERVICE_TYPE_LIGHT,
    SYSTEM_SERVICE_TYPE_LED,
    SYSTEM_SERVICE_TYPE_KEYBOARD,
    SYSTEM_SERVICE_TYPE_MAX,
} SystemServiceType;

typedef enum {
    SYSTEM_NOTIFY_TYPE_TEMPERATURE,
    SYSTEM_NOTIFY_TYPE_HUMIDITY,
    SYSTEM_NOTIFY_TYPE_LIGHT,
    SYSTEM_NOTIFY_TYPE_LED,
    SYSTEM_NOTIFY_TYPE_KEYBOARD,
    SYSTEM_NOTIFY_TYPE_MAX,
} SystemNotifyType;

int system_service_init(lv_ui * guider_ui);
int system_service_val_get(SystemServiceType t, uint32_t channel, uint32_t *value);
int system_service_val_set(SystemServiceType t, uint32_t channel, uint32_t value);
int system_sddc_notify(SystemNotifyType t, uint32_t channel, uint32_t state);

void system_sensor_read_task(lv_task_t *task);

extern int leds_state[SYSTEM_BOARD_LED_NUM];

#endif /* SYSTEM_H */
