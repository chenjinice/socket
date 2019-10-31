#include <stdio.h>

#include "obu_faw_sender.h"
#include "obu_faw.pb-c.h"


//  填充protobuf的 ObuMotion数据
int setMotionMsg(uint8_t *buffer ,int buff_size)
{
    static int msg_count = 0;
    ObuFaw__Msg msg = OBU_FAW__MSG__INIT;
    ObuFaw__ObuMotion motion = OBU_FAW__OBU_MOTION__INIT;
    msg.m_case = OBU_FAW__MSG__M_MOTION;
    msg.motion = &motion;
    motion.msgcount  = msg_count++;
    motion.longitude = 112.2345678*1e7;
    motion.latitude  = 24.1234567*1e7;
    motion.heading   = 100.12*100;
    motion.speed     = 60*100;
    motion.acc       = 1.00;
    motion.devid     = "100001";
    motion.gpstime   = 1234567890123;
    motion.altitude  = 63.11;
    int len = obu_faw__msg__get_packed_size(&msg);
    if(len > buff_size){
        return -1;
    }else{
        obu_faw__msg__pack(&msg,buffer);
        return len;
    }
}

// 填充protobuf的can数据
int setCanMsg(uint8_t *buffer ,int buff_size)
{
    static int msg_count = 0;
    ObuFaw__Msg msg = OBU_FAW__MSG__INIT;
    ObuFaw__CanInfo can = OBU_FAW__CAN_INFO__INIT;
    msg.m_case = OBU_FAW__MSG__M_CAN;
    msg.can = &can;
    can.msgcount    = msg_count++;
    can.devid       = "100001";
    can.trunlight   = "left";
    can.hazardlight = "on";
    can.brakestate  = "??";
    can.gasstatus   = "?";
    can.gearstate   = "P";
    can.wheelangle  = 300;
    can.drivestate  = "auto";
    can.abnormalstate = "?";
    can.gpstime     = 1234567890123;
    can.longitude   = 112.2345678*1e7;
    can.latitude    = 24.1234567*1e7;
    can.altitude    = 11.22;
    can.speed       = 60*100;
    can.heading     = 100.12*100;
    int len = obu_faw__msg__get_packed_size(&msg);
    if(len > buff_size){
        return -1;
    }else{
        obu_faw__msg__pack(&msg,buffer);
        return len;
    }
}



int main(int argc , char *argv[])
{
    obuFawSetMotionFun(setMotionMsg);
    obuFawSetCanFun(setCanMsg);
	
	// 最多加5个
    obuFawAdd("127.0.0.1",12333);
//    obuFawAdd("172.18.2.233",12333);

    while(1)sleep(1);
	return 0;
}






