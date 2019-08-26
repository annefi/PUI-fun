CC = gcc
CFLAGS=

HDFHOME=/home/mussel9/asc/HDF
LIBDIR = ${HDFHOME}/lib
HDFLIBS = -lmfhdf -ldf -ljpeg -lz -lnsl
INC =${HDFHOME}/include
INC2 = ../include
SUB = ../hdfsubs

all:  dump_rd evnt_rd hskp_rd rate_rd stat_tlm_rd statblk_trl_rd hskp_br_rd

dump_rd: dump_rd.o ${SUB}/hdf_uleis_dump.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

dump_rd.o: dump_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

evnt_rd: evnt_rd.o ${SUB}/hdf_uleis_evnt.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

evnt_rd.o: evnt_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

hskp_rd: hskp_rd.o ${SUB}/hdf_uleis_hskp.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

hskp_rd.o: hskp_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

hskp_br_rd: hskp_br_rd.o ${SUB}/hdf_uleis_hskp.o ${SUB}/hdf_uleis_br_out.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

hskp_br_rd.o: hskp_br_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

rate_rd: rate_rd.o ${SUB}/hdf_uleis_rate.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

rate_rd.o: rate_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

stat_tlm_rd: stat_tlm_rd.o ${SUB}/hdf_uleis_stat_tlm.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

stat_tlm_rd.o: stat_tlm_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

statblk_trl_rd: statblk_trl_rd.o ${SUB}/hdf_uleis_statblk_trl.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

statblk_trl_rd.o: statblk_trl_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

${SUB}/hdf_uleis_dump.o: ${SUB}/hdf_uleis_dump.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_uleis_evnt.o: ${SUB}/hdf_uleis_evnt.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_uleis_hskp.o: ${SUB}/hdf_uleis_hskp.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_uleis_br_out.o: ${SUB}/hdf_uleis_br_out.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_uleis_rate.o: ${SUB}/hdf_uleis_rate.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_uleis_stat_tlm.o: ${SUB}/hdf_uleis_stat_tlm.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_uleis_statblk_trl.o: ${SUB}/hdf_uleis_statblk_trl.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
