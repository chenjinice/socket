#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int check_interval(struct timeval *tv,int ms)
{
	struct timeval now={0};
	gettimeofday(&now,NULL);
	long interval = (now.tv_sec-tv->tv_sec)*1000000 + (now.tv_usec-tv->tv_usec);
	interval /= 1000;

	if(interval >= ms){
		printf("interval ========== %ld\n",interval);
		gettimeofday(tv,NULL);
		return 0;
	}
	else{
		return -1;
	}

}

void send()
{
	static struct timeval s_tv={0};

	if(check_interval(&s_tv,1000))return;

	printf("send ok ok \n");

}

int main()
{

	while(1)
	{
		send();
	}

}
