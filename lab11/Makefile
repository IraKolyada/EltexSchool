CFLG = -Wall -Werror -g 

all: lab11_1.bin lab11_2.bin

lab11_1.bin: lab11_1.o 11_1.c
	gcc lab11_1.o $(CFLG) -o lab11_1.bin -lpthread

lab11_1.o: 11_1.c
	gcc 11_1.c $(CFLG) -c -o lab11_1.o 

lab11_2.bin: lab11_2.o 11_2.c
	gcc lab11_2.o $(CFLG) -o lab11_2.bin -lpthread

lab11_2.o: 11_2.c
	gcc 11_2.c $(CFLG) -c -o lab11_2.o




