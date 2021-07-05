
#include <ms_rtos.h>
#include <stdio.h>
#include <string.h>
#include "system.h"
#include "sddc.h"
#include "sensor/ms_drv_sensor.h"
#include "sddc.h"
#include "cJSON.h"
#include "ms_lvgl_async_event.h"

static int led_fd[SYSTEM_BOARD_LED_NUM];
static int key_fd[SYSTEM_BOARD_KEY_NUM];
static int aht20_fd;
static int ap3216c_fd;
static int sockfd;
static int tem_rate;
static int hum_rate;
static int light_ir, light_als, light_ps;

static lv_ui *ui;
static sddc_t *sddc;

int leds_state[SYSTEM_BOARD_LED_NUM];

/**
 * @fn void system_service_val_get();
 *
 * @brief Get the system service value.
 */
int system_service_val_get(SystemServiceType t, uint32_t channel, uint32_t *value)
{
    sddc_return_value_if_fail(value, -1);

    *value = 0;

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
        sddc_return_value_if_fail(channel < SYSTEM_BOARD_LED_NUM, -1);
        *value = leds_state[channel];
        break;

    case SYSTEM_SERVICE_TYPE_KEYBOARD:
        sddc_return_value_if_fail(channel < SYSTEM_BOARD_KEY_NUM, -1);
        {
            ms_uint8_t key_val;
            ms_io_read(key_fd[channel], &key_val, sizeof(key_val));
            *value = key_val;
        }
        break;

    default:
        return -1;
    }

    return 0;
}

/**
 * @fn void system_service_val_set();
 *
 * @brief Set the system service value.
 */
int system_service_val_set(SystemServiceType t, uint32_t channel, uint32_t value)
{
    if (t == SYSTEM_SERVICE_TYPE_LED) {
        ms_uint8_t led_val;

        sddc_return_value_if_fail(channel < SYSTEM_BOARD_LED_NUM, -1);

        leds_state[channel] = value;
        led_val = !value;
        ms_io_write(led_fd[channel], &led_val, sizeof(led_val));
    }

    return 0;
}

/**
 * @fn void system_sddc_notify();
 *
 * @brief Notify the remote system.
 */
int system_sddc_notify(SystemNotifyType t, uint32_t channel, uint32_t state)
{
    cJSON *root;
    char *str;
    char name[32];

    root = cJSON_CreateObject();
    sddc_return_value_if_fail(root, -1);

    switch (t) {
    case SYSTEM_NOTIFY_TYPE_TEMPERATURE:
        cJSON_AddNumberToObject(root, "temperature", state);
        break;

    case SYSTEM_NOTIFY_TYPE_HUMIDITY:
        cJSON_AddNumberToObject(root, "humidity", state);
        break;

    case SYSTEM_NOTIFY_TYPE_LIGHT:
        cJSON_AddNumberToObject(root, "light", state);
        break;

    case SYSTEM_NOTIFY_TYPE_LED:
        ms_snprintf(name, sizeof(name), "led%u", (unsigned)channel + 1);
        cJSON_AddBoolToObject(root, name, (ms_bool_t)state);
        break;

    case SYSTEM_NOTIFY_TYPE_KEYBOARD:
        ms_snprintf(name, sizeof(name), "key%u", (unsigned)channel + 1);
        cJSON_AddBoolToObject(root, name, (ms_bool_t)state);
        break;

    default:
        return -1;
    }

    str = cJSON_Print(root);
    sddc_goto_error_if_fail(str);

    sddc_broadcast_message(sddc, str, strlen(str), 1, MS_FALSE, MS_NULL);

    cJSON_free(str);

    return 0;

error:
    cJSON_Delete(root);

    return -1;
}

static void iot_pi_sddc_thread(ms_ptr_t arg)
{
    sddc_t *sddc = arg;

    while (1) {
        ms_printf("SDDC running...\n");

        sddc_run(sddc);

        ms_printf("SDDC quit!\n");
    }
}

void system_sensor_read_task(lv_task_t *task)
{
    ms_sensor_data_t sensor_data[3];

    bzero(sensor_data, sizeof(sensor_data));

    /*
     * Get AHT20 sensor data.
     */
    sensor_data[0].type = MS_SENSOR_TYPE_TEMP;
    sensor_data[1].type = MS_SENSOR_TYPE_HUMI;
    if (ms_io_read(aht20_fd, sensor_data, sizeof(sensor_data)) > 0) {
        tem_rate = sensor_data[0].u.temp;
        hum_rate = sensor_data[1].u.humi;
    } else {
        ms_printf("Failed to read AHT20!\n");
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
        ms_printf("Failed to read AP3216C!\n");
    }

    if (lv_disp_get_scr_act(MS_NULL) == ui->main_screen) {
        char buf[16];

        ms_snprintf(buf, sizeof(buf), "%d'C", tem_rate);
        lv_label_set_text(ui->main_screen_temperature_value, buf);

        ms_snprintf(buf, sizeof(buf), "%d%%", hum_rate);
        lv_label_set_text(ui->main_screen_humidity_value, buf);

        ms_snprintf(buf, sizeof(buf), "%d", light_als);
        lv_label_set_text(ui->main_screen_illumination_value, buf);
    }
}

/*
 * IoT Pi key scan thread
 */
static void iot_pi_key_thread(ms_ptr_t arg)
{
    sddc_t *sddc = arg;
    fd_set  rfds;
    ms_uint8_t key1_press = 0;
    ms_uint64_t key1_press_begin = 0;
    ms_bool_t smart_config = MS_FALSE;
    struct timeval tv;
    struct ifreq ifreq;
    int ret;

    while (1) {
        if (ioctl(sockfd, SIOCGIFADDR, &ifreq) == 0) {
            smart_config = MS_FALSE;
        }

        if (smart_config) {
            FD_ZERO(&rfds);
            FD_SET(key_fd[0], &rfds);

            tv.tv_sec  = 1;
            tv.tv_usec = 0;

            ret = select(key_fd[0] + 1, &rfds, MS_NULL, MS_NULL, &tv);
            if (ret > 0) {
                key1_press++;
                if (key1_press == 1) {
                    key1_press_begin = ms_time_get_ms();

                } else if (key1_press == 3) {
                    key1_press = 0;

                    if ((ms_time_get_ms() - key1_press_begin) < 800) {
                        sddc_printf("Stop smart configure...\n");
                        smart_config = MS_FALSE;
                        ifreq.ifr_flags = 0;
                        ioctl(sockfd, SIOCSIFPFLAGS, &ifreq);
                        continue;
                    }
                }
            } else if (ret == 0) {
                ms_io_write(led_fd[0], &leds_state[0], 1);
                leds_state[0] = !leds_state[0];

                ms_io_write(led_fd[1], &leds_state[1], 1);
                leds_state[1] = !leds_state[1];

                ms_io_write(led_fd[2], &leds_state[2], 1);
                leds_state[2] = !leds_state[2];
            }
        } else {
            FD_ZERO(&rfds);
            FD_SET(key_fd[0], &rfds);
            FD_SET(key_fd[1], &rfds);
            FD_SET(key_fd[2], &rfds);

            ret = select(key_fd[2] + 1, &rfds, MS_NULL, MS_NULL, MS_NULL);
            if (ret > 0) {
                cJSON *root;
                char *str;

                root = cJSON_CreateObject();
                sddc_return_if_fail(root);

                if (FD_ISSET(key_fd[0], &rfds)) {
                    key1_press++;
                    if (key1_press == 1) {
                        key1_press_begin = ms_time_get_ms();

                    } else if (key1_press == 3) {
                        key1_press = 0;

                        if ((ms_time_get_ms() - key1_press_begin) < 800) {
                            sddc_printf("Start smart configure...\n");
                            smart_config = MS_TRUE;

                            leds_state[0] = 0;
                            ms_io_write(led_fd[0], &leds_state[0], 1);
                            leds_state[0] = !leds_state[0];

                            leds_state[1] = 0;
                            ms_io_write(led_fd[1], &leds_state[1], 1);
                            leds_state[1] = !leds_state[1];

                            leds_state[2] = 0;
                            ms_io_write(led_fd[2], &leds_state[2], 1);
                            leds_state[2] = !leds_state[2];

                            ifreq.ifr_flags = 1;
                            ioctl(sockfd, SIOCSIFPFLAGS, &ifreq);

                            cJSON_Delete(root);
                            continue;
                        }
                    }

                    cJSON_AddBoolToObject(root, "key1", MS_TRUE);

                    ms_io_write(led_fd[0], &leds_state[0], 1);
                    leds_state[0] = !leds_state[0];
                    ms_lvgl_async_event_send(ui->light_control_screen_led1_button, LV_EVENT_INSERT, NULL);
                    cJSON_AddBoolToObject(root, "led1", leds_state[0]);
                }

                if (FD_ISSET(key_fd[1], &rfds)) {
                    cJSON_AddBoolToObject(root, "key2", MS_TRUE);

                    ms_io_write(led_fd[1], &leds_state[1], 1);
                    leds_state[1] = !leds_state[1];
                    ms_lvgl_async_event_send(ui->light_control_screen_led2_button, LV_EVENT_INSERT, NULL);
                    cJSON_AddBoolToObject(root, "led2", leds_state[1]);

                    key1_press = 0;
                }

                if (FD_ISSET(key_fd[2], &rfds)) {
                    cJSON_AddBoolToObject(root, "key3", MS_TRUE);

                    ms_io_write(led_fd[2], &leds_state[2], 1);
                    leds_state[2] = !leds_state[2];
                    ms_lvgl_async_event_send(ui->light_control_screen_led3_button, LV_EVENT_INSERT, NULL);
                    cJSON_AddBoolToObject(root, "led3", leds_state[2]);

                    key1_press = 0;
                }

                str = cJSON_Print(root);
                sddc_return_if_fail(str);

                sddc_broadcast_message(sddc, str, strlen(str), 1, MS_FALSE, MS_NULL);
                cJSON_free(str);

                cJSON_Delete(root);
            }
        }
    }
}

/*
 * Report IoT Pi led state
 */
static int iot_pi_led_state_report(sddc_t *sddc, const uint8_t *uid)
{
    cJSON *root;
    char *str;
    uint32_t led_state;

    root = cJSON_CreateObject();
    sddc_return_value_if_fail(root, -1);

    system_service_val_get(SYSTEM_SERVICE_TYPE_LED, 0, &led_state);
    cJSON_AddBoolToObject(root, "led1", (ms_bool_t)led_state);

    system_service_val_get(SYSTEM_SERVICE_TYPE_LED, 1, &led_state);
    cJSON_AddBoolToObject(root, "led2", (ms_bool_t)led_state);

    system_service_val_get(SYSTEM_SERVICE_TYPE_LED, 2, &led_state);
    cJSON_AddBoolToObject(root, "led3", (ms_bool_t)led_state);

    str = cJSON_Print(root);
    sddc_goto_error_if_fail(str);

    sddc_send_message(sddc, uid, str, strlen(str), 1, MS_FALSE, MS_NULL);
    cJSON_free(str);

    cJSON_Delete(root);

    return 0;

error:
    cJSON_Delete(root);

    return -1;
}

/*
 * Handle MESSAGE
 */
static sddc_bool_t iot_pi_on_message(sddc_t *sddc, const uint8_t *uid, const char *message, ms_size_t len)
{
    cJSON *root = cJSON_Parse(message);
    cJSON *led;
    char *str;

    sddc_return_value_if_fail(root, SDDC_TRUE);

    str = cJSON_Print(root);
    sddc_goto_error_if_fail(str);

    sddc_printf("iot_pi_on_message: %s\n", str);
    cJSON_free(str);

    led = cJSON_GetObjectItem(root, "led1");
    if (cJSON_IsBool(led)) {
        system_service_val_set(SYSTEM_SERVICE_TYPE_LED, 0, cJSON_IsTrue(led));
        ms_lvgl_async_event_send(ui->light_control_screen_led1_button, LV_EVENT_INSERT, NULL);
    }

    led = cJSON_GetObjectItem(root, "led2");
    if (cJSON_IsBool(led)) {
        system_service_val_set(SYSTEM_SERVICE_TYPE_LED, 1, cJSON_IsTrue(led));
        ms_lvgl_async_event_send(ui->light_control_screen_led2_button, LV_EVENT_INSERT, NULL);
    }

    led = cJSON_GetObjectItem(root, "led3");
    if (cJSON_IsBool(led)) {
        system_service_val_set(SYSTEM_SERVICE_TYPE_LED, 2, cJSON_IsTrue(led));
        ms_lvgl_async_event_send(ui->light_control_screen_led3_button, LV_EVENT_INSERT, NULL);
    }

    iot_pi_led_state_report(sddc, uid);

error:
    cJSON_Delete(root);

    return MS_TRUE;
}

/*
 * Handle MESSAGE ACK
 */
static void iot_pi_on_message_ack(sddc_t *sddc, const uint8_t *uid, ms_uint16_t seqno)
{

}

/*
 * Handle MESSAGE lost
 */
static void iot_pi_on_message_lost(sddc_t *sddc, const uint8_t *uid, ms_uint16_t seqno)
{

}

/*
 * Handle EdgerOS lost
 */
static void iot_pi_on_edgeros_lost(sddc_t *sddc, const uint8_t *uid)
{

}

/*
 * Handle UPDATE
 */
static sddc_bool_t iot_pi_on_update(sddc_t *sddc, const uint8_t *uid, const char *update_data, ms_size_t len)
{
    cJSON *root = cJSON_Parse(update_data);
    char *str;

    sddc_return_value_if_fail(root, SDDC_FALSE);

    /*
     * Parse here
     */

    str = cJSON_Print(root);
    sddc_goto_error_if_fail(str);

    sddc_printf("iot_pi_on_update: %s\n", str);
    cJSON_free(str);

    cJSON_Delete(root);

    return SDDC_TRUE;

error:
    cJSON_Delete(root);

    return SDDC_FALSE;
}

/*
 * Handle INVITE
 */
static sddc_bool_t iot_pi_on_invite(sddc_t *sddc, const uint8_t *uid, const char *invite_data, ms_size_t len)
{
    cJSON *root = cJSON_Parse(invite_data);
    char *str;

    sddc_return_value_if_fail(root, SDDC_FALSE);

    /*
     * Parse here
     */

    str = cJSON_Print(root);
    sddc_goto_error_if_fail(str);

    sddc_printf("iot_pi_on_invite: %s\n", str);
    cJSON_free(str);

    cJSON_Delete(root);

    return SDDC_TRUE;

error:
    cJSON_Delete(root);

    return SDDC_FALSE;
}

/*
 * Handle the end of INVITE
 */
static sddc_bool_t iot_pi_on_invite_end(sddc_t *sddc, const uint8_t *uid)
{
    iot_pi_led_state_report(sddc, uid);

    return MS_TRUE;
}

/*
 * Create REPORT data
 */
static char *iot_pi_report_data_create(void)
{
    cJSON *root;
    cJSON *report;
    char *str;

    root = cJSON_CreateObject();
    sddc_return_value_if_fail(root, NULL);

    report = cJSON_CreateObject();
    sddc_return_value_if_fail(report, NULL);

    cJSON_AddItemToObject(root, "report", report);
    cJSON_AddStringToObject(report, "name",   "IoT Pi");
    cJSON_AddStringToObject(report, "type",   "device");
    cJSON_AddBoolToObject(report,   "excl",   SDDC_FALSE);
    cJSON_AddStringToObject(report, "desc",   "翼辉 IoT Pi");
    cJSON_AddStringToObject(report, "model",  "1");
    cJSON_AddStringToObject(report, "vendor", "ACOINFO");

    /*
     * Add extension here
     */

    str = cJSON_Print(root);
    sddc_return_value_if_fail(str, NULL);

    sddc_printf("REPORT DATA: %s\n", str);

    cJSON_Delete(root);

    return str;
}

/*
 * Create INVITE data
 */
static char *iot_pi_invite_data_create(void)
{
    cJSON *root;
    cJSON *report;
    char *str;

    root = cJSON_CreateObject();
    sddc_return_value_if_fail(root, NULL);

    report = cJSON_CreateObject();
    sddc_return_value_if_fail(report, NULL);

    cJSON_AddItemToObject(root, "report", report);
    cJSON_AddStringToObject(report, "name",   "IoT Pi");
    cJSON_AddStringToObject(report, "type",   "device");
    cJSON_AddBoolToObject(report,   "excl",   SDDC_FALSE);
    cJSON_AddStringToObject(report, "desc",   "翼辉 IoT Pi");
    cJSON_AddStringToObject(report, "model",  "1");
    cJSON_AddStringToObject(report, "vendor", "ACOINFO");

    /*
     * Add extension here
     */

    str = cJSON_Print(root);
    sddc_return_value_if_fail(str, NULL);

    sddc_printf("INVITE DATA: %s\n", str);

    cJSON_Delete(root);

    return str;
}

/*
 * Initialize IoT Pi led
 */
static int iot_pi_led_init(void)
{
    ms_gpio_param_t param;
    ms_uint8_t led_val;
    int i;

    led_fd[0]  = ms_io_open("/dev/led1", O_WRONLY, 0666);
    sddc_return_value_if_fail(led_fd[0] >= 0, -1);

    led_fd[1]  = ms_io_open("/dev/led2", O_WRONLY, 0666);
    sddc_return_value_if_fail(led_fd[1] >= 0, -1);

    led_fd[2]  = ms_io_open("/dev/led3", O_WRONLY, 0666);
    sddc_return_value_if_fail(led_fd[2] >= 0, -1);

    led_val     = 1;
    param.mode  = MS_GPIO_MODE_OUTPUT_PP;
    param.pull  = MS_GPIO_PULL_UP;
    param.speed = MS_GPIO_SPEED_HIGH;
    for (i = 0; i < SYSTEM_BOARD_LED_NUM; i++) {
        ms_io_ioctl(led_fd[i], MS_GPIO_CMD_SET_PARAM, &param);
        ms_io_write(led_fd[i], &led_val, sizeof(led_val));
        leds_state[i] = !led_val;
    }

    return 0;
}

/*
 * Initialize IoT Pi key
 */
static int iot_pi_key_init(void)
{
    ms_gpio_param_t param;
    int i;

    key_fd[0]  = ms_io_open("/dev/key1", O_WRONLY, 0666);
    sddc_return_value_if_fail(key_fd[0] >= 0, -1);

    key_fd[1]  = ms_io_open("/dev/key2", O_WRONLY, 0666);
    sddc_return_value_if_fail(key_fd[1] >= 0, -1);

    key_fd[2]  = ms_io_open("/dev/key3", O_WRONLY, 0666);
    sddc_return_value_if_fail(key_fd[2] >= 0, -1);

    /*
     * Set gpio irq mode
     */
    param.mode  = MS_GPIO_MODE_IRQ_FALLING;
    param.pull  = MS_GPIO_PULL_UP;
    param.speed = MS_GPIO_SPEED_HIGH;
    for (i = 0; i < SYSTEM_BOARD_KEY_NUM; i++) {
        ms_io_ioctl(key_fd[i], MS_GPIO_CMD_SET_PARAM, &param);
    }

    return 0;
}

/*
 * Initialize IoT Pi sensor
 */
static int iot_pi_sensor_init(void)
{
    aht20_fd   = ms_io_open("/dev/ath20", O_RDWR, 0666);
    sddc_return_value_if_fail(aht20_fd >= 0, -1);

    ap3216c_fd = ms_io_open("/dev/ap3216c", O_RDWR, 0666);
    sddc_return_value_if_fail(ap3216c_fd >= 0, -1);

    return 0;
}

/*
 * Initialize system service
 */
int system_service_init(lv_ui * guider_ui)
{
    struct ifreq ifreq;
    struct sockaddr_in *psockaddrin = (struct sockaddr_in *)&(ifreq.ifr_addr);
    char *data;
    int ret;

    ui = guider_ui;

    /*
     * Initialize IoT Pi led
     */
    ret = iot_pi_led_init();
    sddc_return_value_if_fail(ret == 0, -1);

    /*
     * Initialize IoT Pi key
     */
    ret = iot_pi_key_init();
    sddc_return_value_if_fail(ret == 0, -1);

    /*
     * Initialize IoT Pi sensor
     */
    ret = iot_pi_sensor_init();
    sddc_return_value_if_fail(ret == 0, -1);

    /*
     * Set network implement
     */
#ifdef SDDC_CFG_NET_IMPL
    ret = ms_net_set_impl(SDDC_CFG_NET_IMPL);
    sddc_return_value_if_fail(ret == MS_ERR_NONE, -1);
#endif

    /*
     * Create SDDC
     */
    sddc = sddc_create(SDDC_CFG_PORT);
    sddc_return_value_if_fail(sddc, -1);

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
     * Set token
     */
#if SDDC_CFG_SECURITY_EN > 0
    ret = sddc_set_token(sddc, "1234567890");
    sddc_return_value_if_fail(ret == 0, -1);
#endif

    /*
     * Set report data
     */
    data = iot_pi_report_data_create();
    sddc_return_value_if_fail(data, -1);
    sddc_set_report_data(sddc, data, strlen(data));

    /*
     * Set invite data
     */
    data = iot_pi_invite_data_create();
    sddc_return_value_if_fail(data, -1);
    sddc_set_invite_data(sddc, data, strlen(data));

    /*
     * Get mac address
     */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    sddc_return_value_if_fail(sockfd >= 0, -1);

    ioctl(sockfd, SIOCGIFHWADDR, &ifreq);

    sddc_printf("MAC addr: %02x:%02x:%02x:%02x:%02x:%02x\n",
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
     * Get and print ip address
     */
    if (ioctl(sockfd, SIOCGIFADDR, &ifreq) == 0) {
        char ip[sizeof("255.255.255.255")];

        inet_ntoa_r(psockaddrin->sin_addr, ip, sizeof(ip));

        sddc_printf("IP addr: %s\n", ip);
    } else {
        sddc_printf("Failed to get IP address, Wi-Fi AP not online!\n");
    }

    /*
     * Create SDDC protocol thread
     */
    ret = ms_thread_create("t_sddc",
                           iot_pi_sddc_thread,
                           sddc,
                           2048U,
                           30U,
                           70U,
                           MS_THREAD_OPT_USER | MS_THREAD_OPT_REENT_EN | MS_THREAD_OPT_FPU_EN,
                           MS_NULL);
    sddc_return_value_if_fail(ret == MS_ERR_NONE, -1);

    /*
     * Create keys scan thread
     */
    ret = ms_thread_create("t_key",
                           iot_pi_key_thread,
                           sddc,
                           2048U,
                           30U,
                           70U,
                           MS_THREAD_OPT_USER | MS_THREAD_OPT_REENT_EN,
                           MS_NULL);
    sddc_return_value_if_fail(ret == MS_ERR_NONE, -1);

    return 0;
}
