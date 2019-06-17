#ifndef __ARS408_PROTOCOL_H__
#define __ARS408_PROTOCOL_H__


#include <linux/can.h>

typedef enum{
    ARS408_CMD_RADAR_CONFIG = 0x200,
    ARS408_CMD_RADAR_STATE = 0x201,
    ARS408_CMD_OBJECT_FILTER = 0x202,
    ARS408_CMD_STATE_HEADER = 0x203,
    ARS408_CMD_CONFIG_STATE = 0x204,
    ARS408_CMD_COLLISION_CONFIG = 0x400,
    ARS408_CMD_COLLISION_REGION_CONFIG = 0x401,
    ARS408_CMD_COLLISION_REGION_STATE = 0x402,
    ARS408_CMD_COLLISION_STATE = 0x408,
    ARS408_CMD_CLUSTER_LIST = 0x600,
    ARS408_CMD_OBJECT_LIST = 0x60A,
    ARS408_CMD_OBJECT_INFO = 0x60B,
    ARS408_CMD_OBJECT_QUALITY = 0x60C,
    ARS408_CMD_OBJECT_EXTEND = 0x60D,
    ARS408_CMD_OBJECT_WARNING = 0x60E,
    ARS408_CMD_VERSION = 0x700,
    ARS408_CMD_CLUSTER_INFO = 0x701,
    ARS408_CMD_CLUSTER_QUALITY = 0x702
}ARS408_CMD;


int  ars408_get_cmd(canid_t can_id);
void ars408_get_version(struct can_frame *pFrame);
int  ars408_get_objectNum(struct can_frame *pFrame);
void ars408_get_objectInfo(struct can_frame *pFrame);
void ars408_get_objectQuality(struct can_frame *pFrame);

#endif


