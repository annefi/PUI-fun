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

#TARGETS = BrowseCris_rd L1CrisHighPriorityRate_rd L1CrisCommandEcho_rd L1CrisCommandTable_rd \
#          L1CrisDiagnosticEvent_rd L1CrisEventCycle_rd L1CrisHskp_rd L1CrisLowPriorityRate_rd \
#          L1CrisSubset_rd L1CrisSummary_rd

TARGETS = L1CrisHighPriorityRate_rd L1CrisCommandEcho_rd L1CrisCommandTable_rd \
          L1CrisDiagnosticEvent_rd L1CrisEventCycle_rd L1CrisHskp_rd L1CrisLowPriorityRate_rd \
          L1CrisSubset_rd L1CrisSummary_rd

all: ${TARGETS}

#BrowseCris_rd: BrowseCris_rd.o ${SUBS}/hdf_BrowseCris.o
#	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@

#BrowseCris_rd.o: BrowseCris_rd.c
#	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

L1CrisHighPriorityRate_rd: L1CrisHighPriorityRate_rd.o ${SUBS}/hdf_L1CrisHighPriorityRate.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@

L1CrisHighPriorityRate_rd.o: L1CrisHighPriorityRate_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

L1CrisCommandEcho_rd: L1CrisCommandEcho_rd.o ${SUBS}/hdf_L1CrisCommandEcho.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@

L1CrisCommandEcho_rd.o: L1CrisCommandEcho_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

L1CrisCommandTable_rd: L1CrisCommandTable_rd.o ${SUBS}/hdf_L1CrisCommandTable.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@

L1CrisCommandTable_rd.o: L1CrisCommandTable_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

L1CrisDiagnosticEvent_rd: L1CrisDiagnosticEvent_rd.o ${SUBS}/hdf_L1CrisDiagnosticEvent.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@

L1CrisDiagnosticEvent_rd.o: L1CrisDiagnosticEvent_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

L1CrisEventCycle_rd: L1CrisEventCycle_rd.o ${SUBS}/hdf_L1CrisEventCycle.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@

L1CrisEventCycle_rd.o: L1CrisEventCycle_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

L1CrisHskp_rd: L1CrisHskp_rd.o ${SUBS}/hdf_L1CrisHskp.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@

L1CrisHskp_rd.o: L1CrisHskp_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

L1CrisLowPriorityRate_rd: L1CrisLowPriorityRate_rd.o ${SUBS}/hdf_L1CrisLowPriorityRate.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@

L1CrisLowPriorityRate_rd.o: L1CrisLowPriorityRate_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

L1CrisSubset_rd: L1CrisSubset_rd.o ${SUBS}/hdf_L1CrisSubset.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@

L1CrisSubset_rd.o: L1CrisSubset_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

L1CrisSummary_rd: L1CrisSummary_rd.o ${SUBS}/hdf_L1CrisSummary.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} -L${LIBDIR2} ${HDFLIBS} ${MLIBS} -o $@

L1CrisSummary_rd.o: L1CrisSummary_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

#${SUBS}/hdf_BrowseCris.o: ${SUBS}/hdf_BrowseCris.c
#	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}

${SUBS}/hdf_L1CrisHighPriorityRate.o: ${SUBS}/hdf_L1CrisHighPriorityRate.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}

${SUBS}/hdf_L1CrisCommandEcho.o: ${SUBS}/hdf_L1CrisCommandEcho.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}

${SUBS}/hdf_L1CrisCommandTable.o: ${SUBS}/hdf_L1CrisCommandTable.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}

${SUBS}/hdf_L1CrisDiagnosticEvent.o: ${SUBS}/hdf_L1CrisDiagnosticEvent.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}

${SUBS}/hdf_L1CrisEventCycle.o: ${SUBS}/hdf_L1CrisEventCycle.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}

${SUBS}/hdf_L1CrisHskp.o: ${SUBS}/hdf_L1CrisHskp.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}

${SUBS}/hdf_L1CrisLowPriorityRate.o: ${SUBS}/hdf_L1CrisLowPriorityRate.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}

${SUBS}/hdf_L1CrisSubset.o: ${SUBS}/hdf_L1CrisSubset.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}

${SUBS}/hdf_L1CrisSummary.o: ${SUBS}/hdf_L1CrisSummary.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}

clean:
	rm -f ${TARGETS} *.o \#* *\~
















