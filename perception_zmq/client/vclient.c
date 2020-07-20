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

static void *readThread(void *arg);

// buffer大小
#define     BUFFER_SIZE 10240


static void *m_subscriber   = NULL;
static char *m_remote_ip    = NULL;
static int   m_remote_port  = 12347;

static void *m_publisher    = NULL;
static int   m_host_port    = 12348;

static char *m_filter       = "vision";

static void *m_context      = NULL;
static int   m_ready        = 0;
static int   m_loop         = 0;
static int   m_has_filter   = 0;

//
void vclient_start(char *remote_ip , uint16_t remote_port, uint16_t host_port)
{
    printf("perception version = %d\n",PERCEPTION__VERSION__VERSION);
    int ret ;
    if(m_ready == 1) return;
    if(remote_ip == NULL){
        printf("vclient : error , remote ip = NULL \n");
        return;
    }
    if( (m_filter != NULL) && (strlen(m_filter) > 0) )m_has_filter = 1;
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
    if(m_has_filter){
        zmq_setsockopt(m_subscriber,ZMQ_SUBSCRIBE,m_filter,strlen(m_filter));
    }else{
        zmq_setsockopt(m_subscriber,ZMQ_SUBSCRIBE,"",0);
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
    pthread_create(&thread,NULL,readThread,NULL);
    m_ready = 1;
}

// 结束这个任务，将会退出while循环，结束线程
void vclient_stop(void)
{
    m_loop = 0;
    zmq_ctx_destroy(m_context);
    m_ready = 0;
    printf("vclient : stop\n");
}

//
static void *readThread(void *arg)
{
    // 线程结束时，自动释放资源
    pthread_detach(pthread_self());

    m_loop = 1;

    uint8_t filter[100];
    uint8_t buffer[BUFFER_SIZE];
    int len ;
    while(m_loop){
        memset(buffer,0,sizeof(buffer));
        if( m_has_filter > 0 )len = zmq_recv(m_subscriber,filter,sizeof(filter),ZMQ_SNDMORE);
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
    return NULL;
}


// zmq 发送函数
static void vclient_send(uint8_t *buffer,int len){
    if(m_ready == 0 )return;
    if(m_has_filter > 0)zmq_send(m_publisher,m_filter,strlen(m_filter),ZMQ_SNDMORE);
    zmq_send(m_publisher,buffer,len,0);
}


// 动态配时场景需要，发送红绿灯信号给视觉那边
void vclient_send_signal(TrafficSignal signal, uint32_t camera)
{
    if(m_ready == 0 )return;

    static Perception__PerceptionMsg *msg      = NULL;
    static Perception__FlowMsg       *flow_msg = NULL;
    static Perception__Flow         **flow     = NULL;

    if(flow == NULL){
        flow    = calloc(1,sizeof(Perception__Flow*));
        flow[0] = calloc(1,sizeof(Perception__Flow ));
        perception__flow__init(flow[0]);
    }
    if(flow_msg == NULL){
        flow_msg = calloc(1,sizeof(Perception__FlowMsg));
        perception__flow_msg__init(flow_msg);
        flow_msg->n_flow = 1;
        flow_msg->flow = flow;
    }
    if(msg == NULL){
        msg = calloc(1,sizeof(Perception__PerceptionMsg));
        perception__perception_msg__init(msg);
        msg->event = PERCEPTION__EVENT_ID__TRAFFIC_FLOW;
        msg->msg_type_case = PERCEPTION__PERCEPTION_MSG__MSG_TYPE_FLOW_MSG;
        msg->flow_msg = flow_msg;
    }
    flow[0]->has_camera = 1;
    flow[0]->camera = camera;
    flow[0]->has_signal = 1;
    flow[0]->signal = signal;
    int length = perception__perception_msg__get_packed_size(msg);
    uint8_t buffer[100] = {0};
    perception__perception_msg__pack(msg,buffer);

    vclient_send(buffer,length);
}




