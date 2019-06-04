#include <stdio.h>
#include <sys/time.h>
#include "analysis.h"
#include "laser.pb-c.h"


void analysis(uint8_t *buffer,int len)
{
    Laser__LaserMsg *msg = laser__laser_msg__unpack(NULL,len,buffer);
    if(msg == NULL){
        printf("laser_client : laser msg unpack failed,len = %d \n",len);
        return;
    }

    int i;
    for(i=0;i<msg->n_objs;i++){
        Laser__LaserObj * p = msg->objs[i];
        printf("laser obj [%d] : id=%d,lng=%d,lat=%d\n",i,p->object_id,p->lng,p->lat);
    }

}


