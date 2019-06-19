#ifndef __ARS408_PROTOCOL_H__
#define __ARS408_PROTOCOL_H__


#include <linux/can.h>
#include <iostream>

typedef enum{
    ARS408_CMD_RELAY = 0x8,
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
    ARS408_CMD_OBJECT_GENERAL = 0x60B,
    ARS408_CMD_OBJECT_QUALITY = 0x60C,
    ARS408_CMD_OBJECT_EXTEND = 0x60D,
    ARS408_CMD_OBJECT_WARNING = 0x60E,
    ARS408_CMD_VERSION = 0x700,
    ARS408_CMD_CLUSTER_INFO = 0x701,
    ARS408_CMD_CLUSTER_QUALITY = 0x702
}Ars408_Cmd;


typedef struct {
    int   id;
    float lng;
    float lat;
    float v_lng;
    float v_lat;
    float rcs;
}Ars408_ObjGeneral;


typedef struct {
    int   id;
    float lng_rms;
    float lat_rms;
    float v_lng_rms;
    float v_lat_rms;
    float acc_lng_rms;
    float acc_lat_rms;
    float orientation_rms;
    int   meas_state;
    float exist;
}Ars408_ObjQuality;


typedef struct {
    int   id;
    int   object_class;
    float acc_lng;
    float acc_lat;
    float angle;
    float length;
    float width;
}Ars408_ObjExtend;


int  ars408_get_id(canid_t can_id);
int  ars408_get_cmd(canid_t can_id);
std::string ars408_get_version(struct can_frame *pFrame);
int  ars408_get_objectNum(struct can_frame *pFrame);
void ars408_get_objectGeneral(struct can_frame *pFrame,Ars408_ObjGeneral *info);
void ars408_get_objectQuality(struct can_frame *pFrame,Ars408_ObjQuality *info);
void ars408_get_objectExtend(struct can_frame *pFrame,Ars408_ObjExtend *info);

#endif


