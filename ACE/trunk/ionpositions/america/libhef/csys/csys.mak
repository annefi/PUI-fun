#
# File: csys.mak
#
# Description:
#   Makefile for libhef/csys directory.
#
# Author(s):  Simon Hefti (hef)
#             Jim Raines  (jmr)
#
# Method:
#   
# This file is controlled by CVS:
# $Id: csys.mak,v 1.4 2003/11/09 12:50:31 jraines Exp $
#
# Major Modification History:
#   08Oct2002  jmr   modified for Red Hat 7.2
#

CFLAGS  = -g -Wall -Wshadow -I../include -I$(NETCDF)/include

objects = csys.o

csys.o:

clean:
	$(RM) $(objects)
