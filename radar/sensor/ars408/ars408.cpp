#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "ars408.h"
#include "can.h"
#include "ars408_analysis.h"



void *ars408_read_thread(void *param)
{
    // 线程结束时，自动释放资源
    pthread_detach(pthread_self());

    ARS408 *ars = (ARS408 *)param;
    ars->run();
}


ARS408::ARS408(char *dev)
{
    m_dev = dev;
    m_can = new Can();
}


ARS408::~ARS408()
{
    if(m_can)delete m_can;
}


void ARS408::start()
{
    if( !m_can->can_open(m_dev) ){
        printf("ARS408 : fail to open %s  !\n",m_dev);
        return;
    }else {
        printf("ARS408 : success to open %s \n",m_dev);
    }
    pthread_t thread;
    pthread_create(&thread,NULL,ars408_read_thread,this);
}


void ARS408::run()
{
    int len;
    while(1){
        struct can_frame frame;
        len = m_can->can_read(&frame);

        if(len <= 0){
            printf("ARS408 can_read error : len = %d\n",len);
            continue;
        }

        ars408_analysis(&frame);
    }

}




