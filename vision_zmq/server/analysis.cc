#include <stdio.h>
#include "analysis.h"
#include "vision.pb.h"

using namespace vision;


static void traffic_flow_fun(uint8_t *buffer,int len)
{
    TrafficFlow t;
    if(!t.ParseFromArray(buffer,len)){
        printf("vserver : traffic_flow parse failed\n");
        return;
    }

    if(t.flow_size() == 0)return;

    for(int i=0;i<t.flow_size();i++){
        if(t.flow(i).has_camera()){
            printf("vserver : traffic_flow  camera = %d",t.flow(i).camera());
        }
        if(t.flow(i).has_signal()){
            printf(",signal = %d",t.flow(i).signal());
        }
        printf("\n");
    }

}


void analysis(uint8_t *buffer,int len)
{
    Base base;
    if(!base.ParseFromArray(buffer,len)){
        printf("vserver : base parse failed\n");
        return;
    }
    switch (base.id()) {
    case TRAFFIC_FLOW:
        traffic_flow_fun(buffer,len);
        break;
    default:
        break;
    }

}


