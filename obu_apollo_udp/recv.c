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
#include "gps.pb-c.h"


void analysis(uint8_t *buffer,int len);
void send_gps(int fd,struct sockaddr_in *from);

int main(int argc,char *argv[])
{
    // 绑定地址
    struct sockaddr_in addrto;
    bzero(&addrto, sizeof(struct sockaddr_in));
    addrto.sin_family = AF_INET;
    addrto.sin_addr.s_addr = htonl(INADDR_ANY);
    addrto.sin_port = htons(6611);

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
        printf("[%s:%d] recv length === %d\n",ip,ntohs(from.sin_port),ret);

        analysis(buffer,ret);
//        sleep(5);

        if(1)
        {
            send_gps(sock,&from);
        }
    }

    return 0;
}


void send_gps(int fd,struct sockaddr_in *from)
{
    Apollo__Drivers__CiDiGps gps = APOLLO__DRIVERS__CI_DI_GPS__INIT;
    gps.has_gps_time = 1;
    gps.gps_time = 9.87654321;
    
    uint8_t buffer[1024] = {0};
    buffer[0]='c';
    buffer[1]='i';
    buffer[2]='d';
    buffer[3]='i';
    int len = apollo__drivers__ci_di_gps__get_packed_size(&gps);
    
    apollo__drivers__ci_di_gps__pack(&gps,buffer+4);

    sendto(fd, buffer, len+4, 0, (struct sockaddr*)from, sizeof(struct sockaddr));
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
    printf("count ============ %d\n",msg->count);
    if(msg->car){
        ObuApollo__CarInfo *c = msg->car;
        printf("this_car = id:0x%x,depth:%d,width:%d,lng:%d,lat:%d,heading:%d,speed:%d,acc:%d,gear:%d,rtk:%d\n",
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
        if(t->current_lane_light)printf("current light:(%d,%d),",t->current_lane_light->color_status,t->current_lane_light->light_remain_times);
        if(t->left_turn)printf("left light:(%d,%d),",t->left_turn->color_status,t->left_turn->light_remain_times);
        if(t->straight)printf("straight light:(%d,%d),",t->straight->color_status,t->straight->light_remain_times);
        if(t->right_turn)printf("right light:(%d,%d),",t->right_turn->color_status,t->right_turn->light_remain_times);
        if(t->current_lane_stop_point)printf("lane_stop_point:lng:%d,lat:%d",t->current_lane_stop_point->longitude,t->current_lane_stop_point->latitude);
        printf("\n");
    }

    if(msg->obs){
	printf("obs(%d)",msg->n_obs);
        for(i=0;i<msg->n_obs;i++){
            printf("[id:%d,lng:%d,lat:%d,type:%d,land_id:%d,speed:%d] , ",msg->obs[i]->id,msg->obs[i]->lng,msg->obs[i]->lat,msg->obs[i]->type,msg->obs[i]->lane_id,msg->obs[i]->speed);
        }
        printf("\n");
    }

    if(msg->cars_nearby){
	printf("cars_nearby(%d)",msg->n_cars_nearby);	
        ObuApollo__CarInfo **array = msg->cars_nearby;
	for(i=0;i<msg->n_cars_nearby;i++){
	    ObuApollo__CarInfo *c = array[i];
	    printf("[id:0x%x,depth:%d,width:%d,lng:%d,lat:%d,heading:%d,speed:%d,acc:%d] , ",
               c->id,c->depth,c->width,c->lng,c->lat,c->heading,c->speed,c->acc);	
	}
	printf("\n");
        
    }

    obu_apollo__obu_msg__free_unpacked(msg,NULL);
}








