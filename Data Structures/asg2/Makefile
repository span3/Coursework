# $Id: Makefile,v 1.1 2011-04-26 03:47:01-07 - - $

JAVASRC    = jroff.java commands.java linkedqueue.java auxlib.java
SOURCES    = ${JAVASRC} Makefile README PARTNER
MAINCLASS  = jroff
CLASSES    = jroff.class commands.class linkedqueue.class auxlib.class
JARCLASSES = ${CLASSES} commands\$$cmd.class commands\$$cmd_00.class \
             commands\$$cmd_bp.class commands\$$cmd_br.class \
             commands\$$cmd_cc.class commands\$$cmd_in.class \
             commands\$$cmd_ll.class commands\$$cmd_mt.class \
             commands\$$cmd_pl.class commands\$$cmd_po.class \
             commands\$$cmd_sp.class commands\$$cmd_tl.class \
             linkedqueue\$$node.class
JARFILE    = jroff
LISTING    = ../asg2j-jroff.code.ps
SUBMITDIR  = cmps012b-wm.s11 asg2

all : ${JARFILE}

${JARFILE} : ${CLASSES} Makefile
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm Manifest
	chmod +x ${JARFILE}

%.class : %.java
	- checksource $<
	- cid + $<
	javac $<

clean :
	- rm ${JARCLASSES} Manifest

spotless : clean
	- rm ${JARFILE}

ci : ${SOURCES}
	- checksource ${SOURCES}
	cid + ${SOURCES}

lis : ${SOURCES}
	mkpspdf ${LISTING} ${SOURCES}

submit : ${SOURCES}
	submit ${SUBMITDIR} ${SOURCES}
	testsubmit ${SUBMITDIR} ${SOURCES}
	
again:
	gmake --no-print-directory spotless ci all lis

