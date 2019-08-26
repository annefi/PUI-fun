CC = gcc 
CFLAGS= -g

HDFHOME=/home/mussel9/asc/HDF
HDFLIBDIR = ${HDFHOME}/lib
HDFLIBS = -lmfhdf -ldf -ljpeg -lz -lnsl
INC=${HDFHOME}/include
INC2=../include

all: br5min_rd brhourly_rd brdaily_rd


# make executable files 

brhourly_rd: brhourly_rd.o hdf_acebr_1hr.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${HDFLIBDIR} ${HDFLIBS} -o $@ -I${INC2}

brdaily_rd: brdaily_rd.o hdf_acebr_1dy.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${HDFLIBDIR} ${HDFLIBS} -o $@ -I${INC2}

br5min_rd: br5min_rd.o hdf_acebr_5min.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${HDFLIBDIR} ${HDFLIBS} -o $@ -I${INC2}

# make object files 

br5min_rd.o: br5min_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
brhourly_rd.o: brhourly_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
brdaily_rd.o: brdaily_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
browseplot.o: browseplot.c abr_1hr.h ace_br_5min.h ace_br_1hr.h ace_br_1dy.h
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

# make hdfsubs object files

hdf_acebr_1dy.o: hdf_acebr_1dy.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
hdf_acebr_1dy.c: ace_br_1dy.h ../hdfgen.pl
	../hdfgen.pl $< $@ F=acebr_1dy

hdf_acebr_1hr.o: hdf_acebr_1hr.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
hdf_acebr_1hr.c: ace_br_1hr.h ../hdfgen.pl
	../hdfgen.pl $< $@ F=acebr_1hr

hdf_acebr_5min.o: hdf_acebr_5min.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
hdf_acebr_5min.c: ace_br_5min.h ../hdfgen.pl
	../hdfgen.pl $< $@ F=acebr_5min

hdf_acebr_16s.o: hdf_acebr_16s.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
hdf_acebr_16s.c: ace_br_16s.h ../hdfgen.pl
	../hdfgen.pl $< $@ F=acebr_16s
