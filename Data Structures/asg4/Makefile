# $Id: Makefile,v 1.2 2011-05-24 01:01:09-07 - - $

MKFILE    = Makefile
DEPSFILE  = ${MKFILE}.deps
NOINCLUDE = ci clean spotless
NEEDINCL  = ${filter ${NOINCLUDE}, ${MAKECMDGOALS}}
GMAKE     = gmake --no-print-directory

GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
MKDEPS    = gcc -MM
LINT      = lint -Xa -fd -m -u -x -errchk=%all

CSOURCE   = auxlib.c hashset.c strhash.c spellchk.c
CHEADER   = auxlib.h hashset.h strhash.h yyextern.h
OBJECTS   = ${CSOURCE:.c=.o} scanner.o
EXECBIN   = spellchk
SUBMITS   = ${CHEADER} ${CSOURCE} scanner.l ${MKFILE}\
README PARTNER
SOURCES   = ${SUBMITS}
LISTING   = ../asg4c-spellchk.code.ps
PROJECT   = cmps012b-wm.s11 asg4

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${GCC} -o $@ ${OBJECTS}

scanner.o : scanner.l
	flex -oscanner.c scanner.l
	gcc -g -O0 -std=gnu99 -c scanner.c

%.o : %.c
	${GCC} -c $<

lint : ${CSOURCE}
	${LINT} ${CSOURCE}
	checksource ${SUBMITS}

ci : ${SOURCES}
	cid + ${SOURCES}
	checksource ${SUBMITS}

lis : ${SOURCES} ${DEPSFILE}
	mkpspdf ${LISTING} ${SOURCES} ${DEPSFILE}

clean :
	- rm ${OBJECTS} ${DEPSFILE} core scanner.c ${EXECBIN}.errs

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


