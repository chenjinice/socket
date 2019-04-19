#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <zmq.h>
#include "vclient.h"
#include "analysis.h"


static void *read_thread(void *arg);


// buffer大小
#define BUFFER_SIZE 10240

static char *m_ip = NULL;
static int   m_port = 12347;
static void *m_subscriber = NULL;
static void *m_context = NULL;
static int   m_ready = 0;
static int 	 m_loop = 0;
static char *m_filter = "vision";

//
void vclient_start(char *ip ,uint16_t port)
{
    if(m_ready == 1) return;

    char endpoint[50] = {0};
    int ret ;
    m_ip = ip;
    m_port = port;

    sprintf(endpoint,"tcp://%s:%d",m_ip,m_port);
    printf("vclient : connect to %s : %d\n",m_ip,m_port);
    m_context = zmq_ctx_new();
    m_subscriber = zmq_socket(m_context,ZMQ_SUB);
    ret = zmq_connect(m_subscriber,endpoint);
    assert(ret == 0);

    ret = zmq_setsockopt(m_subscriber,ZMQ_SUBSCRIBE,m_filter,strlen(m_filter));
    assert(ret == 0);

    pthread_t thread;
    pthread_create(&thread,NULL,read_thread,NULL);

    m_ready = 1;
}

// 结束这个任务，将会退出while循环，结束线程
void vclient_stop(void)
{
    m_loop = 0;
}

//
static void *read_thread(void *arg)
{
    // 线程结束时，自动释放资源
    pthread_detach(pthread_self());

    m_loop = 1;

    uint8_t filter[40] = {0};
    uint8_t buffer[BUFFER_SIZE];
    int len ;
    while(m_loop){
        memset(buffer,0,sizeof(buffer));
        len = zmq_recv(m_subscriber,filter,sizeof(filter),0);
        len = zmq_recv(m_subscriber,buffer,sizeof(buffer),0);
        if(len == -1)continue;
        if(len > BUFFER_SIZE){
            printf("vclient : zmq_recv size = %d > %d(MAX)\n",len,BUFFER_SIZE);
            continue;
        }

        analysis(buffer,len);
    }

    zmq_close(m_subscriber);
    zmq_ctx_destroy(m_context);
    return NULL;
}









