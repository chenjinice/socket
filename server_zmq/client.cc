#include <zmq.hpp>
#include "zhelpers.hpp"
#include <unistd.h>

using namespace std;

int main()
{
	zmq::context_t context(1);
    	zmq::socket_t subscriber (context, ZMQ_SUB);
    	//连接
    	subscriber.connect("tcp://192.168.1.6:12347");
    	//设置频道B
    	subscriber.setsockopt( ZMQ_SUBSCRIBE, "B", 1);
    	while (1) {
 
        	//  Read envelope with address
        	std::string address = s_recv (subscriber);
        	//  Read message contents
        	std::string contents = s_recv (subscriber);
        
        	std::cout << "订阅1：[" << address << "] " << contents << std::endl;
    }

}


