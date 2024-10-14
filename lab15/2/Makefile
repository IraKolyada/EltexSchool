CFLG = -Wall -Werror -g

all: block_sig.bin

block_sig.bin: block_sig.o
	gcc block_sig.o $(CFLG) -o block_sig.bin

block_sig.o: block_sig.c 
	gcc block_sig.c $(CFLG) -c -o block_sig.o
