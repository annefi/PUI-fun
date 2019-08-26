CC      = gcc
CFLAGS  = -g -Wall -Wshadow

objects = nrutil.o pythag.o svbksb.o svdcmp.o svdvar.o

libnr:	$(objects)
	$(AR) crsv libnr.a $(objects)

nrutil.o:	nrutil.h nr.h
pythag.o:	nrutil.h nr.h
svbksb.o:	nrutil.h nr.h
svdcmp.o:	nrutil.h nr.h
svdvar.o:	nrutil.h nr.h

clean:
	rm edit $(objects)
