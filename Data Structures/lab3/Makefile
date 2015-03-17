# $Id: Makefile,v 1.1 2011-04-21 01:48:28-07 - - $

GCC        = gcc -g -O0 -Wall -Wextra -std=gnu99
LINT       = lint -Xa -fd -m -u -x -errchk=%all

CSOURCES   = errno.c
EXECBIN    = errno
ALLSOURCES = ${CSOURCES} Makefile README PARTNER
SUBMITDIR  = cmps012b-wm.s11 lab3

all : ${EXECBIN}

${EXECBIN} : ${CSOURCES}
	${GCC} $< -o ${EXECBIN}

lint : ${CSOURCES}
	${LINT} ${LINTOPT} ${CSOURCES}
	checksource ${ALLSOURCES}

ci : ${ALLSOURCES} 
	cid + ${ALLSOURCES}

clean :
	- rm core

spotless : clean
	- rm ${EXECBIN}

submit: ${ALLSOURCES}
	- checksource ${ALLSOURCES}
	submit ${SUBMITDIR} ${ALLSOURCES}

