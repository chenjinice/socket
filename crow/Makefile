

SRC += main.cc

LIB += -lboost_thread
LIB += -lboost_system
LIB += -lpthread

LIB_DIR += -L/usr/local/lib


all:
	g++ -std=c++11  $(SRC) $(LIB_DIR) $(LIB) -o a.out 

clean:
	-rm a.out
	@echo "abc"


.phony: clean


