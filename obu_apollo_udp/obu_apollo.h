#ifndef __OBU_APOLLO_H__
#define __OBU_APOLLO_H__

#include <stdint.h>

#define MSG_BUFFER_SIZE 1000

void obu_apollo_start(char *device,uint16_t port);
void obu_apollo_stop();
void obu_apollo_send(uint8_t *data, int len);

#endif

