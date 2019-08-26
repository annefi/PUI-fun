#ifndef ERROR_ANALYSE_DATA_H
#define ERROR_ANALYSE_DATA_H

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
typedef vector<int> vint;
typedef vector<double> vdouble;
typedef vector<ion> vion;
typedef Matrix<int> mint;
typedef Matrix<double> mdouble;
#include "read_data.h"
#include "read_header.h"
#include "filter_data.h"
#include "twodgauss4sig.h"
#include "normfit.h"
#include "fitting.h"
#include "boxrates.h"
#include "sort.h"
#include "datagen.h"


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
