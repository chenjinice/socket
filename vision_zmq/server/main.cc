#include <unistd.h>	
#include "vserver.h"	

using namespace vision;

// 逆向行驶告警
void send_backward_car(Vserver &s)	
{	
    IllegalCarWarn a;
    AbnormalCar   *p;
    static struct timeval tv = {0};    // 时间结构体,用于限制发送频率
    a.set_id(BACKWARD_DRIVING);
    for(int i=0;i<1;i++){
        p = a.add_array();
        p->set_object_id(i);
        p->set_camera(i);       // 哪个相机 :1,2,3,4
        p->set_lng(1);          // 经度
        p->set_lat(2);          // 纬度
        p->set_lane_id(1);      // 车道id
    }
    s.send_data(a,&tv);
}	

// 交通态势感知
void send_status(Vserver &s)	
{	
    Crowd a;
    Pedestrian *p;
    static struct timeval tv = {0};     // 时间结构体,用于限制发送频率
    a.set_id(TRAFFIC_STATUS);
    for(int i=0;i<3;i++){
        p = a.add_pedestrian();
        p->set_object_id(i);
        p->set_object_type(HUMAN);      // 类型:人,车,摩托车
        p->set_camera(1);               // 哪个相机 :1,2,3,4
        p->set_lng(11);         // 经度
        p->set_lat(12);	        // 纬度
    }
    s.send_data(a,&tv,1000);            // 两次发送间隔为小于 1000 ms的话，不会发送
}	

// 异常车辆（静止）
void send_abnormal_car(Vserver &s)	
{	
    IllegalCarWarn a;
    AbnormalCar   *p;
    static struct timeval tv = {0};     // 时间结构体,用于限制发送频率
    a.set_id(ABNORMAL_CAR);

    for(int i=0;i<1;i++){
        p = a.add_array();
        p->set_object_id(i);
        p->set_camera(1);         // 哪个相机 :1,2,3,4
        p->set_lng(21);           // 经度
        p->set_lat(22);           // 纬度
        p->set_abnormal_type(LINE_PRESSING);
    }
    s.send_data(a,&tv);
}	

// 道路危险状况提醒（抛洒物）
void send_road_danger(Vserver &s)	
{	
    Obstacles a;
    Obstacle *p;
    static struct timeval tv = {0};    // 时间结构体,用于限制发送频率
    a.set_id(ROAD_DANGER);
    for(int i=0;i<1;i++){
        p = a.add_array();
        p->set_object_id(i);
        p->set_camera(1);       // 哪个相机 :1,2,3,4
        p->set_lng(31);        // 经度
        p->set_lat(32);        // 纬度
    }
    s.send_data(a,&tv);
}	

// 违章车辆预警1（违停）
void send_illegal_car1(Vserver &s)	
{	
    IllegalCarWarn a;
    AbnormalCar   *p;
    static struct timeval tv = {0};   // 时间结构体,用于限制发送频率
    a.set_id(ILLEGAL_V1);
    for(int i=0;i<1;i++){
        p = a.add_array();
        p->set_object_id(i);
        p->set_camera(i);    	// 哪个相机 :1,2,3,4
        p->set_lng(41);       // 经度
        p->set_lat(42);       // 纬度
        p->set_lane_id(1);   	// 车道id
    }
    s.send_data(a,&tv);
}	

// 发送违章车辆2（占用应急车道）
void send_illegal_car2(Vserver &s)	
{	
    IllegalCarWarn a;
    AbnormalCar   *p;
    static struct timeval tv = {0};   // 时间结构体,用于限制发送频率
    a.set_id(ILLEGAL_V2);
    for(int i=0;i<1;i++){
        p = a.add_array();
        p->set_object_id(i);
        p->set_camera(i);      // 哪个相机 :1,2,3,4
        p->set_lng(51);         // 经度
        p->set_lat(52);         // 纬度
    }
    s.send_data(a,&tv);
}	

// 白天能见度检测与预警
void send_visibility(Vserver &s)	
{	
    Visibility a;
    static struct timeval tv = {0};          // 时间结构体,用于限制发送频率
    a.set_id(VISIBILITY);
    a.set_distance(123.456789);              // 能见度距离 米
    a.set_level(3);                          // 能见度等级
    s.send_data(a,&tv);
}	

// 行人与动物闯入检测
void send_crowd(Vserver &s)	
{	
    Crowd a;
    Pedestrian *p;
    static struct timeval tv = {0};     // 时间结构体,用于限制发送频率
    a.set_id(PEDESTRIAN_D);
    for(int i=0;i<2;i++){
        p = a.add_pedestrian();
        p->set_object_id(i);
        p->set_object_type(HUMAN);      // 类型:人,车,摩托车
        p->set_camera(1);               // 哪个相机 :1,2,3,4
        p->set_lng(61);                 // 经度
        p->set_lat(62);                 // 纬度
    }
    s.send_data(a,&tv,1000);            // 两次发送间隔为小于 1000 ms的话，不会发送
}			


// 动态可行驶区域检测
void send_area(Vserver &s)	
{	
    AvailableAreas a;
    AvailableArea *pa;
    static struct timeval tv = {0};      // 时间结构体,用于限制发送频率
    a.set_id(AVAILABLE_AREA);
    pa=a.add_area();
    pa->set_object_id(1);
    pa->set_camera(3);        // 哪个相机 :1,2,3,4
    pa->set_lng1(71);         // 第一个点经度
    pa->set_lat1(72);         // 第二个点纬度
    pa->set_lng2(73);         // 第二个点经度
    pa->set_lat2(74);         // 第二个点纬度
    pa->set_lng3(75);         // 第3个点经度
    pa->set_lat3(76);         // 第3个点纬度
    pa->set_lng4(77);         // 第4个点经度
    pa->set_lat4(78);         // 第4个点纬度
    s.send_data(a,&tv);
}

// 隧道内火焰与烟雾预警
void send_smoke(Vserver &s)	
{	
    SmokeWarn a;
    static struct timeval tv = {0};       // 时间结构体,用于限制发送频率
    a.set_id(FIRE_SMOKE);
    a.set_warn(true);
    s.send_data(a,&tv);
}	

// 前方拥堵提醒
void send_jam(Vserver &s)
{
    TrafficJam a;
    JamInfo *p;
    static struct timeval tv = {0};
    a.set_id(TRAFFIC_JAM);
    for(int i=0;i<2;i++){
        p = a.add_jam();
        p->set_vehicle_num(5);              // 车辆数量
        p->set_vehicle_avg_speed(10.1234);  // 车辆平均速度
        p->set_road_yaw(90.123);            // 道路航向角

        for(int m=0;m<4;m++){
            p->add_vehicle_flow(m*10);      // 车流量
        }
    }
    s.send_data(a,&tv);
}

// 动态配时场景
void send_flow(Vserver &s)
{
    TrafficFlow a;
    FlowInfo *p;
    static struct timeval tv = {0};
    a.set_id(TRAFFIC_FLOW);
    for(int i=0;i<1;i++){
        p = a.add_flow();
        p->set_camera(i);
        for(int m=0;m<3;m++){
            p->add_vehicle_num(m*10);
        }
//        for(int n=0;n<5;n++){
//            p->add_pass_num(n*100);
//        }
    }
    s.send_data(a,&tv);
}

// 特殊车辆
void send_special_car(Vserver &s)
{
    SpecialCarMsg a;
    SpecialCar *p;
    static struct timeval tv={0};
    a.set_id(SPECIALCAR);
    for(int i=0;i<2;i++){
        p = a.add_array();
        p->set_object_id(i);
        p->set_special_type(SpecialCar_SPECIALTYPE_DANGERCAR);
        p->set_lng(81);
        p->set_lat(82);
        p->set_camera(i);
    }
    s.send_data(a,&tv);
}

// 交通事故
void send_accident_area(Vserver &s)
{
    AvailableAreas a;
    AvailableArea *pa;
    static struct timeval tv = {0};      // 时间结构体,用于限制发送频率
    a.set_id(ACCIDENT);
    pa=a.add_area();
    pa->set_object_id(1);
    pa->set_camera(3);         // 哪个相机 :1,2,3,4
    pa->set_lng1(101);         // 第一个点经度
    pa->set_lat1(102);         // 第二个点纬度
    pa->set_lng2(103);         // 第二个点经度
    pa->set_lat2(104);         // 第二个点纬度
    pa->set_lng3(105);         // 第3个点经度
    pa->set_lat3(106);         // 第3个点纬度
    pa->set_lng4(107);         // 第4个点经度
    pa->set_lat4(108);         // 第4个点纬度
    s.send_data(a,&tv);
}

// 结冰
void send_ice_warn(Vserver &s)
{
    IceWarn a;
    static struct timeval tv = {0};       // 时间结构体,用于限制发送频率
    a.set_id(ICEWARN);
    a.set_warn(true);
    s.send_data(a,&tv);
}

// 车道线磨损
void send_lane_ware(Vserver &s)
{
    LaneWare a;
    static struct timeval tv = {0};       // 时间结构体,用于限制发送频率
    a.set_id(LANE_WARE);
    a.set_ware_type(LaneWare_WARETYPE_DOUBLEYELLOWLINE);
    a.set_lng1(91);
    a.set_lat1(92);
    a.set_lng2(93);
    a.set_lat2(94);
    s.send_data(a,&tv);
}


int main(int argc ,char **argv)
{
    int this_port = 12347;
    char *remote_ip = (char *)"127.0.0.1";
    int   remote_port = 12348;

    if(argc >= 2)this_port = atoi(argv[1]);
    if(argc >= 3)remote_ip = argv[2];
    if(argc >= 4)remote_port = atoi(argv[3]);


//    Vserver s(this_port);
    //涉及到交互的初始化
    Vserver s(this_port,remote_ip,remote_port);

    s.start();

    while(1)
    {
        send_backward_car(s);   // 逆向行驶告警
        send_status(s);         // 交通态势感知
        send_abnormal_car(s);   // 异常车辆（静止）
        send_road_danger(s);    // 道路危险状况提醒（抛洒物）
        send_illegal_car1(s);	// 违章车辆预警1（违停）
        send_illegal_car2(s);	// 发送违章车辆2（占用应急车道）
        send_visibility(s);     // 白天能见度检测与预警
        send_crowd(s);          // 行人与动物闯入检测
        send_area(s);           // 动态可行驶区域检测
        send_smoke(s);          // 隧道内火焰与烟雾预警
        send_jam(s);            // 前方拥堵提醒
        send_flow(s);           // 动态配时场景
        send_special_car(s);    // 特殊车辆
        send_accident_area(s);  // 交通事故
        send_ice_warn(s);       // 结冰
        send_lane_ware(s);      // 车道线磨损

        usleep(100000);
    }

    s.stop();
    return 0;
}







