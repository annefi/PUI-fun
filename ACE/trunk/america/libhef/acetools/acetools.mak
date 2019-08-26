#
# File: acetools.mak
#
# Description:
#   Makefile for libhef/acetools directory.
#
# Author(s):  Simon Hefti (hef)
#             Jim Raines  (jmr)
#
# This file is controlled by CVS:
# $Id: acetools.mak,v 1.5 2003/11/09 12:50:31 jraines Exp $
#
# Method:
# Method:
#   
# Major Modification History:
#   08Oct2002  jmr   modified for Red Hat 7.2
#
CFLAGS  = -Wall -Wshadow -I$(NETCDF)/include -I../include

objects = bittools.o \
          asxdpusim.o \
          swxtools.o \
          expand.o \
          expand_tools.o \
	  a3dif.o

libnr:	$(objects)
	$(AR) crsv libacetools.a $(objects)

bittools.o:
asxdpusim.o:
swxtools.o:
expand.o:
expand_tools.o:

clean:
	$(RM) libacetools.a $(objects)

