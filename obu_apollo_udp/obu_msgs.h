#ifndef __OBU_MSGS_H__
#define __OBU_MSGS_H__

#include "obu_apollo.pb-c.h"

void mysleep(uint32_t ms);
int time_interval(struct timeval *tv);
int obumsg_init(ObuApollo__ObuMsg *msg);
void obumsg_free(ObuApollo__ObuMsg *msg);
int obumsg_get_gps(uint8_t *buffer,int len);

#endif


