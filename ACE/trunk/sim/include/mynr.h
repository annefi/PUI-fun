//-----------------------------------------------------------------------------
/*! \file mynr.h
 * \version 1.0
 * \author Fredy Dobler (dobler@phim.unibe.ch)
 * \date Created: 26.03.1999
 * \brief declaration of the functions in mynr.cpp, page numbers from Numerical Recipes see Detailed Description

 * Description: Function copied from the book

 * Numerical Recipes in C, Second Edition

 * W. H. Press, S. A. Teukolsky, W. T. Vetterling, B. P. Flannery

 * Cambridge University Press

 * and own mathematic function
 */
//-----------------------------------------------------------------------------
#ifndef MYNR_H
#define MYNR_H


#include <vector>
#include "matrix.h"
const int ITMAX=100;
const double EPS=3.0e-7;
const double FPMIN=1.0e-30;
const double Pi=3.141592653;


///double vector
typedef vector<double> fVECTOR;
///integer vector
typedef vector<int> iVECTOR;
///stepfunction
int stepf(double x);

///matrix invertation 
void matrix_invert(Matrix<double> &matrix);

///SQR Function
double SQR(const double &a);
///Error Funktion: Page 220, (6.2.8)
double myerff(double x);
///Returns the incomplete gamma function P(a,x) Page 218
double gammp(double a, double x);
///Returns the incomplete gamma function Q(a,x) := 1 - P(a,x) Page 218
double gammq(double a, double x);
///Page 218
void gser(double &gamser, double a, double x, double &gln);
///gcf, page 219
void gcf(double &gammcf, double a, double x, double &gln);
///gammln, page 214
double gammln(double xx);
///compute c=SQRT(a^2+b^2), page 70
double pythag(double a, double b);
///svdcmp, page 67
void svdcmp(Matrix<double> &a,fVECTOR &w, Matrix<double> &v);
///ran1, p.280
float ran1(long &idum);
///gasdev, p.289
float gasdev(long &idum);
float mygasdev(long &idum,const double &m1,const double &s1);
float my2gasdev(long &idum,double &v2,const double &m1,const double &s1, const double &s2);
#endif
