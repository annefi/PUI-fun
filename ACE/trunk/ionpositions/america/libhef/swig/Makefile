#
# File: libhef_wrap.mak
#
# Description:
#   Makefile for libhef/swig directory.
#
# Author(s):  Simon Hefti (hef)
#             Jim Raines  (jmr)
#
# Method:
#   
# This file is controlled by CVS:
# $Id: libhef_wrap.mak,v 1.10 2004/11/08 17:51:30 ddoud Exp $
#
# Major Modification History:
#   08Oct2002  jmr   modified for Red Hat 7.2
#   01NOV2004  ddoud modified for Fedora Core2
#


NETCDF  = /shrg1/local/netcdf-3.4
INCP5 = /usr/lib/perl5/5.8.3/i386-linux-thread-multi/CORE
SWIG  = /shrg1/local/bin/swig
export CC      = gcc

export CFLAGS  = -I ../include \
	-Dbool=char -DHAS_BOOL \
        -I$(INCP5) \
	-I$(NETCDF)/include -D_GNU_SOURCE
export LDFLAGS = -L$(NETCDF)/lib

libhef.so: libhef_wrap.o
	ld $(LDFLAGS)  -G $^ ../libhef.a -lnetcdf -lm -lc -o $@ 

libhef_wrap.o:

libhef_wrap.c:
	$(SWIG) -perl libhef.i

echo:
	@echo NETCDF=$(NETCDF)
	@echo CC=$(CC) 
	@echo CFGLAGS=$(CFLAGS)

clean:
	$(RM) libhef_wrap.o libhef.a
