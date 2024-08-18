CFLG = -Wall -Werror -g

all: lab7.bin

lab7.bin: lab7.o mine.c libcalc.a
	gcc lab7.o $(CFLG) -L. -lcalc -o lab7.bin

lab7.o: mine.c
	gcc mine.c $(CFLG) -c -o lab7.o

libcalc.a: add.o sub.o mul.o div.o
	ar rc libcalc.a add.o sub.o mul.o div.o

div.o: div.c
	gcc div.c $(CFLG) -c -o div.o

mul.o: mul.c
	gcc mul.c $(CFLG) -c -o mul.o

sub.o: sub.c
	gcc sub.c $(CFLG) -c -o sub.o

add.o: add.c
	gcc add.c $(CFLG) -c -o add.o