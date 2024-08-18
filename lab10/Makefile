CFLG = -Wall -Werror -g

all: lab10_2.bin lab10_1.bin

lab10_2.bin: lab10_2.o 10_2.c
	gcc lab10_2.o $(CFLG) -o lab10_2.bin

lab10_2.o: 10_2.c
	gcc 10_2.c $(CFLG) -c -o lab10_2.o

lab10_1.bin: lab10_1.o 10_1.c
	gcc lab10_1.o $(CFLG) -o lab10_1.bin

lab10_1.o: 10_1.c
	gcc 10_1.c $(CFLG) -c -o lab10_1.o




