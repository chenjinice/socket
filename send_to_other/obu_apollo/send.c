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


int main(int argc,char *argv[])
{
    char *device = NULL;
    if(argc > 1){
        device = argv[1];
    }

    signal(SIGINT,fun);
    signal(SIGPIPE,SIG_IGN);
    obu_server_start(device,6611);


    while (flag) {
        usleep(1000*1000);
    }

    return 0;
}




