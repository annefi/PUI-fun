CC = gcc
CFLAGS=

HDFHOME=/home/mussel9/asc/HDF
LIBDIR = ${HDFHOME}/lib
HDFLIBS = -lmfhdf -ldf -ljpeg -lz -lnsl
INC =${HDFHOME}/include
INC2 = ../include
SUB = ../hdfsubs

all: swieng_rdtest swissti_rdtest swical_rdtest swiload_rdtest \
    swiswi_rdtest swihskp_rdtest swisti_rdtest swisti2_rdtest

swieng_rdtest: swieng_rdtest.o ${SUB}/hdf_swepam_dengi.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

swieng_rdtest.o: swieng_rdtest.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

swissti_rdtest: swissti_rdtest.o ${SUB}/hdf_swepam_dssti.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

swissti_rdtest.o: swissti_rdtest.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

swical_rdtest: swical_rdtest.o ${SUB}/hdf_swepam_dcali.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

swical_rdtest.o: swical_rdtest.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

swiload_rdtest: swiload_rdtest.o ${SUB}/hdf_swepam_dloadi.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

swiload_rdtest.o: swiload_rdtest.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

swiswi_rdtest: swiswi_rdtest.o ${SUB}/hdf_swepam_dswi.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

swiswi_rdtest.o: swiswi_rdtest.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

swihskp_rdtest: swihskp_rdtest.o ${SUB}/hdf_swepam_dhskpi.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

swihskp_rdtest.o: swihskp_rdtest.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

swisti_rdtest: swisti_rdtest.o ${SUB}/hdf_swepam_dsti.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

swisti_rdtest.o: swisti_rdtest.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

swisti2_rdtest: swisti2_rdtest.o ${SUB}/hdf_swepam_dsti2.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

swisti2_rdtest.o: swisti2_rdtest.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

${SUB}/hdf_swepam_dcali.o: ${SUB}/hdf_swepam_dcali.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swepam_dengi.o: ${SUB}/hdf_swepam_dengi.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swepam_dhskpi.o: ${SUB}/hdf_swepam_dhskpi.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swepam_dloadi.o: ${SUB}/hdf_swepam_dloadi.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swepam_drawi.o: ${SUB}/hdf_swepam_drawi.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swepam_dssti.o: ${SUB}/hdf_swepam_dssti.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swepam_dswi.o: ${SUB}/hdf_swepam_dswi.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swepam_dsti.o: ${SUB}/hdf_swepam_dsti.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swepam_dsti2.o: ${SUB}/hdf_swepam_dsti2.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
