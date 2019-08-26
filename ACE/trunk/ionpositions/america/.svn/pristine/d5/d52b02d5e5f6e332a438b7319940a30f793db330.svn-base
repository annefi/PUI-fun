CC = gcc
CFLAGS=
HDFHOME=/home/mussel9/asc/HDF
LIBDIR = ${HDFHOME}/lib
LIBDIR2 = /usr/local/lang/SUNWspro/lib
HDFLIBS = -lmfhdf -ldf -ljpeg -lz -lnsl
MLIBS = -lsunmath -lm
INC =${HDFHOME}/include
INC2 = ../include
SUBS = ../hdfsubs

all: edb_rd edb_rd2 dummy_rd

edb_rd: edb_rd.o ${SUBS}/hdf_s3_edb.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@

edb_rd.o: edb_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

edb_rd2: edb_rd2.o ${SUBS}/hdf_s3_edb.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@

edb_rd2.o: edb_rd2.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

dummy_rd: dummy_rd.o ${SUBS}/hdf_s3_dummy.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@

dummy_rd.o: dummy_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

${SUBS}/hdf_s3_edb.o: ${SUBS}/hdf_s3_edb.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
${SUBS}/hdf_s3_dummy.o: ${SUBS}/hdf_s3_dummy.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
