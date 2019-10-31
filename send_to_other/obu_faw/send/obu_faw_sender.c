#include <netinet/in.h>
#include <net/if.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#include "obu_faw_sender.h"


typedef struct sockaddr_in  SockAddr;


#define FAW_INVALID -1
#define FAW_COUNT    5
#define FAW_BUFSIZE  1024


static int      m_motion_fd = FAW_INVALID;
static int      m_can_fd    = FAW_INVALID;
static int      m_loop = 0;
static int      m_ready = 0;
static int      m_count = 0;
static SockAddr m_addr[FAW_COUNT] = {0};
static fawfun_t m_motion_fun = NULL;
static fawfun_t m_can_fun =  NULL;


static void *sendMotionThread(void *arg);
static void *sendCanThread(void *arg);



static void udpOpen(int *fd){
    if(*fd != FAW_INVALID)return;
    *fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (*fd <= 0){
        printf("obuFaw : udp create error, %s\n",strerror(errno));
        exit(-1);
    }
}


static void udpClose(int *fd){
    if(*fd == FAW_INVALID)return;
    close(*fd);
    *fd = FAW_INVALID;
}


// 创建socket，并开启发送线程
static void obuFawInit()
{
    if(m_ready == 1)return;
    pthread_t thread1,thread2;
    udpOpen(&m_motion_fd);
    udpOpen(&m_can_fd);

    pthread_create(&thread1,NULL,sendMotionThread,NULL);
    pthread_create(&thread2,NULL,sendCanThread,NULL);
    m_ready = 1;
}


// fun这个函数用来填充ObuMtion数据，内部会周期性调用
void obuFawSetMotionFun(fawfun_t fun)
{
    m_motion_fun = fun;
}

// fun这个函数用来填充Can数据，内部会周期性调用
void obuFawSetCanFun(fawfun_t fun)
{
    m_can_fun = fun;
}

// 添加要发送数据的ip和端口 , 最多5个
void obuFawAdd(char *ip, uint16_t port)
{
    if(m_count >= FAW_COUNT)return;

    SockAddr *addr = &m_addr[m_count];
    memset(addr,0,sizeof(SockAddr));
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = inet_addr(ip);
    addr->sin_port = htons(port);
    m_count++;

    obuFawInit();
}

// 停止发送线程，关闭socket
void obuFawStop()
{
    m_loop = 0;
    udpClose(&m_motion_fd);
    udpClose(&m_can_fd);
}

// 发送 ObuMtion 数据线程
void *sendMotionThread(void *arg)
{
    // 线程结束时，自动释放资源
    pthread_detach(pthread_self());

    m_loop = 1;
    int i;
    uint8_t buffer[FAW_BUFSIZE] = {0};

    while(m_loop){
        usleep(10000);
        if(m_motion_fun == NULL)continue;

        memset(buffer,0,FAW_BUFSIZE);
        int len = m_motion_fun(buffer,FAW_BUFSIZE);
        if(len <= 0)continue;
        if(len > FAW_BUFSIZE)continue;

        for(i=0;i<m_count;i++){
            sendto(m_motion_fd, buffer, len, 0, (struct sockaddr *)&m_addr[i], sizeof(SockAddr));
        }
    }
}

// 发送 can 数据线程
void *sendCanThread(void *arg)
{
    // 线程结束时，自动释放资源
    pthread_detach(pthread_self());

    m_loop = 1;
    int i;
    uint8_t buffer[FAW_BUFSIZE] = {0};

    while(m_loop){
        usleep(50000);
        if(m_can_fun == NULL)continue;

        memset(buffer,0,FAW_BUFSIZE);
        int len = m_can_fun(buffer,FAW_BUFSIZE);
        if(len <= 0)continue;
        if(len > FAW_BUFSIZE)continue;

        for(i=0;i<m_count;i++){
            sendto(m_can_fd, buffer, len, 0, (struct sockaddr *)&m_addr[i], sizeof(SockAddr));
        }
    }
}








