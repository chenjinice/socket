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
    int   id;       // 障碍id
    float lng;      // 纵向距离 m
    float lat;      // 横向距离 m
    float v_lng;    // 纵向速度 m/s
    float v_lat;    // 横向速度 m/s
    float rcs;      // 雷达截面积
}Ars408_ObjGeneral;


typedef struct {
    int   id;          // 障碍id
    float lng_rms;     // 纵向距离方差
    float lat_rms;     // 横向距离方差
    float v_lng_rms;   // 纵向速度方差
    float v_lat_rms;   // 横向速度方差
    float acc_lng_rms; // 纵向加速度方差
    float acc_lat_rms; // 横向加速度方差
    float orientation_rms; // 方向方差
    int   meas_state;
    float exist;       // 存在的概率
}Ars408_ObjQuality;


typedef struct {
    int   id;
    int   object_class; // 障碍类型：人、车等等，这东西不靠谱，没啥用
    float acc_lng;      // 纵向加速度
    float acc_lat;      // 横向加速度
    float angle;        // 角度 度数
    float length;       // 长 m
    float width;        // 宽 m
}Ars408_ObjExtend;


int  ars408_get_id(canid_t can_id);
int  ars408_get_cmd(canid_t can_id);
std::string ars408_get_version(struct can_frame *pFrame);
int  ars408_get_objectNum(struct can_frame *pFrame);
void ars408_get_objectGeneral(struct can_frame *pFrame,Ars408_ObjGeneral *info);
void ars408_get_objectQuality(struct can_frame *pFrame,Ars408_ObjQuality *info);
void ars408_get_objectExtend(struct can_frame *pFrame,Ars408_ObjExtend *info);

#endif


