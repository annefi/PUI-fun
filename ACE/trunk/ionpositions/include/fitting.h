#ifndef FITTING_H
#define FITTING_H

#include "ion_pos.h"
#include "../libetph/src/dbgmatrix.hh"

bool maxlifit(mdouble &y, vdouble &a,vdouble &a_lo, vdouble &a_hi, vint &ia,
	      mdouble&covar, mdouble&alpha, double &merit,
	      double (*funcs)(int, int, vdouble &, vdouble &, int, int, vint &, double));
 
double logfak(double x);
 
bool get_mod_mer(vdouble&a, double &mod_merit, double (*funcs)(int, int, vdouble &, vdouble &, int, int, vint &, double));
 
bool mrqmin(mdouble &y, vdouble &a, vdouble &a_lo, vdouble &a_hi, vint &ia, mdouble &covar, mdouble &alpha, double &chisq, double (*funcs)(int, int, vdouble &, vdouble &, int, int, vint &, double), double &alamda, vdouble &atry, vdouble &beta, vdouble &da, vector<vdouble> &oneda, double &ochisq);
 
int param_bounds(vdouble &a, vdouble &a_lo, vdouble &a_hi, vint &ia, vint &parahange);
 
bool mrqcof(mdouble &y, vdouble &a, vint &ia,
	    mdouble &alpha, vdouble &beta, double &chisq,
	    double (*funcs)(int, int, vdouble &, vdouble &, int, int,vint &, double));
 
bool covsrt(mdouble &covar, vint &ia, int mfit);

void gaussj(mdouble &a, int n, vector<vdouble> &b);

double calcchisq(mdouble &y,vdouble &param,int ion,double (*funcs)(int, int , vdouble &, vdouble &, int, int,vint &, double));

double calcerror(mdouble &y,vdouble &param,int ion,double (*funcs)(int, int , vdouble &, vdouble &, int, int,vint &, double));

vdouble calcerrors(mdouble &y,vdouble &param,double (*funcs)(int, int , vdouble &, vdouble &, int, int,vint &, double));

bool scanion(mdouble &y,vdouble &param,int ion);

#endif
