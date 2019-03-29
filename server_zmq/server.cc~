#include <zmq.hpp>
#include "zhelpers.hpp"
#include <unistd.h>
#include "vision.pb.h"

using namespace std;

int main()
{
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind("tcp://*:12347");

    while (1) {
	cout << "send send" << endl;	
        s_sendmore (publisher, "A");
	//s_send (publisher, "We don't want to see this");
	s_send (publisher, "B");
//        sleep (1);

        //s_send (publisher, "We would like to see this");
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
	string serialized;
	o.SerializeToString(&serialized);
        s_sendmore (publisher, "B");
	s_send(publisher,serialized);
        usleep (10000);


	Crowd v;
	Pedestrian *p;
	v.set_id(PEDESTRIAN_D);
	for(int i=0;i<3;i++){
		p = v.add_pedestrian();
		p->set_object_id(i);
		p->set_object_type(HUMAN); // 类型:人,车,摩托车
		p->set_camera(1);          // 哪个相机 :1,2,3,4
		p->set_x(1128990180);             // 经度
		p->set_y(281265890);	           // 纬度
	}
	string str;
	v.SerializeToString(&str);
        s_sendmore (publisher, "B");
	s_send(publisher,str);
	usleep(10000);
    }

}


