#ifndef READ_DATA_H
#define READ_DATA_H

#include "analyse_data.h"
#include "databinning.h"
#include "read_et_mat.h"

/*
Reads "et_mat" out of "filename"
filename  : Name of file containing data
step      : E/q-step to be read
et_mat    : matrix containing data ([512,128])
dobin     : switch to turn binning on and off; 1 binning is on 0 binning is off (the switch also determines which kind of datafile is needed - with binning datafile from axlv2 software, without binning datafile from databinning.py

*/

bool read_data(ifstream &datastream,int step,mdouble &et_mat,int dobin);

#endif
