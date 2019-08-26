#! /bin/bash
# local config for building netcdf 3.5.1
# Jim Raines, 26Jul2004

# keep fortran interface from building
export FC=" "
export F90=""

# make installer put in correct tree
./configure --prefix=/shrg1/local

make

make test

# that seemed to do it!

