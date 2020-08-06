/*
 * Copyright (c) 2015-2020 ACOINFO Co., Ltd.
 * All rights reserved.
 *
 * Detailed license information can be found in the LICENSE file.
 *
 * File: demo_uart.c UART ECHO application demo.
 *
 * Author: Yu.kangzhi <yukangzhi@acoinfo.com>
 *
 */

#include <ms_rtos.h>
#include <string.h>
#include <driver/ms_drv_uart.h>

#define UART_DEVICE_PATH    "/dev/uart0"

static ms_uint8_t receive_buffer[256];

int main (int argc, char **argv)
{
    int fd, ret;
    ms_uart_param_t param;

    fd = ms_io_open(UART_DEVICE_PATH, O_RDWR | O_NONBLOCK, 0);
    if (fd < 0) {
        ms_printf("Failed to open %s!\n", UART_DEVICE_PATH);
        return  (-1);
    }

    /*
     * Get uart default parameters.
     */
    ret = ms_io_ioctl(fd, MS_UART_CMD_GET_PARAM, &param);
    if (ret < 0) {
        ms_printf("Failed to get uart parameters!\n");
        return  (-1);
    }

    /*
     * Set uart parameters.
     */
    param.baud      = 115200;
    param.data_bits = MS_UART_DATA_BITS_8B;
    param.stop_bits = MS_UART_STOP_BITS_1B;
    param.parity    = MS_UART_PARITY_NONE;
    ret = ms_io_ioctl(fd, MS_UART_CMD_SET_PARAM, &param);
    if (ret < 0) {
        ms_printf("Failed to set uart parameters!\n");
        return  (-1);
    }

    /*
     * Check uart parameters.
     */
    ret = ms_io_ioctl(fd, MS_UART_CMD_GET_PARAM, &param);
    if (ret < 0) {
        ms_printf("Failed to get uart parameters!\n");
        return  (-1);
    }

    ms_printf("uart parameters: baud=%d, data bits=%d, stop bits=%d.\n", param.baud, param.data_bits, param.stop_bits);

    /*
     * Start uart echo service.
     */
    ms_printf("uart echo service start.\n");

    while (1) {
        ms_ssize_t len = ms_io_read(fd, receive_buffer, sizeof(receive_buffer));

        if (len > 0) {
            ms_io_write(fd, receive_buffer, len);

            ms_printf("uart echo %d byte.\n", len);
        }
    }

    ms_io_close(fd);

    return  (0);
}
