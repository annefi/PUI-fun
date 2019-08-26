NETCDF  = /shrg1/local/netcdf-3.4

CFLAGS    = -I../../include -I$(NETCDF)/include
LDFLAGS   = -L$(NETCDF)/lib
LOADLIBES = -lnetcdf -lm -lc

comp_codes: comp_codes.o ../../libhef.a
