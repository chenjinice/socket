FLAGS += -lpthread
FLAGS += -Lprotobuf-c/lib	-lprotobuf-c
INC   += -Iprotobuf-c/include

all:
	gcc *.c $(INC) $(FLAGS) -lpthread -lprotobuf-c

clean:
	rm a.out


.phony: clean
