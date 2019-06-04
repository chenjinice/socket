#include <unistd.h>	
#include "laser_server.h"


using namespace laser;


void send_msg(LaserServer &s)
{
    LaserMsg a;
    LaserObj   *p;
    static struct timeval tv = {0};    // 时间结构体,用于限制发送频率
    for(int i=0;i<5;i++){
        p = a.add_objs();
        p->set_object_id(i);
        p->set_lng(i*1);
        p->set_lat(i*10000);
    }
    s.send_data(a,&tv,100);    // 控制发送频率，100 ms 发1次
//    s.send_data(a,NULL);        // 不控制发送频率
}


int main(int argc ,char **argv)
{
    LaserServer s(12347);
    s.start();

    while(1)
    {
        send_msg(s);        //  发送检测物体
        usleep(100000);
    }

    s.stop();
    return 0;
}







