// File: hefnum.i
// $Id: hefnum.i,v 1.1.1.1 2000/06/02 13:37:24 jraines Exp $

// get entry of array: res = x[index]
extern double aget(double *x, int index);

// set value: x[idx] = dval
extern void aset(double *x, int idx, double dval);

// set values: x[i] = dval, istart <= i < istart+ilem
extern void aeset(double *x, int istart, int ilen, double dval);

// sum array: res = sum(x[i]), istart <= i < (istart + ilen)
extern double asum             (double *x, int istart, int ilen);

// add two arrays: x[i] = x[i] + y[i]
extern void aadd(double *x, double *y, int istart, int ilen);

// first moment. x is dist function, y is data.
extern double dmom1(double *adx,double *ady, int Nx);

// Nth moment. x is dist function, y is data.
extern double dmomN(double *adx,double *ady, int Nx, double dN);
