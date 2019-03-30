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


typedef struct _myarray{
    int cfd[SOCK_MAX_CONNECT];
    int length;
    int (*add)(struct _myarray *array, int fd);
    void (*close)(struct _myarray *array,int fd);
    void (*close_all)(struct _myarray *array);
    void (*print)(struct _myarray *array);
}myarray;


static pthread_mutex_t m_mutex;
static pthread_mutex_t m_send_mutex;
static uint16_t m_port = 9999;
static myarray  m_array;
static int      m_fd   = SOCK_INVALID;
static int      m_loop = 1;


// myarray function  ==== >>
static int my_add(myarray *array,int fd)
{
    int ret = -1;
    pthread_mutex_lock(&m_mutex);
    if(array->length < SOCK_MAX_CONNECT){
        array->cfd[array->length] = fd;
        array->length++;
        ret = 0;
    }else {
        ret = -1;
    }
    pthread_mutex_unlock(&m_mutex);
    return ret;
}

static void my_close(myarray *array,int fd)
{
    int i;
    pthread_mutex_lock(&m_mutex);
    int length = array->length;
    for(i=length-1;i>=0;i--){
        if(array->cfd[i] != fd)continue;
        shutdown((array->cfd[i]),SHUT_RDWR);
        memset(array->cfd+i,0,FD_SIZE);
        memmove(array->cfd+i,array->cfd+i+1,length-i-1);
        array->length--;
    }
    pthread_mutex_unlock(&m_mutex);
}

static void my_close_all(myarray *array)
{
    pthread_mutex_lock(&m_mutex);
    int i;
    for(i=0;i<array->length;i++){
        shutdown((array->cfd[i]),SHUT_RDWR);
    }
    memset(array->cfd,0,FD_SIZE*SOCK_MAX_CONNECT);
    array->length = 0;
    pthread_mutex_unlock(&m_mutex);
}

static void my_print(myarray *array)
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
    array->add= my_add;
    array->close = my_close;
    array->close_all = my_close_all;
    array->print = my_print;
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

        if(m_array.add(&m_array,client_fd) != 0){
            close(client_fd);
        }
        m_array.print(&m_array);
    }

    m_array.close_all(&m_array);
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
        m_array.print(&m_array);
        pthread_mutex_init(&m_mutex,NULL);
        pthread_mutex_init(&m_send_mutex,NULL);

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
    pthread_mutex_destroy(&m_send_mutex);
}

void obu_server_send()
{
    if(m_fd == SOCK_INVALID){
//        printf("obu_server : server_fd = %d\n",m_fd);
        return;
    }

    char *p = "hello world\n";
    int ret,i;

    pthread_mutex_lock(&m_send_mutex);
    int length = m_array.length;
    for(i=length-1;i>=0;i--){
        ret = send(m_array.cfd[i],p,strlen(p),0);
        printf("send ret[%d][%d] = %d\n",i,m_array.cfd[i],ret);
        if( (ret <= 0) || (ret > strlen(p)) ){
            m_array.close(&m_array,m_array.cfd[i]);
        }
    }
    pthread_mutex_unlock(&m_send_mutex);

}



