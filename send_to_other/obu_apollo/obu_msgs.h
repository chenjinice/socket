#ifndef __OBU_MSGS_H__
#define __OBU_MSGS_H__


#include "obu_apollo.pb-c.h"


void print_interval(int num);
int time_interval(struct timeval *tv);
int get_obumsg_buffer(uint8_t *buffer,int buffer_size);
void obumsg_free(ObuApollo__ObuMsg *msg);
int obumsg_get_gps(uint8_t *buffer,int len);


#endif


