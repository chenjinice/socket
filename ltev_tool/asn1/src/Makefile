
CC = ar
TARGET = libltev_asn.a

all:generate target install clean

generate:
	asn1c -fskeletons-copy -fnative-types -gen-PER -pdu=auto  LTEV.asn
	-rm Makefile.am.*
	-rm converter-example.*

target:
	$(CC) -rcv $(TARGET) *.c

install:
	cp *.h ../include
	cp $(TARGET) ../

clean:
	-rm *.h *.c $(TARGET)

cleanall:clean
	-rm ../include/*.h
	-rm ../$(TARGET)
	

