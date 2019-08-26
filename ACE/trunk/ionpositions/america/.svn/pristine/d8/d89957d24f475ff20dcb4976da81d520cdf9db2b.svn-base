#
# File: swindal/src/Makefile
#
# Description:
#   Makefile for swindal main source directory.  Most of the work for building 
#   swindal is done here.
#
# Author(s): Jim Raines (jmr)
#
# Method:
#   
#  This file is controlled by the Concurent Version System (CVS):
#  $Id: swindal-src.mak,v 1.14 2005/06/06 20:43:39 jraines Exp $
#
# Major Modification History:
#   07Aug2002   jmr   changed to fit new directory structure
#   01May2001   jmr   initial coding
#   13Aug2003   jmr   changed to allow build from different directories
#   06Jun2005   jmr   merged with OSX version by adding OSX options

# ------------------------
# Variables to save typing
# ------------------------
# ===> kiel
export LOCAL = ../..

export SWINDAL = ..
export LIBHEF = $(SWINDAL)/../libhef
export AXLV2 = $(SWINDAL)/../axlv2
export HDF = $(LOCAL)/hdf
export NRCPP   = $(LOCAL)/nr_211/recipes_cpp
export TNTPARENT = $(NRCPP)/utils/tnt
export NRC   = $(LOCAL)/nr_211/recipes_c-ansi

# -------------------
# Version information
# -------------------
VERSIONFILE = $(SWINDAL)/swindal_version
# Set version from file '$(VERSIONFILE)', e.g. major.minor.build
export SWINDAL_VERSION = $(shell cat $(VERSIONFILE))


# ------------------------------------
# Variables controlling implicit rules
# ------------------------------------
export MAKEFLAGS = -e 

export CC = gcc
export CFLAGS = -I$(LIBHEF)/include -I$(TNTPARENT) -I$(LOCAL)/include \
		-I$(SWINDAL)/include \
                -DSWINDAL_VERSION='"$(SWINDAL_VERSION)"' \
		-I$(HDF)/include  \
		-I$(NRC)/include -I$(NRCPP)/utils 


#export CXX = g++-4.0
export CXX = g++
export CPPFLAGS = $(CFLAGS) -Wno-deprecated

LDFLAGS = -L$(LIBHEF) -L$(NRC) -L$(HDF)/lib -L$(NRCPP)
LOADLIBES = -lmfhdf -ldf -ljpeg -lz \
	-lrecipes_c++ -lrecipes_c -lhef -lnetcdf -lstdc++ -lm -lc

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

# ------------------------
# building main executable
# ------------------------

# ===> add .o file for each new module file
SWINDALOBJ = AnalysisData.o AceSwicsData.o swspeed.o BoxRates.o \
	Ion.o initSwindal.o MeasurementArray.o \
	incrementYdoy.o Pha.o Invert.o SpillRates.o ProbRates.o \
	eqte2mmq.o AceSwicsDutyCycle.o UlyssesSwicsEffic.o ElemEffic.o\
	InstrumentConstants.o AceSwicsConstants.o AssignedCounts.o \
	InstrumentHousekeeping.o  \
	AceSwicsFlux.o DistFunc.o AssignedCountsElem.o ErrorLevels.o \
	set_asp_int.o get_asp_int.o binetslice.o unbinetslice.o

libswindal.a: $(SWINDALOBJ)
	$(AR) csrv $@ $^

$(SWINDALOBJ): $(SWINDAL)/include/swindal.h
initSwindal.o: $(SWINDALOBJ)

clean: 
	$(RM) -f *.o 
#	$(RM) -f *.a

# --------------------------------------------
# targets dealing with source files explicitly
# --------------------------------------------
SOURCES = swindal.h $(addsuffix .cc, $(basename $(SWINDALOBJ)) )

# copy sources to a save directory to preserve current state
save:
	 save --tag_now $(SOURCES)

# --- printing code stuff --
# define a rule for making postscript listings of a source files
%.ps : %.cc ../include/%.h
	a2ps --prologue=color --output=$@ $^

%.ps : %.cc
	a2ps --prologue=color --output=$@ $^

%.ps : %.c
	a2ps --prologue=color --output=$@ $<

%.ps : %.h
	a2ps --prologue=color --output=$@ $<

swindal.h: ../include/swindal.h
	$(MAKE) $<

# making actual hardcopy output
PSFILES = $(addsuffix .ps, $(basename $(SOURCES)) )
psfiles: $(PSFILES)

hardcopy:  $(PSFILES)
	lpr -P mass-co $?
	touch $@
