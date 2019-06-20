#ifndef __ARS408_H__
#define __ARS408_H__

#include <linux/can.h>
#include <iostream>
#include <vector>
#include "ars408_protocol.h"
#include "common_defines.h"

class MyCan;
class ZmqPub;

class ARS408{
public:
    ARS408(char *dev);
    ~ARS408();
    void start();

private:
    MyCan  *m_can;
    ZmqPub *m_pub;
    char   *m_dev;
    int     m_device_id;
    bool    m_ready;
    std::string m_soft_version;
    std::vector<Obstacle_Info> m_vector;


    void read_loop();
    void analysis(struct can_frame *pFrame);
    void obj_list_fun(struct can_frame *pFrame);
    void obj_general_fun(struct can_frame *pFrame);
    void obj_quality_fun(struct can_frame *pFrame);
    void obj_extend_fun(struct can_frame *pFrame);
    void version_fun(struct can_frame *pFrame);
    int  seach_obstacle(int id);
    void pub_obstacle();
    void print_obstacle();


    // 友元函数，pthread 创建线程时需要
    friend void *ars408_read_thread(void *param);
};



#endif


