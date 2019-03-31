#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include "client.h"
#include "analysis.h"


static void *socket_thread_fun(void *arg);
static int  socket_init(void);
static void socket_read(void);
static void socket_close(void);
static void socket_shutdown(void);

// tcp读取数据最大长度
#define SOCK_BUFFER_SIZE 2048


static char *m_ip = NULL;
static int 	 m_port = -1;
static int	 m_fd = -1;
static int 	 m_loop = 0;

// 开启，这个函数会创建一个线程，线程里连接视频那边的服务器
void vclient_start(char *ip ,uint16_t port)
{
	if(m_fd != -1) return;

	m_ip = ip;
	m_port = port;

	pthread_t thread;
	pthread_create(&thread,NULL,socket_thread_fun,NULL);
}

// 结束这个任务，将会退出while循环，结束线程
void vclient_stop(void)
{
	m_loop = 0;
	socket_shutdown();
}

// 线程里边会连接服务器，如果连接失败或断开连接，5秒后重连
static void *socket_thread_fun(void *arg)
{
	// 线程结束时，自动释放资源
	pthread_detach(pthread_self());

	m_loop = 1;
	while(m_loop){
		int ret = socket_init();
		if(ret != 0){
			printf("vclient : %s:%d  connect failed\n",m_ip,m_port);
		}else{
			socket_read();
		}
		sleep(5);
	}
	return NULL;
}

// 创建socket ，连接服务器
static int	socket_init(void)
{
	if(m_fd > 0)return 0;

	int error = -1,flag = -1,ret = -1;
	unsigned long ul = 1;
	m_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(m_fd < 0){
		printf("vclient : socket create error\n");
		return -1;
	}

	struct sockaddr_in _server_addr;
	memset(&_server_addr, 0,sizeof(_server_addr));
	_server_addr.sin_family = AF_INET;
	_server_addr.sin_port = htons(m_port);
	_server_addr.sin_addr.s_addr = inet_addr(m_ip);

	// 连接超时设置为两秒
	ioctl(m_fd, FIONBIO, &ul);
	if(connect(m_fd, (struct sockaddr *)&_server_addr, sizeof(struct sockaddr)) == -1){
		fd_set fds;
		struct timeval timout = {2,0};
		FD_ZERO(&fds);
		FD_SET(m_fd,&fds);
		if(select(m_fd+1, NULL, &fds, NULL, &timout) > 0){
			int len = sizeof(int);
			getsockopt(m_fd, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&len);
//			printf("m_fd = %d,error ===== %d\n",m_fd,error);
			// 这个判断有必要的，有时就算服务器关闭了，select返回值还是>0
			if(error == 0) flag = 0;
			else flag = -1;
		}
		else flag = -1;
	}
	ul = 0;
	ioctl(m_fd, FIONBIO, &ul);

	// 判断连接是否成功
	if(flag == -1){
		socket_close();
		return -1;
	}else{
		return 0;
	}

}

// socket读数据
static void socket_read(void)
{
	while(1){
		if(m_fd < 0 )break;
		uint8_t buffer[SOCK_BUFFER_SIZE] = {0};
		int length = recv(m_fd,buffer,sizeof(buffer),0);
//		printf("length = %d\n",length);
		if(length == 0)break;
		if(length == -1){
			if(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)continue;
			else break;
		}
		analysis(buffer,length);
	}
	socket_close();
	return;
}

//关闭socket ，这种方式，处于recv阻塞中的socket不会结束
static void socket_close(void)
{
	if(m_fd > 0){
		close(m_fd);
		m_fd = -1;
	}
}

// 关闭socket ，shutdown函数可以完全关掉socket资源，
// 处于recv阻塞中的socket也会立马结束
static void socket_shutdown(void)
{
	if(m_fd > 0){
		shutdown(m_fd , SHUT_RDWR);
		m_fd = -1;
	}
}



