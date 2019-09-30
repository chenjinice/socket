CXX = g++
RM  = rm -f

target  = send.out
lib 	= -lprotobuf -lzmq -lpthread
obj 	= $(patsubst %.cc,%.o,$(wildcard *.cc))


inc_dir += -I/usr/local/include
lib_dir += -L/usr/local/lib 


all:$(target)

$(target):$(obj)
	$(CXX) -o $(target) $(obj) $(inc_dir) $(lib_dir) $(lib)

%.o:%.cc
	$(CXX) -std=c++11 -c -o $@ $< $(inc_dir)

proto:trigger.proto
	protoc --cpp_out=. $<

clean:
	-$(RM) $(obj) $(target)

cleanall:clean
	-$(RM) trigger.pb.cc trigger.pb.h

.phony: clean cleanall


