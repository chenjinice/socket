/*	
 * 视觉这边发布消息的服务端
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

    /* 下面是发送数据函数 ，
    tv 用于保存时间，最好是全局的变量,发送成功时函数内部会更新tv的值
    ms 为毫秒，
    如果两次调用发送函数的时间间隔 小于 ms的值，
    则此函数内部会滤掉这条数据，不发送
    */
    void send_data(vision::Crowd &msg,struct timeval *tv=NULL,int ms=100);
    void send_data(vision::Obstacles &msg,struct timeval *tv=NULL,int ms=1000);
    void send_data(vision::AvailableAreas &msg,struct timeval *tv=NULL,int ms=1000);
    void send_data(vision::Visibility &msg,struct timeval *tv=NULL,int ms=1000);
    void send_data(vision::SmokeWarn &msg,struct timeval *tv=NULL,int ms=1000);
    void send_data(vision::IllegalCarWarn &msg,struct timeval *tv=NULL,int ms=1000);
    void send_data(vision::TrafficJam &msg,struct timeval *tv=NULL,int ms=1000);

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

