CFLG = -Wall -Werror -g

all: event_loop.bin

event_loop.bin: event_loop.o
	gcc event_loop.o $(CFLG) -o event_loop.bin

event_loop.o: event_loop.c
	gcc event_loop.c $(CFLG) -c -o event_loop.o




