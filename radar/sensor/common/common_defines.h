#ifndef __COMMON_DEFINES_H__
#define __COMMON_DEFINES_H__



typedef struct {
    int   id;
    float lng;
    float lat;
    float v_lng;
    float v_lat;
    float rcs;
    float lng_rms;
    float lat_rms;
    float v_lng_rms;
    float v_lat_rms;
    float exist;
    int   object_class;
    float angle;
    float length;
    float width;
}Obstacle_Info;




#endif

