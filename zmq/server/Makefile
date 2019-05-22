

SRC += main.cc
SRC += vserver.cc
SRC += vision.pb.cc

INC += -I../libs/protoc/include

LIB += -lprotobuf -lzmq -lpthread

LIB_DIR += -L../libs/protoc/lib


all:vision.pb.cc
	g++ -std=c++11 $(INC)  $(SRC) $(LIB_DIR) $(LIB) -o send.out

clean:	
	-rm send.out vision.pb.cc vision.pb.h

vision.pb.cc:vision.proto
	protoc --cpp_out=. vision.proto

.phony: clean


