CC = gcc
CFLAGS=

HDFHOME=/home/mussel9/asc/HDF
LIBDIR = ${HDFHOME}/lib
HDFLIBS = -lmfhdf -ldf -ljpeg -lz
LIBS = -lnsl
INC =${HDFHOME}/include
INC2 = ../include
SUB = ../hdfsubs

TARGETS = sbasic_rd sdiag_rd sdiag_rd2 smatrix_rd smonitor_rd spha_rd ssector_rd \
          sstatus_rd s3schk_rd dhk_rd shk1_rd shk2_rd shk3_rd shk4_rd shk5_rd \
          s3_dspare_class_rd s3_dspare_cmd_rd s3_dspare_contr_rd \
	  s3_dspare_alarm_rd s3_dspare_alarmcnt_rd

all: ${TARGETS}

sbasic_rd: sbasic_rd.o ${SUB}/hdf_sepica_sbasic.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

sbasic_rd.o: sbasic_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

sdiag_rd: sdiag_rd.o ${SUB}/hdf_sepica_sdiag.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

sdiag_rd.o: sdiag_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

sdiag_rd2: sdiag_rd2.o ${SUB}/hdf_sepica_sdiag.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

sdiag_rd2.o: sdiag_rd2.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

s3_dspare_class_rd: s3_dspare_class_rd.o ${SUB}/hdf_s3dspare_class.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@
s3_dspare_class_rd.o: s3_dspare_class_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

s3_dspare_cmd_rd: s3_dspare_cmd_rd.o ${SUB}/hdf_s3dspare_cmd.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} ${HDFLIBS} ${LIBS}  -o $@
s3_dspare_cmd_rd.o: s3_dspare_cmd_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

s3_dspare_contr_rd: s3_dspare_contr_rd.o ${SUB}/hdf_s3dspare_contr.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} ${HDFLIBS} ${LIBS}  -o $@
s3_dspare_contr_rd.o: s3_dspare_contr_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

s3_dspare_alarm_rd: s3_dspare_alarm_rd.o ${SUB}/hdf_s3dspare_alarm.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} ${HDFLIBS} ${LIBS}  -o $@
s3_dspare_alarm_rd.o: s3_dspare_alarm_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

s3_dspare_alarmcnt_rd: s3_dspare_alarmcnt_rd.o ${SUB}/hdf_s3dspare_alarmcnt.o
	$(CC) ${CFLAGS} $^ -I${INC} -I${INC2} -L${LIBDIR} ${HDFLIBS} ${LIBS}  -o $@
s3_dspare_alarmcnt_rd.o: s3_dspare_alarmcnt_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

shk1_rd: shk1_rd.o ${SUB}/hdf_sepica_shk1.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}
shk2_rd: shk2_rd.o ${SUB}/hdf_sepica_shk2.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}
shk3_rd: shk3_rd.o ${SUB}/hdf_sepica_shk3.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}
shk4_rd: shk4_rd.o ${SUB}/hdf_sepica_shk4.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}
shk5_rd: shk5_rd.o ${SUB}/hdf_sepica_shk5.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

shk1_rd.o: shk1_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
shk2_rd.o: shk2_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
shk3_rd.o: shk3_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
shk4_rd.o: shk4_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
shk5_rd.o: shk5_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

smatrix_rd: smatrix_rd.o ${SUB}/hdf_sepica_smatrix.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

smatrix_rd.o: smatrix_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

smonitor_rd: smonitor_rd.o ${SUB}/hdf_sepica_smonitor.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

smonitor_rd.o: smonitor_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

spha_rd: spha_rd.o ${SUB}/hdf_sepica_spha.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

spha_rd.o: spha_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

ssector_rd: ssector_rd.o ${SUB}/hdf_sepica_ssector.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

ssector_rd.o: ssector_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

sstatus_rd: sstatus_rd.o ${SUB}/hdf_sepica_sstatus.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

sstatus_rd.o: sstatus_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

s3schk_rd: s3schk_rd.o ${SUB}/hdf_s3schk.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

s3schk_rd.o: s3schk_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

dhk_rd: dhk_rd.o ${SUB}/hdf_s3dpu_dhk.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

dhk_rd.o: dhk_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

${SUB}/hdf_s3dspare_class_rd.o: ${SUB}/hdf_s3dspare_class.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
${SUB}/hdf_s3dspare_cmd_rd.o: ${SUB}/hdf_s3dspare_cmd.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
${SUB}/hdf_s3dspare_contr_rd.o: ${SUB}/hdf_s3dspare_contr.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
${SUB}/hdf_s3dspare_alarm_rd.o: ${SUB}/hdf_s3dspare_alarm.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
${SUB}/hdf_s3dspare_alarmcnt_rd.o: ${SUB}/hdf_s3dspare_alarmcnt.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
${SUB}/hdf_sepica_sbasic.o: ${SUB}/hdf_sepica_sbasic.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_sepica_sdiag.o: ${SUB}/hdf_sepica_sdiag.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}

${SUB}/hdf_sepica_shk1.o: ${SUB}/hdf_sepica_shk1.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_sepica_shk2.o: ${SUB}/hdf_sepica_shk2.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_sepica_shk3.o: ${SUB}/hdf_sepica_shk3.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_sepica_shk4.o: ${SUB}/hdf_sepica_shk4.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_sepica_shk5.o: ${SUB}/hdf_sepica_shk5.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}

${SUB}/hdf_sepica_smatrix.o: ${SUB}/hdf_sepica_smatrix.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_sepica_smonitor.o: ${SUB}/hdf_sepica_smonitor.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_sepica_spha.o: ${SUB}/hdf_sepica_spha.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_sepica_ssector.o: ${SUB}/hdf_sepica_ssector.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_sepica_sstatus.o: ${SUB}/hdf_sepica_sstatus.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_s3schk.o: ${SUB}/hdf_s3schk.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_s3dpu_dhk.o: ${SUB}/hdf_s3dpu_dhk.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}

clean:
	rm -f ${TARGETS} *.o \#* *\~






