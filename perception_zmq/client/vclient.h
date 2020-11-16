#ifndef __VCLIENT_H__
#define __VCLIENT_H__


#include <stdint.h>

// 开启zmq的tcp接收
void vclient_start(char *remote_ip ,uint16_t remote_port,uint16_t host_port);
// 开启监听端口的udp
void vclient_start_udp(uint16_t this_port);
void vclient_stop(void);


typedef enum{
    SIG_Y2G  = 1,	// 黄灯转绿灯信号
    SIG_OVER = 2,	// 消散时间结束信号
}TrafficSignal;
// 发送红绿灯信号给视觉那边
void vclient_send_signal(TrafficSignal signal,uint32_t camera);



#endif




