CC=gcc
CFLAGS=-I.
DEPS = intlist.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make: dfsTrace.o intList.o 
	gcc -o dfsTrace dfsTrace.o intList.o -I.
