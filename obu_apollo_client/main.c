#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "client.h"

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
	signal(SIGPIPE,fun);

	char *ip = "127.0.0.1";
	int port = 9999;

	if(argc == 2)ip = argv[1];

	vclient_start(ip,port);

	while(flag)
	{
		usleep(200000);
	}
	printf(" ======== \n");
	return 0;
}


