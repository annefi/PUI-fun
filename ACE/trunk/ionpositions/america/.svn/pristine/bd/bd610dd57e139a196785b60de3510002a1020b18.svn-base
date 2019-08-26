CC = gcc
CFLAGS=

HDFHOME=/home/mussel9/asc/HDF
LIBDIR = ${HDFHOME}/lib
HDFLIBS = -lmfhdf -ldf -ljpeg -lz -lnsl
INC =${HDFHOME}/include
INC2 = ../include
SUB = ../hdfsubs

#all: mag_hskp_rd mag_snap_rd mag_vec_rd mag_fft_rd mag_br_rd mag_avgvec_rd
all: mag_hskp_rd mag_snap_rd mag_vec_rd mag_fft_rd mag_avgvec_rd

mag_hskp_rd: mag_hskp_rd.o ${SUB}/hdf_mag_hskp.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

mag_hskp_rd.o: mag_hskp_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

mag_snap_rd: mag_snap_rd.o ${SUB}/hdf_mag_snap.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

mag_snap_rd.o: mag_snap_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

mag_vec_rd: mag_vec_rd.o ${SUB}/hdf_mag_vec.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

mag_avgvec_rd: mag_avgvec_rd.o ${SUB}/hdf_mag_avgvec.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

mag_vec_rd.o: mag_vec_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

mag_fft_rd: mag_fft_rd.o ${SUB}/hdf_mag_fft.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

mag_fft_rd.o: mag_fft_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

#mag_br_rd: mag_br_rd.o ${SUB}/hdf_magframe_out_br.o
#	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

#mag_br_rd.o: mag_br_rd.c
#	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

mag_avgvec_rd.o: mag_avgvec_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

${SUB}/hdf_mag_hskp.o: ${SUB}/hdf_mag_hskp.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_mag_snap.o: ${SUB}/hdf_mag_snap.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_mag_vec.o: ${SUB}/hdf_mag_vec.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_mag_fft.o: ${SUB}/hdf_mag_fft.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_mag_avgvec.o: ${SUB}/hdf_mag_avgvec.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_magframe_out_br.o: ${SUB}/hdf_magframe_out_br.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
