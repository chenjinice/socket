/*
 */

#ifndef __VSERVER_H__
#define __VSERVER_H__


#include <iostream>
#include <pthread.h>
#include <sys/time.h>
#include "vision.pb.h"

using namespace std;

class Vserver
{
public:
    // port 为socket 端口
    Vserver(uint16_t port);
    ~Vserver();

    void start();
    void stop();

    // 下面是发送数据函数 ，ms为毫秒，
    // 如果两次调用发送函数的时间间隔 小于 ms的值，
    // 则此函数内部会滤掉这条数据，不发送
    void send_data(vision::Crowd &msg,int ms=100);
    void send_data(vision::Obstacles &msg,int ms=1000);
    void send_data(vision::AvailableAreas &msg,int ms=1000);
    void send_data(vision::Visibility &msg,int ms=1000);
    void send_data(vision::SmokeWarn &msg,int ms=1000);
    void send_data(vision::IllegalCarWarn &msg,int ms=1000);

private:
    pthread_mutex_t m_mutex;
    uint16_t 	 m_port;	//socket 端口
    void        *m_context;
    void        *m_publisher;
    bool         m_ready;
    char        *m_filter;

    void    server_send(uint8_t *buffer,int len);
    int     check_interval(struct timeval *tv,int ms);

};

#endif

