#include <unistd.h>	
#include <string.h>	
#include <stdio.h>	
#include <stdlib.h>	
#include <errno.h>	
#include <zmq.h>
#include <pthread.h>
#include "trigger_server.h"


#define BUFFER_SIZE 10240


void TriggerServer::init()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    m_host_port = 12349;
    m_context = nullptr;
    m_publisher = nullptr;
    m_ready = false;
    m_filter = (char *)"trigger";
    pthread_mutex_init(&m_mutex,NULL);
}

TriggerServer::TriggerServer(uint16_t host_port)
{	
    this->init();
    m_host_port = host_port;
}

TriggerServer::~TriggerServer()
{	
    this->stop();
    pthread_mutex_destroy(&m_mutex);
    google::protobuf::ShutdownProtobufLibrary();
    printf("~~~trigger server~~~~~~~end~~~~ \n");
}	

void TriggerServer::start()
{	
    if(m_ready)return;

    int ret;
	// 创建服务端，用于发布消息
    char pub_endpoint[50] = {0};
    sprintf(pub_endpoint,"tcp://*:%d",m_host_port);
    printf("trigger server : zmq pub = %s\n",pub_endpoint);
    m_context = zmq_ctx_new();
    m_publisher = zmq_socket(m_context,ZMQ_PUB);
    ret = zmq_bind(m_publisher,pub_endpoint);
    if(ret != 0){
        perror("trigger server : zmq bind error");
        exit(-1);
    }
	m_ready = true;
}	

void TriggerServer::stop()
{
    m_ready = false;
    if(m_publisher){
        zmq_close(m_publisher);
        m_publisher  = nullptr;
    }
    if(m_context){
        zmq_ctx_destroy(m_context);
        m_context = nullptr;
    }
}

// zmq 发送数据,加了线程锁
void TriggerServer::server_send(uint8_t *buffer, int len)
{	
    if(!m_ready){
        printf("trigger server : server is not started \n");
        return;
    }

    if(len > BUFFER_SIZE){
        printf("trigger server : send error , len = %d > %d \n",len,BUFFER_SIZE);
        return;
    }

    pthread_mutex_lock(&m_mutex);
    zmq_send(m_publisher,m_filter,strlen(m_filter),ZMQ_SNDMORE);
    zmq_send(m_publisher,buffer,len,0);
    pthread_mutex_unlock(&m_mutex);
}	

/*
 * 检查与当前时间差是否超过某个值
 *  @param   tv : 需要与当前时间做比较的时间
 *           ms : 时间差是否超过ms（毫秒）
 *  @return	 -1 : 时间差小于 ms
 *  		  0 : 时间差大于等于 ms
*/	
int TriggerServer::check_interval(struct timeval *tv,int ms)
{	
    if((tv->tv_sec == 0) && (tv->tv_usec == 0)){
        gettimeofday(tv,NULL);
        return 0;
    }
    struct timeval now={0};
    gettimeofday(&now,NULL);
    int64_t interval = ((int64_t)now.tv_sec - (int64_t)tv->tv_sec)*1000000 + (now.tv_usec-tv->tv_usec);

    //	printf("%d,now : %ld:%ld\n",sizeof(interval),now.tv_sec,now.tv_usec);
    if( (interval >= ms*1000 ) || (interval < 0) ){
        //		printf("interval ========== %lld\n",interval);
        gettimeofday(tv,NULL);
        return 0;
    }
    else{
        return -1;
    }
}	


// 发送抓拍物
void TriggerServer::send_data(trigger::SnapMsg &msg, struct timeval *tv, int ms)
{	
    if(msg.array_size() == 0)return;
    // 限制一下发送频率
    if(tv != NULL){
        if(check_interval(tv,ms))return;
    }

    int len = 0;
    uint8_t buffer[BUFFER_SIZE];

    len = msg.ByteSize();
    msg.SerializeToArray(buffer,len);

    this->server_send(buffer,len);
}	





