#ifndef COPY_HEADER_H
#define COPY_HEADER_H

#include "analyse_data.h"

/*
Copys header of datastream into ergstream
filename  : Name of file containing data
step      : E/q-step to be read
et_mat    : matrix containing data ([512,128])
dobin     : switch to turn binning on and off; 1 binning is on 0 binning is off (the switch also determines which kind of datafile is needed - with binning datafile from axlv2 software, without binning datafile from databinning.py

*/

bool copy_header(ifstream &datastream,ofstream &ergstream);

#endif
