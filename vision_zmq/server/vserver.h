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
    Vserver();
    // port为socket端口
    Vserver(uint16_t host_port);
    /*  需要交互的初始化函数
	host_port : 本机服务端绑定端口
	remote_ip : 需要连接的对方ip
	remote_port : 需要连接的对方端口
    */	
    Vserver(uint16_t host_port,char *remote_ip,uint16_t remote_port);
    ~Vserver();

    void set_param(uint16_t host_port,char *remote_ip,uint16_t remote_port);
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
    void send_data(vision::TrafficFlow &msg,struct timeval *tv=NULL,int ms=1000);
    void send_data(vision::IceWarn &msg,struct timeval *tv=NULL, int ms=1000);
    void send_data(vision::SpecialCarMsg &msg,struct timeval *tv=NULL, int ms=1000);
    void send_data(vision::LaneWare &msg,struct timeval *tv=NULL, int ms=1000);
    void send_data(vision::Detectobjects &msg,struct timeval *tv=NULL,int ms=1000);

private:
    pthread_mutex_t m_mutex;

    uint16_t 	 m_host_port;	//socket 端口
    void        *m_context;
    void        *m_publisher;

    uint16_t    m_remote_port;
    char       *m_remote_ip;
    void       *m_subscriber;

    bool         m_ready;
    char        *m_filter;

    void    init();
    void    run();
    void    server_send(uint8_t *buffer,int len);
    int     check_interval(struct timeval *tv,int ms);
    // 友元函数，pthread 创建线程时需要
    friend  void *vserver_read_fun(void *param);

};

#endif



