CC=gcc
CFLAGS=-I.
DEPS = intlist.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make: graph02.o intList.o 
	gcc -o graph02 graph02.o intList.o -I.
