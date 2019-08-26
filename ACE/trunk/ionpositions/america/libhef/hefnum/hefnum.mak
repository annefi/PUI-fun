#
# File: hefnum.mak
#
# Description:
#   Makefile for libhef/hefnum directory.
#
# Author(s):  Simon Hefti (hef)
#             Jim Raines  (jmr)
#
# Method:
#   
# Major Modification History:
#   08Oct2002  jmr   modified for Red Hat 7.2
#

#
# File: hefnum.mak
#
# Description:
#   Makefile for libhef/hefnum directory.
#
# Author(s):  Simon Hefti (hef)
#             Jim Raines  (jmr)
#
# Method:
#   
# This file is controlled by CVS:
# $Id: hefnum.mak,v 1.4 2003/11/09 12:50:32 jraines Exp $
#
# Major Modification History:
#   08Oct2002  jmr   modified for Red Hat 7.2
#

CFLAGS  = -g -Wall -Wshadow -I../include -I$(NETCDF)/include

objects = hefnum.o \
	  mfunctions.o \
	  afunctions.o \
	  cfit.o \
	  svd.o

all: $(objects)
#	$(CC) -c $(CFLAGS) hefnum.c mfunctions.c afunctions.c cfit.c

clean:
	$(RM) $(objects)
