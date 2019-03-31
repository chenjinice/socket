#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "obu_server.h"
#include "obu_apollo.pb-c.h"

static int flag = 1;

void fun(int arg){
    flag = 0;
    obu_server_stop();
    printf("integer === %d\n",arg);
}

int main()
{
    signal(SIGINT,fun);
    signal(SIGPIPE,SIG_IGN);
    obu_server_start(9999);

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
        msg.count = 123;

        int len = obu_msg__get_packed_size(&msg);
        uint8_t data[MSG_BUFFER_SIZE] = {0};
        if(len <= sizeof(data)){
            obu_msg__pack(&msg,data);
            obu_server_send(data,len);
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
