SRC += main.c
SRC += vclient.c
SRC += vision.pb-c.c
SRC += analysis.c

LIB += -lprotobuf-c -lzmq -lpthread

LIB_DIR += -L/usr/local/lib

all:vision.pb-c.c
	gcc  $(SRC) $(LIB_DIR) $(LIB) -o recv.out

clean:
	-rm recv.out

vision.pb-c.c:vision.proto
	protoc-c --c_out=. vision.proto

.phony: clean

