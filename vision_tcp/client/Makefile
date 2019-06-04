FLAGS += -lpthread
FLAGS += -Lusr/local/lib	-lprotobuf-c
INC   += -Iusr/local/include

all:
	gcc *.c $(INC) $(FLAGS) -lpthread -lprotobuf-c

clean:
	rm a.out


.phony: clean
