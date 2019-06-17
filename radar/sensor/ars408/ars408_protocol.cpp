#include <stdio.h>
#include <stdint.h>
#include "ars408_protocol.h"


// radar id : 0 - 7
static int g_id = -1;


int ars408_get_cmd(canid_t can_id)
{
    int cmd = can_id & (~(0xF0));
    g_id = (can_id & 0xF0) >> 5 ;
//    printf("radar id == %d\n",g_id);
    return cmd;
}


void ars408_get_version(struct can_frame *pFrame)
{
    uint8_t major = pFrame->data[0];
    uint8_t minor = pFrame->data[1];
    uint8_t patch = pFrame->data[2];
    printf("ARS408 software version = %d.%d.%d\n",major,minor,patch);
}


int ars408_get_objectNum(struct can_frame *pFrame)
{
    uint8_t num = pFrame->data[0];
//    uint16_t count = (pFrame->data[1] << 8) | pFrame->data[2];
//    printf("num === %d,count === %d\n",num,count);
    return num;
}


void ars408_get_objectInfo(struct can_frame *pFrame)
{
    int8_t temp;
    int id = pFrame->data[0];

    int lng_origin = (pFrame->data[1] << 5) | (pFrame->data[2] >> 3);
    float lng = lng_origin*0.2 - 500.0;

    int lat_origin = ((pFrame->data[2] & 0x07) << 8) | pFrame->data[3];
    float lat = lat_origin*0.2 - 204.6;

    int vlng_origin = (pFrame->data[4] << 2) | (pFrame->data[5] >> 6);
    float vlng = vlng_origin*0.25 - 128.00;

    int vlat_origin = ((pFrame->data[5] & 0x3F) << 3 ) | (pFrame->data[6] >> 5);
    float vlat = vlat_origin*0.25 - 64.00;

    float rcs = pFrame->data[7]*0.5 - 64.0;

    printf("id=%d,lng=%f,lat=%f,vlng=%f,vlat=%f,rcs=%f\n",
           id,lng,lat,vlng,vlat,rcs);
}


void ars408_get_objectQuality(can_frame *pFrame)
{

}





































