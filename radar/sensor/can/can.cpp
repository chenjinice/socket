#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <stdio.h>
#include "can.h"


Can::Can()
{
    m_fd = -1;
    m_ready = false;
}

Can::~Can()
{
    if(m_fd != -1)shutdown(m_fd , SHUT_RDWR);
}


bool Can::can_open(char *dev)
{
    struct sockaddr_can addr;
    struct ifreq ifr;

    m_fd = socket(PF_CAN,SOCK_RAW,CAN_RAW);
    strcpy(ifr.ifr_name,dev);
    if(ioctl(m_fd,SIOCGIFINDEX,&ifr) <0 ){
        perror("can ioctl error");
        return m_ready;
    }
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if( bind(m_fd,(struct sockaddr *)&addr,sizeof(addr)) < 0 ){
        perror("can bind error");
    }else{
        m_ready = true;
    }
    return m_ready;
}


int Can::can_write(can_frame *pFrame)
{
    int ret = -1;
    if(!m_ready)return ret;

    ret = sendto(m_fd,pFrame,sizeof(struct can_frame),0,NULL,0);
    return ret;
}


int Can::can_read(can_frame *pFrame)
{
    int ret = -1;
    if(!m_ready)return ret;

    ret = recvfrom(m_fd,pFrame,sizeof(struct can_frame),0,NULL,NULL);
    return ret;
}


