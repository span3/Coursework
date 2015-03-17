# $Id: Makefile,v 1.1 2011-06-03 16:45:21-07 - - $

MKFILE    = Makefile
DEPSFILE  = ${MKFILE}.deps
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}
GMAKE     = gmake --no-print-directory

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS    = gcc -MM
LINT      = lint -Xa -fd -m -u -x -errchk=%all

CSOURCE   = auxlib.c tree.c prioque.c huffman.c
CHEADER   = auxlib.h tree.h prioque.h
OBJECTS   = ${CSOURCE:.c=.o}
EXECBIN   = huffman
SUBMITS   = ${CHEADER} ${CSOURCE} ${MKFILE}
SOURCES   = ${SUBMITS}
LISTING   = ../asg5c-huffman.code.ps
PROJECT   = cmps012b-wm.s11 asg5

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

%.o : %.c
	${GCC} -c $<

lint : ${CSOURCE}
	${LINT} ${CSOURCE}
	checksource ${SUBMITS}

ci : ${SOURCES}
	cid + ${SOURCES}
	checksource ${SUBMITS}

lis : ${SOURCES} ${DEPSFILE}
	mkpspdf ${LISTING} ${SOURCES} ${DEPSFILE} ../phuffman.perl

clean :
	- rm ${OBJECTS} ${DEPSFILE} core

spotless : clean
	- rm ${EXECBIN}

submit : ${SUBMITS}
	submit ${PROJECT} ${SUBMITS}

deps : ${CSOURCE} ${CHEADER}
	@ echo "# ${DEPSFILE} created `date`" >${DEPSFILE}
	${MKDEPS} ${CSOURCE} | sort | uniq >>${DEPSFILE}

${DEPSFILE} :
	@ touch ${DEPSFILE}
	${GMAKE} deps

again :
	${GMAKE} spotless deps ci lint all lis

ifeq "${NEEDINCL}" ""
include ${DEPSFILE}
endif


