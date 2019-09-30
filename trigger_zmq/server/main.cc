#include <unistd.h>	
#include "trigger_server.h"	


using namespace trigger;


// 发送抓拍物
static void send_snap(TriggerServer &s)
{
    SnapMsg a;
    SnapObj *p;
    static struct timeval tv = {0};     // 时间结构体,用于限制发送频率
    a.set_id(SNAP);
    for(int i=0;i<2;i++){
        p = a.add_array();
        p->set_lng(1);
        p->set_lat(2);
        p->set_speed(3);
        p->set_type(4);
        p->set_camera(i);
    }

    // 设置时间
    Timestamp *time = new Timestamp();
    struct timeval tv_now = {0};
    gettimeofday(&tv_now,NULL);
    time->set_seconds(tv_now.tv_sec);       // 秒
    time->set_nanos(tv_now.tv_usec*1000);   // 微秒
    a.set_allocated_time(time);

    s.send_data(a,&tv,1000);     			// 发送
}



// ---------------------------- main -------------------------------------

int main(int argc ,char **argv)
{
    int this_port = 12349;
    if(argc >= 2)this_port = atoi(argv[1]);

    TriggerServer s(this_port);
    s.start();

    while(1)
    {
        send_snap(s);  // 发送抓拍物
        usleep(100000);
    }

    return 0;
}







