#ifndef DATAGEN_H
#define DATAGEN_H

#include <vector>
#include "../libetph/src/dbgvector.hh"
#include "../libetph/src/dbgmatrix.hh"
#include "../libetph/src/matrix.hh"
typedef std::vector<int> vint;
typedef std::vector<double> vdouble;
typedef Matrix<int> mint;
typedef Matrix<double> mdouble;
#include "twodgauss4sig.h"
#include "../libetph/src/ran_urand.h"
const int xdim = 512;
const int ydim = 128;
const int dim = 1000;

mdouble datagen (vdouble &param);

#endif




/*
 * Overrides for Emacs so that we follow a common tabbing style.
 * Emacs will notice this stuff at the end of the file and automatically
 * adjust the settings for this buffer only.  This must remain at the end
 * of the file.
 * ---------------------------------------------------------------------------
 * Local variables:
 * c-file-style: "gnu"
 * End:
 */
