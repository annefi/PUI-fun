#ifndef TESTDATAGEN_H
#define TESTDATAGEN_H

#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include <math.h>
#include <assert.h>
#include "../libetph/src/dbgvector.hh"
#include "../libetph/src/matrix.hh"
#include "../libetph/src/dbgmatrix.hh"
#include "ion.h"
const int xdim = 512;
const int ydim = 128;
const int dim = 1000;
extern long idum;
typedef vector<int> vint;
typedef vector<double> vdouble;
typedef vector<ion> vion;
typedef Matrix<int> mint;
typedef Matrix<double> mdouble;
#include "twodgauss4sig.h"
#include "../libetph/src/ran_urand.h"
extern int numberions;
extern vdouble normgauss;



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
