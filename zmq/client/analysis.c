#include <stdio.h>
#include <sys/time.h>
#include "analysis.h"
#include "vision.pb-c.h"


static void crowd_fun(uint8_t *buffer,int length)
{
    int i;
    Vision__Crowd *c = vision__crowd__unpack(NULL,length,buffer);
    if(c == NULL){
        printf("vclient : crowd unpack failed \n");
        return;
    }
    printf("vclient : [%d crowd]\n",c->n_pedestrian);

    for(i=0;i<c->n_pedestrian;i++){
        Vision__Pedestrian * p = c->pedestrian[i];
        printf("vclient : pedestrian[%d],type=%d,camera=%d,x=%d,y=%d\n",i,p->object_type,p->camera,p->x,p->y);
    }
    vision__crowd__free_unpacked(c,NULL);
}


static void obstacles_fun(uint8_t *buffer,int length)
{
    int i;
    Vision__Obstacles *obs = vision__obstacles__unpack(NULL,length,buffer);
    if(obs == NULL){
        printf("vclient : obstacles unpack failed \n");
        return;
    }
    printf("vclient : [%d  obstacles]\n",obs->n_array);

    for(i=0;i<obs->n_array;i++){
        Vision__Obstacle * p = obs->array[i];
        printf("vclient : obstacle[%d],id=%d,lane_id=%d,camera=%d,x=%d,y=%d\n",i,p->object_id,p->lane_id,p->camera,p->x,p->y);
    }
    vision__obstacles__free_unpacked(obs,NULL);
}


static void availableAreas_fun(uint8_t *buffer,int length)
{
    int i;
    Vision__AvailableAreas *area = vision__available_areas__unpack(NULL,length,buffer);
    if(area == NULL){
        printf("vclient : available areas unpack failed \n");
        return;
    }
    printf("vclient : [%d  available areas]\n",area->n_area);

    for(i=0;i<area->n_area;i++){
        Vision__AvailableArea *p = area->area[i];
        printf("vclient : area[%d],camera=%d,x1=%d,y1=%d,x2=%d,y2=%d\n",i,p->camera,p->x1,p->y1,p->x2,p->y2);
    }
    vision__available_areas__free_unpacked(area,NULL);
}


void analysis(uint8_t *buffer,int len)
{
    Vision__ID	id =  -1;
    Vision__Base *base = vision__base__unpack(NULL,len,buffer);
    if(base == NULL){
        printf("vclient : base unpack failed,len = %d \n",len);
        return;
    }
    id = base->id;
    vision__base__free_unpacked(base,NULL);

    switch(id)
    {
    case VISION__ID__PEDESTRIAN_D:      // 行人与动物闯入检测
        crowd_fun(buffer,len);
        break;
    case VISION__ID__ILLEGAL_V1:        // 违章车辆1(违停)
        break;
    case VISION__ID__CAMERA_CAL:        // 超视距视频感知(相机标定信息)
        break;
    case VISION__ID__ROCKFALL_D:        // 落石/抛撒物检测
        break;
    case VISION__ID__VISIBILITY:        // 白天能见度检测
        break;
    case VISION__ID__AVAILABLE_AREA:    // 可行驶区域检测
        availableAreas_fun(buffer,len);
        break;
    case VISION__ID__ABNORMAL_CAR:      // 异常车辆检测
        break;
    case VISION__ID__ILLEGAL_V2:        // 违章车辆2(应急车道)
        break;
    case VISION__ID__TRAFFIC_STATUS:    // 交通态势感知
        crowd_fun(buffer,len);
        break;
    case VISION__ID__BACKWARD_DRIVING:  // 逆向行驶告警
        break;
    case VISION__ID__ROAD_DANGER:       // 道路危险状况提醒(抛洒物)
        break;
    case VISION__ID__FIRE_SMOKE:        // 隧道内火焰与烟雾预警
        break;
    default:
        break;
    }

}


