#include <stdio.h>
#include "analysis.h"
#include "perception.pb.h"

using namespace perception;

void analysis(uint8_t *buffer,int len)
{
    PerceptionMsg msg;
    if(!msg.ParseFromArray(buffer,len)){
        printf("vserver : traffic_flow parse failed\n");
        return;
    }
    if(msg.event() != TRAFFIC_FLOW)return;
    if(!msg.has_flow_msg())return;

    const FlowMsg &flow_msg = msg.flow_msg();
    for(int i=0;i<flow_msg.flow_size();i++){
        const Flow & f = flow_msg.flow(i);
        if(f.has_camera())printf("vserver : traffic_flow  camera = %d",f.camera());
        if(f.has_signal())printf(",signal = %d",f.signal());
        printf("\n");
    }
}


