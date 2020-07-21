/*
 * Copyright (c) 2015-2020 ACOINFO Co., Ltd.
 * All rights reserved.
 *
 * Detailed license information can be found in the LICENSE file.
 *
 * File: demo_tcp.c TCP ECHO server application demo.
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

static char receive_buf[TEST_BUF_SIZE];

int main (int argc, char **argv)
{
    int ret;
    int sockfd_server;
    int sockfd_client;
    struct sockaddr_in sockaddr_server;
    struct sockaddr_in sockaddr_client;
    socklen_t sockaddr_len;

    sockfd_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd_server < 0) {
        ms_printf("Failed to create TCP socket, errno = %d!\n", errno);
        return  (-1);
    }

    memset(&sockaddr_server, 0, sizeof(sockaddr_server));
    sockaddr_server.sin_len         = sizeof(struct sockaddr_in);
    sockaddr_server.sin_family      = AF_INET;
    sockaddr_server.sin_addr.s_addr = inet_addr(SERVER_LISTENING_IP);
    sockaddr_server.sin_port        = htons(SERVER_LISTENING_PORT);

    ret = bind(sockfd_server, (struct sockaddr *)&sockaddr_server, sizeof(sockaddr_server));
    if (ret < 0) {
        close(sockfd_server);
        ms_printf("Failed to bind port %d, errno = %d!\n", SERVER_LISTENING_PORT, errno);
        return  (-1);
    }

    ms_printf("TCP echo server start listening.\n");

    listen(sockfd_server, 5);

    sockaddr_len = sizeof(struct sockaddr_in);
    sockfd_client = accept(sockfd_server, (struct sockaddr *)&sockaddr_client, &sockaddr_len);
    if (sockfd_client < 0) {
        close(sockfd_server);
        ms_printf("Failed to accept connection, errno = %d\n", errno);
        return  (-1);
    }

    ms_printf("TCP echo server accept one connection.\n");

    while (1) {
        ssize_t len;

        len = read(sockfd_client, receive_buf, TEST_BUF_SIZE);
        if (len <= 0) {
            if ((errno != ETIMEDOUT) && (errno != EWOULDBLOCK)) {
                 close(sockfd_client);
                 ms_printf("Failed to read form TCP echo client, errno = %d\n", errno);
                 return  (-1);
            }

            continue;
        }

        len = write(sockfd_client, receive_buf, len);

        ms_printf("TCP echo server echo %d byte.\n", len);
    }

    close(sockfd_client);
    close(sockfd_server);

    return  (0);
}
