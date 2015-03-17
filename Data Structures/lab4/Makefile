# $Id: Makefile,v 1.1 2011-04-29 02:50:22-07 - - $

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99
LINT     = lint -Xa -fd -m -u -x -errchk=%all

CSOURCE    = bcat.c
EXECBIN    = bcat
ALLSOURCES = ${CSOURCE} Makefile README PARTNER
SUBMITDIR  = cmps012b-wm.s11 lab4 
LISTING  = ../lab4c-stdio.bcat.ps

all : ${EXECBIN}

${EXECBIN} : ${CSOURCE}
	${GCC} ${CSOURCE} -o ${EXECBIN}

lint : ${CSOURCE}
	checksource ${ALLSOURCES}
	${LINT} ${CSOURCE}

ci : ${ALLSOURCES}
	cid + ${ALLSOURCES}

clean :
	- rm core

spotless : clean
	- rm ${EXECBIN}

submit: ${ALLSOURCES}
	- checksource ${ALLSOURCES}
	submit ${SUBMITDIR} ${ALLSOURCES}

lis : ${ALLSOURCES}
	mkpspdf ${LISTING} ${ALLSOURCES}

again :
	gmake --no-print-directory spotless ci lint all lis

