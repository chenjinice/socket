#include <unistd.h>
#include "vserver.h"

int main(int argc ,char **argv)
{
	Vserver s(12347);
	s.start();

	int flag = 1;
	while(flag)
	{
		// 发送 crowd
		Crowd v;
		Pedestrian *p;
		v.set_id(PEDESTRIAN_D);
		for(int i=0;i<1;i++){
			p = v.add_pedestrian();
			p->set_object_id(i);
			p->set_object_type(HUMAN); // 类型:人,车,摩托车
			p->set_camera(1);          // 哪个相机 :1,2,3,4
			p->set_x(1128990180);             // 经度
			p->set_y(281265890);	           // 纬度
		}
		s.send_data(v);
		usleep(100000);

		// 发送 障碍物
		Obstacles o;
		Obstacle  *po;
		o.set_id(OBSTACLE_D);
		for(int i=0;i<2;i++){
			po = o.add_obstacle();
			po->set_object_id(i);
			po->set_camera(2);        // 哪个相机 :1,2,3,4
			po->set_x(i*3333);          // 经度
			po->set_y(i*333333);        // 纬度
		}
		s.send_data(o);
		usleep(100000);


		// 发送可行驶区域
		AvailableAreas a;
		AvailableArea *pa;
		a.set_id(AVAILABLE_AREA);
		pa=a.add_area();
		pa->set_object_id(1);
		pa->set_camera(3);           // 哪个相机 :1,2,3,4
		pa->set_x1(1000000);           // 第一个点经度
		pa->set_y1(1111111);         // 第二个点纬度
		pa->set_x2(2000000);           // 第二个点经度
		pa->set_y2(2222222);         // 第二个点纬度
		s.send_data(a);
		usleep(100000);

	}
	return 0;
}


