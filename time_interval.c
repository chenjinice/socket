#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

int check_interval(struct timeval *tv,int ms)
{
	if((tv->tv_sec == 0) && (tv->tv_usec == 0)){
		gettimeofday(tv,NULL);
		return 0;
	}
	struct timeval now={0};
	gettimeofday(&now,NULL);
	int64_t interval = ((int64_t)now.tv_sec - (int64_t)tv->tv_sec)*1000000 + (now.tv_usec-tv->tv_usec);

	printf("%d,now : %ld:%ld\n",sizeof(interval),now.tv_sec,now.tv_usec);
	if(interval >= ms*1000){
		printf("interval ========== %lld\n",interval);
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
/*	
	int x = 3000;
	int y = 100;
	int64_t a = ((int64_t)x-(int64_t)y)*1000000;	
	printf("a ========= %lld\n",a);
*/
}

int main()
{

	while(1)
	{
		send();
		usleep(200*1000);
	}

}
