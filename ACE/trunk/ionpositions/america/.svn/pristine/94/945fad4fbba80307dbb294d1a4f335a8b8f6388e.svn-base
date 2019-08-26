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

all: epam_data_rd

epam_data_rd: epam_data_rd.o ${SUBS}/hdf_epam_data.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@

epam_data_rd.o: epam_data_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

${SUBS}/hdf_epam_data.o: ${SUBS}/hdf_epam_data.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
