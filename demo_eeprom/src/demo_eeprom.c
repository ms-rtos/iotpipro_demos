/*
 * Copyright (c) 2015-2020 ACOINFO Co., Ltd.
 * All rights reserved.
 *
 * Detailed license information can be found in the LICENSE file.
 *
 * File: demo_eeprom.c EEPROM application demo.
 *
 * Author: Yu.kangzhi <yukangzhi@acoinfo.com>
 *
 */

#include <ms_rtos.h>

#define EEPROM_DEV_NAME     "/dev/eeprom"
#define TEST_BUF_SIZE       (16)

static ms_uint8_t           test_buf[TEST_BUF_SIZE];

int main (int argc, char **argv)
{
    ms_eeprom_msg_t msg;
    int fd;
    int i;

    fd = ms_io_open(EEPROM_DEV_NAME, O_RDWR, 0666);
    if (fd < 0) {
        ms_printf("Failed to open %s!\n", EEPROM_DEV_NAME);
        return  (-1);
    }

    msg.memaddr = 0;
    msg.buf     = test_buf;
    msg.len     = sizeof(test_buf);
    memset(test_buf, 0xab, sizeof(test_buf));

    if (ms_io_write(fd, &msg, sizeof(msg)) == sizeof(msg)) {
        ms_printf("EEPROM write ok.\n");
    } else {
        ms_printf("EEPROM write failed!\n");
    }

    msg.memaddr = 0;
    msg.buf     = test_buf;
    msg.len     = sizeof(test_buf);
    memset(test_buf, 0, sizeof(test_buf));

    if (ms_io_read(fd, &msg, sizeof(msg)) == sizeof(msg)) {
        ms_printf("EEPROM read ok.\n");
    } else {
        ms_printf("EEPROM read failed!\n");
    }

    for (i = 0; i < sizeof(test_buf); i++) {
        if (test_buf[i] != 0xab) {
            break;
        }
    }

    if (i == sizeof(test_buf)) {
        ms_printf("EEPROM compare ok.\n");
    } else {
        ms_printf("EEPROM compare failed at %d!\n", i);
    }

    ms_io_close(fd);

    return  (0);
}
