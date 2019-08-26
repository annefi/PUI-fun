#
# File: axlv2/src/Makefile
#
# Description:
#   Source directory makefile for axlv2 project.
#
# Author(s): Jim Raines (jmr)
#
# Method:
#   
# Revision controlled by CVS:
# $Id: axlv2-src.mak,v 1.20 2005/06/06 20:43:50 jraines Exp $
#
# Major Modification History:
#   07Aug2002   jmr   imported parts from old swindal Makefile
#   13Aug2003   jmr   changed to allow build from different directories; 
#	              changed to axlv2-src.mak and linked back to Makefile
#   06Jun2005   jmr   merged with OSX version by adding OSX options

# ===> kiel
export	LOCAL  = ../..
AXLV2   = ..
LIBHEF  = $(AXLV2)/../libhef
export NETCDF  = $(LOCAL)/netcdf-3.6.0-p1
SWINDAL = $(AXLV2)/../swindal
export NRCPP = $(LOCAL)/nr_211/recipes_cpp
export TNTPARENT = $(NRCPP)/utils/tnt
export NRC = $(LOCAL)/nr_211/recipes_c-ansi

# ------------------------------------
# Variables controlling implicit rules
# ------------------------------------
MAKEFLAGS = -e 

CC = gcc
CFLAGS = -I$(SWINDAL)/include -I$(LIBHEF)/include \
	        -I$(NETCDF)/include -I$(TNTPARENT) -I$(NRC)/include \
	-I$(NRCPP)/utils

#CXX = g++-4.0
CXX = g++
CPPFLAGS = $(CFLAGS) -Wno-deprecated

LDFLAGS = -L$(AXLV2)/../libace_ancil -L$(LIBHEF) -L$(NRC) \
	-L$(NRCPP) -L$(NETCDF)/lib

LOADLIBES = -lrecipes_c++ -lrecipes_c -lhef -lnetcdf -lstdc++ -lm -lc

# add 'DEBUG=t' to command line
# Note: only objects built with this flag will have symbol info.  Do
# 'make clean; make DEBUG=t' to get full symbol info.
ifdef DEBUG
  CFLAGS += -g -DDEBUG -Wall
  # CPPFLAGS will get this too, automatically, because of make's 
  # deferred expansion of variables (see 'info make' for details)
else
  # optimize if not debugging
  CFLAGS += -O3
endif

OBJECTS = correctFeFM.o doyfr2doy_fr_str.o cycletimetodate.o\
	  xfmexp.o xfmexp_phys.o correctFM_phys.o AxPhysicsFM.o \
	  setPrGaussCutoff.o showVersions.o loadIons.o setErrorLevels.o

default:
	echo cflags = $(CFLAGS)
	$(MAKE) ver
	$(MAKE) axlv2

ver:
	../tools/makeShowVersions.pl $(SWINDAL) .
	$(MAKE) showVersions.o

axlv2: axlv2.o $(OBJECTS) $(SWINDAL)/libswindal.a

axlv2_devel: axlv2_devel.o $(OBJECTS) $(SWINDAL)/libswindal.a

axlv2_shock: axlv2_shock.o $(OBJECTS) $(SWINDAL)/libswindal.a

clean:
	$(RM) *.o axlv2
