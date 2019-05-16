#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "obu_msgs.h"
#include "gps.pb-c.h"


//
void print_interval(int num)
{
    time_t timep;
    struct tm *p;
    time (&timep);
    p=gmtime(&timep);
    printf("[%02d:%02d:%02d] num == %d\n",p->tm_hour+8,p->tm_min,p->tm_sec,num);
}

// 获取时间戳的差值
int time_interval(struct timeval *tv)
{
    if((tv->tv_sec == 0) && (tv->tv_usec == 0)){
        gettimeofday(tv,NULL);
        return 0;
    }
    struct timeval now={0};
    gettimeofday(&now,NULL);
    int ret = (now.tv_sec - tv->tv_sec)*1000 + (now.tv_usec-tv->tv_usec)/1000;
    gettimeofday(tv,NULL);
    return ret;
}


// 解析gps数据
int obumsg_get_gps(uint8_t *buffer,int len)
{
    static struct timeval s_tv = {0};
    Apollo__Drivers__CiDiGps * gps = apollo__drivers__ci_di_gps__unpack(NULL,len,buffer);
    if(gps == NULL){
        printf("obu_server : gps unpack failed , length = %d\n",len);
        return -1;
    }
    int ms = time_interval(&s_tv);
    printf("%d(ms):gps_time:%lf,heading:%lf",ms,gps->gps_time,gps->heading);
    if(gps->position && gps->position->has_altitude && gps->position->has_latitude && gps->position->has_longitude){
    	printf(",position(lng:%d,lat:%d,alt:%d)",gps->position->longitude,gps->position->latitude,gps->position->altitude);
    }
    if(gps->linear_velocity && gps->linear_velocity->has_x && gps->linear_velocity->has_y && gps->linear_velocity->has_z){
    	printf(",linear_v(x:%lf,y:%lf,z:%lf)",gps->linear_velocity->x,gps->linear_velocity->y,gps->linear_velocity->z);
    }
    if(gps->position_std_dev && gps->position_std_dev->has_x && gps->position_std_dev->has_y && gps->position_std_dev->has_z){
    	printf(",dev(x:%lf,y:%lf,z:%lf)",gps->position_std_dev->x,gps->position_std_dev->y,gps->position_std_dev->z);
    }
    printf(",length = %d\n",len);

    apollo__drivers__ci_di_gps__free_unpacked(gps,NULL);
    return 0;
}

int obumsg_init(ObuApollo__ObuMsg *msg)
{
    if(msg == NULL)return -1;

    static int count = 0;
    count++;
    int i;

    obu_apollo__obu_msg__init(msg);
    msg->count = count;

    //car_info
    ObuApollo__CarInfo *car_info = calloc(1,sizeof(ObuApollo__CarInfo));
    obu_apollo__car_info__init(car_info);
    car_info->id = 0x12345;
    car_info->depth = 3.5*100;
    car_info->width = 2.2*100;
    car_info->lng = 111.111*1e7;
    car_info->lat = 22.22 *1e7;
    car_info->heading = 99.99*100;
    car_info->speed = 2*100;
    car_info->acc = 1*10;
    car_info->has_gear=1;	// c版本的protobuf，optional的基本数据类型的成员必须这么弄
    car_info->gear = 2;
    car_info->has_rtk = 1;
    car_info->rtk = 5;
    msg->car = car_info;

    // lane_info
    int lane_num = 2;
    ObuApollo__LaneInfo *lane_info = calloc(1,sizeof(ObuApollo__LaneInfo));
    obu_apollo__lane_info__init(lane_info);
    lane_info->count = count;
    lane_info->in_map = 1;
    lane_info->in_lane = 1;
    lane_info->current_lane = 3;
    ObuApollo__LaneFlag ** lane_array = calloc(lane_num,sizeof(ObuApollo__LaneFlag*));
    for(i=0;i<lane_num;i++){
        lane_array[i] = calloc(1,sizeof(ObuApollo__LaneFlag));
        obu_apollo__lane_flag__init(lane_array[i]);
        lane_array[i]->lane_id = i+100;
        lane_array[i]->has_flag = 1;
        lane_array[i]->flag = i+200;
    }
    lane_info->n_lane_flags = lane_num;
    lane_info->lane_flags = lane_array;
    msg->lanes = lane_info;

    //traffic light
    ObuApollo__TrafficLightInfo *lights = calloc(1,sizeof(ObuApollo__TrafficLightInfo));
    obu_apollo__traffic_light_info__init(lights);
    lights->traffic_light_cycle_count = count;
    // current light
    lights->current_lane_light = calloc(1,sizeof(ObuApollo__SingleLightInfo));
    obu_apollo__single_light_info__init(lights->current_lane_light);
    lights->current_lane_light->has_color_status = 1;
    lights->current_lane_light->has_light_remain_times = 1;
    lights->current_lane_light->color_status = OBU_APOLLO__SINGLE_LIGHT_INFO__COLOR__YELLOW;
    lights->current_lane_light->light_remain_times = 10;
    // left light
    lights->left_turn = calloc(1,sizeof(ObuApollo__SingleLightInfo));
    obu_apollo__single_light_info__init(lights->left_turn);
    lights->left_turn->has_color_status = 1;
    lights->left_turn->has_light_remain_times = 1;
    lights->left_turn->color_status = OBU_APOLLO__SINGLE_LIGHT_INFO__COLOR__YELLOW;
    lights->left_turn->light_remain_times = 20;
    // stop point
    lights->current_lane_stop_point = calloc(1,sizeof(ObuApollo__LaneStopPoint));
    obu_apollo__lane_stop_point__init(lights->current_lane_stop_point);
    lights->current_lane_stop_point->has_latitude = 1;
    lights->current_lane_stop_point->has_longitude = 1;
    lights->current_lane_stop_point->latitude  = 33.33*1e7;
    lights->current_lane_stop_point->longitude = 44.44*1e7;
    msg->lights = lights;

    // obstacle
    int obs_num = 3;
    ObuApollo__Obstacle **obs_array = calloc(obs_num,sizeof(ObuApollo__Obstacle*));
    for(i=0;i<obs_num;i++){
        obs_array[i] = calloc(1,sizeof(ObuApollo__Obstacle));
        obu_apollo__obstacle__init(obs_array[i]);
        obs_array[i]->id = i;
        obs_array[i]->type = OBU_APOLLO__OBSTACLE__OBS__TYPE__HUMAN;
        obs_array[i]->lng = 55.55*1e7;
        obs_array[i]->lat = 66.66*1e7;
        obs_array[i]->has_speed = 1;
        obs_array[i]->speed = i*200;
    }
    msg->n_obs = obs_num;
    msg->obs = obs_array;

    return 0;
}

//
void obumsg_free(ObuApollo__ObuMsg *msg)
{
    if(msg == NULL)return;

    int i;

    if(msg->car){
        free(msg->car);
        msg->car = NULL;
    }

    if(msg->lanes){
        for(i=0;i<msg->lanes->n_lane_flags;i++){
            free(msg->lanes->lane_flags[i]);
            msg->lanes->lane_flags[i] = NULL;
        }
        free(msg->lanes->lane_flags);
        msg->lanes->lane_flags = NULL;
        msg->lanes->n_lane_flags = 0;

        free(msg->lanes);
        msg->lanes = NULL;
    }

    if(msg->lights){
        if(msg->lights->current_lane_light){
            free(msg->lights->current_lane_light);
            msg->lights->current_lane_light = NULL;
        }
        if(msg->lights->left_turn){
            free(msg->lights->left_turn);
            msg->lights->left_turn = NULL;
        }
        if(msg->lights->straight){
            free(msg->lights->straight);
            msg->lights->straight = NULL;
        }
        if(msg->lights->right_turn){
            free(msg->lights->right_turn);
            msg->lights->right_turn = NULL;
        }
        if(msg->lights->current_lane_stop_point){
            free(msg->lights->current_lane_stop_point);
            msg->lights->current_lane_stop_point = NULL;
        }
        free(msg->lights);
        msg->lights = NULL;
    }

    if(msg->signs){
        for(i=0;i<msg->n_signs;i++){
            free(msg->signs[i]);
            msg->signs[i] = NULL;
        }
        free(msg->signs);
        msg->signs = NULL;
        msg->n_signs = 0;
    }

    if(msg->obs){
        for(i=0;i<msg->n_obs;i++){
            free(msg->obs[i]);
            msg->obs[i] = NULL;
        }
        free(msg->obs);
        msg->obs = NULL;
        msg->n_obs = 0;
    }

    if(msg->cars_nearby){
        for(i=0;i<msg->n_cars_nearby;i++){
            free(msg->cars_nearby[i]);
            msg->cars_nearby[i] = NULL;
        }
        free(msg->cars_nearby);
        msg->cars_nearby = NULL;
        msg->n_cars_nearby = 0;
    }
}










