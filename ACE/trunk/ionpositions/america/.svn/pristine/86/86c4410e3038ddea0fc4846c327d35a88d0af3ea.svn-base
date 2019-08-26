export LIBHEF = /home/jraines/ace/libhef

export CC = gcc
export CFLAGS = -Wall -ansi
LDFLAGS = 
LOADLIBES = -lc # -lstdc++ -lc

cacctest: cfunc.o cacctest.o

cmain: cfunc.o cmain.o
adtest: AnalysisData.o adtest.o 
#	gcc -o $@ $(LDFLAGS)  $^ $(LOADLIBES)

adtestman: AnalysisData.o adtest.o cfunc.o
	ld -L$(LIBHEF) -L/usr/lib -o adtest AnalysisData.o adtest.o  \
	/usr/lib/libstdc++.so.2.9 \
	-lhef -lstdc++ -lc 
clean: 
	rm *.o
	rm cacctest
