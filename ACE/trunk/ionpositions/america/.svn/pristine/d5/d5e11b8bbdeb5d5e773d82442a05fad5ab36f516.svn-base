#
# File: libace_ancil-tools.mak
#
# Description:
#   
#
# Author(s): Jessica Hovater Feeman (jhf), Jim Raines (jmr)
#
# Method:
#   
# This file is controlled by CVS:
# $Id: libace_ancil-tools.mak,v 1.1.1.1 2003/10/02 17:08:31 jraines Exp $
#
# Major Modification History:
#   05Aug2003   jhf   initial coding
#   25Sep2003   jmr   adapted to use make macros/built-ins where possible
#

#------------------------------------------------------------------------------
# Variables which affect implicit rules
# See 'catalog of implicit rules' in make info file for details.
#------------------------------------------------------------------------------
# fortran compiler
FC =
# fortran compiler flags
FFLAGS =

# C compiler
CC = gcc
# C preprocessor flags (note: Also applied to Fortran and C++ compilations)
CPPFLAGS =
# C complier flags
CFLAGS = 

# C++ compiler
CXX = gcc
# C++ flags
CXXFLAGS =

# linker flags
LDFLAGS =
# libraries to include
LOADLIBES =
#------------------------------------------------------------------------------
#
#
# Description:
#   Makefile for libancil directory.
#

SWIG  = /shrg1/local/bin/swig
HDF     = /shrg1/local/hdf
INCP5 = /usr/lib/perl5/5.6.0/i386-linux/CORE
ACETEST = /shrg1/ace/sw/src/acetest/include

CC      = gcc
CFLAGS  = -I../include \
	  -Dbool=char -DHAS_BOOL \
	  -I$(INCP5) -I/shrg1/local/include \
          #-Wall -Wshadow

LDFLAGS = -L/shrg1/local/lib
LOADLIBES = -lmfhdf -lz -ljpeg -ldf -lc -lm ../src/libace_ancil.a

libace_ancil.so: libace_ancil_wrap.o ../src/libace_ancil.a
	ld -shared $^ $(LDFLAGS) $(LOADLIBES) -o $@

libace_ancil.i: ../include/libace_ancil.h
	../tools/h2i.pl ../include/libace_ancil.h libace_ancil.i

libace_ancil_wrap.o: libace_ancil_wrap.c

libace_ancil_wrap.c: libace_ancil.i
	$(SWIG) -perl5 $^


echo:
	@echo CC=$(CC) 
	@echo CFLAGS=$(CFLAGS)
	@echo HDF=$(HDF)
	@echo SWIG=$(SWIG)
clean:
	rm libace_ancil.so libace_ancil_wrap.* libace_ancil.i
