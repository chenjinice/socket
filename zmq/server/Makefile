CC  = gcc
CPP = g++
RM  = rm -f

protobuf_dir = /usr/local

target  = send.out
inc_dir += -I$(protobuf_dir)/include
lib_dir += -L$(protobuf_dir)/lib
lib 	+= -lprotobuf -lzmq -lpthread
obj 	= $(patsubst %.cc,%.o,$(wildcard *.cc))

all:$(target)

$(target):$(obj)
	$(CPP) -o $(target) $(obj) $(inc_dir) $(lib_dir) $(lib)

%.o:%.cc
	$(CPP) -std=c++11 -c -o $@ $<

p:vision.proto
	protoc --cpp_out=. vision.proto

clean:	
	-$(RM) $(obj) $(target)

cleanall:clean
	-$(RM) vision.pb.cc vision.pb.h

.phony: clean cleanall


