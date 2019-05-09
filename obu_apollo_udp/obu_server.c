#include <netinet/in.h>
#include <net/if.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include "obu_server.h"


#define SOCK_INVALID	-1
#define HEADER_SIZE      2
static uint8_t g_header[2] = {0x60,0x61};

static pthread_mutex_t m_mutex;
static char   * m_device   = "eth0";
static uint16_t m_port = 9999;
static int      m_fd   = SOCK_INVALID;
static struct sockaddr_in m_addr;
static int      m_loop = 0;


static void udp_close()
{
    if(m_fd != SOCK_INVALID){
        close(m_fd);
        m_fd = SOCK_INVALID;
    }
}

static void *read_thread()
{
    // 线程结束时，自动释放资源
    pthread_detach(pthread_self());

    uint8_t buffer[20] = {0};
    struct sockaddr_in from;
    int len = sizeof(struct sockaddr_in);
    int ret,count;

    m_loop = 1;
	count = 0;
    while(m_loop){
        memset(buffer,0,sizeof(buffer));
        ret=recvfrom(m_fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&from,(socklen_t*)&len);
        printf("[%s:%d] ret === %d\n",inet_ntoa(from.sin_addr),ntohs(from.sin_port),ret);
        if( (ret > 0) && (strcmp(buffer,"apollo") == 0) )
        {
            char *ip = inet_ntoa(from.sin_addr);
            m_addr.sin_addr.s_addr=inet_addr(ip);
			m_addr.sin_port = from.sin_port;
			count = 0;
        }else{
			if(count++ == 10){
				m_addr.sin_addr.s_addr=htonl(INADDR_BROADCAST);
    			m_addr.sin_port=htons(m_port);
			}
		}
    }


}

static void udp_init()
{
    int ret = -1;
    int opt = 1;
    pthread_t thread;

    m_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_fd <= 0)
    {
        perror("obu_server create udp socket failed");
        exit(-1);
    }

    //设置该套接字为广播类型
    if(setsockopt(m_fd, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt)) < 0){
        udp_close();
        perror("obu_server set socket broadcast error");
        exit(-1);
    }

    // 绑定网卡
	struct ifreq ifr = {0};
    strcpy(ifr.ifr_name,m_device);
    if (setsockopt(m_fd, SOL_SOCKET, SO_BINDTODEVICE, (char *)&ifr, sizeof(ifr)) < 0){
        udp_close();
        perror("obu_server bind interface error");
        exit(-1);
    }

	//设置读数据的超时时间
    struct timeval tv_out;
    tv_out.tv_sec = 2;
    tv_out.tv_usec = 0;
    setsockopt(m_fd,SOL_SOCKET,SO_RCVTIMEO,&tv_out, sizeof(tv_out));

 	// 绑定地址,用于接收消息
    struct sockaddr_in this_addr;
    bzero(&this_addr, sizeof(struct sockaddr_in));
    this_addr.sin_family = AF_INET;
    this_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    this_addr.sin_port = htons(8888);
    if(bind(m_fd,(struct sockaddr *)&(this_addr), sizeof(struct sockaddr_in)) == -1)
    {
        udp_close();
        perror("obu_server bind error...");
        exit(-1);
    }

	// 设置广播地址和端口
    bzero(&m_addr, sizeof(struct sockaddr_in));
    m_addr.sin_family=AF_INET;
    m_addr.sin_addr.s_addr=htonl(INADDR_BROADCAST);
    m_addr.sin_port=htons(m_port);
//    m_addr.sin_addr.s_addr=inet_addr("192.168.1.255");

	// 创建读消息线程
    pthread_create(&thread,NULL,read_thread,NULL);
}


void obu_server_start(char * device,uint16_t port)
{
    if(m_fd == SOCK_INVALID)
    {
        m_port = port;
        if(device)m_device = device;
        pthread_mutex_init(&m_mutex,NULL);
        udp_init();
    }

}

void obu_server_stop()
{
    m_loop = 0;
    udp_close();
    pthread_mutex_destroy(&m_mutex);
}


void obu_server_send(uint8_t *data,int len)
{
    if(len > MSG_BUFFER_SIZE){
        return;
    }

    int ret,i;
    int send_size = 0;
    uint8_t sum = 0 ;

    //
    uint8_t buffer[MSG_BUFFER_SIZE+10] = {0};
    memcpy(buffer,g_header,HEADER_SIZE);
    memcpy(buffer+HEADER_SIZE,data,len);
    for (i=0;i<HEADER_SIZE+len;i++) {
        sum+=buffer[i];
    }
    buffer[len+HEADER_SIZE] = sum;
    send_size = len+HEADER_SIZE+1;

    pthread_mutex_lock(&m_mutex);
    ret=sendto(m_fd, buffer, send_size, 0, (struct sockaddr*)&m_addr, sizeof(m_addr));
    if(ret<0){
        perror("obu_server sendto error");
    }
    pthread_mutex_unlock(&m_mutex);
}


