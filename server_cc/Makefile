

SRC += main.cc
SRC += vserver.cc
SRC += vision.pb.cc

LIB += -lprotobuf
LIB += -lboost_thread
LIB += -lboost_system

LIB_DIR += -L/usr/local/lib


all:
	g++ -std=c++11  $(SRC) $(LIB_DIR) $(LIB) -o a.out 

clean:
	rm a.out


.phony: clean


