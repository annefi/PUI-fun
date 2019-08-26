#
# File: libhef.mak
#
# Description:
#   Makefile for top level of libhef project.
#
# Author(s):  Simon Hefti (hef)
#             Jim Raines  (jmr)
#
# Method:
#   
# This file is controlled by CVS:
# $Id: libhef.mak,v 1.11 2003/11/09 15:03:10 jraines Exp $
#
# Major Modification History:
#   08Oct2002  jmr   modified for Red Hat 7.2
#

export LOCAL   = $(HOME)/ace
export NETCDF  = $(LOCAL)/netcdf-3.5.1
export INCP5   = /usr/lib/perl5/5.6.0/i386-linux/CORE \
export CC      = gcc
export CFLAGS  = -Wall -Wshadow -I ../include
export CFLAGS  = -Wall -Wshadow -I ../include -I $(NETCDF)/include
export RM      = rm -f
INSTALL_DIR = /shrg1/ace/sw/perl
#export SHELL = /bin/bash

objects = csys/csys.o \
	  acetools/bittools.o \
          acetools/asxdpusim.o \
          acetools/swxtools.o \
          acetools/expand.o \
          acetools/expand_tools.o \
          acetools/a3dif.o \
          heffile/heffile.o \
          libtim/libtim.o \
          hefnum/hefnum.o \
          hefnum/mfunctions.o \
          hefnum/afunctions.o \
          hefnum/cfit.o \
          hefnum/svd.o \
	  hefutil/hefutil.o

all:
	@cd acetools; $(MAKE)
	@cd heffile; $(MAKE)
	@cd hefnum; $(MAKE)
	@cd hefutil; $(MAKE)
	@cd libtim; $(MAKE)
	@cd csys; $(MAKE)
	$(AR) crsv libhef.a $(objects)
	#@cd swig; $(MAKE)

# for testing variable overrides
echo:
	@echo MAKE=$(MAKE)
	@echo NETCDF=$(NETCDF)
	@echo CC=$(CC) 
	@echo CFLAGS=$(CFLAGS)
	@cd swig; $(MAKE) echo

install: 
	cp -f swig/libhef.pm $(INSTALL_DIR)
	cp -f swig/libhef.so $(INSTALL_DIR)
	cp -f swig/libhef_wrap.doc $(INSTALL_DIR)/libhef.doc
	cp -f swig/libhef_wrap.html $(INSTALL_DIR)/libhef.html
	chmod 0775 $(INSTALL_DIR)/*
	chgrp shrgdev $(INSTALL_DIR)/*
	ls -l $(INSTALL_DIR)

# this target dnw and is under development for replacment of install
install2: swig/libhef.pm swig/libhef.so libhef.doc libhef.html
	for f in this that; do echo f=$f; done
	#$(MAKE) preinstall2
	#echo cp -vf \$f $(INSTALL_DIR); \
	#echo chmod 0775 $(INSTALL_DIR)/$f;  \
	#echo chgrp shrgdev $(INSTALL_DIR)/$f; \
	#done
	#ls -l $(INSTALL_DIR)

preinstall2:
	cp -vf swig/libhef_wrap.doc libhef.doc
	cp -vf swig/libhef_wrap.html libhef.html

clean:
	@cd acetools; $(MAKE) clean
	@cd heffile; $(MAKE) clean
	@cd hefnum; $(MAKE) clean
	@cd hefutil; $(MAKE) clean
	@cd libtim; $(MAKE) clean
	@cd csys; $(MAKE) clean
	$(RM) libhef.a
	@cd swig; $(MAKE) clean
