

SRC += main.cc
#SRC += vserver.cc
#SRC += vision.pb.cc

LIB += -lprotobuf
#LIB += -lboost_thread
#LIB += -lboost_system
LIB += -lzmq

LIB_DIR += -L/usr/local/lib


all:
	g++ -std=c++11  server.cc vision.pb.cc $(LIB_DIR) $(LIB) -o s
	g++ -std=c++11  client.cc $(LIB_DIR) $(LIB) -o c
 

clean:
	rm a.out


.phony: clean


