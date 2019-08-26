CC = gcc
CFLAGS=

HDFHOME=/home/mussel9/asc/HDF
LIBDIR = ${HDFHOME}/lib
HDFLIBS = -lmfhdf -ldf -ljpeg -lz -lnsl
INC =${HDFHOME}/include
INC2 = ../include
SUB = ../hdfsubs

#all: mbasic_rd  mhk_rd mtof_rd  mmonitor_rd  mpha_rd  mstatus_rd s3schk_rd
all: s3schk_rd

#mbasic_rd: mbasic_rd.o ${SUB}/hdf_swims_mbasic.o
#	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

#mbasic_rd.o: mbasic_rd.c
#	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

#mhk_rd: mhk_rd.o ${SUB}/hdf_swims_mhk.o
#	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

#mhk_rd.o: mhk_rd.c
#	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

#mtof_rd: mtof_rd.o ${SUB}/hdf_swims_mtof.o
#	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

#mtof_rd.o: mtof_rd.c
#	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

#mmonitor_rd: mmonitor_rd.o ${SUB}/hdf_swims_mmonitor.o
#	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

#mmonitor_rd.o: mmonitor_rd.c
#	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

#mpha_rd: mpha_rd.o ${SUB}/hdf_swims_mpha.o
#	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

#mpha_rd.o: mpha_rd.c
#	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

#mstatus_rd: mstatus_rd.o ${SUB}/hdf_swims_mstatus.o
#	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

#mstatus_rd.o: mstatus_rd.c
#	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

s3schk_rd: s3schk_rd.o ${SUB}/hdf_s3schk.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

s3schk_rd.o: s3schk_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

#${SUB}/hdf_swims_mbasic.o: ${SUB}/hdf_swims_mbasic.c
#	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
#${SUB}/hdf_swims_mhk.o: ${SUB}/hdf_swims_mhk.c
#	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
#${SUB}/hdf_swims_mtof.o: ${SUB}/hdf_swims_mtof.c
#	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
#${SUB}/hdf_swims_mmonitor.o: ${SUB}/hdf_swims_mmonitor.c
#	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
#${SUB}/hdf_swims_mpha.o: ${SUB}/hdf_swims_mpha.c
#	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
#${SUB}/hdf_swims_mstatus.o: ${SUB}/hdf_swims_mstatus.c
#	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_s3schk.o: ${SUB}/hdf_s3schk.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}

