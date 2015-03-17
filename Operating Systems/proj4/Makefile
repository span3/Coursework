# Working directory
DIR       = /root/project4

# Set up setkey system call.
# /usr/src/include/
SKDIR     = $(DIR)/setkey
SKINCL    = $(SKDIR)/include/set_key.h
SKMINIX   = $(SKDIR)/include/minix/callnr.h
# /usr/src/servers/
SKFS     = $(SKDIR)/fs/table.c $(SKDIR)/fs/proto.h \
            $(SKDIR)/fs/setkey.c

# Set up protectfile user program
PFDIR     = protectfile


all : sksetup


#
# Move all the necessary file to the correct place for the system call
# setkey.
#
sksetup :
	cp $(SKINCL) /usr/src/include
	cp $(SKINCL) /usr/include
	cp $(SKMINIX) /usr/src/include/minix
	cp $(SKMINIX) /usr/include/minix
	cp $(SKFS) /usr/src/servers/fs