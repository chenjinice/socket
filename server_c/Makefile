

PROTO_SRC = obu_apollo.pb-c.c

SRC += main.c
SRC += $(PROTO_SRC)
SRC += obu_server.c

LIB += -lpthread
LIB += -lprotobuf-c

LIB_DIR += -L/usr/local/lib

all: $(PROTO_SRC)
	gcc $(SRC) -o a.out  $(LIB_DIR) $(LIB)

$(PROTO_SRC):obu_apollo.proto
	protoc-c --c_out=. $< 

clean:
	-rm a.out
	-rm obu_apollo.pb-c.c
	-rm obu_apollo.pb-c.h


.PHONY: clean
