#include <netinet/in.h>
#include <net/if.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#include "obu_faw.pb-c.h"


void analysis(uint8_t *buffer,int len);


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


int main(int argc,char *argv[])
{
    // 绑定本地的端口，用于监听，接收数据
    struct sockaddr_in addrto;
    bzero(&addrto, sizeof(struct sockaddr_in));
    addrto.sin_family = AF_INET;
    addrto.sin_addr.s_addr = htonl(INADDR_ANY);
    addrto.sin_port = htons(12333);

    struct sockaddr_in from;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0){
        perror("creat socket error");
        return -1;
    }
    if(bind(sock,(struct sockaddr *)&(addrto), sizeof(struct sockaddr_in)) == -1){
        perror("bind error...");
        return -1;
    }
    int len = sizeof(struct sockaddr_in);
    uint8_t buffer[1024] = {0};
    while(1)
    {
        memset(buffer,0,sizeof(buffer));
        int ret = recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&from,(socklen_t*)&len);
//        char *ip = inet_ntoa(from.sin_addr);
//        printf("[%s:%d] recv length === %d\n",ip,ntohs(from.sin_port),ret);
        analysis(buffer,ret);
    }
    return 0;
}


void analysis(uint8_t *buffer,int len)
{
    static struct timeval tv1 = {0} ,tv2 = {0};
    ObuFaw__Msg *msg = obu_faw__msg__unpack(NULL,len,buffer);
    if(msg == NULL){
        printf("obu faw msg : unpack failed\n");
        return;
    }
    if(msg->m_case == OBU_FAW__MSG__M_MOTION){
        ObuFaw__ObuMotion *p = msg->motion;
        printf("MM-%06d(%04d) : lng(%d),lat(%d),heading(%d),speed(%d),acc(%lf),id(%s),time(%lld),alt(%lf)\n",
               p->msgcount,time_interval(&tv1),p->longitude,p->latitude,p->heading,p->speed,p->acc,p->devid,p->gpstime,p->altitude);
    }
    if(msg->m_case == OBU_FAW__MSG__M_CAN){
        ObuFaw__CanInfo *p = msg->can;
        printf("CC-%06d(%04d) : id(%s),trun(%s),hazard(%s),brake(%s),gas(%s),gear(%s),wheel(%lf),drive(%s)\n"
               "       abnormal(%s),time(%lld),lng(%d),lat(%d),alt(%lf),speed(%d),heading(%d)\n",
               p->msgcount,time_interval(&tv2),p->devid,p->trunlight,p->hazardlight,p->brakestate,p->gasstatus,p->gearstate,p->wheelangle,
               p->drivestate,p->abnormalstate,p->gpstime,p->longitude,p->latitude,p->altitude,p->speed,p->heading);
    }
}

