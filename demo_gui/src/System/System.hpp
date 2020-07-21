/*
 * Copyright (c) 2015-2020 ACOINFO Co., Ltd.
 * All rights reserved.
 *
 * Detailed license information can be found in the LICENSE file.
 *
 * File: System.hpp TOUCHGFX system interface.
 *
 * Author: Yu.Kangzhi <yukangzhi@acoinfo.com>
 *
 */

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <ms_rtos.h>
#include "sddc.h"

#define SYSTEM_BOARD_LED_NUM    (3)
#define SYSTEM_BOARD_KEY_NUM    (3)

namespace touchgfx_msrtos
{
/**
 * @typedef enum system service type.
 *
 * @brief Enum for the system service type.
 */
typedef enum
{
    SYSTEM_SERVICE_TYPE_TEMPERATURE,
    SYSTEM_SERVICE_TYPE_HUMIDITY,
    SYSTEM_SERVICE_TYPE_LIGHT,
    SYSTEM_SERVICE_TYPE_LED,
    SYSTEM_SERVICE_TYPE_KEYBOARD,
    SYSTEM_SERVICE_TYPE_MAX,
} SystemServiceType;

/**
 * @typedef enum system service type.
 *
 * @brief Enum for the system service type.
 */
typedef enum
{
    SYSTEM_NOTIFY_TYPE_TEMPERATURE,
    SYSTEM_NOTIFY_TYPE_HUMIDITY,
    SYSTEM_NOTIFY_TYPE_LIGHT,
    SYSTEM_NOTIFY_TYPE_LED,
    SYSTEM_NOTIFY_TYPE_KEYBOARD,
    SYSTEM_NOTIFY_TYPE_MAX,
} SystemNotifyType;

/**
 * @class SYSTEM System.hpp touchgfx/hal/System.hpp
 *
 * @brief Interface class for manipulating system service of MS-RTOS.
 */
class System
{
public:
    static void system_service_init(void);
    static void system_service_deinit(void);

    /**
     * @fn void System::system_service_channel_query();
     *
     * @brief Query the service channel number.
     */
    static void system_service_channel_query(SystemServiceType t, uint32_t *channel_num);

    /**
     * @fn void System::system_service_val_get();
     *
     * @brief Get the system service value.
     */
    static void system_service_val_get(SystemServiceType t, uint32_t channel, uint32_t *value);

    /**
     * @fn void System::system_service_val_set();
     *
     * @brief Set the system service value.
     */
    static void system_service_val_set(SystemServiceType t, uint32_t channel, uint32_t value);

    /**
     * @fn void System::system_service_thread();
     *
     * @brief System service thread.
     */
    static void system_service_thread(ms_ptr_t arg);

    /**
     * @fn void System::system_sddc_thread();
     *
     * @brief System SDDC service thread.
     */
    static void system_sddc_thread(ms_ptr_t arg);

    /**
     * @fn void System::system_sddc_notify();
     *
     * @brief Notify the remote system.
     */
    static void system_sddc_notify(SystemNotifyType t, uint32_t channel, uint32_t state);

private:
    /**
     * @brief service fds.
     */
    static ms_handle_t thread_service_tid;
    static ms_handle_t thread_sddc_tid;
    static int led_fd[SYSTEM_BOARD_LED_NUM];
    static int key_fd[SYSTEM_BOARD_LED_NUM];
    static int aht20_fd;
    static int ap3216c_fd;

    /**
     * @brief SDDC service handle.
     */
    static int sockfd;
    static sddc_t *sddc;

    /**
     * @brief led and key state.
     */
    static int leds_state[SYSTEM_BOARD_LED_NUM];

    /**
     * @brief service value.
     */
    static int tem_rate;
    static int hum_rate;
    static int light_ir, light_als, light_ps;

    static int ref_count;
}; // class SYSTEM
} // namespace touchgfx_msrtos

#endif /* SYSTEM_HPP */
