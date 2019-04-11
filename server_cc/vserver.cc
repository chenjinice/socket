#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <boost/thread.hpp>
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

void Vserver::stop()
{
	this->closeall_client();
	if(m_fd != SOCK_INVALID){
		shutdown(m_fd,SHUT_RDWR);
		m_fd = SOCK_INVALID;
	}
	google::protobuf::ShutdownProtobufLibrary();
}

void Vserver::server_init()
{
	if(m_fd != SOCK_INVALID)return;

	int sock_reuse = 1;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t length = sizeof(struct sockaddr);

	m_fd = socket(AF_INET,SOCK_STREAM,0);
	if(m_fd <= 0){
		printf("vserver : create socket error\n");
		return;
	}

	// 端口复用，防止关掉程序再开的时候不能创建socket
	setsockopt(m_fd,SOL_SOCKET,SO_REUSEADDR,&sock_reuse,sizeof(sock_reuse));

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(m_port);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(m_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
		perror("vserver : bind socket error");
		this->server_close();
		return ;
	}

	listen(m_fd,SOCK_MAX_CONNECT);

	while(1)
	{
		if(m_fd == SOCK_INVALID)break;
		int client_fd = accept(m_fd,(struct sockaddr *)&client_addr, &length);
		if(client_fd == -1){
			perror("vserver : accept error , client_fd === -1");
			break;
		}
		printf("vserver : client(c_fd=%d) connect ,online = %d\n",client_fd,(int)(m_list.size()+1));

		if(m_list.size() > SOCK_MAX_CONNECT){
			close(client_fd);
			continue;
		}else{
			this->add_client(client_fd);
		}

		// 每连接一个客户端，创建一个线程 (boost线程调用类成员函数，并带个参数的写法，有点恶心)
		boost::function0<void> fun = boost::bind(&Vserver::client_thread,this,client_fd);
		boost::thread t(fun);
		t.detach();
	}

	this->stop();
	return;
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

	m_mutex.lock();
	list<int>::iterator i;
	for(i=m_list.begin();i!=m_list.end();i++){
		int ret = send(*i,buffer,len,0);
		if(ret == len)send_result = "success";
		printf("vserver : send %s !! (c_fd=%d,ret=%d,pack_len=%d)\n",send_result,*i,ret,len);
	}
	m_mutex.unlock();
}

void Vserver::server_close(){
	if(m_fd != SOCK_INVALID){
		close(m_fd);
		m_fd = SOCK_INVALID;
	}
}

void Vserver::server_shutdown(){
	if(m_fd != SOCK_INVALID){
		shutdown(m_fd,SHUT_RDWR);
		m_fd = SOCK_INVALID;
	}
}

void Vserver::client_thread(int fd)
{
	int length;
	int client_fd = fd;

	while(1)
	{
		char buffer[SOCK_BUFFER_SIZE] = {0};
		length = recv(client_fd,buffer,SOCK_BUFFER_SIZE,0);
		// length 为-1时，出了错误，为 0时，表示对方已经关闭socket，为避免某些莫名的bug，这两种情况下都关闭这个连接
		if(length == 0)break;
		if(length == -1){
			if(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)continue;
			else break;
		}
	}

	printf("vserver : client(c_fd=%d) disconnect ,online = %d\n",client_fd,(int)(m_list.size()));
	close(client_fd);
	this->remove_client(client_fd);
	return ;
}

void Vserver::add_client(int fd)
{
	m_mutex.lock();
	m_list.push_back(fd);
	m_mutex.unlock();
}

void Vserver::remove_client(int fd)
{
	m_mutex.lock();
	m_list.remove(fd);
	m_mutex.unlock();
}

void Vserver::closeall_client()
{
	m_mutex.lock();
	int count = m_list.size();
	for(int i=count;i>0;i--){
		shutdown(m_list.back(),SHUT_RDWR);
		m_list.pop_back();
	}
	m_mutex.unlock();
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



