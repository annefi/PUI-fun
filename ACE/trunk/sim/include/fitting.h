#ifndef FITTING_H
#define FITTING_H

#include "swicstest.h"



bool maxlifit(Matrix<double> &y, vector<double> &para, vector<double> &a,vector<double> &a_lo, vector<double> &a_hi, vector<int> &ia,
	      Matrix<double>&covar, Matrix<double>&alpha, double &merit,
	      bool (*funcs)(int, int, vector<double> &, vector<double> &, double *, vector<double> &, int, int),
	      int &newit);
 
double logfak(double x);
 
bool get_mod_mer(vector<double> &para,vector<double>&a, double &mod_merit, bool (*funcs)(int, int, vector<double> &, vector<double> &, double *, vector<double> &, int, int));
 
bool mrqmin(Matrix<double> &y, vector<double> &para, vector<double> &a, vector<double> &a_lo, vector<double> &a_hi, vector<int> &ia,
	     Matrix<double> &covar, Matrix<double> &alpha, double &chisq,
	    bool (*funcs)(int, int, vector<double> &, vector<double> &, double *, vector<double> &, int, int), double &alamda, int &newit);
 
 int param_bounds(vector<double> &a, vector<double> &a_lo, vector<double> &a_hi, vector<int> &ia);
 
bool mrqcof(Matrix<double> &y, vector<double> &para, vector<double> &a, vector<int> &ia,
	    Matrix<double> &alpha, vector<double> &beta, double &chisq,
	     bool (*funcs)(int, int, vector<double> &, vector<double> &, double *, vector<double> &, int, int));
 
 bool covsrt(Matrix<double> &covar, vector<int> &ia, int mfit);
 
 bool gaussj(Matrix<double> &a, int n, vector<vector<double> > &b);






#endif
