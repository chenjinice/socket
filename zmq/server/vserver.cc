#include <unistd.h>	
#include <string.h>	
#include <stdio.h>	
#include <stdlib.h>	
#include <errno.h>	
#include <zmq.h>	
#include "vserver.h"	

#define BUFFER_SIZE 10240

Vserver::Vserver(uint16_t port)
{	
    m_port = port;
    m_context = nullptr;
    m_publisher = nullptr;
    m_ready = false;
    m_filter = (char *)"vision";
}	

Vserver::~Vserver()
{	
    printf("~~~vserver~~~~~~~end~~~~ \n");
    this->stop();
}	

void Vserver::start()
{	
    if(m_ready)return;

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    int ret;
    char endpoint[50] = {0};
    sprintf(endpoint,"tcp://*:%d",m_port);

    //zmq
    m_context = zmq_ctx_new();
    m_publisher = zmq_socket(m_context,ZMQ_PUB);
    ret = zmq_bind(m_publisher,endpoint);
    assert(ret == 0);

    pthread_mutex_init(&m_mutex,NULL);

    m_ready = true;
}	

void Vserver::stop()
{	
    if(m_publisher)zmq_close(m_publisher);
    if(m_context)zmq_ctx_destroy(m_context);

    pthread_mutex_destroy(&m_mutex);
    google::protobuf::ShutdownProtobufLibrary();
}	

void Vserver::server_send(uint8_t *buffer, int len)
{	
    if(len > BUFFER_SIZE){
        printf("vserver : send error , len = %d > %d \n",len,BUFFER_SIZE);
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
int Vserver::check_interval(struct timeval *tv,int ms)	
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


// 发送行人
void Vserver::send_data(vision::Crowd &msg,struct timeval *tv, int ms)
{	
    if(msg.pedestrian_size() == 0)return;
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

//发送障碍物
void Vserver::send_data(vision::Obstacles &msg,struct timeval *tv,int ms)
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

//发送可行驶区域
void Vserver::send_data(vision::AvailableAreas &msg,struct timeval *tv, int ms)
{	
    if(msg.area_size() == 0)return;
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

// 发送能见度
void Vserver::send_data(vision::Visibility &msg,struct timeval *tv, int ms)
{	
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

// 发送烟雾报警
void Vserver::send_data(vision::SmokeWarn &msg,struct timeval *tv, int ms)
{	
    if(msg.warn() == false)return;
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

// 发送相关车辆
void Vserver::send_data(vision::IllegalCarWarn &msg,struct timeval *tv, int ms)
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

// 发送前方拥堵提醒
void Vserver::send_data(vision::TrafficJam &msg,struct timeval *tv, int ms)
{
    if(msg.jam_size() == 0)return;
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




