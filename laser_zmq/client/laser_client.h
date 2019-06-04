#ifndef __LASER_CLIENT_H__
#define __LASER_CLIENT_H__


#include <stdint.h>

void laser_client_start(char *remote_ip ,uint16_t remote_port);
void laser_client_stop(void);


#endif




