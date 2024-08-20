CFLG = -Wall -Werror -g

all: client.bin server.bin

server.bin: server.o
	gcc server.o $(CFLG) -o server.bin

client.bin: client.o
	gcc client.o $(CFLG) -o client.bin

client.o: client.c
	gcc client.c $(CFLG) -c -o client.o

server.o: server.c
	gcc server.c $(CFLG) -c -o server.o






