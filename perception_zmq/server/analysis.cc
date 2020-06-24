#include <stdio.h>
#include "analysis.h"
#include "perception.pb.h"

using namespace perception;


extern void process_signal(Flow_TrafficSig sig,int camera_id);


void analysis(uint8_t *buffer,int len)
{
    PerceptionMsg msg;
    if(!msg.ParseFromArray(buffer,len)){
        printf("vserver : PerceptionMsg parse failed\n");
        return;
    }
    if(msg.event() != TRAFFIC_FLOW)return;
    if(!msg.has_flow_msg())return;

    const FlowMsg &flow_msg = msg.flow_msg();
    for(int i=0;i<flow_msg.flow_size();i++){
        const Flow & f = flow_msg.flow(i);
        if(!f.has_camera())continue;
        if(!f.has_signal())continue;
        printf("vserver : traffic_flow , sig = %d, camera = %d\n",f.signal(),f.camera());
        process_signal(f.signal(),f.camera());
    }
}

