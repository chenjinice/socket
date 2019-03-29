#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "obu_server.h"

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
        obu_server_send();
        sleep(1);
    }

    return 0;
}
