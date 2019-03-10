/*
 *  视频服务端程序，采用单例模式
 */

#ifndef __VSERVER_H__
#define __VSERVER_H__


#include <iostream>
#include <list>
#include <boost/thread/mutex.hpp>
#include "vision.pb.h"

using namespace std;

class Vserver
{
public:
	// port 为socket 端口
	Vserver(uint16_t port);
	~Vserver();

	void start();
	void stop();
	void send_data(Crowd &msg);
	void send_data(Obstacles &msg);
	void send_data(AvailableAreas &msg);

private:
	uint16_t 	 m_port;	//socket 端口
	int 	 	 m_fd;		//socket 句柄
	list<int> 	 m_list; 	//list用来存储当前连接的客户端句柄
	boost::mutex m_mutex;	// 操作 m_list时的互斥锁
	static Vserver *m_instance;

	void 	server_init();
	void	server_close();
	void	server_send(uint8_t *buffer,int len);
	void	server_shutdown();
	void 	client_thread(int fd);

	void 	add_client(int fd);
	void 	remove_client(int fd);
	void	closeall_client();

};

#endif

