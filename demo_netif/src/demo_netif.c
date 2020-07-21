/*
 * Copyright (c) 2015-2020 ACOINFO Co., Ltd.
 * All rights reserved.
 *
 * Detailed license information can be found in the LICENSE file.
 *
 * File: demo_netif.c NETIF configuration demo.
 *
 * Author: Yu.kangzhi <yukangzhi@acoinfo.com>
 *
 */

#include <ms_rtos.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int show_mac_addr(int sockfd)
{
    int ret;
    struct ifreq ifreq;

    if (sockfd < 0) {
        return  (-1);
    }

    bzero(&ifreq, sizeof(struct ifreq));

    /*
     * Get MAC address
     */
    ret = ioctl(sockfd, SIOCGIFHWADDR, &ifreq);
    if (ret < 0) {
        return  (-1);
    }

    ms_printf("MAC addr: %02x:%02x:%02x:%02x:%02x:%02x\n",
              (ms_uint8_t)ifreq.ifr_hwaddr.sa_data[0],
              (ms_uint8_t)ifreq.ifr_hwaddr.sa_data[1],
              (ms_uint8_t)ifreq.ifr_hwaddr.sa_data[2],
              (ms_uint8_t)ifreq.ifr_hwaddr.sa_data[3],
              (ms_uint8_t)ifreq.ifr_hwaddr.sa_data[4],
              (ms_uint8_t)ifreq.ifr_hwaddr.sa_data[5]);

    return  (0);
}

int show_ip_addr(int sockfd)
{
    int ret;
    struct ifreq ifreq;
    struct sockaddr_in *psockaddrin;
    char ipAddrString[sizeof("255.255.255.255")];

    if (sockfd < 0) {
        return  (-1);
    }

    bzero(&ifreq, sizeof(struct ifreq));
    psockaddrin = (struct sockaddr_in *)&(ifreq.ifr_addr);

    /*
     * Get IP address
     */
    ret = ioctl(sockfd, SIOCGIFADDR, &ifreq);
    if (ret < 0) {
        return  (-1);
    }

    inet_ntoa_r(psockaddrin->sin_addr, ipAddrString, sizeof(ipAddrString));
    ms_printf("IP addr: %s\n", ipAddrString);

    return  (0);
}

int main (int argc, char **argv)
{
    int ret;
    int sockfd;

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
        ms_printf("Failed to create socket fd. errno = %d\n", errno);
        return  (-1);
    }

    ret = show_mac_addr(sockfd);
    if (ret < 0) {
        close(sockfd);
        ms_printf("Failed to show MAC address.\n");
        return  (-1);
    }

    ret = show_ip_addr(sockfd);
    if (ret < 0) {
        close(sockfd);
        ms_printf("Failed to show IP address.\n");
        return  (-1);
    }

    close(sockfd);

    return  (0);
}
