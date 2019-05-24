#ifndef __VCLIENT_H__
#define __VCLIENT_H__


#include <stdint.h>

void vclient_start(char *remote_ip ,uint16_t remote_port,uint16_t host_port);
void vclient_stop(void);


typedef enum{
    SIG_Y2G = 1,
    SIG_OVER = 2,
}TRAFFIC_SIGNAL;
void vclient_send_signal(TRAFFIC_SIGNAL signal,uint32_t camera);



#endif




