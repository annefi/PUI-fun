#
# File: libtim.mak
#
# Description:
#   Makefile for libhef/libtim directory.
#
# Author(s):  Simon Hefti (hef)
#             Jim Raines  (jmr)
#
# Method:
#   
# This file is controlled by CVS:
# $Id: libtim.mak,v 1.4 2003/11/09 12:50:32 jraines Exp $
#
# Major Modification History:
#   08Oct2002  jmr   modified for Red Hat 7.2
#

export CFLAGS  = -Wall -Wshadow -I ../include

objects = libtim.o

libnr:	$(objects)
	$(AR) crsv libtim.a $(objects)

libtim.o:

clean:
	$(RM) libtim.a $(objects)

