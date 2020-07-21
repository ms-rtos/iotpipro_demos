/*
 * Copyright (c) 2015-2020 ACOINFO Co., Ltd.
 * All rights reserved.
 *
 * Detailed license information can be found in the LICENSE file.
 *
 * File: demo_sensor.c AHT20 and AP3216C sensor application demo.
 *
 * Author: Yu.kangzhi <yukangzhi@acoinfo.com>
 *
 */

#include <ms_rtos.h>
#include "sensor/ms_drv_sensor.h"
#include "sensor/ms_drv_ahtxx.h"

#define SENSOR_AHT20_DEV_NAME       "/dev/ath20"

int main (int argc, char **argv)
{
    int fd;
    int test_count;
    double hum_rate, tem_rate;
    ms_sensor_data_t sensor_data[2];

    test_count = 10;

    fd = ms_io_open(SENSOR_AHT20_DEV_NAME, O_RDWR, 0666);
    if (fd > 0) {

        while (--test_count) {
            memset(sensor_data, 0, sizeof(sensor_data));

            sensor_data[0].type = MS_SENSOR_TYPE_TEMP;
            sensor_data[1].type = MS_SENSOR_TYPE_HUMI;

            if (ms_io_read(fd, sensor_data, sizeof(sensor_data)) > 0) {
                tem_rate = sensor_data[0].u.temp;
                hum_rate = sensor_data[1].u.humi;

                ms_printf("[data]: hum_rate: %f, tem_rate: %f\n\r", hum_rate, tem_rate);
            } else {
                ms_printf("Failed to read sensor data.\n");
                break;
            }
        }

        ms_io_close(fd);
    } else {
        ms_printf("Failed to open device file %s.\n", SENSOR_AHT20_DEV_NAME);
    }

    return  (0);
}
