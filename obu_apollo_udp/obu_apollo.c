#include <netinet/in.h>
#include <net/if.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include "obu_apollo.h"


#define SOCK_INVALID	-1
#define HEADER_SIZE      4
static uint8_t g_header[4] = {0x61,0x62,0x63,0x64};

static pthread_mutex_t m_mutex;
static char   * m_device   = "eth0";
static uint16_t m_port = 9999;
static int      m_fd   = SOCK_INVALID;
static struct sockaddr_in m_addr;


static void udp_close()
{
    if(m_fd != SOCK_INVALID){
        close(m_fd);
        m_fd = SOCK_INVALID;
    }
}

static void udp_init()
{
    int ret = -1;
    int opt = 1;
    struct ifreq ifr = {0};

    strcpy(ifr.ifr_name,m_device);

    m_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_fd <= 0)
    {
        perror("obu_apollo create udp socket failed");
        exit(-1);
    }


    //设置该套接字为广播类型
    if(setsockopt(m_fd, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt)) < 0){
        udp_close();
        perror("obu_apollo set socket broadcast error");
        exit(-1);
    }

    // 绑定网卡
    if (setsockopt(m_fd, SOL_SOCKET, SO_BINDTODEVICE, (char *)&ifr, sizeof(ifr)) < 0){
        udp_close();
        perror("obu_apollo bind interface error");
        exit(-1);
    }

    bzero(&m_addr, sizeof(struct sockaddr_in));
    m_addr.sin_family=AF_INET;
    m_addr.sin_addr.s_addr=htonl(INADDR_BROADCAST);
    m_addr.sin_port=htons(m_port);
//    m_addr.sin_addr.s_addr=inet_addr("192.168.1.255");
}

void obu_apollo_start(char * device,uint16_t port)
{
    if(m_fd == SOCK_INVALID)
    {
        m_port = port;
        if(device)m_device = device;
        pthread_mutex_init(&m_mutex,NULL);
        udp_init();
    }

}

void obu_apollo_stop()
{
    udp_close();
    pthread_mutex_destroy(&m_mutex);
}


void obu_apollo_send(uint8_t *data,int len)
{
    if(len > MSG_BUFFER_SIZE){
        return;
    }

    int ret,i;
    int send_size = 0;
    uint8_t sum = 0 ;

    //
    uint8_t buffer[MSG_BUFFER_SIZE+10] = {0};
    memcpy(buffer,g_header,HEADER_SIZE);
    memcpy(buffer+HEADER_SIZE,data,len);
    for (i=0;i<HEADER_SIZE+len;i++) {
        sum+=buffer[i];
    }
    buffer[len+HEADER_SIZE] = sum;
    send_size = len+HEADER_SIZE+1;

    pthread_mutex_lock(&m_mutex);
    ret=sendto(m_fd, buffer, send_size, 0, (struct sockaddr*)&m_addr, sizeof(m_addr));
    if(ret<0){
        perror("obu_apollo sendto error");
    }
    pthread_mutex_unlock(&m_mutex);
}


