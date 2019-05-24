#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "vclient.h"

static int flag = 1;

void fun(int arg)
{
	printf("sig int = %d \n",arg);
	vclient_stop();
	flag = 0;
}

int main(int argc ,char **argv)
{
	signal(SIGINT,fun);

    static int s_count = 0;
	char *ip = "127.0.0.1";
	int port = 12347;
    int this_port = 12348;
	if(argc == 2)ip = argv[1];


    vclient_start(ip,port,this_port);


	while(flag)
	{
        s_count++;
        if(s_count %5 ==0)vclient_send_signal(SIG_Y2G,1);
        if(s_count %9 ==0)vclient_send_signal(SIG_OVER,1);
        usleep(1000000);
	}

	printf(" ======== \n");
	return 0;
}


