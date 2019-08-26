#ifndef FILTER_DATA_H
#define FILTER_DATA_H

#include "analyse_data.h"

/*
Filter data. Some ranges containing dirt are set to 0.
step      : E/q-step to be filtered
et_mat    : matrix containing data ([512,128])
*/

bool filter_data(int &step,mdouble &et_mat);

#endif
