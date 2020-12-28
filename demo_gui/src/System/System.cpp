/*
 * Copyright (c) 2015-2020 ACOINFO Co., Ltd.
 * All rights reserved.
 *
 * Detailed license information can be found in the LICENSE file.
 *
 * File: System.cpp TOUCHGFX system interface.
 *
 * Author: Yu.Kangzhi <yukangzhi@acoinfo.com>
 *
 */

#include "System.hpp"
#include "sensor/ms_drv_sensor.h"
#include <stdio.h>
#include <string.h>
#include "sddc.h"
#include "u8x8.h"
#include "ms_u8g2_porting.h"
#include "cJSON.h"

#include "gui/model/Model.hpp"

using namespace touchgfx_msrtos;

/**
 * @brief Constant value define.
 */
int System::ref_count = 0;

/**
 * @brief service thread handle.
 */
ms_handle_t System::thread_service_tid;
ms_handle_t System::thread_sddc_tid;

/**
 * @brief service fds.
 */
int System::led_fd[SYSTEM_BOARD_LED_NUM];
int System::key_fd[SYSTEM_BOARD_KEY_NUM];
int System::aht20_fd;
int System::ap3216c_fd;

/**
 * @brief sddc service handle.
 */
sddc_t* System::sddc;
int System::sockfd;

/**
 * @brief service fds.
 */
int System::leds_state[SYSTEM_BOARD_LED_NUM];

/**
 * @brief service value.
 */
int System::tem_rate;
int System::hum_rate;
int System::light_ir, System::light_als, System::light_ps;

Model* System::data_model;

/**
 * @brief SDDC service functions.
 */
static ms_bool_t iot_pi_on_message(sddc_t *sddc, const uint8_t *uid, const char *message, ms_size_t len);
static void iot_pi_on_message_ack(sddc_t *sddc, const uint8_t *uid, ms_uint16_t seqno);
static void iot_pi_on_message_lost(sddc_t *sddc, const uint8_t *uid, ms_uint16_t seqno);
static void iot_pi_on_edgeros_lost(sddc_t *sddc, const uint8_t *uid);
static ms_bool_t iot_pi_on_update(sddc_t *sddc, const uint8_t *uid, const char *update_data, ms_size_t len);
static ms_bool_t iot_pi_on_invite(sddc_t *sddc, const uint8_t *uid, const char *invite_data, ms_size_t len);
static ms_bool_t iot_pi_on_invite_end(sddc_t *sddc, const uint8_t *uid);
static char *iot_pi_report_data_create(void);
static char *iot_pi_invite_data_create(void);
static void iot_pi_led_state_report(sddc_t *sddc, const uint8_t *uid);

void System::system_service_init(Model *model)
{
    int i;
    ms_uint8_t led_val;
    ms_gpio_param_t param;

    /*
     * System reference count checking
     */
    if (++ref_count != 1) {
        return;
    }

    data_model = model;

    /*
     * System service initialization
     */
    led_fd[0]  = ms_io_open("/dev/led1", O_WRONLY, 0666);
    led_fd[1]  = ms_io_open("/dev/led2", O_WRONLY, 0666);
    led_fd[2]  = ms_io_open("/dev/led3", O_WRONLY, 0666);
    key_fd[0]  = ms_io_open("/dev/key1", O_WRONLY, 0666);
    key_fd[1]  = ms_io_open("/dev/key2", O_WRONLY, 0666);
    key_fd[2]  = ms_io_open("/dev/key3", O_WRONLY, 0666);
    aht20_fd   = ms_io_open("/dev/ath20", O_RDWR, 0666);
    ap3216c_fd = ms_io_open("/dev/ap3216c", O_RDWR, 0666);

    /*
     * LED service initialization
     */
    led_val     = 0xff;
    param.mode  = MS_GPIO_MODE_OUTPUT_PP;
    param.pull  = MS_GPIO_PULL_UP;
    param.speed = MS_GPIO_SPEED_HIGH;
    for (i = 0; i < SYSTEM_BOARD_LED_NUM; i++) {
        if (led_fd[i] > 0) {
            ms_io_ioctl(led_fd[i], MS_GPIO_CMD_SET_PARAM, &param);
            ms_io_write(led_fd[i], &led_val, sizeof(led_val));
            leds_state[i] = 0;
        } else {
            ms_printf("Failed to init led%d!\n", i);
        }
    }

    /*
     * Keyboard service initialization
     */
    param.mode  = MS_GPIO_MODE_IRQ_FALLING;
    param.pull  = MS_GPIO_PULL_UP;
    param.speed = MS_GPIO_SPEED_HIGH;
    for (i = 0; i < SYSTEM_BOARD_KEY_NUM; i++) {
        if (key_fd[i] > 0) {
            ms_io_ioctl(key_fd[i], MS_GPIO_CMD_SET_PARAM, &param);
        } else {
            ms_printf("Failed to init key%d!\n", i);
        }
    }

    /*
     * SDDC service initialization
     */
#ifdef SDDC_CFG_NET_IMPL
    ms_net_set_impl(SDDC_CFG_NET_IMPL);
#endif
    sddc = sddc_create(SDDC_CFG_PORT);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    /*
     * system_service_thread initialization
     */
    ms_thread_create("t_service",
                     system_service_thread,
                     MS_NULL,
                     2048U,
                     4U,
                     70U,
                     MS_THREAD_OPT_USER | MS_THREAD_OPT_REENT_EN,
                     &thread_service_tid);

    /*
     * system_sddc_thread initialization
     */
    ms_thread_create("t_sddc",
                     system_sddc_thread,
                     MS_NULL,
                     2048U,
                     30U,
                     70U,
                     MS_THREAD_OPT_USER | MS_THREAD_OPT_REENT_EN,
                     &thread_sddc_tid);
}

void System::system_service_deinit(void)
{
    if (--ref_count != 0) {
        return;
    }

    if (thread_service_tid != MS_HANDLE_INVALID) {
        int i;

        ms_thread_kill(thread_service_tid);
        ms_io_close(ap3216c_fd);
        ms_io_close(aht20_fd);

        for (i = 0; i < SYSTEM_BOARD_LED_NUM; i++) {
            ms_io_close(led_fd[i]);
        }
    }

    if (thread_sddc_tid != MS_HANDLE_INVALID) {
        ms_thread_kill(thread_sddc_tid);
        sddc_destroy(sddc);
        ms_io_close(sockfd);
    }
}

/**
 * @fn void System::system_sddc_thread();
 *
 * @brief System SDDC service thread.
 */
void System::system_sddc_thread(ms_ptr_t arg)
{
    struct ifreq ifreq;
    struct sockaddr_in *psockaddrin = (struct sockaddr_in *)&(ifreq.ifr_addr);
    char *data;

    /*
     * Set call backs
     */
    sddc_set_on_message(sddc, iot_pi_on_message);
    sddc_set_on_message_ack(sddc, iot_pi_on_message_ack);
    sddc_set_on_message_lost(sddc, iot_pi_on_message_lost);
    sddc_set_on_invite(sddc, iot_pi_on_invite);
    sddc_set_on_invite_end(sddc, iot_pi_on_invite_end);
    sddc_set_on_update(sddc, iot_pi_on_update);
    sddc_set_on_edgeros_lost(sddc, iot_pi_on_edgeros_lost);

    /*
     * Set report data
     */
    data = iot_pi_report_data_create();
    sddc_set_report_data(sddc, data, strlen(data));

    /*
     * Set invite data
     */
    data = iot_pi_invite_data_create();
    sddc_set_invite_data(sddc, data, strlen(data));

    /*
     * Get mac address
     */
    ioctl(sockfd, SIOCGIFHWADDR, &ifreq);

    ms_printf("MAC addr: %02x:%02x:%02x:%02x:%02x:%02x\n",
              (ms_uint8_t)ifreq.ifr_hwaddr.sa_data[0],
              (ms_uint8_t)ifreq.ifr_hwaddr.sa_data[1],
              (ms_uint8_t)ifreq.ifr_hwaddr.sa_data[2],
              (ms_uint8_t)ifreq.ifr_hwaddr.sa_data[3],
              (ms_uint8_t)ifreq.ifr_hwaddr.sa_data[4],
              (ms_uint8_t)ifreq.ifr_hwaddr.sa_data[5]);

    /*
     * Set uid
     */
    sddc_set_uid(sddc, (const ms_uint8_t *)ifreq.ifr_hwaddr.sa_data);

    /*
     * Get ip address
     */
    if (ioctl(sockfd, SIOCGIFADDR, &ifreq) == 0) {
        char ip[sizeof("255.255.255.255")];

        inet_ntoa_r(psockaddrin->sin_addr, ip, sizeof(ip));

        ms_printf("IP addr: %s\n", ip);
    } else {
        ms_printf("Failed to get IP address, WiFi AP not online!\n");
    }

    /*
     * SDDC run
     */
    while (1) {
        ms_printf("SDDC running...\n");

        sddc_run(sddc);

        ms_printf("SDDC quit!\n");
    }
}

/**
 * @fn void System::system_service_thread();
 *
 * @brief System service thread.
 */
void System::system_service_thread(ms_ptr_t arg)
{
    ms_sensor_data_t sensor_data[3];

    while (1) {
        memset(sensor_data, 0, sizeof(sensor_data));

        /*
         * Get AHT20 sensor data.
         */
        sensor_data[0].type = MS_SENSOR_TYPE_TEMP;
        sensor_data[1].type = MS_SENSOR_TYPE_HUMI;
        if (ms_io_read(aht20_fd, sensor_data, sizeof(sensor_data)) > 0) {
            tem_rate = sensor_data[0].u.temp;
            hum_rate = sensor_data[1].u.humi;
        } else {
            ms_printf("[error]: ms_io_read AHT20 failed!\n");
        }

        /*
         * Get AP3216C sensor data.
         */
        sensor_data[0].type = MS_SENSOR_TYPE_IR;
        sensor_data[1].type = MS_SENSOR_TYPE_LIGHT;
        sensor_data[2].type = MS_SENSOR_TYPE_PROXIMITY;
        if (ms_io_read(ap3216c_fd, sensor_data, sizeof(sensor_data)) > 0) {
            light_ir  = sensor_data[0].u.ir;
            light_als = sensor_data[1].u.light;
            light_ps  = sensor_data[2].u.proximity;
        } else {
            ms_printf("[error]: ms_io_read AP3216C failed!\n");
        }

        ms_thread_sleep_ms(100);
    }
}

/**
 * @fn void System::system_service_channel_query();
 *
 * @brief Query the service channel number.
 */
void System::system_service_channel_query(SystemServiceType t, uint32_t *channel_num)
{
    if (channel_num) {
        switch (t) {
        case SYSTEM_SERVICE_TYPE_TEMPERATURE:
            *channel_num = 1;
            break;
        case SYSTEM_SERVICE_TYPE_HUMIDITY:
            *channel_num = 1;
            break;
        case SYSTEM_SERVICE_TYPE_LIGHT:
            *channel_num = 1;
            break;
        case SYSTEM_SERVICE_TYPE_LED:
            *channel_num = SYSTEM_BOARD_LED_NUM;
            break;
        case SYSTEM_SERVICE_TYPE_KEYBOARD:
            *channel_num = SYSTEM_BOARD_KEY_NUM;
            break;
        default:
            *channel_num = 0;
            break;
        }
    }
}

/**
 * @fn void System::system_service_val_get();
 *
 * @brief Get the system service value.
 */
void System::system_service_val_get(SystemServiceType t, uint32_t channel, uint32_t *value)
{
    if (value) {
        switch (t) {
        case SYSTEM_SERVICE_TYPE_TEMPERATURE:
            *value = tem_rate;
            break;
        case SYSTEM_SERVICE_TYPE_HUMIDITY:
            *value = hum_rate;
            break;
        case SYSTEM_SERVICE_TYPE_LIGHT:
            *value = light_als;
            break;
        case SYSTEM_SERVICE_TYPE_LED:
            if (channel < SYSTEM_BOARD_KEY_NUM) {
                *value = leds_state[channel];
            }
            break;
        case SYSTEM_SERVICE_TYPE_KEYBOARD:
            if (channel < SYSTEM_BOARD_KEY_NUM) {
                ms_uint8_t key_val;
                ms_io_read(key_fd[channel], &key_val, sizeof(key_val));
                *value = key_val;
            }
            break;
        default:
            *value = 0;
            break;
        }
    }
}

/**
 * @fn void System::system_service_val_set();
 *
 * @brief Set the system service value.
 */
void System::system_service_val_set(SystemServiceType t, uint32_t channel, uint32_t value)
{
    if (t == SYSTEM_SERVICE_TYPE_LED) {
        ms_uint8_t led_val;

        if (channel < SYSTEM_BOARD_LED_NUM) {
            if (value == 1) {
                leds_state[channel] = 1;
                led_val = 0x00;
                ms_io_write(led_fd[channel], &led_val, sizeof(led_val));
            } else {
                leds_state[channel] = 0;
                led_val = 0xff;
                ms_io_write(led_fd[channel], &led_val, sizeof(led_val));
            }

        }
    }
}

/**
 * @fn void System::system_sddc_notify();
 *
 * @brief Notify the remote system.
 */
void System::system_sddc_notify(SystemNotifyType t, uint32_t channel, uint32_t state)
{
    cJSON *root;
    char *str;
    char name[32];
    uint32_t index;

    root = cJSON_CreateObject();

    index = channel + 1;
	
    switch (t) {
    case SYSTEM_NOTIFY_TYPE_TEMPERATURE:
        snprintf(name, 32, "temperature-%ld", index);
        cJSON_AddNumberToObject(root, name, state);
        break;
    case SYSTEM_NOTIFY_TYPE_HUMIDITY:
        snprintf(name, 32, "humidity-%ld", index);
        cJSON_AddNumberToObject(root, name, state);
        break;
    case SYSTEM_NOTIFY_TYPE_LIGHT:
        snprintf(name, 32, "light-%ld", index);
        cJSON_AddNumberToObject(root, name, state);
        break;
    case SYSTEM_NOTIFY_TYPE_LED:
        snprintf(name, 32, "led%ld", index);
        cJSON_AddBoolToObject(root, name, (ms_bool_t)state);
        break;
    case SYSTEM_NOTIFY_TYPE_KEYBOARD:
        snprintf(name, 32, "keyboard-%ld", index);
        cJSON_AddBoolToObject(root, name, (ms_bool_t)state);
        break;
    default:
        return;
    }

    str = cJSON_Print(root);

    sddc_broadcast_message(sddc, str, strlen(str), 1, MS_FALSE, MS_NULL);

    cJSON_free(str);

    cJSON_Delete(root);
}

/*********************************************************************************************************
 SDDC service functions
*********************************************************************************************************/

static ms_bool_t iot_pi_on_message(sddc_t *sddc, const uint8_t *uid, const char *message, ms_size_t len)
{
    cJSON *root = cJSON_Parse(message);
    cJSON *led;
    cJSON *display;

    char *str = cJSON_Print(root);
    ms_printf("iot_pi_on_message: %s\n", str);
    cJSON_free(str);

    led = cJSON_GetObjectItem(root, "led1");
    if (cJSON_IsBool(led)) {
        if (cJSON_IsTrue(led)) {
            ms_uint8_t on = 1;
            System::system_service_val_set(SYSTEM_SERVICE_TYPE_LED, 0, on);
            System::data_model->ledStateChanged(0, on);
        } else {
            ms_uint8_t off = 0;
            System::system_service_val_set(SYSTEM_SERVICE_TYPE_LED, 0, off);
            System::data_model->ledStateChanged(0, off);
        }
    }

    led = cJSON_GetObjectItem(root, "led2");
    if (cJSON_IsBool(led)) {
        if (cJSON_IsTrue(led)) {
            ms_uint8_t on = 1;
            System::system_service_val_set(SYSTEM_SERVICE_TYPE_LED, 1, on);
            System::data_model->ledStateChanged(1, on);
        } else {
            ms_uint8_t off = 0;
            System::system_service_val_set(SYSTEM_SERVICE_TYPE_LED, 1, off);
            System::data_model->ledStateChanged(1, off);
        }
    }

    led = cJSON_GetObjectItem(root, "led3");
    if (cJSON_IsBool(led)) {
        if (cJSON_IsTrue(led)) {
            ms_uint8_t on = 1;
            System::system_service_val_set(SYSTEM_SERVICE_TYPE_LED, 2, on);
            System::data_model->ledStateChanged(2, on);
        } else {
            ms_uint8_t off = 0;
            System::system_service_val_set(SYSTEM_SERVICE_TYPE_LED, 2, off);
            System::data_model->ledStateChanged(2, off);
        }
    }

    display = cJSON_GetObjectItem(root, "display");
    if (cJSON_IsObject(display)) {
        cJSON *x_number, *y_number, *clr_number;
        cJSON *text;
        ms_uint8_t x = 0, y = 0, clr = 0;

        x_number = cJSON_GetObjectItem(display, "x");
        y_number = cJSON_GetObjectItem(display, "y");

        if (cJSON_IsNumber(x_number)) {
            x = (int)x_number->valuedouble;
        }

        if (cJSON_IsNumber(y_number)) {
            y = (int)y_number->valuedouble;
        }

        //iot_pi_display_pos_set(x, y);
        //TODO:

        text = cJSON_GetObjectItem(display, "text");
        if (cJSON_IsString(text)) {
            //iot_pi_display_puts(text->valuestring);
            //TODO:

        } else {
            clr_number = cJSON_GetObjectItem(display, "clear");
            if (cJSON_IsNumber(clr_number)) {
                int i;

                clr = (int)clr_number->valuedouble;
                for (i = 0; i < clr; i++) {
                    //iot_pi_display_putch(' ');
                    //TODO:
                }
            }
        }
    }

    cJSON_Delete(root);

    iot_pi_led_state_report(sddc, uid);

    return MS_TRUE;
}

static void iot_pi_on_message_ack(sddc_t *sddc, const uint8_t *uid, ms_uint16_t seqno)
{

}

static void iot_pi_on_message_lost(sddc_t *sddc, const uint8_t *uid, ms_uint16_t seqno)
{

}

static void iot_pi_on_edgeros_lost(sddc_t *sddc, const uint8_t *uid)
{

}

static ms_bool_t iot_pi_on_update(sddc_t *sddc, const uint8_t *uid, const char *update_data, ms_size_t len)
{
    cJSON *root = cJSON_Parse(update_data);

    /*
     * Parse here
     */

    char *str = cJSON_Print(root);
    ms_printf("iot_pi_sddc_on_update: %s\n", str);
    cJSON_free(str);

    cJSON_Delete(root);

    return MS_TRUE;
}

static ms_bool_t iot_pi_on_invite(sddc_t *sddc, const uint8_t *uid, const char *invite_data, ms_size_t len)
{
    cJSON *root = cJSON_Parse(invite_data);

    /*
     * Parse here
     */

    char *str = cJSON_Print(root);
    ms_printf("===> iot_pi_on_invite: %s\n", str);
    cJSON_free(str);

    cJSON_Delete(root);

    return MS_TRUE;
}

static ms_bool_t iot_pi_on_invite_end(sddc_t *sddc, const uint8_t *uid)
{
    iot_pi_led_state_report(sddc, uid);

    return MS_TRUE;
}

static char *iot_pi_report_data_create(void)
{
    cJSON *root;
    cJSON *report;
    char *str;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "report", report = cJSON_CreateObject());
        cJSON_AddStringToObject(report, "name",   "IoT Pi");
        cJSON_AddStringToObject(report, "type",   "device");
        cJSON_AddBoolToObject(report,   "excl",   MS_FALSE);
        cJSON_AddStringToObject(report, "desc",   "https://www.edgeros.com/iotpi");
        cJSON_AddStringToObject(report, "model",  "1");
        cJSON_AddStringToObject(report, "vendor", "ACOINFO");

    /*
     * Add extension here
     */

    str = cJSON_Print(root);
    ms_printf("REPORT DATA: %s\n", str);

    cJSON_Delete(root);

    return str;
}

static char *iot_pi_invite_data_create(void)
{
    cJSON *root;
    cJSON *report;
    char *str;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "report", report = cJSON_CreateObject());
        cJSON_AddStringToObject(report, "name",   "IoT Pi");
        cJSON_AddStringToObject(report, "type",   "device");
        cJSON_AddBoolToObject(report,   "excl",   MS_FALSE);
        cJSON_AddStringToObject(report, "desc",   "https://www.edgeros.com/iotpi");
        cJSON_AddStringToObject(report, "model",  "1");
        cJSON_AddStringToObject(report, "vendor", "ACOINFO");

    /*
     * Add extension here
     */

    str = cJSON_Print(root);
    ms_printf("INVITE DATA: %s\n", str);

    cJSON_Delete(root);

    return str;
}

static void iot_pi_led_state_report(sddc_t *sddc, const uint8_t *uid)
{
    cJSON *root;
    char *str;
    uint32_t led_state;

    root = cJSON_CreateObject();

    System::system_service_val_get(SYSTEM_SERVICE_TYPE_LED, 0, &led_state);
    cJSON_AddBoolToObject(root, "led1", (ms_bool_t)led_state);

    System::system_service_val_get(SYSTEM_SERVICE_TYPE_LED, 1, &led_state);
    cJSON_AddBoolToObject(root, "led2", (ms_bool_t)led_state);

    System::system_service_val_get(SYSTEM_SERVICE_TYPE_LED, 2, &led_state);
    cJSON_AddBoolToObject(root, "led3", (ms_bool_t)led_state);

    str = cJSON_Print(root);

    sddc_send_message(sddc, uid, str, strlen(str), 1, MS_FALSE, MS_NULL);

    cJSON_free(str);

    cJSON_Delete(root);
}
