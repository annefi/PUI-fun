CC = gcc
CFLAGS= -Wall

HDFHOME=/home/mussel9/asc/HDF
LIBDIR = ${HDFHOME}/lib
HDFLIBS = -lmfhdf -ldf -ljpeg -lz -lnsl
INC =${HDFHOME}/include
INC2 = ../include
SUB = ../hdfsubs

#all: cbasic_rd  chk_rd celement_rd  cmonitor_rd  cpha_rd  cstatus_rd s3schk_rd
#all: cbasic_rd  chk_rd s3schk_rd swicsbr
all: s3schk_rd swicsbr

swicsbr: swicsbr.o swics_brsub.o ${SUB}/hdf_swics_br.o
	$(CC) ${CFLAGS} $^ -I${INC} -L/usr/local/lang/SUNWspro/lib -L${LIBDIR} ${HDFLIBS} -lF77 -lM77 -lm -lsunmath -o $@ -I${INC2}

swicsbr.o: swicsbr.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

swics_brsub.o: swics_brsub.for
	f77 -c $< -I${INC2}

#cbasic_rd: cbasic_rd.o ${SUB}/hdf_swics_cbasic.o
#	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

#cbasic_rd.o: cbasic_rd.c
#	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

#chk_rd: chk_rd.o ${SUB}/hdf_swics_chk.o
#	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

#chk_rd.o: chk_rd.c
#	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

#celement_rd: celement_rd.o ${SUB}/hdf_swics_celement.o
#	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

#celement_rd.o: celement_rd.c
#	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

#cmonitor_rd: cmonitor_rd.o ${SUB}/hdf_swics_cmonitor.o
#	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

#cmonitor_rd.o: cmonitor_rd.c
#	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

#cpha_rd: cpha_rd.o ${SUB}/hdf_swics_cpha.o
#	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

#cpha_rd.o: cpha_rd.c
#	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

#cstatus_rd: cstatus_rd.o ${SUB}/hdf_swics_cstatus.o
#	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

#cstatus_rd.o: cstatus_rd.c
#	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

s3schk_rd: s3schk_rd.o ${SUB}/hdf_s3schk.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

s3schk_rd.o: s3schk_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

#${SUB}/hdf_swics_cbasic.o: ${SUB}/hdf_swics_cbasic.c
#	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
#${SUB}/hdf_swics_chk.o: ${SUB}/hdf_swics_chk.c
#	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
#${SUB}/hdf_swics_celement.o: ${SUB}/hdf_swics_celement.c
#	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
#${SUB}/hdf_swics_cmonitor.o: ${SUB}/hdf_swics_cmonitor.c
#	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
#${SUB}/hdf_swics_cpha.o: ${SUB}/hdf_swics_cpha.c
#	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
#${SUB}/hdf_swics_cstatus.o: ${SUB}/hdf_swics_cstatus.c
#	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_s3schk.o: ${SUB}/hdf_s3schk.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_swics_br.o: ${SUB}/hdf_swics_br.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
