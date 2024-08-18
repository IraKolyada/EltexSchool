CFLG = -Wall -Werror -g

all: lab6.bin

lab6.bin: lab6.o 51.c
	gcc lab6.o $(CFLG) -o lab6.bin

lab6.o: 51.c
	gcc 51.c $(CFLG) -c -o lab6.o
