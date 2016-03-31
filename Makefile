objects=hospital.o parse.o structure.o
CC=gcc
CFLAGS=-Wall -Werror
all: hospital
hospital: hospital.c parse.h structure.h
	$(CC) $(CFLAGS) -o hospital parse.c structure.c hospital.c 
	
parse.o: parse.c parse.h
	$(CC) $(CFLAGS) -c parse.c
	
structure.o: structure.c structure.h
	$(CC) $(CFLAGS) -c structure.c
	
clean :
	-rm hospital *.o *~