#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zmq.h>
#include "zmq/zmq_pub.h"


ZmqPub::ZmqPub()
{
    m_port = 12347;
    m_context = NULL;
    m_pub = NULL;
    m_filter = NULL;
    m_ready = false;
}

ZmqPub::~ZmqPub()
{
    this->stop();
}

bool ZmqPub::start(uint16_t port, char *filter)
{
    if(m_ready)return m_ready;
    int ret;

    m_filter = filter;
    // 创建服务端，用于发布消息
    char pub_endpoint[50] = {0};
    sprintf(pub_endpoint,"tcp://*:%d",m_port);
    printf("ZmqPub : zmq pub = %s , filter = %s\n",pub_endpoint,filter);
    m_context = zmq_ctx_new();
    m_pub = zmq_socket(m_context,ZMQ_PUB);
    ret = zmq_bind(m_pub,pub_endpoint);
    if(ret != 0){
        perror("ZmqPub : zmq bind error");
        m_ready = false;
    }else {
        m_ready = true;
    }

    return m_ready;
}

void ZmqPub::stop()
{
    m_ready = false;
    if(m_pub){
        zmq_close(m_pub);
        m_pub = NULL;
    }
    if(m_context){
        zmq_ctx_destroy(m_context);
        m_context = NULL;
    }
}

int ZmqPub::send(uint8_t *buffer, int len)
{
    int ret = -1;
    if(!m_ready)return ret;

    if(m_filter)zmq_send(m_pub,m_filter,strlen(m_filter),ZMQ_SNDMORE);
    ret = zmq_send(m_pub,buffer,len,0);

    return ret;
}




