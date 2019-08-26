#
# File: axlv2/Makefile
#
# Description:
#   Top-level makefile for axlv2 project.
#
# Author(s): Jim Raines (jmr)
#
# Method:
#   
# Revision controlled by CVS:
# $Id: axlv2.mak,v 1.10 2005/02/21 18:16:18 jraines Exp $
#
# Major Modification History:
#   07Aug2002   jmr   imported parts from old swindal Makefile
#

export SWINDAL = ../swindal
#export LIBHEF  = /home/jraines/ace/libhef
export LOCAL = ../
export LIBHEF  = $(LOCAL)/libhef

default:
	$(MAKE) axlv2

axlv2:
	cd $(SWINDAL); make
	cd src; $(MAKE); 
	cp src/axlv2 .

axlv2_devel:
	cd $(SWINDAL); make
	cd src; $(MAKE) axlv2_devel; 
	cp src/axlv2_devel .

axlv2_shock:
	cd $(SWINDAL); make
	cd src; $(MAKE) axlv2_shock; 
	cp src/axlv2_shock .

install:
	cp -v axlv2 $(ACESW)/bin

clean:
	cd src; $(MAKE) clean

allclean:
	$(MAKE) clean
	cd $(SWINDAL); make clean

.PHONY: default axlv2 axlv2_devel axlv2_shock clean install

# note: axlv2* must be phony because no dependencies are specified
