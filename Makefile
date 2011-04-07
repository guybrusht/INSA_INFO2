DBG = 1


# Compilateur
CC	= gcc

# Flags
ifeq ($(DBG),1)
     CFLAGS	= -c -g
else
     CFLAGS	= -c
endif


all: head.h main.o func.o 
	$(CC) main.o func.o libmat.a -lm
	
clean:
	rm -rf *.o
	

main.o: head.h main.c 
	$(CC) $(CFLAGS) main.c


func.o: head.h func.c 
	$(CC) $(CFLAGS) func.c

libmat.a: 
	ar -a libmat.a func.o