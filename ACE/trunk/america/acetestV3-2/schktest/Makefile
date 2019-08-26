CC = gcc
CFLAGS=

HDFHOME=/home/mussel9/asc/HDF
LIBDIR = ${HDFHOME}/lib
HDFLIBS = -lmfhdf -ldf -ljpeg -lz -lnsl
INC =${HDFHOME}/include
INC2 = ../include
SUB = ../hdfsubs

all: schk_rd sunpulse_rd temp_rd

schk_rd: schk_rd.o ${SUB}/hdf_schskp.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

schk_rd.o: schk_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

temp_rd: temp_rd.o ${SUB}/hdf_schskp.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

temp_rd.o: temp_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}

sunpulse_rd: sunpulse_rd.o ${SUB}/hdf_sunpulsetime.o
	$(CC) ${CFLAGS} $^ -I${INC} -L${LIBDIR} ${HDFLIBS} -o $@ -I${INC2}

sunpulse_rd.o: sunpulse_rd.c
	$(CC) ${CFLAGS} -c $< -o $@ -I${INC} -I${INC2}
		
${SUB}/hdf_schskp.o: ${SUB}/hdf_schskp.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
${SUB}/hdf_sunpulsetime.o: ${SUB}/hdf_sunpulsetime.c
	$(CC) $(CFLAGS) -c $< -o $@ -I${INC} -I${INC2}
	

	
