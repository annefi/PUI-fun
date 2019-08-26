/* ---------------------------------------------------------------------------
   afunctions.h --- matrix functions
   1998 by Hefti, University of Michigan (hefti@umich.edu)
   $Id: afunctions.h,v 1.1.1.1 2000/06/02 13:37:22 jraines Exp $
   -------------------------------------------------------------------------*/

#ifndef AFUNCTIONSH
#define AFUNCTIONSH

double asum      (double *x, int istart, int ilen);
void   aind      (double *x, int istart, int ilen);

double aget      (double *x, int idx);
void   aset      (double *x, int idx, double dval);
void   aeset     (double *x, int istart, int ilen, double dval);

void   aadd      (double *x, double *y, int istart, int ilen);
void   aemul     (double *x, double *y, int istart, int ilen);
void   asmul     (double *x, int istart, int ilen, double a);

void   aprint    (double *x, int istart, int ilen, char *ztit);
double achi2     (double *x, double *y, double *w, int istart, int ilen);

#endif
