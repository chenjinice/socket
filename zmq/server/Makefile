


SRC += main.cc
SRC += vserver.cc
SRC += vision.pb.cc
SRC += analysis.cc

INC += -I../libs/protoc/include
LIB_DIR += -L../libs/protoc/lib
LIB += -lprotobuf -lzmq -lpthread

all:vision.pb.cc
	g++ -std=c++11 $(INC) $(SRC) $(LIB_DIR) $(LIB) -o send.out

clean:	
	-rm send.out vision.pb.cc vision.pb.h

vision.pb.cc:vision.proto
	protoc --cpp_out=. vision.proto

.phony: clean


