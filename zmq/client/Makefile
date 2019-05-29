CC  = gcc
CPP = g++
RM  = rm -f

protobuf_dir = /usr/local

target  = recv.out
inc_dir += -I$(protobuf_dir)/include
lib_dir += -L$(protobuf_dir)/lib
lib 	+= -lprotobuf-c -lzmq -lpthread
obj 	= $(patsubst %.c,%.o,$(wildcard *.c))

all:$(target)

$(target):$(obj)
	$(CC) -o $(target) $(obj) $(inc_dir) $(lib_dir) $(lib)

%.o:%.cc
	$(CC) -c -o $@ $<

p:vision.proto
	protoc-c --c_out=. vision.proto

clean:	
	-$(RM) $(obj) $(target)

cleanall:clean
	-$(RM) vision.pb-c.c vision.pb-c.h

.phony: clean cleanall


