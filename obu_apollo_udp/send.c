#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "obu_apollo.h"
#include "obu_apollo.pb-c.h"

static int flag = 1;

void fun(int arg){
    flag = 0;
    obu_apollo_stop();
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
    obu_apollo_start(device,9999);

    int count = 0;
    while (flag) {

        int num = 3,i;
        ObuMsg msg = OBU_MSG__INIT;
        Obstacle **obs = calloc(sizeof(Obstacle *),num);
        for(i=0;i<num;i++){
            obs[i] = calloc(sizeof(Obstacle),1);
            obstacle__init(obs[i]);
            obs[i]->id = 8;
            obs[i]->type = TYPE__HUMAN;
            obs[i]->lat = 1111;
            obs[i]->lng = 2222;
        }
        msg.obs = obs;
        msg.n_obs = num;
        msg.count = count++;

        int len = obu_msg__get_packed_size(&msg);
        uint8_t data[MSG_BUFFER_SIZE] = {0};
        if(len <= sizeof(data)){
            obu_msg__pack(&msg,data);
            obu_apollo_send(data,len);
        }

        for(i=0;i<num;i++){
            free(obs[i]);
            obs[i] = NULL;
        }
        free(obs);
        obs = NULL;

        sleep(1);
    }

    return 0;
}







