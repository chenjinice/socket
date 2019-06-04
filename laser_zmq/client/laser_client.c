#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <zmq.h>
#include "laser_client.h"
#include "analysis.h"
#include "laser.pb-c.h"

static void *read_thread(void *arg);


// buffer大小
#define BUFFER_SIZE 10240

static void *m_subscriber = NULL;
static char *m_remote_ip = NULL;
static int   m_remote_port = 12347;

static void *m_context = NULL;
static int   m_ready = 0;
static int 	 m_loop = 0;
static char *m_filter = "laser";

//
void laser_client_start(char *remote_ip , uint16_t remote_port)
{
    int ret ;
    if(m_ready == 1) return;
    if(remote_ip == NULL){
        printf("vclient : error , remote ip = NULL \n");
        return;
    }
    m_remote_ip = remote_ip;
    m_remote_port = remote_port;
    m_context = zmq_ctx_new();

    // 创建客户端，用于接收消息
    char sub_endpoint[50] = {0};
    sprintf(sub_endpoint,"tcp://%s:%d",m_remote_ip,m_remote_port);
    printf("laser_client : connect to %s : %d\n",m_remote_ip,m_remote_port);
    m_subscriber = zmq_socket(m_context,ZMQ_SUB);
    ret = zmq_connect(m_subscriber,sub_endpoint);
    if(ret !=0 ){
        perror("laser_client : zmq connect error");
        return;
    }
    ret = zmq_setsockopt(m_subscriber,ZMQ_SUBSCRIBE,m_filter,strlen(m_filter));
    if(ret != 0){
        printf("laser_client : zmq set filter error\n");
        return;
    }

    pthread_t thread;
    pthread_create(&thread,NULL,read_thread,NULL);
    m_ready = 1;
}

// 结束这个任务，将会退出while循环，结束线程
void laser_client_stop(void)
{
    m_loop = 0;
    m_ready = 0;
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
            printf("laser_client : zmq_recv size = %d > %d(MAX)\n",len,BUFFER_SIZE);
            continue;
        }

        analysis(buffer,len);
    }

    zmq_close(m_subscriber);
    zmq_ctx_destroy(m_context);
    m_subscriber = NULL;
    m_context = NULL;
    return NULL;
}


