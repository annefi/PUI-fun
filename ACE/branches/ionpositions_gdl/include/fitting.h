#ifndef FITTING_H
#define FITTING_H

#include "ion_pos.h"
#include "matrix.h"
#include "poidev.h"

bool maxlifit(mdouble &y, vdouble &a,vdouble &a_lo, vdouble &a_hi, vint &ia,
	      mdouble&covar, mdouble&alpha, double &merit,
	      double (*funcs)(int, int, vdouble &, vdouble &, int, int, vint &, double));
 
double logfak(double x);
 
bool get_mod_mer(vdouble&a, double &mod_merit, double (*funcs)(int, int, vdouble &, vdouble &, int, int, vint &, double));
 
bool mrqmin(mdouble &y, vdouble &a, vdouble &a_lo, vdouble &a_hi, vint &ia, mdouble &covar, mdouble &alpha, double &chisq, double (*funcs)(int, int, vdouble &, vdouble &, int, int, vint &, double), double &alamda, vdouble &atry, vdouble &beta, vdouble &da, dbgvector<vdouble> &oneda, double &ochisq);
 
int param_bounds(vdouble &a, vdouble &a_lo, vdouble &a_hi, vint &ia);
 
bool mrqcof(mdouble &y, vdouble &a, vint &ia,
	    mdouble &alpha, vdouble &beta, double &chisq,
	    double (*funcs)(int, int, vdouble &, vdouble &, int, int,vint &, double));
 
 bool covsrt(mdouble &covar, vint &ia, int mfit);
 
 void gaussj(mdouble &a, int n, dbgvector<vdouble> &b);






#endif
