#ifndef ION_POS_H
#define ION_POS_H

#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include <math.h>
#include <assert.h>
#include "dbgvector.h"
#include "matrix.h"
#include "dbgmatrix.h"
#include "ion.h"
typedef dbgvector<int> vint;
typedef dbgvector<double> vdouble;
typedef dbgvector<ion> vion;
typedef Dbgmatrix<int> mint;
typedef Dbgmatrix<double> mdouble;
#include "twodgauss4sig.h"
#include "twodgaussschief.h"
#include "twodgauss.h"

#include "fitting.h"

const double PI = 3.141592653;




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
