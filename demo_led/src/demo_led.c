/*
 * Copyright (c) 2015-2020 ACOINFO Co., Ltd.
 * All rights reserved.
 *
 * Detailed license information can be found in the LICENSE file.
 *
 * File: demo_led.c LED and KEY application demo.
 *
 * Author: Yu.kangzhi <yukangzhi@acoinfo.com>
 *
 */

#include <ms_rtos.h>

int main (int argc, char **argv)
{
    fd_set rfds;
    struct timeval tv;
    ms_gpio_param_t param;
    ms_uint8_t led1_val = 0xff;
    ms_uint8_t led2_val = 0xff;
    ms_uint8_t led3_val = 0xff;

    int led1 = ms_io_open("/dev/led1", O_WRONLY, 0666);
    int led2 = ms_io_open("/dev/led2", O_WRONLY, 0666);
    int led3 = ms_io_open("/dev/led3", O_WRONLY, 0666);

    int key1 = ms_io_open("/dev/key1", O_WRONLY, 0666);
    int key2 = ms_io_open("/dev/key2", O_WRONLY, 0666);
    int key3 = ms_io_open("/dev/key3", O_WRONLY, 0666);

    if ((led1 < 0) || (led2 < 0) || (led3 < 0) ||
        (key1 < 0) || (key2 < 0) || (key3 < 0) ) {
        ms_printf("Failed to open led and key devices!\n");
        return  (-1);
    }

    param.mode  = MS_GPIO_MODE_OUTPUT_PP;
    param.pull  = MS_GPIO_PULL_UP;
    param.speed = MS_GPIO_SPEED_HIGH;
    ms_io_ioctl(led1, MS_GPIO_CMD_SET_PARAM, &param);
    ms_io_ioctl(led2, MS_GPIO_CMD_SET_PARAM, &param);
    ms_io_ioctl(led3, MS_GPIO_CMD_SET_PARAM, &param);

    param.mode  = MS_GPIO_MODE_IRQ_FALLING;
    param.pull  = MS_GPIO_PULL_UP;
    param.speed = MS_GPIO_SPEED_HIGH;
    ms_io_ioctl(key1, MS_GPIO_CMD_SET_PARAM, &param);
    ms_io_ioctl(key2, MS_GPIO_CMD_SET_PARAM, &param);
    ms_io_ioctl(key3, MS_GPIO_CMD_SET_PARAM, &param);

    while (1) {
        FD_ZERO(&rfds);
        FD_SET(key1, &rfds);
        FD_SET(key2, &rfds);
        FD_SET(key3, &rfds);

        tv.tv_sec  = 10;
        tv.tv_usec = 0;

        if (select(key3 + 1, &rfds, MS_NULL, MS_NULL, &tv) > 0) {
            if (FD_ISSET(key1, &rfds)) {
                ms_io_write(led1, &led1_val, sizeof(led1_val));
                led1_val = ~led1_val;
                ms_printf("key1 press.\n");
            }

            if (FD_ISSET(key2, &rfds)) {
                ms_io_write(led2, &led2_val, sizeof(led2_val));
                led2_val = ~led2_val;
                ms_printf("key2 press.\n");
            }

            if (FD_ISSET(key3, &rfds)) {
                ms_io_write(led3, &led3_val, sizeof(led3_val));
                led3_val = ~led3_val;
                ms_printf("key3 press.\n");
            }
        } else {
            ms_printf("timeout!\n");
        }
    }

    return  (0);
}
