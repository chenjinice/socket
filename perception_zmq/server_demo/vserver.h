/*	
 * 视觉这边发布消息的服务端
 */

#ifndef __VSERVER_H__	
#define __VSERVER_H__	


#include <sys/time.h>
#include <netinet/in.h>

#include <iostream>	
#include <thread>

#include "perception.pb.h"
#include "my_zmq.h"


using namespace std;
using namespace perception;


typedef void (*VCallBack)(uint8_t *buffer,int len,int index);


struct RemoteServer{
    string  addr;
    string  filter;
};


const string    kVserverIpcAddr     = "ipc:///tmp/crss.ipc";
const string    kVserverTcpAddr     = "tcp://*:12347";
const string    kVserverFilter      = "vision";


class Vserver {
public:
    Vserver();
    ~Vserver();
    void                 setParam(uint16_t this_port, vector<RemoteServer> remotes, string filter = kVserverFilter, string ipc_addr = kVserverIpcAddr);
    void                 setCallBack(VCallBack fun);
    void                 start();
    void                 addUdpIp(char *ip,uint16_t port);
    void                 send(PerceptionMsg &msg,timeval *tv=nullptr,int ms=1000);
    void                 udpSend(PerceptionMsg &msg,timeval *tv=nullptr,int ms=1000);

private:
    void                 udpInit();
    void                 zmqMsgReceived(uint8_t *buffer, int len, void *arg);
    int                  checkInterval(timeval *tv,int ms);


    bool                 m_ready                = false;
    int                  m_udp_fd               = -1;
    string               m_ipc_addr             = kVserverIpcAddr;
    string               m_tcp_addr             = kVserverTcpAddr;
    string               m_filter               = kVserverFilter;
    MyZmq *              m_tcp_pub              = nullptr;
    MyZmq *              m_ipc_pub              = nullptr;

    VCallBack            m_callback;

    vector<RemoteServer> m_remotes;
    vector<MyZmq *>      m_remote_zmq;
    vector<sockaddr_in>  m_udp_list;
};

#endif



