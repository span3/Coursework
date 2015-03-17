DIR = $(shell pwd)
SRCS = protectfile.c rijndael.c
INCS = rijndael.h
OBJS = $(SRCS:.c=.o)
EXECBIN = protectfile
OTHERS = Makefile


GCC = gcc -Wall

all: $(EXECBIN)

$(EXECBIN): $(OBJS) $(INCS)
	$(GCC) -o$(EXECBIN) $(OBJS)
	rm *.o

%.o: %.c
	$(GCC) -c $<

clean:
	rm *.o

spotless: 
	rm $(EXECBIN) $(TESTFILE) *.o