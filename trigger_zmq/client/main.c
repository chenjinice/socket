#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "trigger_client.h"

static int flag = 1;

void fun(int arg)
{
	printf("sig int = %d \n",arg);
    triggerCLientStop();
	flag = 0;
}

int main(int argc ,char **argv)
{
	signal(SIGINT,fun);

	char *ip = "127.0.0.1";
	int port = 12349;

	if(argc >= 2)ip = argv[1];
	if(argc >= 3)port = atoi(argv[2]);


    triggerCLientStart(ip,port);


    while(flag)usleep(1000000);

	return 0;
}





