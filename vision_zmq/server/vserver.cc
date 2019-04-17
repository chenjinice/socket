#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "vserver.h"


#define SOCK_BUFFER_SIZE 2048
#define SOCK_MAX_CONNECT 5
#define SOCK_INVALID	-1


Vserver::Vserver(uint16_t port)
{
	signal(SIGPIPE,SIG_IGN);

	m_port = port;
	m_fd   = SOCK_INVALID;
	m_list.clear();
}

Vserver::~Vserver()
{
	printf("~~~vserver~~~~~~~end~~~~ \n");
	this->stop();
}

void Vserver::start()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	// socket服务端为阻塞模式 ，需要创建线程
	boost::thread t(&Vserver::server_init, this);
	t.detach();
}


void Vserver::server_send(uint8_t *buffer,int len){

	int client_count = 0;
	const char *send_result = "fail";

	if(len > SOCK_BUFFER_SIZE){
		printf("vserver : socket send error , len = %d > %d \n",len,SOCK_BUFFER_SIZE);
		return;
	}

	if(m_fd == SOCK_INVALID){
		printf("vserver : server_fd = %d\n",m_fd);
		return;
	}

	client_count = m_list.size();
	printf("vserver : online = %d\n",client_count);
	if(client_count <= 0)return;

//	m_mutex.lock();
	list<int>::iterator i;
	for(i=m_list.begin();i!=m_list.end();i++){
		int ret = send(*i,buffer,len,0);
		if(ret == len)send_result = "success";
		printf("vserver : send %s !! (c_fd=%d,ret=%d,pack_len=%d)\n",send_result,*i,ret,len);
	}
//	m_mutex.unlock();
}


// 发送行人
void Vserver::send_data(Crowd &msg)
{
	static struct timeval s_tv={0};

	if(msg.pedestrian_size() == 0)return;
	// 限制一下发送频率
	if(check_interval(&s_tv,100))return;

	int len = 0;
	uint8_t buffer[SOCK_BUFFER_SIZE];

	len = msg.ByteSize();
	msg.SerializeToArray(buffer,len);

	this->server_send(buffer,len);
}

//发送障碍物
void Vserver::send_data(Obstacles &msg)
{                                 
	static struct timeval s_tv={0};

	if(msg.obstacle_size() == 0)return;
	// 限制一下发送频率
	if(check_interval(&s_tv,1000))return;

	int len = 0;
	uint8_t buffer[SOCK_BUFFER_SIZE];

	len = msg.ByteSize();
	msg.SerializeToArray(buffer,len);

	this->server_send(buffer,len);
}

//发送可行驶区域
void Vserver::send_data(AvailableAreas &msg)
{
	static struct timeval s_tv={0};

	if(msg.area_size() == 0)return;
	// 限制一下发送频率
	if(check_interval(&s_tv,1000))return;

	int len = 0;
	uint8_t buffer[SOCK_BUFFER_SIZE];

	len = msg.ByteSize();
	msg.SerializeToArray(buffer,len);

	this->server_send(buffer,len);
}


/*
 * 检查与当前时间差是否超过某个值
 *  @param   tv : 需要与当前时间做比较的时间
 *           ms : 时间差是否超过ms（毫秒）
 *  @return	 -1 : 时间差小于 ms
 *  		  0 : 时间差大于等于 ms
*/
int Vserver::check_interval(struct timeval *tv,int ms)
{
	if((tv->tv_sec == 0) && (tv->tv_usec == 0)){
		gettimeofday(tv,NULL);
		return 0;
	}
	struct timeval now={0};
	gettimeofday(&now,NULL);
	int64_t interval = ((int64_t)now.tv_sec - (int64_t)tv->tv_sec)*1000000 + (now.tv_usec-tv->tv_usec);

//	printf("%d,now : %ld:%ld\n",sizeof(interval),now.tv_sec,now.tv_usec);
	if(interval >= ms*1000){
//		printf("interval ========== %lld\n",interval);
		gettimeofday(tv,NULL);
		return 0;
	}
	else{
		return -1;
	}
}



