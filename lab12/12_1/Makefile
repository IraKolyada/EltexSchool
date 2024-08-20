CFLG = -Wall -Werror -g

all: lab12_1.bin


lab12_1.bin: lab12_1.o read.o write.o
	gcc lab12_1.o read.o write.o $(CFLG) -o lab12_1.bin

lab12_1.o: lab12_1.c mypipe.h
	gcc lab12_1.c $(CFLG) -c -o lab12_1.o

write.o: write.c
	gcc write.c $(CFLG) -c -o write.o

read.o: read.c
	gcc read.c $(CFLG) -c -o read.o




