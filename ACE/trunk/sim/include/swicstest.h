#ifndef SWICSTEST_H
#define SWICSTEST_H

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cstdio>
#include <assert.h>

const double PI = 3.141592653;
const int xdim = 1024;
const int ydim = 256;
extern long idum;

//bool twodgauss(int ,int , vector<double> &, double *, vector<double> &, int , int );
//vector<double> normgauss;


#include "matrix.h"
#include "mynr.h"
//#include "gammln.h"
#include "ran_1.h"
#include "ran_2.h"
#include "poidev.h"
#include "getcontmat.h"
extern int numberions;
#include "fitting.h"
extern vector<double> normgauss;
#include "twodgauss.h"

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
