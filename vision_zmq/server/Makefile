

SRC += main.cc
SRC += vserver.cc
SRC += vision.pb.cc

LIB += -lprotobuf -lzmq -lpthread

LIB_DIR += -L/usr/local/lib


all:vision.pb.cc
	g++ -std=c++11  $(SRC) $(LIB_DIR) $(LIB) -o a.out

clean:
	rm a.out

vision.pb.cc:vision.proto
	protoc --cpp_out=. vision.proto

.phony: clean


