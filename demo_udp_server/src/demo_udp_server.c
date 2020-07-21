/*
 * Copyright (c) 2015-2020 ACOINFO Co., Ltd.
 * All rights reserved.
 *
 * Detailed license information can be found in the LICENSE file.
 *
 * File: demo_udp.c UDP ECHO server application demo.
 *
 * Author: Yu.kangzhi <yukangzhi@acoinfo.com>
 *
 */

#include <ms_rtos.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#define SERVER_LISTENING_IP         "10.6.253.242"
#define SERVER_LISTENING_PORT       (8100)

#define TEST_BUF_SIZE               (256)
#define IP_ADDR_STR_LEN_MAX         (16)

static char receive_buf[TEST_BUF_SIZE];

int main (int argc, char **argv)
{
    int ret;
    int sockfd;
    struct sockaddr_in sockaddr_local;
    struct sockaddr_in sockaddr_remote;
    socklen_t sockaddr_len;

    sockaddr_len = sizeof(sockaddr_remote);

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
        ms_printf("Failed to create UDP socket, errno = %d!\n", errno);
        return  (-1);
    }

    memset(&sockaddr_local, 0, sizeof(sockaddr_local));
    sockaddr_local.sin_len         = sizeof(struct sockaddr_in);
    sockaddr_local.sin_family      = AF_INET;
    sockaddr_local.sin_addr.s_addr = INADDR_ANY;
    sockaddr_local.sin_port        = htons(SERVER_LISTENING_PORT);

    ret = bind(sockfd, (struct sockaddr *)&sockaddr_local, sizeof(sockaddr_local));
    if (ret < 0) {
        close(sockfd);
        ms_printf("Failed to bind port %d, errno = %d!\n", SERVER_LISTENING_PORT, errno);
        return  (-1);
    }

    ms_printf("UDP echo server start.\n");

    while (1) {
        ssize_t len;

        len = recvfrom(sockfd, receive_buf, TEST_BUF_SIZE,
                            0, (struct sockaddr *)&sockaddr_remote, &sockaddr_len);
        if (len <= 0) {
            if ((errno != ETIMEDOUT) && (errno != EWOULDBLOCK)) {
                 close(sockfd);
                 ms_printf("Failed to recvfrom UDP echo client, errno = %d!\n", errno);
                 return  (-1);
            }

            continue;
        }

        sendto(sockfd, receive_buf, len,
              0, (struct sockaddr *)&sockaddr_remote, sizeof(sockaddr_remote));
    }

    return  (0);
}
