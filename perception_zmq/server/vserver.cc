#include <unistd.h>	
#include <string.h>	
#include <stdio.h>	
#include <stdlib.h>	
#include <errno.h>	
#include <zmq.h>
#include <pthread.h>
#include "vserver.h"
#include "analysis.h"

#define BUFFER_SIZE 10240

void *vserver_read_fun(void *param)
{
    // 线程结束时，自动释放资源
    pthread_detach(pthread_self());

    Vserver *v = (Vserver *)param;
    v->run();
    return  nullptr;
}

void Vserver::init()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    m_host_port = 12347;
    m_context = nullptr;
    m_publisher = nullptr;

    m_remote_port = 12348;
    m_remote_ip = nullptr;
    m_subscriber = nullptr;

    m_ready = false;
    pthread_mutex_init(&m_mutex,nullptr);
}

Vserver::Vserver()
{
    this->init();
}

Vserver::~Vserver()
{	
    this->stop();
    pthread_mutex_destroy(&m_mutex);
    google::protobuf::ShutdownProtobufLibrary();
    printf("~~~vserver~~~~~~~end~~~~ \n");
}

void Vserver::setParam(uint16_t host_port,char *remote_ip,uint16_t remote_port)
{
    m_host_port = host_port;
    m_remote_ip = remote_ip;
    m_remote_port = remote_port;
}

void Vserver::start()
{	
    if(m_ready)return;

    int ret;
	// 创建服务端，用于发布消息
    char pub_endpoint[50] = {0};
    sprintf(pub_endpoint,"tcp://*:%d",m_host_port);
    printf("vserver : zmq pub = %s\n",pub_endpoint);
    m_context = zmq_ctx_new();
    m_publisher = zmq_socket(m_context,ZMQ_PUB);
    ret = zmq_bind(m_publisher,pub_endpoint);
    if(ret != 0){
        perror("vserver : zmq tcp bind error");
        exit(-1);
    }

    if(m_remote_ip){
		// 创建客户端，用于订阅消息，接收消息
        char sub_endpoint[50] = {0};
        sprintf(sub_endpoint,"tcp://%s:%d",m_remote_ip,m_remote_port);
        printf("vserver : zmq sub to %s\n",sub_endpoint);
        m_subscriber = zmq_socket(m_context,ZMQ_SUB);
        ret = zmq_connect(m_subscriber,sub_endpoint);
        if(ret != 0){
            perror("vserver : zmq tcp connect error");
            exit(-1);
        }
        ret = zmq_setsockopt(m_subscriber,ZMQ_SUBSCRIBE,"",0);
        pthread_t thread;
        pthread_create(&thread,nullptr,vserver_read_fun,this);
    }
    m_ready = true;
}	

void Vserver::stop()
{
    m_ready = false;
    if(m_context){
        zmq_ctx_destroy(m_context);
        m_context = nullptr;
    }
}

void Vserver::run()
{
    uint8_t filter[40] = {0};
    uint8_t buffer[BUFFER_SIZE];
    int len;
    while (m_ready){
        memset(buffer,0,sizeof(buffer));
        len = zmq_recv(m_subscriber,filter,sizeof(filter),0);
        len = zmq_recv(m_subscriber,buffer,sizeof(buffer),0);
        if(len == -1)continue;
        if(len > BUFFER_SIZE){
            printf("vserver : zmq_recv size = %d > %d(MAX)\n",len,BUFFER_SIZE);
            continue;
        }
        analysis(buffer,len);
    }
    zmq_close(m_subscriber);
    zmq_close(m_publisher);
    m_subscriber = nullptr;
    m_publisher  = nullptr;
}

// 检查与当前时间差是否超过某个值,tv : 需要与当前时间做比较的时间,ms : 时间差是否超过ms（毫秒）
// 返回值 -1 : 时间差小于 ms,0 : 时间差大于等于 ms
int Vserver::checkInterval(timeval *tv,int ms)
{	
    if((tv->tv_sec == 0) && (tv->tv_usec == 0)){
        gettimeofday(tv,nullptr);
        return 0;
    }
    timeval now = {0};
    gettimeofday(&now,nullptr);
    int64_t interval = ((int64_t)now.tv_sec - (int64_t)tv->tv_sec)*1000000 + (now.tv_usec-tv->tv_usec);
    if( (interval >= ms*1000 ) || (interval < 0) ){
        gettimeofday(tv,nullptr);
        return 0;
    }else{
        return -1;
    }
}	

// 发送
void Vserver::send(PerceptionMsg &msg,timeval *tv,int ms)
{	
    if(!m_ready){
        printf("vserver : server is not started \n");
        return;
    }
    // 限制一下发送频率
    if(tv != nullptr){
        if(checkInterval(tv,ms))return;
    }
    int len = msg.ByteSize();
    if(len > BUFFER_SIZE){
        printf("vserver : send error , len = %d > %d \n",len,BUFFER_SIZE);
        return;
    }
    uint8_t buffer[BUFFER_SIZE] = {0};
    msg.SerializeToArray(buffer,len);
    // zmq 发送数据,加线程锁
    pthread_mutex_lock(&m_mutex);
    zmq_send(m_publisher,buffer,len,0);
    pthread_mutex_unlock(&m_mutex);
}





