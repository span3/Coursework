CC=gcc
CFLAGS=-I.
DEPS = intlist.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make: graph.o intList.o
	gcc -o graph graph.o intList.o -I.

