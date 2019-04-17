/*
 *
 */

#ifndef __VSERVER_H__
#define __VSERVER_H__


#include <iostream>
#include <list>
#include <sys/time.h>
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

	void	server_close();
	void	server_send(uint8_t *buffer,int len);
	void	server_shutdown();
	void 	client_thread(int fd);

	void 	add_client(int fd);
	void 	remove_client(int fd);
	void	closeall_client();
    int     check_interval(struct timeval *tv,int ms);

};

#endif

