#include <stdio.h>
#include <sys/time.h>
#include "analysis.h"
#include "vision.pb-c.h"

// 行人与动物闯入检测
static void pedestrian_fun(uint8_t *buffer,int length)
{
    int i;
    Vision__Crowd *c = vision__crowd__unpack(NULL,length,buffer);
    if(c == NULL){
        printf("vclient : crowd unpack failed \n");
        return;
    }
    printf("vclient : [%d pedestrian] --- %s\n",c->n_pedestrian,__FUNCTION__);

    for(i=0;i<c->n_pedestrian;i++){
        Vision__Pedestrian * p = c->pedestrian[i];
        printf("vclient : pedestrian[%d],type=%d,camera=%d,lng=%d,lat=%d\n",i,p->object_type,p->camera,p->lng,p->lat);
    }
    vision__crowd__free_unpacked(c,NULL);
}

// 违章车辆1(违停)
static void illegal1_fun(uint8_t *buffer,int length)
{
    int i;
    Vision__IllegalCarWarn *c = vision__illegal_car_warn__unpack(NULL,length,buffer);
    if(c == NULL){
        printf("vclient : illegalCarWarn unpack failed \n");
        return;
    }
    printf("vclient : [%d car] --- %s\n",c->n_array,__FUNCTION__);

    for(i=0;i<c->n_array;i++){
        Vision__AbnormalCar * p = c->array[i];
        printf("vclient : car[%d],camera=%d,lng=%d,lat=%d,lane_id=%d\n",i,p->camera,p->lng,p->lat,p->lane_id);
    }
    vision__illegal_car_warn__free_unpacked(c,NULL);
}

// 白天能见度检测
static void visibility_fun(uint8_t *buffer,int length)
{
    Vision__Visibility *c = vision__visibility__unpack(NULL,length,buffer);
    if(c == NULL){
        printf("vclient : visibility unpack failed \n");
        return;
    }
    printf("vclient : visible distance = %lf, level = %d --- %s\n",c->distance,c->level,__FUNCTION__);
    vision__visibility__free_unpacked(c,NULL);
}

// 可行驶区域检测
static void availableAreas_fun(uint8_t *buffer,int length)
{
    int i;
    Vision__AvailableAreas *area = vision__available_areas__unpack(NULL,length,buffer);
    if(area == NULL){
        printf("vclient : available areas unpack failed \n");
        return;
    }
    printf("vclient : [%d  available areas] --- %s\n",area->n_area,__FUNCTION__);

    for(i=0;i<area->n_area;i++){
        Vision__AvailableArea *p = area->area[i];
        printf("vclient : area[%d],camera=%d,lng1=%d,lat1=%d,lng2=%d,lat2=%d,lng3=%d,lat3=%d,lng4=%d,lat4=%d\n",
               i,p->camera,p->lng1,p->lat1,p->lng2,p->lat2,p->lng3,p->lat3,p->lng4,p->lat4);
    }
    vision__available_areas__free_unpacked(area,NULL);
}

// 异常车辆检测(静止)
static void abnormal_fun(uint8_t *buffer,int length)
{
    int i;
    Vision__IllegalCarWarn *c = vision__illegal_car_warn__unpack(NULL,length,buffer);
    if(c == NULL){
        printf("vclient : illegalCarWarn unpack failed \n");
        return;
    }
    printf("vclient : [%d car] --- %s\n",c->n_array,__FUNCTION__);

    for(i=0;i<c->n_array;i++){
        Vision__AbnormalCar * p = c->array[i];
        printf("vclient : car[%d],camera=%d,lng=%d,lat=%d\n",i,p->camera,p->lng,p->lat);
    }
    vision__illegal_car_warn__free_unpacked(c,NULL);
}

// 违章车辆2(应急车道)
static void illegal2_fun(uint8_t *buffer,int length)
{
    int i;
    Vision__IllegalCarWarn *c = vision__illegal_car_warn__unpack(NULL,length,buffer);
    if(c == NULL){
        printf("vclient : illegalCarWarn unpack failed \n");
        return;
    }
    printf("vclient : [%d car] --- %s\n",c->n_array,__FUNCTION__);
    if(c->time)printf("++++++++++++++++++++++++++=time = %lld : %d \n",c->time->sec,c->time->usec);

    for(i=0;i<c->n_array;i++){
        Vision__AbnormalCar * p = c->array[i];
        printf("vclient : car[%d],camera=%d,lng=%d,lat=%d\n",i,p->camera,p->lng,p->lat);
    }
    vision__illegal_car_warn__free_unpacked(c,NULL);
}

// 交通态势感知
static void traffic_fun(uint8_t *buffer,int length)
{
    int i;
    Vision__Crowd *c = vision__crowd__unpack(NULL,length,buffer);
    if(c == NULL){
        printf("vclient : crowd unpack failed \n");
        return;
    }
    printf("vclient : [%d pedestrian] --- %s\n",c->n_pedestrian,__FUNCTION__);

    for(i=0;i<c->n_pedestrian;i++){
        Vision__Pedestrian * p = c->pedestrian[i];
        printf("vclient : pedestrian[%d],type=%d,camera=%d,lng=%d,lat=%d\n",i,p->object_type,p->camera,p->lng,p->lat);
    }
    vision__crowd__free_unpacked(c,NULL);
}


// 逆向行驶告警
static void backward_fun(uint8_t *buffer,int length)
{
    int i;
    Vision__IllegalCarWarn *c = vision__illegal_car_warn__unpack(NULL,length,buffer);
    if(c == NULL){
        printf("vclient : illegalCarWarn unpack failed \n");
        return;
    }
    printf("vclient : [%d car] --- %s\n",c->n_array,__FUNCTION__);

    for(i=0;i<c->n_array;i++){
        Vision__AbnormalCar * p = c->array[i];
        printf("vclient : car[%d],camera=%d,lng=%d,lat=%d,lane_id=%d\n",i,p->camera,p->lng,p->lat,p->lane_id);
    }
    vision__illegal_car_warn__free_unpacked(c,NULL);
}

// 道路危险状况提醒(抛洒物)
static void road_danger_fun(uint8_t *buffer,int length)
{
    int i;
    Vision__Obstacles *obs = vision__obstacles__unpack(NULL,length,buffer);
    if(obs == NULL){
        printf("vclient : obstacles unpack failed \n");
        return;
    }
    printf("vclient : [%d  obstacles] --- %s\n",obs->n_array,__FUNCTION__);

    for(i=0;i<obs->n_array;i++){
        Vision__Obstacle * p = obs->array[i];
        printf("vclient : obstacle[%d],id=%d,lane_id=%d,camera=%d,lng=%d,lat=%d\n",i,p->object_id,p->lane_id,p->camera,p->lng,p->lat);
    }
    vision__obstacles__free_unpacked(obs,NULL);
}

// 隧道内火焰与烟雾预警
static void smoke_fun(uint8_t *buffer,int length)
{
    Vision__SmokeWarn *c = vision__smoke_warn__unpack(NULL,length,buffer);
    if(c == NULL){
        printf("vclient : smokeWarn unpack failed \n");
        return;
    }
    printf("vclient : warn = %d --- %s\n",c->warn,__FUNCTION__);
    vision__smoke_warn__free_unpacked(c,NULL);
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
        pedestrian_fun(buffer,len);
        break;
    case VISION__ID__ILLEGAL_V1:        // 违章车辆1(违停)
        illegal1_fun(buffer,len);
        break;
    case VISION__ID__VISIBILITY:        // 白天能见度检测
        visibility_fun(buffer,len);
        break;
    case VISION__ID__AVAILABLE_AREA:    // 可行驶区域检测
        availableAreas_fun(buffer,len);
        break;
    case VISION__ID__ABNORMAL_CAR:      // 异常车辆检测(静止)
        abnormal_fun(buffer,len);
        break;
    case VISION__ID__ILLEGAL_V2:        // 违章车辆2(应急车道)
        illegal2_fun(buffer,len);
        break;
    case VISION__ID__TRAFFIC_STATUS:    // 交通态势感知
        traffic_fun(buffer,len);
        break;
    case VISION__ID__BACKWARD_DRIVING:  // 逆向行驶告警
        backward_fun(buffer,len);
        break;
    case VISION__ID__ROAD_DANGER:       // 道路危险状况提醒(抛洒物)
        road_danger_fun(buffer,len);
        break;
    case VISION__ID__FIRE_SMOKE:        // 隧道内火焰与烟雾预警
        smoke_fun(buffer,len);
        break;
    default:
        break;
    }

}


