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
#include "sensor/ms_drv_ap3216c.h"
#include "sensor/ms_drv_ahtxx.h"

#define SENSOR_AP3216C_DEV_NAME     "/dev/ap3216c"

int main (int argc, char **argv)
{
    int fd;
    int test_count;
    ms_uint32_t ir_val, als_val, ps_val;
    ms_sensor_data_t sensor_data[3];

    test_count = 10;

    fd = ms_io_open(SENSOR_AP3216C_DEV_NAME, O_RDWR, 0666);
    if (fd > 0) {
        while (--test_count) {
            memset(sensor_data, 0, sizeof(sensor_data));

            sensor_data[0].type = MS_SENSOR_TYPE_IR;
            sensor_data[1].type = MS_SENSOR_TYPE_LIGHT;
            sensor_data[2].type = MS_SENSOR_TYPE_PROXIMITY;

            if (ms_io_read(fd, sensor_data, sizeof(sensor_data)) > 0) {
                ir_val  = sensor_data[0].u.ir;
                ps_val  = sensor_data[1].u.proximity;
                als_val = sensor_data[2].u.light;

                ms_printf("[data]: ir: 0x%08X, ps: 0x%08X, als: 0x%08X\n", ir_val, ps_val, als_val);
            } else {
                ms_printf("Failed to read sensor data!\n");
                break;
            }
        }

        ms_io_close(fd);

    } else {
        ms_printf("Failed to open device %s!\n", SENSOR_AP3216C_DEV_NAME);
    }

    return  (0);
}
