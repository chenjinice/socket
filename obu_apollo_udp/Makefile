CC = gcc
CROSS = arm-linux-gnueabihf-$(CC) 

PROTO_SRC = obu_apollo.pb-c.c
SEND_SRC = send.c $(PROTO_SRC) obu_apollo.c
RECV_SRC = recv.c $(PROTO_SRC) obu_apollo.c

LIB += -lpthread
LIB += -lprotobuf-c

LIB_DIR += -L/usr/local/lib
LIB_DIR_ARM += -L./protobuf-c/lib
INC_DIR_ARM += -I./protobuf-c/include

all: $(PROTO_SRC)
	$(CC) $(SEND_SRC) -o send.out  $(LIB_DIR) $(LIB)
	$(CC) $(RECV_SRC) -o recv.out  $(LIB_DIR) $(LIB)

arm: $(PROTO_SRC)
	$(CROSS) $(SEND_SRC) -o send_arm.out $(INC_DIR_ARM) $(LIB_DIR_ARM) $(LIB)
	$(CROSS) $(RECV_SRC) -o recv_arm.out $(INC_DIR_ARM) $(LIB_DIR_ARM) $(LIB)

$(PROTO_SRC):obu_apollo.proto
	protoc-c --c_out=. $< 

clean:
	-rm send.out 
	-rm recv.out
	-rm send_arm.out
	-rm recv_arm.out
	-rm obu_apollo.pb-c.c
	-rm obu_apollo.pb-c.h
	
.PHONY: clean



