#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "ars408.h"
#include "can/mycan.h"
#include "zmq/zmq_pub.h"
#include "interval.h"

using namespace std;

void *ars408_read_thread(void *param)
{
    // 线程结束时，自动释放资源
    pthread_detach(pthread_self());

    ARS408 *ars = (ARS408 *)param;
    ars->read_loop();
}


ARS408::ARS408(char *dev)
{
    m_dev = dev;
    m_device_id = -1;
    m_can = new MyCan();
    m_pub = new ZmqPub();
    m_ready = false;
}


ARS408::~ARS408()
{
    m_ready = false;
    if(m_can)delete m_can;
    if(m_pub)delete m_pub;
}


void ARS408::start()
{
    if(m_ready)return;

    if( !m_can->can_open(m_dev) ){
        printf("ARS408 : fail to open %s  !\n",m_dev);
        return;
    }else {
        printf("ARS408 : success to open %s \n",m_dev);
    }
    m_pub->start(22222,(char *)"radar");
    m_ready = true;

    pthread_t thread;
    pthread_create(&thread,NULL,ars408_read_thread,this);
}


void ARS408::read_loop()
{
    int len;
    while(m_ready){
        struct can_frame frame;
        len = m_can->can_read(&frame);

        if(len <= 0){
            printf("ARS408 can_read error : len = %d\n",len);
            continue;
        }

        this->analysis(&frame);
    }

}


// 解析can收到的雷达数据
void ARS408::analysis(can_frame *pFrame)
{
    static int s_id = m_device_id;
    static struct timeval s_tv = {0};

    int cmd = ars408_get_cmd(pFrame->can_id);
//    printf("id ==== 0x%X,num = %d,cmd = 0x%X\n",pFrame->can_id,pFrame->can_dlc,cmd);

    if( cmd != ARS408_CMD_RELAY )m_device_id = ars408_get_id(pFrame->can_id);
    if(m_device_id != s_id){
        printf("ARS408 : device id === %d\n",m_device_id);
        s_id = m_device_id;
    }

    switch (cmd) {
        case ARS408_CMD_OBJECT_LIST:
            this->obj_list_fun(pFrame);
//            printf("interval ============ %d\n",time_interval(&s_tv));
            break;
        case ARS408_CMD_OBJECT_GENERAL:
            this->obj_general_fun(pFrame);
            break;
        case ARS408_CMD_OBJECT_QUALITY:
            this->obj_quality_fun(pFrame);
            break;
        case ARS408_CMD_OBJECT_EXTEND:
            this->obj_extend_fun(pFrame);
            break;
        case ARS408_CMD_VERSION:
            this->version_fun(pFrame);
            break;
        default:
            break;
    }

}


void ARS408::obj_list_fun(can_frame *pFrame)
{
    this->pub_obstacle();
//    ars408_get_objectNum(pFrame);
}

// 解析雷达探测到的object的普通信息，并保存到vector
void ARS408::obj_general_fun(can_frame *pFrame)
{
    Ars408_ObjGeneral obj_general = {0};
    Obstacle_Info obs = {0};

    ars408_get_objectGeneral(pFrame,&obj_general);
    obs.id = obj_general.id;
    obs.lat = obj_general.lat;
    obs.lng = obj_general.lng;
    obs.v_lng = obj_general.v_lng;
    obs.v_lat = obj_general.v_lat;
    obs.rcs = obj_general.rcs;
    m_vector.push_back(obs);
}

// 解析雷达探测到的object的quality信息，并保存到vector
void ARS408::obj_quality_fun(can_frame *pFrame)
{
    Ars408_ObjQuality obj_quality = {0};
    obj_quality.id = -1;
    Obstacle_Info *obs = NULL;
    ars408_get_objectQuality(pFrame,&obj_quality);

    int index = this->seach_obstacle(obj_quality.id);
    if(index < 0)return;

    obs = &m_vector[index];
    obs->lng_rms = obj_quality.lng_rms;
    obs->lat_rms = obj_quality.lat_rms;
    obs->exist = obj_quality.exist;
}

// 解析雷达探测到的object的扩展信息，并保存到vector
void ARS408::obj_extend_fun(can_frame *pFrame)
{
    Ars408_ObjExtend obj_extend = {0};
    obj_extend.id = -1;
    Obstacle_Info *obs = NULL;
    ars408_get_objectExtend(pFrame,&obj_extend);

    int index = this->seach_obstacle(obj_extend.id);
    if(index < 0)return;

    obs = &m_vector[index];
    obs->object_class = obj_extend.object_class;
    obs->angle = obj_extend.angle;
}

//解析雷达软件版本号
void ARS408::version_fun(can_frame *pFrame)
{
     m_soft_version = ars408_get_version(pFrame);
//    cout << "ARS408 : software version  ------------------- " << m_soft_version << endl;
}


int ARS408::seach_obstacle(int id)
{
    int index = -1;
    int size = m_vector.size();
    for(int i=0;i<size;i++){
        if(m_vector[i].id == id)index = i;
    }
    return index;
}

// zmq发送障碍信息
void ARS408::pub_obstacle()
{
    this->print_obstacle();

    uint8_t buffer[1024] = {0};
    int count = 10;
    for(int i=0;i<count;i++)buffer[i]='0'+i;
    m_pub->send(buffer,count);

    m_vector.clear();
}


// 打印存储的雷达的障碍信息
void ARS408::print_obstacle()
{
    int size = m_vector.size();
    printf("ARS408 ::::::: %d objects\n",size);
    for(int i=0;i<size;i++){
        Obstacle_Info *p = &m_vector[i];
        printf("id:%d,lng:%f,lat:%f,vlng:%f,vlat:%f,rcs=%f,lng_rms:%f,lat_rms:%f,exist:%f\n",
               p->id,p->lng,p->lat,p->v_lng,p->v_lat,p->rcs,p->lng_rms,p->lat_rms,p->exist);
    }
}





