CFLG = -Wall -Werror -g

all: server.bin client.bin

client.bin: client.o client.c
	gcc client.o $(CFLG) -o client.bin -lrt

client.o: client.c
	gcc client.c $(CFLG) -c -o client.o

server.bin: server.o server.c
	gcc server.o $(CFLG) -o server.bin -lrt

server.o: server.c
	gcc server.c $(CFLG) -c -o server.o




