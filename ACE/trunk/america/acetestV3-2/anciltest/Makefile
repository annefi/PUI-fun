CC = gcc
# Added -fPIC option for libace_ancil.so.  J. Raines, 2Oct2003.
CFLAGS=-Wall -fPIC

# You will want to change HDFHOME for your installation
#HDFHOME=/home/mussel9/asc/HDF
#HDFHOME=/shrg1/local/hdf
LOCAL = $(HOME)/ace

HDFHOME=$(LOCAL)/HDF4.2r1

LIBDIR = ${HDFHOME}/lib -L$(LOCAL)/jpeg-6b/lib -L$(LOCAL)/zlib-1.2.1
HDFLIBS = -lmfhdf -ldf -ljpeg -lz 
# nsl library required for Sun Solaris 
LIBS = -lm # -lnsl
INC =${HDFHOME}/include
INC2 = ../include
HDFSUBS = ../hdfsubs

all: aos_data_rd ccr_data_rd ccr_data_rd_oneliner get_attitude \
	get_position get_daily_position get_velocity get_aosr_struct \
	get_ACEepoch get_scclock get_position_GCI get_start_clocks

get_attitude: get_attitude.o ancil_subs.o ${HDFSUBS}/hdf_aosr.o \
        ${HDFSUBS}/hdf_ccr.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

get_attitude.o: get_attitude.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

get_position: get_position.o ancil_subs.o ${HDFSUBS}/hdf_aosr.o \
        ${HDFSUBS}/hdf_ccr.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

get_position.o: get_position.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

get_position_GCI: get_position_GCI.o ancil_subs.o ${HDFSUBS}/hdf_aosr.o \
        ${HDFSUBS}/hdf_ccr.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

get_position_GCI.o: get_position_GCI.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

get_daily_position: get_daily_position.o ancil_subs.o ${HDFSUBS}/hdf_aosr.o \
        ${HDFSUBS}/hdf_ccr.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

get_daily_position.o: get_daily_position.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

get_velocity: get_velocity.o ancil_subs.o ${HDFSUBS}/hdf_aosr.o \
        ${HDFSUBS}/hdf_ccr.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

get_velocity.o: get_velocity.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

get_aosr_struct: get_aosr_struct.o ancil_subs.o ${HDFSUBS}/hdf_aosr.o \
        ${HDFSUBS}/hdf_ccr.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

get_aosr_struct.o: get_aosr_struct.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

get_ACEepoch: get_ACEepoch.o ancil_subs.o ${HDFSUBS}/hdf_aosr.o \
        ${HDFSUBS}/hdf_ccr.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

get_ACEepoch.o: get_ACEepoch.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

get_scclock: get_scclock.o ancil_subs.o ${HDFSUBS}/hdf_aosr.o \
        ${HDFSUBS}/hdf_ccr.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

get_scclock.o: get_scclock.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

aos_data_rd: aos_data_rd.o ancil_subs.o ${HDFSUBS}/hdf_aosr.o \
        ${HDFSUBS}/hdf_ccr.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

aos_data_rd.o: aos_data_rd.c ${INC2}/aosr.h
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

ccr_data_rd: ccr_data_rd.o ancil_subs.o ${HDFSUBS}/hdf_aosr.o \
        ${HDFSUBS}/hdf_ccr.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

ccr_data_rd_oneliner: ccr_data_rd_oneliner.o ancil_subs.o ${HDFSUBS}/hdf_aosr.o \
        ${HDFSUBS}/hdf_ccr.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} ${LIBS} -o $@ -I${INC2}

ccr_data_rd.o: ccr_data_rd.c ${INC2}/ccr.h
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

ccr_data_rd_oneliner.o: ccr_data_rd_oneliner.c ${INC2}/ccr.h
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

get_start_clocks: get_start_clocks.o ancil_subs.o ${HDFSUBS}/hdf_aosr.o ${HDFSUBS}/hdf_ccr.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} \
	${HDFLIBS} -lm -lnsl -o $@ -I${INC2}
#	${HDFLIBS} -lsunmath -lm -lnsl -o $@ -I${INC2}

get_start_clocks.o: get_start_clocks.c 
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

ancil_subs.o: ancil_subs.c ${INC2}/aosr.h ${INC2}/ccr.h
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

${HDFSUBS}/hdf_aosr.c: ${INC2}/aosr.h

${HDFSUBS}/hdf_aosr.o: ${HDFSUBS}/hdf_aosr.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}

${HDFSUBS}/hdf_ccr.c: ${INC2}/ccr.h

${HDFSUBS}/hdf_ccr.o: ${HDFSUBS}/hdf_ccr.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC2} -I${INC}
clean:
	rm -f *.o aos_data_rd ccr_data_rd get_attitude get_position get_position_GCI get_daily_position get_velocity  get_aosr_struct get_ACEepoch get_scclock \#* *\~
