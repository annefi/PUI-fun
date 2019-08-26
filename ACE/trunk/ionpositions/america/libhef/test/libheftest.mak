CC      = gcc
CFLAGS  = -g -Wall -Wshadow -I../include

tminv:  tminv.o
	$(CC) -o tminv $(CFLAGS) tminv.c libhef.a -lm
	./tminv

tlmfit: tlmfit.o
	$(CC) -o tlmfit $(CFLAGS) tlmfit.c libhef.a -lm
	./tlmfit

ta3dif: ta3dif.o
	$(CC) -o ta3dif $(CFLAGS) ta3dif.c libhef.a -lnetcdf -lm
