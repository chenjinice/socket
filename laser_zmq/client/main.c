#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "laser_client.h"

static int flag = 1;

void fun(int arg)
{
	printf("sig int = %d \n",arg);
    laser_client_stop();
	flag = 0;
}

int main(int argc ,char **argv)
{
	signal(SIGINT,fun);

	char *ip = "127.0.0.1";
	int port = 12347;

	if(argc >= 2)ip = argv[1];
	if(argc >= 3)port = atoi(argv[2]);

    laser_client_start(ip,port);
	while(flag)
	{
		usleep(1000000);
	}
	printf(" ======== \n");
	return 0;
}





