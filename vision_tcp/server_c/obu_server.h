#ifndef __OBU_SERVER__
#define __OBU_SERVER__

#include <stdint.h>

#define MSG_BUFFER_SIZE 1400

void obu_server_start(uint16_t port);
void obu_server_stop();
void obu_server_send(uint8_t *data, int len);


#endif
