#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <string.h>
#include "obu_apollo.pb-c.h"


int main(int argc,char *argv[])
{
    // 绑定地址
    struct sockaddr_in addrto;
    bzero(&addrto, sizeof(struct sockaddr_in));
    addrto.sin_family = AF_INET;
    addrto.sin_addr.s_addr = htonl(INADDR_ANY);
    addrto.sin_port = htons(9999);

    struct sockaddr_in from;

    int sock = -1;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("creat socket error");
        return 0;
    }

    const int opt = 1;
    //设置该套接字为广播类型，
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));

    if(bind(sock,(struct sockaddr *)&(addrto), sizeof(struct sockaddr_in)) == -1)
    {
        perror("bind error...");
        return 0;
    }

    int len = sizeof(struct sockaddr_in);
    uint8_t buffer[1000] = {0};

    int count  = 0;
    while(1)
    {
        memset(buffer,0,sizeof(buffer));
        int ret=recvfrom(sock, buffer, 100, 0, (struct sockaddr*)&from,(socklen_t*)&len);
		char *ip = inet_ntoa(from.sin_addr);
		printf("[%s:%d] ret === %d\n",ip,ntohs(from.sin_port),ret);


		if(1)
		{
	    	sendto(sock, "apollo", 7, 0, (struct sockaddr*)&from, sizeof(from));
		}
    }

    return 0;
}



