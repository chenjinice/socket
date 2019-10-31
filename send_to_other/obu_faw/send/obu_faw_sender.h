#ifndef __OBU_FAW_SENDER_H__
#define __OBU_FAW_SENDER_H__


#include <stdint.h>


typedef int (*fawfun_t)(uint8_t *buffer,int buff_size);



// fun这个函数用来填充ObuMtion数据，内部会周期性调用 
void obuFawSetMotionFun(fawfun_t fun);

// fun这个函数用来填充Can数据，内部会周期性调用 
void obuFawSetCanFun(fawfun_t fun);

// 添加要发送数据的ip和端口 , 最多5个
void obuFawAdd(char *ip,uint16_t port);

// 停止发送线程，关闭socket
void obuFawStop();




#endif




