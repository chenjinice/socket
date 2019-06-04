/*	
 * 视觉这边发布消息的服务端
 */

#ifndef __LASER_SERVER_H__
#define __LASER_SERVER_H__


#include <iostream>	
#include <pthread.h>	
#include <sys/time.h>	
#include "laser.pb.h"

using namespace std;

class LaserServer
{	
public:	
    // host_port : 本机服务端绑定端口
    LaserServer(uint16_t host_port);
    ~LaserServer();

    void start();
    void stop();
    /* 下面是发送数据函数 ，
    tv 用于保存时间，最好是全局的变量,发送成功时函数内部会更新tv的值
    ms 为毫秒，
    如果两次调用发送函数的时间间隔 小于 ms的值，
    则此函数内部会滤掉这条数据，不发送
    */
    void send_data(laser::LaserMsg &msg,struct timeval *tv=NULL,int ms=100);


private:
    pthread_mutex_t m_mutex;

    uint16_t 	 m_host_port;
    void        *m_context;
    void        *m_publisher;

    bool         m_ready;
    char        *m_filter;

    void    init();
    void    server_send(uint8_t *buffer,int len);
    int     check_interval(struct timeval *tv,int ms);

};

#endif



