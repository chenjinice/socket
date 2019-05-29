
CC  = gcc
RM  = rm -f

target   = recv.out
inc_dir += -I/usr/local/include
lib_dir += -L/usr/local/lib
lib 	+= -lprotobuf-c -lzmq -lpthread
obj 	 = $(patsubst %.c,%.o,$(wildcard *.c))

all:$(target)


$(target):$(obj)
	$(CC) -o $(target) $(obj) $(inc_dir) $(lib_dir) $(lib)

%.o:%.c
	$(CC) -c -o $@ $< $(inc_dir)

p:
	protoc-c --c_out=. vision.proto

clean:	
	-$(RM) $(obj) $(target)

cleanall:clean
	-$(RM) vision.pb-c.c vision.pb-c.h

.phony: clean cleanall




