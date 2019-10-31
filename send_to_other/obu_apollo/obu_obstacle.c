#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include "obu_apollo.pb-c.h"
#include "obu_obstacle.h"


#define TIMEOUT	500			// 过时的时间 ms
#define MY_ARRAY_SIZE	30	// 最多保存的障碍物数量


// 收到视觉那边发过来数据的场景ID
typedef enum{
	MSG_PEDESTRIAN			= 1,  // 行人与动物闯入检测
	MSG_ILLEGAL_V1			= 2,  // 违章车辆1(违停)
	MSG_VISIBILITY			= 3,  // 白天能见度检测
	MSG_AVAILABLE_AREA		= 4,  // 可行驶区域检测
	MSG_ABNORMAL_CAR		= 5,  // 异常车辆检测(静止)
	MSG_ILLEGAL_V2			= 6,  // 违章车辆2(应急车道)
	MSG_TRAFFIC				= 7,  // 交通态势感知
	MSG_BACKWARD_DRIVING	= 8,  // 逆向行驶告警
	MSG_ROAD_DANGER			= 9,  // 道路危险状况提醒(抛洒物)
	MSG_FIRE_SMOKE			= 10, // 隧道内火焰与烟雾预警
}MSG_ID;


typedef struct _obstacle_info{
	int32_t id;
	enum OBS_TYPE{HUMAN= 0,VEHICLE= 1,OTHER= 2} type;
	int32_t lat;
	int32_t lng;
	uint32_t speed;
	uint32_t lane_id;
	uint32_t sec;
	uint32_t msec;
	struct timeval tv;
}Obstacle_info;


// 自定义一个结构体 ，存储障碍物信息 ，作用类似于链表
typedef struct _myarray{
	Obstacle_info obs[MY_ARRAY_SIZE];
	int length;
}MyArray;


static MyArray m_array = {0};

static pthread_mutex_t m_mutex = PTHREAD_MUTEX_INITIALIZER;



//查找元素
static int array_find(int32_t id)
{
	int index = -1,i;
	for(i=0;i<m_array.length;i++){
		if(m_array.obs[i].id == id){
			index = i;
			break;
		}
	}
	return index;
}


/*
// 添加元素
static int array_add(PersonalSafetyMessage_t *pPsm)
{
//	printf("psm count = %d, 0x%X, size=%d,array_len=%d",pPsm->msgCnt,pPsm->accuracy.buf,pPsm->accuracy.size,m_array.length);

	if(pPsm == NULL)return -1;
	if(pPsm->accuracy.buf == NULL)return -1;
	if(pPsm->accuracy.size < 6*4)return -1;
	if(m_array.length >= MY_ARRAY_SIZE)return -1;

	Obstacle_info *obs  = NULL;
	uint32_t array[20] = {0};
	int len = sizeof(array);
	len = (len > pPsm->accuracy.size) ? pPsm->accuracy.size : len;
	memcpy(array,pPsm->accuracy.buf,len);

	int id = array[0] ;
	int index = array_find(id);
	if(index == -1){
		obs = &m_array.obs[m_array.length];
		obs->id = id;
		m_array.length++;
	}else{
		obs = &m_array.obs[index];
	}

	obs->lat = pPsm->position.lat;
	obs->lng = pPsm->position.Long;
	obs->type = array[1];
	obs->lane_id = array[2];
	obs->speed = 0;
	gettimeofday(&obs->tv,NULL);
	obs->sec = 0;
	obs->msec = 0;

//	printf("id:%d,lng:%d,lat:%d,type=%d,lane_id=%d,array length = %d\n",
//			obs->id,obs->lng,obs->lat,obs->type,obs->lane_id,m_array.length);

    return 0;
}
*/

// 获取两个时间戳之间的差值， 毫秒
static int get_interval(struct timeval *tv1,struct timeval *tv2)
{
	int ms = (tv1->tv_sec-tv2->tv_sec)*1000 + (tv1->tv_usec-tv2->tv_usec)/1000;
	ms = abs(ms);
	return ms;
}

//清理数组，清除过时的数据
static void array_cleanup()
{
	int i;
	int length = m_array.length;
	struct timeval tv = {0};
	gettimeofday(&tv,NULL);

	for(i=length-1;i>=0;i--){
		if(get_interval(&tv,&m_array.obs[i].tv) < TIMEOUT)continue;
		memset(m_array.obs+i,0,sizeof(Obstacle_info));
		memmove(m_array.obs+i,m_array.obs+i+1,(MY_ARRAY_SIZE-i-1)*sizeof(Obstacle_info));
		memset(m_array.obs+MY_ARRAY_SIZE-1,0,sizeof(Obstacle_info));
		m_array.length--;
	}
}

// 清空数组
static void array_clear_all()
{
	memset(m_array.obs,0,sizeof(m_array.obs));
	m_array.length = 0;
}

/*
void obstacle_analysic(PersonalSafetyMessage_t *pPsm)
{
	// 加锁
	pthread_mutex_lock(&m_mutex);
	switch(pPsm->msgCnt){
		case MSG_PEDESTRIAN:
		case MSG_TRAFFIC:
			array_add(pPsm);
			break;
		default:
			break;
	}
//	array_cleanup();
	pthread_mutex_unlock(&m_mutex);
}
*/


// 把障碍物信息放入 msg 消息里
void set_obumsg_obstacle(ObuApollo__ObuMsg *msg)
{
	if(msg == NULL)return;
	int i;

	// 加锁
	pthread_mutex_lock(&m_mutex);
	array_cleanup();
	int obs_num = m_array.length;
	ObuApollo__Obstacle **obs_array = calloc(obs_num,sizeof(ObuApollo__Obstacle*));
	for(i=0;i<obs_num;i++){
		obs_array[i] = calloc(1,sizeof(ObuApollo__Obstacle));
		obu_apollo__obstacle__init(obs_array[i]);
		obs_array[i]->id = m_array.obs[i].id;
		obs_array[i]->type = m_array.obs[i].type;
		obs_array[i]->lng = m_array.obs[i].lng;
	    obs_array[i]->lat = m_array.obs[i].lat;
	    obs_array[i]->has_speed = 1;
	    obs_array[i]->speed = m_array.obs[i].speed;
	    obs_array[i]->has_lane_id = 1;
	    obs_array[i]->lane_id = m_array.obs[i].lane_id;
	}
	msg->n_obs = obs_num;
	msg->obs = obs_array;

//	array_clear_all();
	pthread_mutex_unlock(&m_mutex);

}


void test()
{
	pthread_mutex_lock(&m_mutex);
	array_cleanup();
	Obstacle_info *obs  = NULL;

	int id = rand()%10;
	int index = array_find(id);
	if(index == -1){
		obs = &m_array.obs[m_array.length];
		obs->id = id;
		m_array.length++;
	}else{
		obs = &m_array.obs[index];
	}

	obs->lat = id*1000;
	obs->lng = id*2000;
	obs->type = id*2;
	obs->lane_id = id*3;
	obs->speed = id*4;
	gettimeofday(&obs->tv,NULL);
	pthread_mutex_unlock(&m_mutex);
	printf("id:%d,lng:%d,lat:%d,type=%d,lane_id=%d,array length = %d\n",
				obs->id,obs->lng,obs->lat,obs->type,obs->lane_id,m_array.length);

	usleep(20*1000);
	static int s_num = 1;
	if(s_num++%100 == 0)sleep(10);

}






