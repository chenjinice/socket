#include <stdio.h>
#include <stdint.h>
#include "ars408_protocol.h"


float g_rms[32] = {0.005,0.006,0.008,0.011,0.014,0.018,0.023,0.029,
                  0.038,0.049,0.063,0.081,0.105,0.135,0.174,0.224,
                  0.288,0.371,0.478,0.616,0.794,1.023,1.317,1.697,
                  2.187,2.817,3.630,4.676,6.025,7.762,10.000,-1.0
                 };

float g_exist[8] = {-1,0.25,0.50,0.75,0.90,0.99,0.999,1.00};


int ars408_get_id(canid_t can_id)
{
    int id = (can_id & 0xF0) >> 5;
    return id;
}


int ars408_get_cmd(canid_t can_id)
{
    int cmd = can_id & (~(0xF0));
    return cmd;
}


std::string ars408_get_version(struct can_frame *pFrame)
{
    std::string version;
    uint8_t major = pFrame->data[0];
    uint8_t minor = pFrame->data[1];
    uint8_t patch = pFrame->data[2];

    char buffer[20] = {0};
    sprintf(buffer,"%d.%d.%d",major,minor,patch);
    version = buffer;
    return version;
}


int ars408_get_objectNum(struct can_frame *pFrame)
{
    uint8_t num = pFrame->data[0];
//    uint16_t meas_count = (pFrame->data[1] << 8) | pFrame->data[2];
//    printf("ARS408 object num === %d,meas_count === %d\n",num,meas_count);
    return num;
}


void ars408_get_objectGeneral(struct can_frame *pFrame, Ars408_ObjGeneral *info)
{
    __u8 *data = pFrame->data;
    int id = data[0];

    int lng_origin = (data[1] << 5) | (data[2] >> 3);
    float lng = lng_origin*0.2 - 500.0;

    int lat_origin = ((data[2] & 0b111) << 8) | data[3];
    float lat = lat_origin*0.2 - 204.6;

    int vlng_origin = (data[4] << 2) | (data[5] >> 6);
    float vlng = vlng_origin*0.25 - 128.00;

    int vlat_origin = ((data[5] & 0b111111) << 3 ) | (data[6] >> 5);
    float vlat = vlat_origin*0.25 - 64.00;

    float rcs = data[7]*0.5 - 64.0;

    if(info){
        info->id = id;
        info->lng = lng;
        info->lat = lat;
        info->v_lng = vlng;
        info->v_lat = vlat;
        info->rcs = rcs;
    }

//    printf("ARS408 object general: id=%d,lng=%f,lat=%f,vlng=%f,vlat=%f,rcs=%f\n",
//           id,lng,lat,vlng,vlat,rcs);
}


static float ars408_rms_value(int index)
{
    int g_rms_size = sizeof(g_rms);
    if( (index >= g_rms_size) || (index < 0) )index = g_rms_size-1;
    return g_rms[index];
}


static float ars408_exist_value(int index)
{
    int g_exist_size = sizeof(g_exist);
    if( (index >= g_exist_size) || (index < 0) )index = g_exist_size-1;
    return g_exist[index];
}


void ars408_get_objectQuality(can_frame *pFrame, Ars408_ObjQuality *info)
{
    __u8 *data = pFrame->data;
    int id = data[0];

    int lng_rms_origin = data[1] >> 3;
    float lng_rms = ars408_rms_value(lng_rms_origin);

    int lat_rms_origin = ((data[1] & 0b111) << 2) | (data[2] >> 6);
    float lat_rms = ars408_rms_value(lat_rms_origin);

    int vlng_rms_origin = (data[2] & 0b111110) >> 1;
    float vlng_rms = ars408_rms_value(vlng_rms_origin);

    int vlat_rms_origin = ((data[2] & 0b1) << 4) | (data[3] >> 4);
    float vlat_rms = ars408_rms_value(vlat_rms_origin);

    int exist_origin = data[6] >> 5;
    float exist = ars408_exist_value(exist_origin);

    uint8_t meas_state_origin = (data[6] << 0b11100) >> 2;

    if(info){
        info->id = id;
        info->lng_rms = lng_rms;
        info->lat_rms = lat_rms;
        info->v_lng_rms = vlng_rms;
        info->v_lat_rms = vlat_rms;
        info->exist = exist;
        info->meas_state = meas_state_origin;
    }

//    printf("ARS408 object quality :id=%d,lng=%f,lat=%f,vlng=%f,vlat=%f,exist=%f\n",
//           id,lng_rms,lat_rms,vlng_rms,vlat_rms,exist);
}


void ars408_get_objectExtend(struct can_frame *pFrame, Ars408_ObjExtend *info)
{
    __u8 *data = pFrame->data;
    int id = data[0];

    int class_origin = data[3] & 0b111;

    int angle_origin = (data[4] << 2) | (data[5] >> 6);
    float angle = angle_origin*0.4 - 180.0;

    float length = data[6]*0.2;
    float width = data[7]*0.2;

    if(info){
        info->id = id;
        info->object_class = class_origin;
        info->length = length;
        info->width = width;
    }

//    printf("ARS408 object extend: id=%d,class=%d,angle=%f,length=%f,width=%f\n",
//           id,class_origin,angle,length,width);
}








































