CC = gcc
CFLAGS=

HDFHOME=/home/mussel9/asc/HDF
LIBDIR = ${HDFHOME}/lib
HDFLIBS = -lmfhdf -ldf -ljpeg -lz -lnsl
INC =${HDFHOME}/include
INC2 = ../include
SUB = ../hdfsubs

all: sepica_rwbr_rd swepam_br_rd epam_br_rd mag_br_rd uleis_br_rd swics_br_rd


# make executable files 

sepica_rwbr_rd: sepica_rwbr_rd.o ${SUB}/hdf_sepica_rwbr.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

swepam_br_rd: swepam_br_rd.o ${SUB}/hdf_swepam_br.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

epam_br_rd: epam_br_rd.o ${SUB}/hdf_epam_br.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

mag_br_rd: mag_br_rd.o ${SUB}/hdf_magframe_out_br.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

uleis_br_rd: uleis_br_rd.o ${SUB}/hdf_uleis_br_out.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

swics_br_rd: swics_br_rd.o ${SUB}/hdf_swics_br.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}


# make object files 

sepica_rwbr_rd.o: sepica_rwbr_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

swepam_br_rd.o: swepam_br_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

epam_br_rd.o: epam_br_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

mag_br_rd.o: mag_br_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

uleis_br_rd.o: uleis_br_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

swics_br_rd.o: swics_br_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}


# make hdfsubs object files

${SUB}/hdf_sepica_rwbr.o: ${SUB}/hdf_sepica_rwbr.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swepam_br.o: ${SUB}/hdf_swepam_br.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_epam_br.o: ${SUB}/hdf_epam_br.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_mag_br.o: ${SUB}/hdf_magframe_out_br.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_uleis_br_out.o: ${SUB}/hdf_uleis_br_out.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swics_br.o: ${SUB}/hdf_swics_br.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
