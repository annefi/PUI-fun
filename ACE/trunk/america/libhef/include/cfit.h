/* ---------------------------------------------------------------------------
   cfit.h --- curve fitting
   1998 by Hefti, University of Michigan (hefti@umich.edu)
   $Id: cfit.h,v 1.1.1.1 2000/06/02 13:37:22 jraines Exp $
   -------------------------------------------------------------------------*/

#ifndef CFITH
#define CFITH

void cfit        (double x[], double y[], double w[], int Nx,
		  double g[], double sg[], int Ng, double *chi2, int ireport,
		  void (*funcs)(double *x, double *y, int Nx, double *a, 
				int Na, double *dyda),
		  void cnstr(double *x, double *y, double *w, double *f, 
			     int Nx, double *g, int Ng));
void noconstraint(double *x, double *y, double *w, double *f, int Nx, 
		  double *g, int Ng);

#endif
