SRC += main.c
SRC += vclient.c
SRC += vision.pb-c.c
SRC += analysis.c

INC += -I../libs/protoc-c/include

LIB += -lprotobuf-c -lzmq -lpthread

LIB_DIR += -L../libs/protoc-c/lib

all:vision.pb-c.c
	gcc $(INC) $(SRC) $(LIB_DIR) $(LIB) -o recv.out

clean:
	-rm recv.out vision.pb-c.h vision.pb-c.c

vision.pb-c.c:vision.proto
	protoc-c --c_out=. vision.proto

.phony: clean

