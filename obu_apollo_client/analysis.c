#include <stdio.h>
#include "analysis.h"
#include "obu_apollo.pb-c.h"



void analysis(uint8_t *buffer,int len)
{

    ObuMsg *msg = obu_msg__unpack(NULL,len-5,buffer+4);
    if(msg == NULL){
        printf("client : obu msg unpack failed \n");
        return;
    }
    printf("count ==== %d\n",msg->count);

    int i;
    for(i=0;i<msg->n_obs;i++){
        Obstacle *obs= msg->obs[i];
        printf("obs[%d]:id=%d,type=%d,lat=%d,lng=%d\n",i,obs->id,obs->type,obs->lat,obs->lng);
    }

    obu_msg__free_unpacked(msg,NULL);

}


