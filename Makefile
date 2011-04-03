DBG = y


# Compilateur
CC	= gcc

# Flags
ifeq ($(DBG),y)
     CFLAGS	= -c -g
else
     CFLAGS	= -c
endif


all: head.h main.o func.o 
	$(CC) main.o func.o
	
clean:
	rm -rf *.o
	

main.o: head.h main.c 
	$(CC) $(CFLAGS) main.c


func.o: head.h func.c 
	$(CC) $(CFLAGS) func.c
