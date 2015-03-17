# $Id: Makefile,v 1.1 2011-06-01 20:30:56-07 - - $

GCC        = gcc -g -O0 -Wall -Wextra -std=gnu99
LINT       = lint -Xa -fd -m -u -x -errchk=%all

CSOURCES   = 19stat.c
EXECBIN    = 19stat
ALLSOURCES = ${CSOURCES} Makefile README
SUBMITDIR  = cmps012b-wm.s11 lab9

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

