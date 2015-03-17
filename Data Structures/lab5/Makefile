# $Id: Makefile,v 1.2 2011-04-05 15:36:49-07 - - $

JAVASRC    = hello.c
SOURCES    = README PARTNER part01.script part02.script part03.script part04.script part05.script part06.script part07.script part08.script part09.script part10.script list2.c list3.c list4.c environ.c
MAINCLASS  = hello
CLASSES    = hello.class
JARFILE    = hello
JARCLASSES = ${CLASSES}
SUBMITDIR  = cmps012b-wm.s11 lab5

check: ${SOURCES}
	- checksource ${SOURCES}


submit: check
	submit ${SUBMITDIR} ${SOURCES}
	- testsubmit ${SUBMITDIR} ${SOURCES}

again:
	gmake --no-print-directory spotless ci all test check

