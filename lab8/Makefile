CFLG = -Wall -Werror -g

all: lab8.bin

lab8.bin: lab8.o mine.c libcalc.so
	gcc lab8.o -L. -lcalcul -Wl,-rpath,. -o lab8.bin

lab8.o: mine.c
	gcc mine.c $(CFLG) -c -o lab8.o

libcalc.so: calcul.c
	gcc -shared calcul.o -o libcalcul.so

calcul.o: calcul.c
	gcc calcul.c $(CFLG) -fPIC -c -o calcul.o