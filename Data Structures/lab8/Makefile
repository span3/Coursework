# $Id: Makefile,v 1.21 2011-05-25 21:02:12-07 - - $

MKFILE    = Makefile
NOINCLUDE = ci
GMAKE     = gmake --no-print-directory

CSOURCE   = inssort.c numsort.c linesort.c
CHEADER   = inssort.h
OBJECTS   = ${CSOURCE:.c=.o}
SUBMITS   = ${CHEADER} ${CSOURCE} ${MKFILE} README
SOURCES   = ${SUBMITS}
PROJECT   = cmps012b-wm.s11 lab8

all : linesort numsort

%.o : %.c
	gcc -c $<

linesort : linesort.o inssort.o
	gcc -o linesort.c linesort.o
numsort : numsort.o inssort.o
	gcc -o numsort.c numsort.o
ci : ${SOURCES}
	cid + ${SOURCES}
	checksource ${SUBMITS}

submit : ${SUBMITS}
	submit ${PROJECT} ${SUBMITS}

ifeq "${NEEDINCL}" ""
endif


