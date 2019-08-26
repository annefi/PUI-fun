#ifndef NORMFIT_H
#define NORMFIT_H

#include "ion_pos.h"
#include "../libetph/src/dbgmatrix.hh"

vdouble normfit(vdouble &param,mdouble &et_mat,double (*funcs)(int, int , vdouble &, vdouble &, int, int,vint &, double));

#endif
