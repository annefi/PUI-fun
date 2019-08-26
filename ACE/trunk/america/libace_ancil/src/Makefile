#
# File: libace_ancil-src.mak
#
# Description:
#   Makefile for libace_ancil routines which call routines in the anciltest
#   directory of the acetest package from the ACE Science Center.
#   Linking based on 'Makefile' in the anciltest subdirectory.
#
# Author(s): Jim Raines (jmr)
#
# Method:
#   
# Revision controlled by CVS:
# $Id: libace_ancil-src.mak,v 1.5 2003/10/21 16:06:03 jraines Exp $
#
# Major Modification History:
#   06Jun2003   jmr   initial coding


export LOCAL = ../..

# location of acetest package
export ACETEST = $(LOCAL)/acetestV3-2
export HDFHOME = $(LOCAL)/HDF4.2r1

#------------------------------------------------------------------------------
# Variables which affect implicit rules
# See 'catalog of implicit rules' section in 'info make' for details.
#------------------------------------------------------------------------------
# C compiler
CC = gcc

# C complier flags
#CFLAGS = -Wall -I../include -I$(ACETEST)/include -I$(HDFHOME)/include
CFLAGS =  -fPIC -g -Wall -I../include -I$(ACETEST)/include -I$(HDFHOME)/include

# C++ compiler flags
CPPFLAGS = $(CFLAGS)

# linker flags
export LDFLAGS =  -L$(HDFHOME)/lib -L$(LOCAL)/libace_ancil \
	-L$(LOCAL)/zlib-1.2.1/lib -L$(LOCAL)/jpeg-6b/lib

# libraries to include when linking
LOADLIBES =  -lmfhdf -ldf -ljpeg -lz -lm -lstdc++ -lc

#------------------------------------------------------------------------------
OBJECTS =  a3goa.o $(ACETEST)/anciltest/ancil_subs.o \
	$(ACETEST)/hdfsubs/hdf_aosr.o $(ACETEST)/hdfsubs/hdf_ccr.o

default:
	#$(MAKE) libace_ancilc.so; pwd; cp -fv libace_ancilc.so .. 
	$(MAKE) libace_ancil.a
	$(MAKE) get_ace_aspect; cp -v get_ace_aspect ..
	$(MAKE) dump_ace_aosr; cp -v dump_ace_aosr ..
	$(MAKE) get_ace_angles; cp -v get_ace_angles ..

# Note: For building libace_ancilc.so, $(OBJECTS) *cannot* be replaced
# with libace_ancil.a !  The shared library builds but executables
# complain of undefined symbols at link time.  And, 'nm
# libace_ancilc.so' does not list any of the expected anciltest, HDF
# or libace_ancil functions.
#libace_ancilc.so: $(OBJECTS)
#	echo LOADLIBES is $(LOADLIBES)
#	gcc -shared -Wl,-soname=$@ $(LDFLAGS) $^ $(LOADLIBES) -o $@

libace_ancil.a: $(OBJECTS)
	 $(AR) crsv $@ $^

#LOADLIBES =  -lace_ancilc -lmfhdf -ldf -ljpeg -lz -lm -lstdc++ -lc

get_ace_aspect: get_ace_aspect.o libace_ancil.a

dump_ace_aosr: dump_ace_aosr.o libace_ancil.a

get_ace_angles: get_ace_angles.o libace_ancil.a

install:
	echo Make 'install' target from top level makefile

clean:
	$(RM) -f *.o *.a *.so

test:
	echo $(LOCAL)
	echo $(HDFHOME)
	echo $(ACETEST)

