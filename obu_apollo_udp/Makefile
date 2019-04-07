

PROTO_SRC = obu_apollo.pb-c.c

SEND_SRC = send.c $(PROTO_SRC) obu_apollo.c
RECV_SRC = recv.c $(PROTO_SRC) obu_apollo.c

LIB += -lpthread
LIB += -lprotobuf-c

LIB_DIR += -L/usr/local/lib

all: $(PROTO_SRC)
	gcc $(SEND_SRC) -o send.out  $(LIB_DIR) $(LIB)
	gcc $(RECV_SRC) -o recv.out  $(LIB_DIR) $(LIB)


$(PROTO_SRC):obu_apollo.proto
	protoc-c --c_out=. $< 

clean:
	-rm send.out 
	-rm recv.out
	-rm obu_apollo.pb-c.c
	-rm obu_apollo.pb-c.h

.PHONY: clean
