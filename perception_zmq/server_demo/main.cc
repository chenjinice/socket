#include <unistd.h>	
#include "vserver.h"	


//
extern void process_signal(Flow_TrafficSig sig,int camera_id);

// 收到消息回调函数
void callback(uint8_t *buffer,int len,int index)
{
    PerceptionMsg msg;
    if(!msg.ParseFromArray(buffer,len)){
        printf("vserver : PerceptionMsg parse failed\n");
        return;
    }
    if(msg.event() != TRAFFIC_FLOW)return;
    if(!msg.has_dynamic_msg())return;

    const DynamicTimingMsg &d_msg = msg.dynamic_msg();
    for(int i=0;i<d_msg.flow_size();i++){
        const Flow & f = d_msg.flow(i);
        if(!f.has_camera())continue;
        if(!f.has_signal())continue;
        process_signal(f.signal(),f.camera());
    }
}

// 李旺的动态配时场景，收到消息的处理函数
void process_signal(Flow_TrafficSig sig,int camera_id)
{
    printf("traffic sig = %d,camera = %d\n",sig,camera_id);
}




// 发给融合程序的
void send_to_fusion(Vserver &s)
{
    PerceptionMsg msg;
    TargetMsg   * target_msg = new TargetMsg;
    Target      * target;
    static timeval tv = {0};    // 时间结构体,用于限制发送频率
    msg.set_event(TARGET_TO_FUSION);
    for(int i=0;i<1;i++){
        Position * pos= new Position;
        pos->set_lon(1);
        pos->set_lat(11);
        target = target_msg->add_target();
        target->set_id(i);
        target->set_type(HUMAN);
        target->set_allocated_pos(pos);
        target->set_camera(1);
    }
    msg.set_allocated_target_msg(target_msg);
    s.send(msg,&tv);
}

// 逆向行驶告警
void send_backward_car(Vserver &s)
{
    PerceptionMsg msg;
    TargetMsg   * target_msg = new TargetMsg;
    Target      * target;
    static struct timeval tv = {0};    // 时间结构体,用于限制发送频率
    msg.set_event(BACKWARD_DRIVING);
    for(int i=0;i<1;i++){
        Position * pos= new Position;
        pos->set_lon(2);
        pos->set_lat(22);
        target = target_msg->add_target();
        target->set_id(i);
        target->set_type(VEHICLE);
        target->set_allocated_pos(pos);
        target->set_camera(1);
        target->set_lane_id(2222);
    }
    msg.set_allocated_target_msg(target_msg);
    s.send(msg,&tv);
}

// 交通态势感知
void send_status(Vserver &s)
{
    PerceptionMsg msg;
    TargetMsg   * target_msg = new TargetMsg;
    Target      * target;
    static timeval tv = {0};    // 时间结构体,用于限制发送频率
    msg.set_event(TRAFFIC_STATUS);
    for(int i=0;i<1;i++){
        Position * pos= new Position;
        pos->set_lon(3);
        pos->set_lat(33);
        target = target_msg->add_target();
        target->set_id(i);
        target->set_type(HUMAN);
        target->set_allocated_pos(pos);
        target->set_camera(1);
    }
    msg.set_allocated_target_msg(target_msg);
    s.send(msg,&tv);
}

// 异常车辆（静止）
void send_abnormal_car(Vserver &s)
{
    PerceptionMsg msg;
    TargetMsg   * target_msg = new TargetMsg;
    Target      * target;
    static timeval tv = {0};    // 时间结构体,用于限制发送频率
    msg.set_event(ABNORMAL_CAR);
    for(int i=0;i<1;i++){
        Position * pos= new Position;
        pos->set_lon(4);
        pos->set_lat(44);
        target = target_msg->add_target();
        target->set_id(i);
        target->set_type(VEHICLE);
        target->set_allocated_pos(pos);
        target->set_camera(1);
        target->set_car_status(LINE_PRESSING);
    }
    msg.set_allocated_target_msg(target_msg);
    s.send(msg,&tv);
}

// 道路危险状况提醒（抛洒物）
void send_road_danger(Vserver &s)
{
    PerceptionMsg msg;
    TargetMsg   * target_msg = new TargetMsg;
    Target      * target;
    static timeval tv = {0};    // 时间结构体,用于限制发送频率
    msg.set_event(ROAD_DANGER);
    for(int i=0;i<1;i++){
        Position * pos= new Position;
        pos->set_lon(5);
        pos->set_lat(55);
        target = target_msg->add_target();
        target->set_id(i);
        target->set_type(OBSTACLE);
        target->set_allocated_pos(pos);
        target->set_camera(1);
    }
    msg.set_allocated_target_msg(target_msg);
    s.send(msg,&tv);
}

// 违章车辆预警1（违停）
void send_illegal_car1(Vserver &s)
{
    PerceptionMsg msg;
    TargetMsg   * target_msg = new TargetMsg;
    Target      * target;
    static timeval tv = {0};    // 时间结构体,用于限制发送频率
    msg.set_event(ILLEGAL_V1);
    for(int i=0;i<1;i++){
        Position * pos= new Position;
        pos->set_lon(6);
        pos->set_lat(66);
        target = target_msg->add_target();
        target->set_id(i);
        target->set_type(VEHICLE);
        target->set_allocated_pos(pos);
        target->set_camera(1);
    }
    msg.set_allocated_target_msg(target_msg);
    s.send(msg,&tv);
}

// 发送违章车辆2（占用应急车道）
void send_illegal_car2(Vserver &s)
{
    PerceptionMsg msg;
    TargetMsg   * target_msg = new TargetMsg;
    Target      * target;
    static timeval tv = {0};    // 时间结构体,用于限制发送频率
    msg.set_event(ILLEGAL_V2);
    for(int i=0;i<1;i++){
        Position * pos= new Position;
        pos->set_lon(7);
        pos->set_lat(77);
        target = target_msg->add_target();
        target->set_id(i);
        target->set_type(VEHICLE);
        target->set_allocated_pos(pos);
        target->set_camera(1);
    }
    msg.set_allocated_target_msg(target_msg);
    s.send(msg,&tv);
}

// 白天能见度检测与预警
void send_visibility(Vserver &s)
{
    PerceptionMsg  msg;
    VisibilityMsg *v_msg = new VisibilityMsg;
    static timeval tv = {0};                  // 时间结构体,用于限制发送频率
    msg.set_event(VISIBILITY);
    Position *pos = new Position;
    pos->set_lon(8);
    pos->set_lat(88);
    v_msg->set_level(8);                      // 能见度等级
    v_msg->set_allocated_camera_pos(pos);
    msg.set_allocated_visibility_msg(v_msg);
    s.send(msg,&tv);
}

// 行人与动物闯入检测
void send_crowd(Vserver &s)
{
    PerceptionMsg msg;
    TargetMsg   * target_msg = new TargetMsg;
    Target      * target;
    static timeval tv = {0};    // 时间结构体,用于限制发送频率
    msg.set_event(PEDESTRIAN);
    for(int i=0;i<1;i++){
        Position * pos= new Position;
        pos->set_lon(9);
        pos->set_lat(99);
        target = target_msg->add_target();
        target->set_id(i);
        target->set_type(HUMAN);
        target->set_allocated_pos(pos);
        target->set_camera(1);
    }
    msg.set_allocated_target_msg(target_msg);
    s.send(msg,&tv);
}


// 动态可行驶区域检测
void send_area(Vserver &s)
{
    PerceptionMsg msg;
    LaneAreaMsg * area_msg = new LaneAreaMsg;
    LaneArea    * area;
    Position    * pos;
    static timeval tv = {0};    // 时间结构体,用于限制发送频率
    msg.set_event(AVAILABLE_AREA);
    for(int i=0;i<1;i++){
        area = area_msg->add_area();
        for(int m=0;m<4;m++){   // 设置4个经纬度点
            pos = area->add_pos();
            pos->set_lon(100+m);
            pos->set_lat(1000+m);
        }
        area->set_camera(1);
    }
    msg.set_allocated_lane_area_msg(area_msg);
    s.send(msg,&tv);
}

// 隧道内火焰与烟雾预警
void send_smoke(Vserver &s)
{
    PerceptionMsg msg;
    WarnMsg      *warn_msg = new WarnMsg;
    static timeval tv = {0};    // 时间结构体,用于限制发送频率
    msg.set_event(FIRE_SMOKE);
    warn_msg->set_warn(true);
    msg.set_allocated_warn_msg(warn_msg);
    s.send(msg,&tv);
}

// 前方拥堵提醒
void send_jam(Vserver &s)
{
    PerceptionMsg msg;
    JamMsg      * jam_msg = new JamMsg;
    Jam         * jam;
    static timeval tv = {0};    // 时间结构体,用于限制发送频率
    msg.set_event(TRAFFIC_JAM);
    for(int i=0;i<1;i++){
        jam = jam_msg->add_jam();
        jam->set_vehicle_num(110);          // 车辆数量
        jam->set_vehicle_velocity(110.123); // 车辆平均速度
        jam->set_lane_heading(110.987);     // 道路航向角

        for(int m=0;m<4;m++){
            jam->add_vehicle_flow(1100+m);  // 车流量
        }
    }
    msg.set_allocated_jam_msg(jam_msg);
    s.send(msg,&tv);
}

// 动态配时场景
void send_flow(Vserver &s)
{
    PerceptionMsg msg;
    DynamicTimingMsg * d_msg = new DynamicTimingMsg;
    Flow             * flow;
//    static timeval tv = {0};                // 时间结构体,用于限制发送频率
    msg.set_event(DYNAMIC_TIMING);
    for(int i=0;i<1;i++){
        flow = d_msg->add_flow();
        flow->set_camera(1);
        for(int m=0;m<3;m++){
            flow->add_vehicle_num(1200+m);  // 每个车道车辆数
        }
//        for(int n=0;n<3;n++){
//            flow->add_pass_num(12000+n);    // 每个车道消散时间内通过车辆数
//        }
    }
//     设置开始时间
    Timestamp *time_begin = new Timestamp;
    timeval tv_now = {0};
    gettimeofday(&tv_now,nullptr);
    time_begin->set_seconds(tv_now.tv_sec);         // 秒
    time_begin->set_nanos(tv_now.tv_usec*1000);     // 纳秒
    d_msg->set_allocated_time_begin(time_begin);

    msg.set_allocated_dynamic_msg(d_msg);
    s.send(msg,nullptr);
}

// 特殊车辆
void send_special_car(Vserver &s)
{
    PerceptionMsg msg;
    TargetMsg   * target_msg = new TargetMsg;
    Target      * target;
    static timeval tv = {0};    // 时间结构体,用于限制发送频率
    msg.set_event(SPECIALCAR);
    for(int i=0;i<1;i++){
        Position * pos= new Position;
        pos->set_lon(130);
        pos->set_lat(1300);
        target = target_msg->add_target();
        target->set_id(i);
        target->set_type(VEHICLE);
        target->set_allocated_pos(pos);
        target->set_camera(1);
        target->set_car_type(DANGERCAR);
    }
    msg.set_allocated_target_msg(target_msg);
    s.send(msg,&tv);
}

// 交通事故
void send_accident_area(Vserver &s)
{
    PerceptionMsg msg;
    LaneAreaMsg * area_msg = new LaneAreaMsg;
    LaneArea    * area;
    Position    * pos;
    static timeval tv = {0};    // 时间结构体,用于限制发送频率
    msg.set_event(ACCIDENT);
    for(int i=0;i<1;i++){
        area = area_msg->add_area();
        for(int m=0;m<4;m++){   // 设置4个经纬度点
            pos = area->add_pos();
            pos->set_lon(140+m);
            pos->set_lat(1400+m);
        }
        area->set_camera(1);
    }
    msg.set_allocated_lane_area_msg(area_msg);
    s.send(msg,&tv);
}

// 结冰
void send_ice_warn(Vserver &s)
{
    PerceptionMsg msg;
    WarnMsg      *warn_msg = new WarnMsg;
    static timeval tv = {0};    // 时间结构体,用于限制发送频率
    msg.set_event(ICEWARN);
    warn_msg->set_warn(true);
    msg.set_allocated_warn_msg(warn_msg);
    s.send(msg,&tv);
}

// 车道线磨损
void send_lane_ware(Vserver &s)
{
    PerceptionMsg msg;
    LaneAreaMsg * area_msg = new LaneAreaMsg;
    LaneArea    * area;
    Position    * pos;
    static timeval tv = {0};    // 时间结构体,用于限制发送频率
    msg.set_event(LANE_WARE);
    for(int i=0;i<1;i++){
        area = area_msg->add_area();
        for(int m=0;m<2;m++){   // 设置2个经纬度点
            pos = area->add_pos();
            pos->set_lon(150+m);
            pos->set_lat(1500+m);
        }
        area->set_ware(DOUBLEYELLOWLINE);
    }
    msg.set_allocated_lane_area_msg(area_msg);
    s.send(msg,&tv);
}

// 车流量检测
void send_traffic_flow(Vserver &s)
{
    PerceptionMsg    msg;
    TrafficFlowMsg * t_msg = new TrafficFlowMsg;
    TrafficFlow    * flow;
//    static timeval tv = {0};                // 时间结构体,用于限制发送频率
    msg.set_event(TRAFFIC_FLOW);
    for(int i=0;i<1;i++){
        flow = t_msg->add_flow();
        flow->set_node_id(16);
        flow->set_link_id(160);
        for(int m=0;m<3;m++){
            flow->add_vehicle_num(1600+m);  // 每个车道车辆数
        }
        for(int n=0;n<3;n++){
            flow->add_maneuvers(16000+n);    // 车道属性
        }
        for(int n=0;n<3;n++){
            flow->add_pass_num(160000+n);    // 每个车道消散时间内通过车辆数
        }
    }
//     设置开始时间
    Timestamp *time_begin = new Timestamp;
    timeval tv_now = {0};
    gettimeofday(&tv_now,nullptr);
    time_begin->set_seconds(tv_now.tv_sec);         // 秒
    time_begin->set_nanos(tv_now.tv_usec*1000);     // 纳秒
    t_msg->set_allocated_time_begin(time_begin);
//     设置结束时间
    Timestamp *time_end = new Timestamp;
    timeval tv_end = {0};
    gettimeofday(&tv_end,nullptr);
    time_end->set_seconds(tv_end.tv_sec);         // 秒
    time_end->set_nanos(tv_end.tv_usec*1000);     // 纳秒
    t_msg->set_allocated_time_end(time_end);

    msg.set_allocated_traffic_flow_msg(t_msg);
    s.send(msg,nullptr);
}

// 排队长度
void send_queue_length(Vserver &s)
{
    PerceptionMsg    msg;
    QueueMsg *       q_msg = new QueueMsg;
    QueueLength    * queue;
//    static timeval tv = {0};                // 时间结构体,用于限制发送频率
    msg.set_event(QUEUE_LENGTH);
    for(int i=0;i<1;i++){
        queue = q_msg->add_queue();
        queue->set_node_id(17);
        queue->set_link_id(170);
        for(int m=0;m<3;m++){
            queue->add_vehicle_num(1700+m);   // 每个车道车辆数
        }
        for(int n=0;n<3;n++){
            queue->add_maneuvers(17000+n);    // 车道属性
        }
    }
    msg.set_allocated_queue_msg(q_msg);
    s.send(msg,nullptr);
    s.udpSend(msg,nullptr);
}



// ---------------------------- main -------------------------------------

int main(int argc ,char **argv)
{
    int          this_port = 12347;
    char *       remote_ip = (char *)"127.0.0.1";
    int          remote_port = 12348;
    if(argc >= 2)this_port = atoi(argv[1]);
    if(argc >= 3)remote_ip = argv[2];
    if(argc >= 4)remote_port = atoi(argv[3]);


    Vserver s;
    // 设置本机端口，远程ip和端口
    s.setParam(this_port,remote_ip,remote_port);
    s.start();

    // 李旺的动态配时场景要接收数据 ， 需要设置回调函数
    s.setCallBack(callback);

    // 打印协议版本号
    printf("perception version = %d\n",VERSION);

    // 添加要udp发送的ip和端口
    s.addUdpIp((char *)"127.0.0.1",12349);

    while(1){
        send_to_fusion(s);          // 发给融合程序的 ----------

        send_backward_car(s);       // 逆向行驶告警
        send_status(s);             // 交通态势感知
        send_abnormal_car(s);       // 异常车辆（静止）
        send_road_danger(s);        // 道路危险状况提醒（抛洒物）
        send_illegal_car1(s);       // 违章车辆预警1（违停）
        send_illegal_car2(s);       // 发送违章车辆2（占用应急车道）
        send_visibility(s);         // 白天能见度检测与预警
        send_crowd(s);              // 行人与动物闯入检测
        send_area(s);               // 动态可行驶区域检测
        send_smoke(s);              // 隧道内火焰与烟雾预警
        send_jam(s);                // 前方拥堵提醒
        send_flow(s);               // 动态配时场景
        send_special_car(s);        // 特殊车辆
        send_accident_area(s);      // 交通事故
        send_ice_warn(s);           // 结冰
        send_lane_ware(s);          // 车道线磨损
        send_traffic_flow(s);       // 车流量检测
        send_queue_length(s);       // 排队长度

        usleep(1000000);
    }

    return 0;
}







