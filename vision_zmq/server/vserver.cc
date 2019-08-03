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
}

void Vserver::init()
{
    m_host_port = 12347;
    m_context = nullptr;
    m_publisher = nullptr;

    m_remote_port = 12348;
    m_remote_ip = nullptr;
    m_subscriber = nullptr;

    m_ready = false;
    m_filter = (char *)"vision";
    pthread_mutex_init(&m_mutex,NULL);
}

Vserver::Vserver(uint16_t host_port)
{	
    this->init();
    m_host_port = host_port;
}

Vserver::Vserver(uint16_t host_port, char *remote_ip, uint16_t remote_port)
{
    this->init();
    m_host_port = host_port;
    m_remote_ip = remote_ip;
    m_remote_port = remote_port;
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
	// 创建服务端，用于发布消息
    char pub_endpoint[50] = {0};
    sprintf(pub_endpoint,"tcp://*:%d",m_host_port);
    printf("vserver : zmq pub = %s\n",pub_endpoint);
    m_context = zmq_ctx_new();
    m_publisher = zmq_socket(m_context,ZMQ_PUB);
    ret = zmq_bind(m_publisher,pub_endpoint);
    if(ret != 0){
        perror("vserver : zmq bind error");
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
            perror("vserver : zmq connect error");
            exit(-1);
        }
        ret = zmq_setsockopt(m_subscriber,ZMQ_SUBSCRIBE,m_filter,strlen(m_filter));
        if(ret != 0){
            printf("vserver : zmq set filter error\n");
            exit(-1);
        }
        pthread_t thread;
        pthread_create(&thread,NULL,vserver_read_fun,this);
    }

    m_ready = true;
}	

void Vserver::stop()
{	
    m_ready = false;
    if(m_publisher){
        zmq_close(m_publisher);
        m_publisher = nullptr;
    }
    if(m_context){
        zmq_ctx_destroy(m_context);
        m_context = nullptr;
    }
    if(m_subscriber){
        zmq_close(m_subscriber);
        m_subscriber = nullptr;
    }
    pthread_mutex_destroy(&m_mutex);
    google::protobuf::ShutdownProtobufLibrary();
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
}

// zmq 发送数据,为方便视觉的同志们，加了线程锁
void Vserver::server_send(uint8_t *buffer, int len)
{	
    if(!m_ready){
        printf("vserver : server is not started \n");
        return;
    }

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

// 发送动态配时场景需要数据
void Vserver::send_data(vision::TrafficFlow &msg,struct timeval *tv, int ms)
{
    if(msg.flow_size() == 0)return;
    // 限制一下发送频率

    bool has_vehicle = false;
    bool has_pass = false;

    for(int i=0;i<msg.flow_size();i++){
        int v_num = msg.flow(i).vehicle_num_size();
        int p_num = msg.flow(i).pass_num_size();
        if(v_num > 0)has_vehicle = true;
        if(p_num > 0)has_pass = true;
    }

    if((!has_vehicle) && (!has_pass))return;

    if(tv != NULL){
        if( (!has_pass) && check_interval(tv,ms) )return;
    }

    int len = 0;
    uint8_t buffer[BUFFER_SIZE];
    len = msg.ByteSize();
    msg.SerializeToArray(buffer,len);

    this->server_send(buffer,len);
}

// 发送结冰
void Vserver::send_data(vision::IceWarn &msg,struct timeval *tv, int ms)
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

// 特殊车辆
void Vserver::send_data(vision::SpecialCarMsg &msg,struct timeval *tv, int ms)
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

// 车道线磨损
void Vserver::send_data(vision::LaneWare &msg, timeval *tv, int ms)
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





