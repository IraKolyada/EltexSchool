CFLG = -Wall -Werror -g

all: resefine.bin killing_proc.bin

resefine.bin: resefine.o
	gcc resefine.o $(CFLG) -o resefine.bin

resefine.o: resefine.c
	gcc resefine.c $(CFLG) -c -o resefine.o

killing_proc.bin: killing_proc.o
	gcc killing_proc.o $(CFLG) -o killing_proc.bin

killing_proc.o: killing_proc.c
	gcc killing_proc.c $(CFLG) -c -o killing_proc.o