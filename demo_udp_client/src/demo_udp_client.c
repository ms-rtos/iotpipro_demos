/*
 * Copyright (c) 2015-2020 ACOINFO Co., Ltd.
 * All rights reserved.
 *
 * Detailed license information can be found in the LICENSE file.
 *
 * File: demo_udp.c UDP ECHO client application demo.
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
    int sockfd;
    struct sockaddr_in sockaddr_remote;
    socklen_t sockaddr_len;
    int ret;

    sockaddr_len = sizeof(struct sockaddr_in);

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
        ms_printf("Failed to create UDP socket, errno = %d!\n", errno);
        return  (-1);
    }

    /*
     * Binding operations must be performed in the case of multiple network CARDS
     */
    struct sockaddr_in sockaddr_local;

    memset(&sockaddr_local, 0, sizeof(sockaddr_local));
    sockaddr_local.sin_len         = sizeof(struct sockaddr_in);
    sockaddr_local.sin_family      = AF_INET;
    sockaddr_local.sin_addr.s_addr = inet_addr(LOCAL_BIND_IP);
    sockaddr_local.sin_port        = htons(LOCAL_BIND_PORT);

    ret = bind(sockfd, (struct sockaddr *)&sockaddr_local, sizeof(sockaddr_local));
    if (ret < 0) {
        ms_printf("Failed to bind port %d, errno = %d!\n", LOCAL_BIND_PORT, errno);
        close(sockfd);
        return  (-1);
    }

    memset(&sockaddr_remote, 0, sizeof(sockaddr_remote));
    sockaddr_remote.sin_len         = sizeof(struct sockaddr_in);
    sockaddr_remote.sin_family      = AF_INET;
    sockaddr_remote.sin_addr.s_addr = inet_addr(REMOVE_SERVER_IP);
    sockaddr_remote.sin_port        = htons(REMOVE_SERVER_PORT);

    ms_printf("UDP echo client start.\n");

    while (1) {
        ssize_t ret_size;

        ret_size = sendto(sockfd, "Hello, MS-RTOS!\n", sizeof("Hello, MS-RTOS!\n"),
                          0, (struct sockaddr *)&sockaddr_remote, sockaddr_len);
        if (ret_size <= 0) {
            if ((errno != ETIMEDOUT) && (errno != EWOULDBLOCK)) {
                ms_printf("Failed to sendto UDP echo server, errno = %d!\n", errno);
                 close(sockfd);
                 return  (-1);
            }

            continue;
        }

        ret_size = recvfrom(sockfd, receive_buf, (TEST_BUF_SIZE - 1),
                            0, (struct sockaddr *)&sockaddr_remote, &sockaddr_len);
        if (ret_size <= 0) {
            if ((errno != ETIMEDOUT) &&(errno != EWOULDBLOCK)) {
                ms_printf("Failed to recvfrom UDP echo server, errno = %d!\n", errno);
                 close(sockfd);
                 return  (-1);
            }

            continue;
        }

        receive_buf[ret_size] = '\0';
        ms_printf("[recv data]: %s\n", receive_buf);
    }

    return  (0);
}
