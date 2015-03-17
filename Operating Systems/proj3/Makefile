MKFILE    = Makefile

#GCC       = gcc -g -O0 -Wall -Wextra -std=gnu99
GCC       = gcc
AR        = ar -rvs

DIR      = /root
LIBSRC   = mem.c
OSRC     = mem.o
ASRC     = mem.a
SRCS     = ${CSRCS} ${HSRCS}
EXECBIN  = tester
OBJECTS  = ${CSRCS:.c=.o}
MISC     = ${MKFILE}
ALLSRCS  = ${SRCS} ${MISC}

all : ${EXECBIN}

${EXECBIN} :
	${GCC} -c ${LIBSRC}
	${AR} ${ASRC} ${OSRC}

clean :
	- rm ${OSRC} ${OBJECTS} core

spotless : clean
	- rm ${EXECBIN} ${ASRC}