#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "obu_server.h"
#include "obu_apollo.pb-c.h"

void init_msg(ObuApollo__ObuMsg *msg);
void free_msg(ObuApollo__ObuMsg *msg);

static int flag = 1;

void fun(int arg){
    flag = 0;
    obu_server_stop();
    printf("integer === %d\n",arg);
}



int main(int argc,char *argv[])
{
    char *device = NULL;
    if(argc > 1){
        device = argv[1];
    }

    signal(SIGINT,fun);
    signal(SIGPIPE,SIG_IGN);
    obu_server_start(device,9999);

    int length = 0;

    while (flag) {
        uint8_t buffer[1024] ={0};
        ObuApollo__ObuMsg msg;
        init_msg(&msg);

        length = obu_apollo__obu_msg__get_packed_size(&msg);
        printf("length == %d\n",length);
        if(length <= sizeof(buffer)){
            obu_apollo__obu_msg__pack(&msg,buffer);
            obu_server_send(buffer,length);
        }

        free_msg(&msg);
        usleep(1000*1000);
    }

    return 0;
}



void init_msg(ObuApollo__ObuMsg *msg)
{
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
    car_info->gear = 2;
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
    lights->current_lane_light->color_status = OBU_APOLLO__SINGLE_LIGHT_INFO__COLOR__YELLOW;
    lights->current_lane_light->light_remain_times = 10;
    // left light
    lights->left_turn = calloc(1,sizeof(ObuApollo__SingleLightInfo));
    obu_apollo__single_light_info__init(lights->left_turn);
    lights->left_turn->color_status = OBU_APOLLO__SINGLE_LIGHT_INFO__COLOR__YELLOW;
    lights->left_turn->light_remain_times = 10;
    // stop point
    lights->current_lane_stop_point = calloc(1,sizeof(ObuApollo__LaneStopPoint));
    obu_apollo__lane_stop_point__init(lights->current_lane_stop_point);
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
        obs_array[i]->speed = i*200;
    }
    msg->n_obs = obs_num;
    msg->obs = obs_array;

}


void free_msg(ObuApollo__ObuMsg *msg)
{
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







