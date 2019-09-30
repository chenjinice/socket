
CC  = gcc
RM  = rm -f

INC_SYS_PATH = /usr/local/include
LIB_SYS_PATH = /usr/local/lib 

INC_ARM_PATH = ../../libs/arm/include
LIB_ARM_PATH = ../../libs/arm/lib


target   = recv.out
lib 	 = -lprotobuf-c -lzmq -lpthread
obj 	 = $(patsubst %.c,%.o,$(wildcard *.c))


ifeq ($(MAKECMDGOALS),arm)
	CC = arm-linux-gnueabihf-gcc
	target = recv-arm.out
	inc_dir += -I$(INC_ARM_PATH)
	lib_dir += -L$(LIB_ARM_PATH)
else
	inc_dir += -I$(INC_SYS_PATH)
	lib_dir += -L$(LIB_SYS_PATH)
endif


all pc arm:$(target)

$(target):$(obj)
	$(CC) -o $(target) $(obj) $(inc_dir) $(lib_dir) $(lib)

%.o:%.c
	$(CC) -c -o $@ $< $(inc_dir)

proto:trigger.proto
	protoc-c --c_out=. $<

clean:	
	-$(RM) $(obj) *.out

cleanall:clean
	-$(RM) trigger.pb-c.c trigger.pb-c.h

.phony: clean cleanall




