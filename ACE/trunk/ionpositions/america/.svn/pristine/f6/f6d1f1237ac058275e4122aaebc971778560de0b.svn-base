#
# File: libace_ancil.mak
#
# Description:
#   Makefile for top level of libace_ancil project.
#
# Author(s): Jim Raines (jmr)
#
# Method:
#   
# Revision controlled by CVS:
# $Id:
#
# Major Modification History:
#   02Oct2003   jmr   initial coding
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
# include files for this package
INCS = include/libace_ancil.h
# libraries in this package
LIBS = libace_ancil.so libace_ancilc.so
# executables in this packages
EXES = dump_ace_aosr get_ace_angles get_ace_aspect


default:
	cd src; $(MAKE)

clean:
	cd src; $(MAKE) clean



