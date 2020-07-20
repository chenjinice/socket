/*	
 * 视觉这边发布消息的服务端
 */

#ifndef __VSERVER_H__	
#define __VSERVER_H__	


#include <iostream>	
#include <pthread.h>	
#include <sys/time.h>	
#include "perception.pb.h"	

using namespace std;
using namespace perception;

typedef void (*VCallBack)(uint8_t *buffer,int len);

class Vserver
{	
public:
    Vserver();
    ~Vserver();
    // host_port : 本机服务端绑定端口 ,remote_ip : 需要连接的对方ip , remote_port : 对方端口
    void setParam(uint16_t host_port,char *remote_ip,uint16_t remote_port,char *filter=(char *)"vision",char *ipc =(char *)"crss");
    void setCallBack(VCallBack fun);
    void start();
    void stop();
    /* tv 用于保存时间，最好是全局的变量,发送成功时函数内部会更新tv的值,ms 为毫秒，
        如果两次调用发送函数的时间间隔 小于 ms的值，则此函数内部会滤掉这条数据，不发送 */
    void send(PerceptionMsg &msg,timeval *tv=nullptr,int ms=1000);

private:
    static void *readThread(void *param);
    void    init();
    void    run();
    int     checkInterval(timeval *tv,int ms);

    pthread_mutex_t m_mutex;
    bool         m_ready;
    bool         m_has_filter;
    uint16_t     m_host_port;       // 本机端口
    void *       m_context;
    void *       m_publisher;
    void *       m_ipc_publisher;
    uint16_t     m_remote_port;     // 远程端口
    char *       m_remote_ip;       // 远程ip
    void *       m_subscriber;
    char *       m_filter;
    char *       m_ipc;
    VCallBack    m_callback;
};

#endif



