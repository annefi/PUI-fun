#
# File: swindal/Makefile
#
# Description:
#   Top-level makefile for swindal package.
#
# Author(s): Jim Raines (jmr)
#
# Method:
#   
# Revision controlled by CVS:
# $Id: swindal.mak,v 1.2 2003/11/06 21:53:08 jraines Exp $
#
# Major Modification History:
#   07Aug2002   jmr   initial coding
#

# -------------------
# Version information
# -------------------

VERSIONFILE = swindal_version
# Set version from file '$(VERSIONFILE)', e.g. major.minor.build
export SWINDAL_VERSION = $(shell cat $(VERSIONFILE) 2> /dev/null || echo 0.0.0|tee $(VERSIONFILE))



default:
	@echo "SWINDAL version:" $(SWINDAL_VERSION)
	cd src; $(MAKE)
	cp src/libswindal.a .
	# increment build number in development directory
	perl tools/uv.pl $(SWINDAL_VERSION) > $(VERSIONFILE)

clean:
	cd src; $(RM) *.o
	rm libswindal.a

# for convenience during development
axlv2:
	cd ~/ace/axlv2; $(MAKE)


