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

all: L1SisCommandEcho_rd L1SisCommandTable_rd \
L1SisDacOffset0_rd L1SisDacOffset1_rd L1SisDiagnosticEvent_rd \
L1SisEventCycle_rd L1SisHighPriorityRate_rd L1SisHskp_rd \
L1SisLowPriorityRate_rd L1SisSubset_rd L1SisSummary_rd

L1SisCommandEcho_rd: L1SisCommandEcho_rd.o ${SUBS}/hdf_L1SisCommandEcho.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@
L1SisCommandTable_rd: L1SisCommandTable_rd.o ${SUBS}/hdf_L1SisCommandTable.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@
L1SisDacOffset0_rd: L1SisDacOffset0_rd.o ${SUBS}/hdf_L1SisDacOffset0.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@
L1SisDacOffset1_rd: L1SisDacOffset1_rd.o ${SUBS}/hdf_L1SisDacOffset1.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@
L1SisDiagnosticEvent_rd: L1SisDiagnosticEvent_rd.o ${SUBS}/hdf_L1SisDiagnosticEvent.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@
L1SisEventCycle_rd: L1SisEventCycle_rd.o ${SUBS}/hdf_L1SisEventCycle.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@
L1SisHighPriorityRate_rd: L1SisHighPriorityRate_rd.o ${SUBS}/hdf_L1SisHighPriorityRate.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@
L1SisHskp_rd: L1SisHskp_rd.o ${SUBS}/hdf_L1SisHskp.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@
L1SisLowPriorityRate_rd: L1SisLowPriorityRate_rd.o ${SUBS}/hdf_L1SisLowPriorityRate.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@
L1SisSubset_rd: L1SisSubset_rd.o ${SUBS}/hdf_L1SisSubset.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@
L1SisSummary_rd: L1SisSummary_rd.o ${SUBS}/hdf_L1SisSummary.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@

L1SisCommandEcho_rd.o: L1SisCommandEcho_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
L1SisCommandTable_rd.o: L1SisCommandTable_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
L1SisDacOffset0_rd.o: L1SisDacOffset0_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
L1SisDacOffset1_rd.o: L1SisDacOffset1_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
L1SisDiagnosticEvent_rd.o: L1SisDiagnosticEvent_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
L1SisEventCycle_rd.o: L1SisEventCycle_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
L1SisHighPriorityRate_rd.o: L1SisHighPriorityRate_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
L1SisHskp_rd.o: L1SisHskp_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
L1SisLowPriorityRate_rd.o: L1SisLowPriorityRate_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
L1SisSubset_rd.o: L1SisSubset_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
L1SisSummary_rd.o: L1SisSummary_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

${SUBS}/hdf_L1SisCommandEcho_rd.o: ${SUBS}/hdf_L1SisCommandEcho.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
${SUBS}/hdf_L1SisCommandTable_rd.o: ${SUBS}/hdf_L1SisCommandTable.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
${SUBS}/hdf_L1SisDacOffset0_rd.o: ${SUBS}/hdf_L1SisDacOffset0.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
${SUBS}/hdf_L1SisDacOffset1_rd.o: ${SUBS}/hdf_L1SisDacOffset1.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
${SUBS}/hdf_L1SisDiagnosticEvent_rd.o: ${SUBS}/hdf_L1SisDiagnosticEvent.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
${SUBS}/hdf_L1SisEventCycle_rd.o: ${SUBS}/hdf_L1SisEventCycle.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
${SUBS}/hdf_L1SisHighPriorityRate_rd.o: ${SUBS}/hdf_L1SisHighPriorityRate.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
${SUBS}/hdf_L1SisHskp_rd.o: ${SUBS}/hdf_L1SisHskp.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
${SUBS}/hdf_L1SisLowPriorityRate_rd.o: ${SUBS}/hdf_L1SisLowPriorityRate.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
${SUBS}/hdf_L1SisSubset_rd.o: ${SUBS}/hdf_L1SisSubset.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
${SUBS}/hdf_L1SisSummary_rd.o: ${SUBS}/hdf_L1SisSummary.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
