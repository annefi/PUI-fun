#ifndef DATABINNING_H
#define DATABINNING_H

#include "analyse_data.h"

/*
  Binns data from "et_mat" to "et_mat_binned" ; currently et_mat[1024;256] et_mat_binned[512;128].

*/

bool databinning(mdouble &et_mat, mdouble &et_mat_binned);

#endif
