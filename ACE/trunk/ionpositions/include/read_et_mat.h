#ifndef READ_ET_MAT_H
#define READ_ET_MAT_H

#include "analyse_data.h"

/*
  Reads matrix "et_mat"
  filenamedata : name of data file (format as produced by axlv2 software is needed)
  loadstep : defines E/q-step to be loaded (loadstep=0 means E/q-step 2 of SWICS; Since data of E/q-step 1 and 60 are useless)   
  et_mat : after a call of read_et_mat et_mat contains the loaded data (xdim=1024,ydim=256) 
*/

bool read_et_mat(ifstream &datastream,int loadstep,mdouble &et_mat);

#endif
