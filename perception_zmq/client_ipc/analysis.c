#include <stdio.h>
#include <sys/time.h>
#include "analysis.h"


// 发给融合程序的，rsu里边不需要这段代码
static void to_fusion_fun(Perception__PerceptionMsg *p)
{
    int i;
    Perception__TargetMsg * msg = p->target_msg;
    if(msg == NULL)return;
    for(i=0;i<msg->n_target;i++){
        Perception__Target * t = msg->target[i];
        int camera = t->has_camera ? t->camera : -1;
        printf("=%02d=:target[%d],lon=%d,lat=%d,type=%d,camera=%d\n",p->event,i,t->pos->lon,t->pos->lat,t->type,camera);
    }
}

// 行人与动物闯入检测
static void pedestrian_fun(Perception__PerceptionMsg *p)
{
    int i;
    Perception__TargetMsg * msg = p->target_msg;
    if(msg == NULL)return;
    for(i=0;i<msg->n_target;i++){
        Perception__Target * t = msg->target[i];
        int camera = t->has_camera ? t->camera : -1;
        printf("=%02d=:target[%d],lon=%d,lat=%d,type=%d,camera=%d\n",p->event,i,t->pos->lon,t->pos->lat,t->type,camera);
    }
}

// 违章车辆1(违停)
static void illegal1_fun(Perception__PerceptionMsg *p)
{
    int i;
    Perception__TargetMsg * msg = p->target_msg;
    if(msg == NULL)return;
    for(i=0;i<msg->n_target;i++){
        Perception__Target * t = msg->target[i];
        int camera = t->has_camera ? t->camera : -1;
        printf("=%02d=:target[%d],lon=%d,lat=%d,type=%d,camera=%d\n",p->event,i,t->pos->lon,t->pos->lat,t->type,camera);
    }
}

// 白天能见度检测
static void visibility_fun(Perception__PerceptionMsg *p)
{
    Perception__VisibilityMsg * msg = p->visibility_msg;
    if(msg == NULL)return;
    printf("=%02d=: visibility distance = %f,level = %d\n",p->event,msg->distance,msg->level);
}

// 可行驶区域检测
static void availableAreas_fun(Perception__PerceptionMsg *p)
{
    int i , m;
    Perception__LaneAreaMsg * msg = p->lane_area_msg;
    if(msg == NULL)return;
    for(i=0;i<msg->n_area;i++){
        Perception__LaneArea * a = msg->area[i];
        if(a->n_pos != 4)continue;                  // 4个经纬度点
        printf("=%02d=:area[%d],pos=",p->event,i);
        for(m=0;m<4;m++)printf("(%d,%d),",a->pos[m]->lon,a->pos[m]->lat);
        printf("\n");
    }
}

// 异常车辆检测(静止)
static void abnormal_fun(Perception__PerceptionMsg *p)
{
    int i;
    Perception__TargetMsg * msg = p->target_msg;
    if(msg == NULL)return;
    for(i=0;i<msg->n_target;i++){
        Perception__Target * t = msg->target[i];
        int status = t->car_status ? t->car_status : 0;
        printf("=%02d=:target[%d],lon=%d,lat=%d,type=%d,status=%d\n",p->event,i,t->pos->lon,t->pos->lat,t->type,status);
    }
}

// 违章车辆2(应急车道)
static void illegal2_fun(Perception__PerceptionMsg *p)
{
    int i;
    Perception__TargetMsg * msg = p->target_msg;
    if(msg == NULL)return;
    for(i=0;i<msg->n_target;i++){
        Perception__Target * t = msg->target[i];
        int camera = t->has_camera ? t->camera : -1;
        printf("=%02d=:target[%d],lon=%d,lat=%d,type=%d,camera=%d\n",p->event,i,t->pos->lon,t->pos->lat,t->type,camera);
    }
}

// 交通态势感知
static void traffic_fun(Perception__PerceptionMsg *p)
{
    int i;
    Perception__TargetMsg * msg = p->target_msg;
    if(msg == NULL)return;
    for(i=0;i<msg->n_target;i++){
        Perception__Target * t = msg->target[i];
        int camera = t->has_camera ? t->camera : -1;
        printf("=%02d=:target[%d],lon=%d,lat=%d,type=%d,camera=%d\n",p->event,i,t->pos->lon,t->pos->lat,t->type,camera);
    }
}

// 逆向行驶告警
static void backward_fun(Perception__PerceptionMsg *p)
{
    int i;
    Perception__TargetMsg * msg = p->target_msg;
    if(msg == NULL)return;
    for(i=0;i<msg->n_target;i++){
        Perception__Target * t = msg->target[i];
        int camera = t->has_camera ? t->camera : -1;
        printf("=%02d=:target[%d],lon=%d,lat=%d,type=%d,camera=%d\n",p->event,i,t->pos->lon,t->pos->lat,t->type,camera);
    }
}

// 道路危险状况提醒(抛洒物)
static void road_danger_fun(Perception__PerceptionMsg *p)
{
    int i;
    Perception__TargetMsg * msg = p->target_msg;
    if(msg == NULL)return;
    for(i=0;i<msg->n_target;i++){
        Perception__Target * t = msg->target[i];
        printf("=%02d=:target[%d],lon=%d,lat=%d,type=%d\n",p->event,i,t->pos->lon,t->pos->lat,t->type);
    }
}

// 隧道内火焰与烟雾预警
static void smoke_fun(Perception__PerceptionMsg *p)
{
    Perception__WarnMsg * msg = p->warn_msg;
    if(msg == NULL)return;
    printf("=%02d=:smoke warn=%d\n",p->event,msg->warn);
}

// 前方拥堵提醒
static void jam_fun(Perception__PerceptionMsg *p)
{
    int i , m;
    Perception__JamMsg * msg = p->jam_msg;
    if(msg == NULL)return;
    for(i=0;i<msg->n_jam;i++){
        Perception__Jam * j = msg->jam[i];
        printf("=%02d=:jam[%d]num=%d,velocity=%f,heading=%f,flow=",p->event,i,j->vehicle_num,j->vehicle_velocity,j->lane_heading);
        for(m=0;m<j->n_vehicle_flow;m++)printf("%d,",j->vehicle_flow[m]);
        printf("\n");
    }
}

// 动态配时场景
static void traffic_flow_fun(Perception__PerceptionMsg *p)
{
    int i , m;
    Perception__FlowMsg * msg = p->flow_msg;
    if(msg == NULL)return;
    for(i=0;i<msg->n_flow;i++){
        Perception__Flow * f = msg->flow[i];
        printf("=%02d=:flow[%d]num=",p->event,i);
        for(m=0;m<f->n_vehicle_num;m++)printf("%d,",f->vehicle_num[m]);
        printf("pass=");
        for(m=0;m<f->n_pass_num;m++)printf("%d,",f->pass_num[m]);
        printf("\n");
    }
}

// 特殊车辆
static void special_car_fun(Perception__PerceptionMsg *p)
{
    int i;
    Perception__TargetMsg * msg = p->target_msg;
    if(msg == NULL)return;
    for(i=0;i<msg->n_target;i++){
        Perception__Target * t = msg->target[i];
        int car_type = t->has_car_type ? t->car_type : -1;
        printf("=%02d=:target[%d],lon=%d,lat=%d,type=%d,car_type=%d\n",p->event,i,t->pos->lon,t->pos->lat,t->type,car_type);
    }
}

// 交通事故
static void accident_area_fun(Perception__PerceptionMsg *p)
{
    int i , m;
    Perception__LaneAreaMsg * msg = p->lane_area_msg;
    if(msg == NULL)return;
    for(i=0;i<msg->n_area;i++){
        Perception__LaneArea * a = msg->area[i];
        if(a->n_pos != 4)continue;                  // 4个经纬度点
        printf("=%02d=:area[%d],pos=",p->event,i);
        for(m=0;m<4;m++)printf("(%d,%d),",a->pos[m]->lon,a->pos[m]->lat);
        printf("\n");
    }
}

// 结冰
static void ice_fun(Perception__PerceptionMsg *p)
{
    Perception__WarnMsg * msg = p->warn_msg;
    if(msg == NULL)return;
    printf("=%02d=:ice warn=%d\n",p->event,msg->warn);
}

// 车道线磨损
static void lane_ware_fun(Perception__PerceptionMsg *p)
{
    int i , m;
    Perception__LaneAreaMsg * msg = p->lane_area_msg;
    if(msg == NULL)return;
    for(i=0;i<msg->n_area;i++){
        Perception__LaneArea * a = msg->area[i];
        if(a->n_pos != 2)continue;                  // 2个经纬度点
        printf("=%02d=:area[%d],pos=",p->event,i);
        for(m=0;m<2;m++)printf("(%d,%d),",a->pos[m]->lon,a->pos[m]->lat);
        printf("\n");
    }
}


#include <stdlib.h>
// 解析
void analysis(uint8_t *buffer,int len)
{
    Perception__PerceptionMsg *p = perception__perception_msg__unpack(NULL,len,buffer);
    if(p == NULL){
        printf("vclient : PerceptionMsg unpack failed,len = %d \n",len);
        return;
    }
    Perception__EventId event = p->event;
    switch(event)
    {
        case PERCEPTION__EVENT_ID__TARGET_TO_FUSION:  // 发给融合程序的，rsu里边不需要这段代码
            to_fusion_fun(p);
            break;
        case PERCEPTION__EVENT_ID__PEDESTRIAN:        // 行人与动物闯入检测
            pedestrian_fun(p);
            break;
        case PERCEPTION__EVENT_ID__ILLEGAL_V1:        // 违章车辆1(违停)
            illegal1_fun(p);
            break;
        case PERCEPTION__EVENT_ID__VISIBILITY:        // 白天能见度检测
            visibility_fun(p);
            break;
        case PERCEPTION__EVENT_ID__AVAILABLE_AREA:    // 可行驶区域检测
            availableAreas_fun(p);
            break;
        case PERCEPTION__EVENT_ID__ABNORMAL_CAR:      // 异常车辆检测(静止)
            abnormal_fun(p);
            break;
        case PERCEPTION__EVENT_ID__ILLEGAL_V2:        // 违章车辆2(应急车道)
            illegal2_fun(p);
            break;
        case PERCEPTION__EVENT_ID__TRAFFIC_STATUS:    // 交通态势感知
            traffic_fun(p);
            break;
        case PERCEPTION__EVENT_ID__BACKWARD_DRIVING:  // 逆向行驶告警
            backward_fun(p);
            break;
        case PERCEPTION__EVENT_ID__ROAD_DANGER:       // 道路危险状况提醒(抛洒物)
            road_danger_fun(p);
            break;
        case PERCEPTION__EVENT_ID__FIRE_SMOKE:        // 隧道内火焰与烟雾预警
            smoke_fun(p);
            break;
        case PERCEPTION__EVENT_ID__TRAFFIC_JAM:       // 前方拥堵提醒
            jam_fun(p);
            break;
        case PERCEPTION__EVENT_ID__TRAFFIC_FLOW:      // 动态配时场景
            traffic_flow_fun(p);
            break;
        case PERCEPTION__EVENT_ID__SPECIALCAR:        // 特殊车辆
            special_car_fun(p);
            break;
        case PERCEPTION__EVENT_ID__ACCIDENT:          // 交通事故
            accident_area_fun(p);
            break;
        case PERCEPTION__EVENT_ID__ICEWARN:           // 结冰
            ice_fun(p);
            break;
        case PERCEPTION__EVENT_ID__LANE_WARE:         // 车道线磨损
            lane_ware_fun(p);
            break;
        default:
            break;
    }
    perception__perception_msg__free_unpacked(p,NULL);
}


