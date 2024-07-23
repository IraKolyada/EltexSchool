CFLG = -Wall -Werror -g

all: lab3_1.bin lab3_2.bin lab3_3.bin #lab3_4.bin

#lab3_4.bin: lab3_4.o
#	gcc lab3_4.o $(CFLG) -c -o lab3_4.bin

#lab3_4.o: 34.c
#	gcc 34.c $(CFLG) -c -o lab3_4.o

lab3_3.bin: lab3_3.o
	gcc lab3_3.o $(CFLG) -o lab3_3.bin

lab3_3.o: 33.c
	gcc 33.c $(CFLG) -c -o lab3_3.o

lab3_2.bin: lab3_2.o
	gcc lab3_2.o $(CFLG) -o lab3_2.bin

lab3_2.o: 32.c
	gcc 32.c $(CFLG) -c -o lab3_2.o

lab3_1.bin: lab3_1.o
	gcc lab3_1.o $(CFLG) -o lab3_1.bin

lab3_1.o: 31.c
	gcc 31.c $(CFLG) -c -o lab3_1.o


