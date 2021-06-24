#include <unistd.h>	
#include <string.h>	
#include <stdio.h>	
#include <stdlib.h>	
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "vserver.h"


#define BUFFER_SIZE 10240


void Vserver::udpInit() {
    if(m_udp_fd != -1)return;
    m_udp_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_udp_fd <= 0){
        printf("vserver : udp create error, %s\n",strerror(errno));
        exit(-1);
    }
    printf("vserver : udp init\n");
}

Vserver::Vserver() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    m_tcp_pub = new MyZmq();
    m_ipc_pub = new MyZmq();
}

Vserver::~Vserver() {
    delete m_tcp_pub;
    delete m_ipc_pub;
    m_tcp_pub = nullptr;
    m_ipc_pub = nullptr;

    for(size_t i=0;i<m_remote_zmq.size();i++){
        delete m_remote_zmq[i];
        m_remote_zmq[i] = nullptr;
    }
    m_remote_zmq.clear();
    printf("~~~vserver~~~~~~~end~~~~ \n");
}

void Vserver::setParam(uint16_t this_port, vector<RemoteServer> remotes, string filter, string ipc_addr) {
    m_remotes           = remotes;
    m_filter            = filter;
    m_tcp_addr          = "tcp://*:" + to_string(this_port);
    m_ipc_addr          = ipc_addr;
}

void Vserver::setCallBack(VCallBack fun) {
    m_callback = fun;
}

void Vserver::start() {
    if  (m_ready)  return;
    else m_ready = true;

    m_ipc_pub->startPublisher(m_ipc_addr,"");
    m_tcp_pub->startPublisher(m_tcp_addr,m_filter);

    this->udpInit();

    for(size_t i=0;i<m_remotes.size();i++){
        MyZmq *zmq      = new MyZmq();
        ZmqCallBack fun = ZmqBindClassFun(&Vserver::zmqMsgReceived,this);
        zmq->startSubscriber(m_remotes[i].addr,m_remotes[i].filter,fun);
        m_remote_zmq.push_back(zmq);
    }

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
void Vserver::send(PerceptionMsg &msg,timeval *tv,int ms) {
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
    m_ipc_pub->send(buffer,len);
    m_tcp_pub->send(buffer,len);
}

// 添加要udp的发送的ip和端口
void Vserver::addUdpIp(char *ip, uint16_t port)
{
    sockaddr_in addr;
    memset(&addr,0,sizeof(sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    m_udp_list.push_back(addr);
    printf("vserver : add udp %s:%d\n",ip,port);
}

// udp 发送
void Vserver::udpSend(PerceptionMsg &msg, timeval *tv, int ms)
{
    if(m_udp_fd == -1){
        printf("vserver : udp fd = -1 \n");
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
    // udp 发送数据
    for(uint i=0;i<m_udp_list.size();i++){
        sendto(m_udp_fd, buffer, len, 0, (struct sockaddr *)&m_udp_list[i], sizeof(sockaddr_in));
    }
}

void Vserver::zmqMsgReceived(uint8_t *buffer, int len,void *arg) {
    string  addr    = (char *)arg;
    int     index   = -1;

    for(size_t i=0;i<m_remotes.size();i++){
        if(addr == m_remotes[i].addr){
            index = i;
            break;
        }
    }
    m_callback(buffer,len,index);
}


