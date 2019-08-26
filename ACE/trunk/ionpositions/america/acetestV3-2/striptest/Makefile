CC = gcc
CFLAGS=

HDFHOME=/home/mussel9/asc/HDF
LIBDIR = ${HDFHOME}/lib
HDFLIBS = -lmfhdf -ldf -ljpeg -lz -lnsl
INC =${HDFHOME}/include
INC2 = ../include
SUB = .

all: mag_strip 

mag_strip: mag_strip.o ${SUB}/hdf_mag_vec_in.o ${SUB}/hdf_mag_vec_out.o \
	${SUB}/hdf_mag_fft_in.o ${SUB}/hdf_mag_fft_out.o \
	${SUB}/hdf_mag_snap_in.o ${SUB}/hdf_mag_snap_out.o \
	${SUB}/hdf_mag_hskp_in.o ${SUB}/hdf_mag_hskp_out.o \
	${SUB}/hdf_mag_avgvec_in.o ${SUB}/hdf_mag_avgvec_out.o \
	${SUB}/hdf_schskp_in.o ${SUB}/hdf_schskp_out.o \
	${SUB}/hdf_sunpulsetime_in.o ${SUB}/hdf_sunpulsetime_out.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

mag_strip.o: mag_strip.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

${SUB}/hdf_mag_avgvec_in.o: ${SUB}/hdf_mag_avgvec_in.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_mag_avgvec_out.o: ${SUB}/hdf_mag_avgvec_out.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}

${SUB}/hdf_mag_vec_in.o: ${SUB}/hdf_mag_vec_in.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_mag_vec_out.o: ${SUB}/hdf_mag_vec_out.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}

${SUB}/hdf_mag_snap_in.o: ${SUB}/hdf_mag_snap_in.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_mag_snap_out.o: ${SUB}/hdf_mag_snap_out.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}

${SUB}/hdf_mag_fft_in.o: ${SUB}/hdf_mag_fft_in.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_mag_fft_out.o: ${SUB}/hdf_mag_fft_out.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}

${SUB}/hdf_mag_hskp_in.o: ${SUB}/hdf_mag_hskp_in.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_mag_hskp_out.o: ${SUB}/hdf_mag_hskp_out.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}

${SUB}/hdf_schskp_in.o: ${SUB}/hdf_schskp_in.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_schskp_out.o: ${SUB}/hdf_schskp_out.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}

${SUB}/hdf_sunpulsetime_in.o: ${SUB}/hdf_sunpulsetime_in.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_sunpulsetime_out.o: ${SUB}/hdf_sunpulsetime_out.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}

clean:
	rm -f mag_strip.o hdf_mag_vec_in.o hdf_mag_vec_out.o \
	hdf_mag_fft_in.o hdf_mag_fft_out.o hdf_mag_snap_in.o \
	hdf_mag_snap_out.o hdf_mag_hskp_in.o hdf_mag_hskp_out.o \
	hdf_schskp_in.o hdf_schskp_out.o \
	hdf_mag_avgvec_in.o hdf_mag_avgvec_out.o \
	hdf_sunpulsetime_in.o hdf_sunpulsetime_out.o
