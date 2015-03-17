# Leodegario Anacleto (lanaclet@ucsc.edu)
# Steven Pan (span3@ucsc.edu)
# $Id: Makefile,v 1.3 2011-01-10 19:03:07-08 - - $

JAVASRC    = jfmt.java auxlib.java
SOURCES    = ${JAVASRC} Makefile README pfmt.perl PARTNER
MAINCLASS  = jfmt
CLASSES    = ${JAVASRC:.java=.class}
JARCLASSES = ${CLASSES}
JARFILE    = jfmt
LISTING    = ../asg1j-jfmt.code.ps
SUBMITDIR  = cmps012b-wm.w11 asg1

all : ${JARFILE}

${JARFILE} : ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm Manifest
	chmod +x ${JARFILE}

%.class : %.java
	cid + $<
	checksource $<
	javac $<

clean :
	- rm ${JARCLASSES}

spotless : clean
	- rm ${JARFILE}

ci : ${SOURCES}
	cid + ${SOURCES}
	checksource ${SOURCES}

lis : ${SOURCES}
	mkpspdf ${LISTING} ${SOURCES}

submit : ${SOURCES} ci
	submit ${SUBMITDIR} ${SOURCES}
	testsubmit ${SUBMITDIR} ${SOURCES}

again : ${SOURCES}
	gmake --no-print-directory spotless all lis
	
