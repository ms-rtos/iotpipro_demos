/*
 * Copyright (c) 2015-2020 ACOINFO Co., Ltd.
 * All rights reserved.
 *
 * Detailed license information can be found in the LICENSE file.
 *
 * File: demo_tcp.c TCP ECHO client application demo.
 *
 * Author: Yu.kangzhi <yukangzhi@acoinfo.com>
 *
 */

#include <ms_rtos.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#define LOCAL_BIND_IP           "10.6.253.242"
#define LOCAL_BIND_PORT         (8100)

#define REMOVE_SERVER_IP        "10.6.253.243"
#define REMOVE_SERVER_PORT      (8101)

#define TEST_BUF_SIZE           (256)

static char receive_buf[TEST_BUF_SIZE];

int main (int argc, char **argv)
{
    int ret;
    int sockfd;
    struct sockaddr_in sockaddr;
    struct sockaddr_in sockaddr_local;

    sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0) {
        ms_printf("Failed to create TCP socket, errno = %d!\n", errno);
        return  (-1);
    }

    /*
     * Binding operations must be performed in the case of multiple network CARDS
     */
    memset(&sockaddr_local, 0, sizeof(sockaddr_local));
    sockaddr_local.sin_len         = sizeof(struct sockaddr_in);
    sockaddr_local.sin_family      = AF_INET;
    sockaddr_local.sin_addr.s_addr = inet_addr(LOCAL_BIND_IP);
    sockaddr_local.sin_port        = htons(LOCAL_BIND_PORT);

    ret = bind(sockfd, (struct sockaddr *)&sockaddr_local, sizeof(sockaddr_local));
    if (ret < 0) {
        close(sockfd);
        ms_printf("Failed to bind port %d, errno = %d!\n", LOCAL_BIND_PORT, errno);
        return  (-1);
    }

    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_len         = sizeof(struct sockaddr_in);
    sockaddr.sin_family      = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(REMOVE_SERVER_IP);
    sockaddr.sin_port        = htons(REMOVE_SERVER_PORT);

    if (connect(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) == -1) {
        close(sockfd);
        ms_printf("Failed to connect TCP server, errno = %d\n", errno);
        return  (-1);
    }

    ms_printf("TCP echo client connect server success.\n");

    while (1) {
        ssize_t len;

        len = write(sockfd, "Hello, MS-RTOS!\n", sizeof("Hello, MS-RTOS!\n"));
        if (len <= 0) {
            if ((errno != ETIMEDOUT) && (errno != EWOULDBLOCK)) {
                close(sockfd);
                ms_printf("Failed to write to TCP server, errno = %d\n", errno);
                return  (-1);
            }

            continue;
        }

        len = read(sockfd, receive_buf, (TEST_BUF_SIZE - 1));
        if (len > 0) {
            receive_buf[len] = 0;
            ms_printf("[recv data]: %s\n", receive_buf);
        }
    }

    close(sockfd);

    return  (0);
}
