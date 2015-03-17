# $Id: Makefile,v 1.3 2011-05-19 22:30:05-07 - - $

MKFILE    = Makefile
DEPSFILE  = ${MKFILE}.deps
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS    = gcc -MM
LINT      = lint -Xa -fd -m -u -x -errchk=%all
GRIND     = valgrind --leak-check=full

CSOURCE   = main.c queue.c auxlib.c
CHEADER   =        queue.h auxlib.h
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = catqueue
SOURCES   = ${CHEADER} ${CSOURCE} ${MKFILE}
LISTSRC   = ${SOURCES} ${DEPSFILE}
LISTING   = ../lab7c.catqueue.ps
OUTPUT    = output*.lis
SUBMIT   = submit cmps012b-wm.s11 lab7

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

%.o : %.c
	cid + $<
	${GCC} -c $<

lint : ${CSOURCE}
	lint ${LINTOPT} ${CSOURCE}

ci : ${SOURCES}
	cid + ${SOURCES} test*.data

lis : ${SOURCES} test
	mkpspdf ${LISTING} ${LISTSRC} ${OUTPUT}

clean :
	- rm ${OBJECTS} ${DEPSFILE} core ${OUTPUT}

spotless : clean
	- rm ${EXECBIN}

submit : ${SOURCES}
	${SUBMIT} ${SOURCES}

test : ${EXECBIN}
	- runprogram.perl -x output1.lis -0test1.data ${EXECBIN}
	- runprogram.perl -x output2.lis ${EXECBIN} test*.data
	- ${GRIND} ${EXECBIN} <test1.data >output3.lis 2>&1

deps : ${CSOURCE} ${CHEADER}
	@ echo "# ${DEPSFILE} created `date`" >${DEPSFILE}
	${MKDEPS} ${CSOURCE} | sort | uniq >>${DEPSFILE}

${DEPSFILE} :
	@ touch ${DEPSFILE}
	${MAKE} --no-print-directory deps


again :
	gmake spotless deps ci lint all lis

ifeq "${NEEDINCL}" ""
include ${DEPSFILE}
endif


