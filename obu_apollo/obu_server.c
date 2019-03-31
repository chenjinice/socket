#include <netinet/in.h>
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
#define SOCK_MAX_CONNECT 5
#define FD_SIZE          sizeof(int)
#define HEADER_SIZE      4
static uint8_t g_header[4] = {0x61,0x62,0x63,0x64};

typedef struct _myarray{
    int cfd[SOCK_MAX_CONNECT];
    int length;
}myarray;


static pthread_mutex_t m_mutex;
static uint16_t m_port = 9999;
static myarray  m_array;
static int      m_fd   = SOCK_INVALID;
static int      m_loop = 1;


// myarray function  ==== >>
static int add_client(myarray *array,int fd)
{
    int ret = -1;
    if(array->length < SOCK_MAX_CONNECT){
        array->cfd[array->length] = fd;
        array->length++;
        ret = 0;
    }else {
        ret = -1;
    }
    return ret;
}

static void close_client(myarray *array,int fd)
{
    int i;
    int length = array->length;
    for(i=length-1;i>=0;i--){
        if(array->cfd[i] != fd)continue;
        close(array->cfd[i]);
        array->cfd[i] = 0;
        memmove(array->cfd+i,array->cfd+i+1,(SOCK_MAX_CONNECT-i-1)*FD_SIZE);
        array->cfd[SOCK_MAX_CONNECT-1] = 0;
        array->length--;
    }
}

static void close_all_client(myarray *array)
{
    int i;
    for(i=0;i<array->length;i++){
//        close(array->cfd[i]);
        shutdown((array->cfd[i]),SHUT_RDWR);
    }
    memset(array->cfd,0,FD_SIZE*SOCK_MAX_CONNECT);
    array->length = 0;
}

static void print_client(myarray *array)
{
    int i;
    int length = array->length;
    printf("obu_server : cfd[%d online] = [",length);
    for(i=0;i<SOCK_MAX_CONNECT;i++){
        printf("%d",array->cfd[i]);
        if(i < SOCK_MAX_CONNECT-1)printf(",");
    }
    printf("]\n");
}

static void init_array(myarray *array)
{
    memset(array,0,sizeof(myarray));
}

// my array function << ==========


static void server_close()
{
    if(m_fd != SOCK_INVALID){
        close(m_fd);
        m_fd = SOCK_INVALID;
    }
}

static void socket_init()
{
    // 线程结束时，自动释放资源
    pthread_detach(pthread_self());

    int sock_reuse = 1;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(struct sockaddr);

    m_fd = socket(AF_INET,SOCK_STREAM,0);
//    printf("m_fd === %d\n",m_fd);
    if(m_fd <= 0){
        printf("obu_server : create socket error\n");
        return;
    }

    // 端口复用，防止关掉程序再开的时候不能创建socket
    setsockopt(m_fd,SOL_SOCKET,SO_REUSEADDR,&sock_reuse,sizeof(sock_reuse));

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(m_port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(m_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
        printf("obu_server : bind socket error\n");
        server_close();
        return;
    }

    if(listen(m_fd,SOCK_MAX_CONNECT) == -1){
        printf("obu_server : listen error\n");
        server_close();
        return;
    }

    while(1)
    {
        int client_fd = accept(m_fd,(struct sockaddr *)&client_addr, &length);
        if(client_fd == -1){
            printf("obu_server : accept error , client_fd === -1\n");
            break;
        }

        pthread_mutex_lock(&m_mutex);
        if(add_client(&m_array,client_fd) != 0){
            close(client_fd);
        }
        pthread_mutex_unlock(&m_mutex);

        print_client(&m_array);
    }

    pthread_mutex_lock(&m_mutex);
    close_all_client(&m_array);
    pthread_mutex_unlock(&m_mutex);

    server_close();
    return;

}

static void *socket_thread()
{
    if(m_fd != SOCK_INVALID)return NULL;

    while (1) {
        socket_init();
        sleep(5);
    }
}

void obu_server_start(uint16_t port)
{
    if(m_fd == SOCK_INVALID)
    {
        m_port = port;
        init_array(&m_array);
        pthread_mutex_init(&m_mutex,NULL);

        pthread_t thread;
        pthread_create(&thread,NULL,socket_thread,NULL);
    }

}

void obu_server_stop()
{
    m_loop = 0;
    if(m_fd != SOCK_INVALID){
        shutdown(m_fd,SHUT_RDWR);
        m_fd = SOCK_INVALID;
    }
    pthread_mutex_destroy(&m_mutex);
}

void obu_server_send(uint8_t *data,int len)
{
    if(m_fd == SOCK_INVALID){
        return;
    }
    if(len > MSG_BUFFER_SIZE){
        return;
    }

    int ret,i;
    int send_size = 0;
    uint8_t sum = 0 ;
    uint8_t buffer[MSG_BUFFER_SIZE+100] = {0};
    memcpy(buffer,g_header,HEADER_SIZE);
    memcpy(buffer+HEADER_SIZE,data,len);
    for (i=0;i<HEADER_SIZE+len;i++) {
        sum+=buffer[i];
    }
    buffer[len+HEADER_SIZE] = sum;
    send_size = len+HEADER_SIZE+1;

    pthread_mutex_lock(&m_mutex);
    int length = m_array.length;
    for(i=length-1;i>=0;i--){
        ret = send(m_array.cfd[i],buffer,send_size,0);
        printf("send ret[%d][%d] = %d\n",i,m_array.cfd[i],ret);
        if( (ret <= 0) || (ret > send_size) ){
            close_client(&m_array,m_array.cfd[i]);
        }
    }
    print_client(&m_array);
    pthread_mutex_unlock(&m_mutex);

}



