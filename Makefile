CC=cc
CFLAGS=-Wall -Werror
SRCS=hospital.c parse.c structure.c
OBJS=$(SRCS:.c=.o)
DBG=$(SRCS:.c=_dbg.o)

all: hospital.o parse.o structure.o
	$(CC) $(CFLAGS) -o hospital $(OBJS)
hospital.o: hospital.c parse.h structure.h
	$(CC) $(CFLAGS) -c hospital.c

parse.o: parse.c parse.h
	$(CC) $(CFLAGS) -c parse.c

structure.o: structure.c structure.h
	$(CC) $(CFLAGS) -c structure.c

debug: hospital_dbg.o parse_dbg.o structure_dbg.o
	$(CC) $(CFLAGS) -g -o hospital.dbg $(DBG)

hospital_dbg.o: hospital.c parse.h structure.h
	$(CC) $(CFLAGS) -g -o hospital_dbg.o -c hospital.c

parse_dbg.o: parse.c parse.h
	$(CC) $(CFLAGS) -g -o parse_dbg.o -c parse.c

structure_dbg.o: structure.c structure.h
	$(CC) $(CFLAGS) -g -o structure_dbg.o -c structure.c


clean :
	-rm hospital hospital.dbg $(OBJS) $(DBG)
