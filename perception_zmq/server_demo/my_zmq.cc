/*
 * Copyright 2021 Cidi.chen. All Rights Reserved.
 */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include "zmq.h"
#include "my_zmq.h"


#define myLog               printf
#define CLASS               "MyZmq : "


static const int kSubBufSize = 8192;


MyZmq::MyZmq()
{
}

MyZmq::~MyZmq()
{
    m_ready             = false;
    if(m_context){
        zmq_ctx_destroy(m_context);
        m_context       = nullptr;
    }
}

// 发布模式 , ipc:///tmp/example.ipc ,  tcp://*:12345
void MyZmq::startPublisher(string addr, string filter)
{
    if(m_ready){myLog(CLASS"already start\n");return;}
    int ret;

    m_filter           = filter;
    m_addr             = addr;
    m_context          = zmq_ctx_new();
    m_fd               = zmq_socket(m_context,ZMQ_PUB);
    myLog(CLASS"pub = %s,filter = %s\n", m_addr.c_str(),m_filter.c_str());
    ret = zmq_bind(m_fd,m_addr.c_str());
    if(ret != 0){
        myLog(CLASS"zmq bind error,%s\n",strerror(errno));
        exit(1);
    }
    m_ready = true;
}

// 订阅模式 , ipc:///tmp/example.ipc ,  tcp://192.168.1.10:12345
void MyZmq::startSubscriber(string addr, string filter, ZmqCallBack callback)
{
    if(m_ready){myLog(CLASS"already start\n");return;}
    int ret;

    m_filter           = filter;
    m_addr             = addr;
    m_callback         = callback;
    m_context          = zmq_ctx_new();
    m_fd               = zmq_socket(m_context,ZMQ_SUB);
    myLog(CLASS"sub = %s,filter = %s\n",m_addr.c_str(),m_filter.c_str());
    ret = zmq_connect(m_fd,m_addr.c_str());
    if(ret != 0){
        myLog(CLASS"connect error,%s\n",strerror(errno));
        exit(1);
    }
    zmq_setsockopt(m_fd,ZMQ_SUBSCRIBE,m_filter.c_str(),m_filter.length());
    m_ready = true;
    std::thread tmp_thread(&MyZmq::run,this);
    tmp_thread.detach();
}

// 发送数据
void MyZmq::send(uint8_t *buffer, int len)
{
    if(!m_ready){
        myLog(CLASS"send error , zmq not start\n");
        return;
    }
    m_mutex.lock();
    if(m_filter.length() > 0 )zmq_send(m_fd,m_filter.c_str(),m_filter.length(),ZMQ_SNDMORE);
    zmq_send(m_fd,buffer,len,0);
    m_mutex.unlock();
}

// 订阅模式的线程里边，阻塞接收数据
void MyZmq::run()
{
    if(!m_callback)return;

    int len;
    uint8_t filter[100];
    uint8_t buffer[kSubBufSize];
    while(m_ready){
        if(m_filter.length() > 0)zmq_recv(m_fd,filter,sizeof(filter),0);
        len = zmq_recv(m_fd,buffer,kSubBufSize,0);
        if(len == -1){
            myLog(CLASS"recv failed(%d)\n",len);
            break;
        }
        if(len > kSubBufSize){
            myLog(CLASS"recv len(%d) > buffer len(%d)\n",len,kSubBufSize);
            continue;
        }
        m_callback(buffer,len,(void *)m_addr.c_str());
    }
    zmq_close(m_fd);
    m_fd = nullptr;
}

