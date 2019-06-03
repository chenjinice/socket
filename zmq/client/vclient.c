#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <zmq.h>
#include "vclient.h"
#include "analysis.h"
#include "vision.pb-c.h"

static void *read_thread(void *arg);


// buffer大小
#define BUFFER_SIZE 10240


static void *m_subscriber = NULL;
static char *m_remote_ip = NULL;
static int   m_remote_port = 12347;

static void *m_publisher = NULL;
static int   m_host_port = 12348;

static void *m_context = NULL;
static int   m_ready = 0;
static int 	 m_loop = 0;
static char *m_filter = "vision";

//
void vclient_start(char *remote_ip , uint16_t remote_port, uint16_t host_port)
{
    int ret ;
    if(m_ready == 1) return;
    if(remote_ip == NULL){
        printf("vclient : error , remote ip = NULL \n");
        return;
    }
    m_remote_ip = remote_ip;
    m_remote_port = remote_port;
    m_host_port = host_port;
    m_context = zmq_ctx_new();

    // 创建客户端，用于接收消息
    char sub_endpoint[50] = {0};
    sprintf(sub_endpoint,"tcp://%s:%d",m_remote_ip,m_remote_port);
    printf("vclient : connect to %s : %d\n",m_remote_ip,m_remote_port);
    m_subscriber = zmq_socket(m_context,ZMQ_SUB);
    ret = zmq_connect(m_subscriber,sub_endpoint);
    if(ret !=0 ){
        perror("vclient : zmq connect error");
        return;
    }
    ret = zmq_setsockopt(m_subscriber,ZMQ_SUBSCRIBE,m_filter,strlen(m_filter));
    if(ret != 0){
        printf("vclient : zmq set filter error\n");
        return;
    }

    // 创建PUB模式的服务端，用于发布数据
    char pub_endpoint[50] = {0};
    sprintf(pub_endpoint,"tcp://*:%d",m_host_port);
    printf("vclient : zmq pub = %s\n",pub_endpoint);
    m_publisher = zmq_socket(m_context,ZMQ_PUB);
    ret = zmq_bind(m_publisher,pub_endpoint);
    if(ret != 0){
        perror("vclient : zmq bind error");
        return;
    }

    pthread_t thread;
    pthread_create(&thread,NULL,read_thread,NULL);
    m_ready = 1;
}

// 结束这个任务，将会退出while循环，结束线程
void vclient_stop(void)
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
            printf("vclient : zmq_recv size = %d > %d(MAX)\n",len,BUFFER_SIZE);
            continue;
        }

        analysis(buffer,len);
    }

    zmq_close(m_subscriber);
    zmq_close(m_publisher);
    zmq_ctx_destroy(m_context);
    return NULL;
}


// zmq 发送函数
static void vclient_send(uint8_t *buffer,int len){
    if(m_ready == 0 )return;

    zmq_send(m_publisher,m_filter,strlen(m_filter),ZMQ_SNDMORE);
    zmq_send(m_publisher,buffer,len,0);
}


// 动态配时场景需要，发送红绿灯信号给视觉那边
void vclient_send_signal(TRAFFIC_SIGNAL signal, uint32_t camera)
{
    if(m_ready == 0 )return;

    static Vision__TrafficFlow *msg = NULL;
    static Vision__FlowInfo **flow_array = NULL;

    if(msg == NULL){
        msg = calloc(1,sizeof(Vision__TrafficFlow));
    }
    if(flow_array == NULL){
        flow_array = calloc(1,sizeof(Vision__FlowInfo *));
        flow_array[0] = calloc(1,sizeof(Vision__FlowInfo));
    }
    vision__traffic_flow__init(msg);
    vision__flow_info__init(flow_array[0]);
    msg->id = VISION__ID__TRAFFIC_FLOW;
    flow_array[0]->has_camera = 1;
    flow_array[0]->camera = camera;
    flow_array[0]->has_signal = 1;
    flow_array[0]->signal = signal;
    msg->n_flow = 1;
    msg->flow = flow_array;
    int length = vision__traffic_flow__get_packed_size(msg);
    uint8_t buffer[100] = {0};
    vision__traffic_flow__pack(msg,buffer);

    vclient_send(buffer,length);
}




