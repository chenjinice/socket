#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <string.h>
#include "obu_apollo.pb-c.h"

void analysis(uint8_t *buffer,int len);

int main(int argc,char *argv[])
{
    // 绑定地址
    struct sockaddr_in addrto;
    bzero(&addrto, sizeof(struct sockaddr_in));
    addrto.sin_family = AF_INET;
    addrto.sin_addr.s_addr = htonl(INADDR_ANY);
    addrto.sin_port = htons(9999);

    struct sockaddr_in from;

    int sock = -1;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("creat socket error");
        return 0;
    }

    //设置该套接字为广播类型，
    const int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));

    if(bind(sock,(struct sockaddr *)&(addrto), sizeof(struct sockaddr_in)) == -1)
    {
        perror("bind error...");
        return 0;
    }

    int len = sizeof(struct sockaddr_in);
    uint8_t buffer[1024] = {0};

    int count  = 0;
    while(1)
    {
        memset(buffer,0,sizeof(buffer));
        int ret=recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&from,(socklen_t*)&len);
        char *ip = inet_ntoa(from.sin_addr);
        printf("[%s:%d] ret === %d\n",ip,ntohs(from.sin_port),ret);

        analysis(buffer,ret);

        if(1)
        {
            sendto(sock, "apollo", 7, 0, (struct sockaddr*)&from, sizeof(from));
        }
    }

    return 0;
}


void analysis(uint8_t *buffer,int len)
{
    int i;
//    for(i=0;i<10;i++){
//        printf("%02X ",buffer[i]);
//    }
//    printf("\n");
//    return;
    if(len <= 5)return;

    ObuApollo__ObuMsg *msg =  obu_apollo__obu_msg__unpack(NULL,len-5,buffer+4);
    if(msg == NULL){
        printf("obumsg unpack failed \n");
        return;
    }

    if(msg->car){
        ObuApollo__CarInfo *c = msg->car;
        printf("car=id:0x%x,depth:%d,width:%d,lng:%d,lat:%d,heading:%d,speed:%d,acc:%d,gear:%d,rtk:%d\n",
               c->id,c->depth,c->width,c->lng,c->lat,c->heading,c->speed,c->acc,c->gear,c->rtk);
    }

    if(msg->lanes){
        ObuApollo__LaneInfo *l = msg->lanes;
        printf("current lane = %d,",l->current_lane);
        for(i=0;i<l->n_lane_flags;i++){
            printf("id:%d,flag:%d ,",l->lane_flags[i]->lane_id,l->lane_flags[i]->flag);
        }
        printf("\n");
    }

    if(msg->lights){
        ObuApollo__TrafficLightInfo *t = msg->lights;
        if(t->current_lane_light)printf("current:(%d,%d),",t->current_lane_light->color_status,t->current_lane_light->light_remain_times);
        if(t->left_turn)printf("left:(%d,%d),",t->left_turn->color_status,t->left_turn->light_remain_times);
        if(t->straight)printf("straight:(%d,%d),",t->straight->color_status,t->straight->light_remain_times);
        if(t->right_turn)printf("right:(%d,%d),",t->right_turn->color_status,t->right_turn->light_remain_times);
        if(t->current_lane_stop_point)printf("lng:%d,lat:%d",t->current_lane_stop_point->longitude,t->current_lane_stop_point->latitude);
        printf("\n");
    }

    if(msg->obs){
        for(i=0;i<msg->n_obs;i++){
            printf("%d[lng:%d,lat:%d,speed:%d] , ",msg->obs[i]->id,msg->obs[i]->lng,msg->obs[i]->lat,msg->obs[i]->speed);
        }
        printf("\n");
    }

    obu_apollo__obu_msg__free_unpacked(msg,NULL);
}








