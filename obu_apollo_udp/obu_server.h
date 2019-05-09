#ifndef __OBU_SERVER_H__
#define __OBU_SERVER_H__

#include <stdint.h>

#define MSG_BUFFER_SIZE 1000

void obu_server_start(char *device,uint16_t port);
void obu_server_stop();
void obu_server_send(uint8_t *data, int len);

#endif

