CFLG = -Wall -Werror -g

all: lab12_3.bin

lab12_3.bin: lab12_3.o get_string_all.o
	gcc lab12_3.o get_string_all.o $(CFLG) -o lab12_3.bin

lab12_3.o: 12_3.c
	gcc 12_3.c $(CFLG) -c -o lab12_3.o

get_string_all.o: get_string_all.c
	gcc get_string_all.c $(CFLG) -c -o get_string_all.o