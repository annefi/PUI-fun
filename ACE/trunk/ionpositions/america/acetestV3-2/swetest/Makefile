CC = gcc
CFLAGS=

HDFHOME=/home/mussel9/asc/HDF
LIBDIR = ${HDFHOME}/lib
HDFLIBS = -lmfhdf -ldf -ljpeg -lz -lnsl
INC =${HDFHOME}/include
INC2 = ../include
SUB = ../hdfsubs

all: sweeng_rdtest swensw_rdtest swecal_rdtest sweload_rdtest \
    swestea_rdtest swehskp_rdtest sweraw_rdtest swephe_rdtest

sweeng_rdtest: sweeng_rdtest.o ${SUB}/hdf_swepam_denge.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

sweeng_rdtest.o: sweeng_rdtest.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

swensw_rdtest: swensw_rdtest.o ${SUB}/hdf_swepam_dnswe.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

swensw_rdtest.o: swensw_rdtest.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

swecal_rdtest: swecal_rdtest.o ${SUB}/hdf_swepam_dcale.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

swecal_rdtest.o: swecal_rdtest.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

sweload_rdtest: sweload_rdtest.o ${SUB}/hdf_swepam_dloade.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

sweload_rdtest.o: sweload_rdtest.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

swestea_rdtest: swestea_rdtest.o ${SUB}/hdf_swepam_dstea.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

swestea_rdtest.o: swestea_rdtest.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

swehskp_rdtest: swehskp_rdtest.o ${SUB}/hdf_swepam_dhskpe.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

swehskp_rdtest.o: swehskp_rdtest.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

sweraw_rdtest: sweraw_rdtest.o ${SUB}/hdf_swepam_drawe.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

sweraw_rdtest.o: sweraw_rdtest.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

swephe_rdtest: swephe_rdtest.o ${SUB}/hdf_swepam_dphe.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

swephe_rdtest.o: swephe_rdtest.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

${SUB}/hdf_swepam_dcale.o: ${SUB}/hdf_swepam_dcale.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swepam_denge.o: ${SUB}/hdf_swepam_denge.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swepam_dhskpe.o: ${SUB}/hdf_swepam_dhskpe.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swepam_dloade.o: ${SUB}/hdf_swepam_dloade.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swepam_drawe.o: ${SUB}/hdf_swepam_drawe.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swepam_dnswe.o: ${SUB}/hdf_swepam_dnswe.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swepam_dstea.o: ${SUB}/hdf_swepam_dstea.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swepam_dphe.o: ${SUB}/hdf_swepam_dphe.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
