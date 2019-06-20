#ifndef __ZMQ_PUB_H__
#define __ZMQ_PUB_H__

#include <stdint.h>
#include <iostream>

// zmq 发布端
class ZmqPub{
public:
    ZmqPub();
    ~ZmqPub();
    bool start(uint16_t port,char *filter);
    void stop();
    int  send(uint8_t *buffer,int len);

private:
    uint16_t m_port;
    void    *m_context;
    void    *m_pub;
    char    *m_filter;
    bool     m_ready;
};


#endif

