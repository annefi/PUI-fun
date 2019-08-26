#
# File: hefutil.mak
#
# Description:
#   Makefile for libhef/hefutil directory.
#
# Author(s):  Simon Hefti (hef)
#             Jim Raines  (jmr)
#
# Method:
#   
# This file is controlled by CVS:
# $Id: hefutil.mak,v 1.4 2003/11/09 12:50:32 jraines Exp $
#
# Major Modification History:
#   08Oct2002  jmr   modified for Red Hat 7.2
#

CFLAGS  = -g -Wall -Wshadow -I../include

objects = hefutil.o

all: $(objects)

clean:
	$(RM) $(objects)

#test:   arnaud_wrapper.o arnaud_share.o
#	gcc $(CFLAGS) -o arnaud_test arnaud_test.c \
#	  arnaud_wrapper.o arnaud_share.o -lm -lg2c
#	./arnaud_test
