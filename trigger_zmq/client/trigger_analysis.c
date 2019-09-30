#include <stdio.h>
#include <sys/time.h>
#include "trigger_analysis.h"
#include "trigger.pb-c.h"


// 抓拍物
static void snap_fun(uint8_t *buffer,int length)
{
    int i;
    Trigger__SnapMsg *msg = trigger__snap_msg__unpack(NULL,length,buffer);
    if(msg == NULL){
        mylog("SnapMsg unpack failed\n");
        return;
    }
    mylog("[%d SnapObj] --- %s\n",msg->n_array,__FUNCTION__);
    for(i=0;i<msg->n_array;i++){
        Trigger__SnapObj *p = msg->array[i];
        mylog("SnapObj[%d],lng=%d,lat=%d,speed=%d,type=%d,camera=%d\n",i,p->lng,p->lat,p->speed,p->type,p->camera);
    }
    trigger__snap_msg__free_unpacked(msg,NULL);
}


// 解析
void trigger_analysis(uint8_t *buffer,int len)
{
    Trigger__ID	id =  -1;
    Trigger__Base *base = trigger__base__unpack(NULL,len,buffer);
    if(base == NULL){
        printf("vclient : base unpack failed,len = %d \n",len);
        return;
    }
    id = base->id;
    trigger__base__free_unpacked(base,NULL);

    switch(id)
    {
        case TRIGGER__ID__SNAP:             // 抓拍物
            snap_fun(buffer,len);
            break;
        default:
            break;
    }

}


