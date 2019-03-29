#ifndef __OBU_SERVER__
#define __OBU_SERVER__

#include <stdint.h>

void obu_server_start(uint16_t port);
void obu_server_stop();
void obu_server_send();


#endif
