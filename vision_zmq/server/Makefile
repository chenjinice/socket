CXX = g++
RM  = rm -f

INC_SYS_PATH = /usr/local/include
LIB_SYS_PATH = /usr/local/lib 

INC_PC_PATH = ../../libs/pc/include
LIB_PC_PATH = ../../libs/pc/lib


target  = send.out
lib 	= -lprotobuf -lzmq -lpthread
obj 	= $(patsubst %.cc,%.o,$(wildcard *.cc))



ifeq ($(MAKECMDGOALS),pc)
	inc_dir += -I$(INC_PC_PATH)
	lib_dir += -L$(LIB_PC_PATH)
else
	inc_dir += -I$(INC_SYS_PATH)
	lib_dir += -L$(LIB_SYS_PATH)
endif


all pc:$(target)

$(target):$(obj)
	$(CXX) -o $(target) $(obj) $(inc_dir) $(lib_dir) $(lib)

%.o:%.cc
	$(CXX) -std=c++11 -c -o $@ $<

proto:vision.proto
	protoc --cpp_out=. $<

clean:
	-$(RM) $(obj) $(target)

cleanall:clean
	-$(RM) vision.pb.cc vision.pb.h

.phony: clean cleanall


