CFLG = -Wall -Werror -g

all: 13_1server.bin client.bin

client.bin: client.o client.c
	gcc client.o $(CFLG) -o client.bin

client.o: client.c
	gcc client.c $(CFLG) -c -o client.o

13_1server.bin: server.o server.c
	gcc server.o $(CFLG) -o 13_1server.bin

server.o: server.c
	gcc server.c $(CFLG) -c -o server.o

