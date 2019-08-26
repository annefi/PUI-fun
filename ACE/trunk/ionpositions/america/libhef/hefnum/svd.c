/* $Id: svd.c,v 1.1.1.1 2000/06/02 13:37:22 jraines Exp $ */
#include <math.h>
#include <stdio.h>

#include "libhef.h"

void svdd(double *a, int Nr, int Nc, double *w, double *v)
{
  int    flag;
  int    i;
  int    its;
  int    j;
  int    jj;
  int    k;
  int    l;
  int    nm;
  double anorm;
  double c;
  double f;
  double g;
  double h;
  double s;
  double scale;
  double x;
  double y;
  double z;
  double *rv1;

  rv1   = dvec_get(Nc);
  g     = 0.0;
  scale = 0.0;
  anorm = 0.0;

  for (i = 0; i < Nc;i++) {

    l      = i + 1;
    rv1[i] = scale * g;

    g     = 0.0;
    scale = 0.0;
    s     = 0.0;

    if (i < Nr) {
      for (k = i;k < Nr;k++) scale += fabs(a[I(k,Nc,i)]);

      if (scale) {
	for (k = i;k < Nr;k++) {
	  a[I(k,Nc,i)] /= scale;
	  s += dsqr(a[I(k,Nc,i)]);
	}
	f = a[I(i,Nc,i)];
	g = -dsign(sqrt(s),f);
	h = f * g - s;
	a[I(i,Nc,i)] = f - g;

	for (j = l;j < Nc;j++) {
	  s = 0.0;
	  for (k = i; k < Nr;k++) s += a[I(k,Nc,i)] * a[I(k,Nc,j)];
	  f = s / h;
	  for (k = i;k < Nr; k++) a[I(k,Nc,j)] += f * a[I(k,Nc,i)];
	}

	for (k = i;k < Nr;k++) a[I(k,Nc,i)] *= scale;
      }
    }
    w[i] = scale * g;

    g     = 0.0;
    scale = 0.0;
    s     = 0.0;

    if ((i < Nr) && (i != Nc)) {

      for(k=l;k < Nc;k++) scale += fabs(a[I(i,Nc,k)]);
      if (scale) {
	for (k = l;k < Nc;k++) {
	  a[I(i,Nc,k)] /= scale;
	  s += dsqr(a[I(i,Nc,k)]);
	}
	f = a[I(i,Nc,l)];
	g = -dsign(sqrt(s),f);
	h = f * g - s;
	a[I(i,Nc,l)] = f - g;
	for (k = l;k < Nc;k++) rv1[k] = a[I(i,Nc,k)] / h;
	for (j = l;j < Nr;j++) {
	  s = 0.0;
	  for (k = l;k < Nc;k++) s += a[I(j,Nc,k)]*a[I(i,Nc,k)];
	  for (k = l;k < Nc;k++) a[I(j,Nc,k)] += s * rv1[k];
	}
	for (k = l;k < Nc;k++) a[I(i,Nc,k)] *= scale;
      }
    }
    anorm = dmax(anorm,(fabs(w[i]) + fabs(rv1[i])));
  }
  for (i = (Nc-1);i >= 0;i--) {
    if (i < Nc) {
      if (g) {
	for (j = l;j < Nc;j++)
	  v[I(j,Nc,i)] = (a[I(i,Nc,j)] / a[I(i,Nc,l)]) / g;
	for (j = l;j < Nc;j++) {
	  s = 0.0;
	  for (k = l;k < Nc;k++) s += a[I(i,Nc,k)] * v[I(k,Nc,j)];
	  for (k = l;k < Nc;k++) v[I(k,Nc,j)] += s * v[I(k,Nc,i)];
	}
      }
      for (j = l;j < Nc;j++) {
	v[I(i,Nc,j)] = 0.0;
	v[I(j,Nc,i)] = 0.0;
      }
    }
    v[I(i,Nc,i)] = 1.0;
    g            = rv1[i];
    l            = i;
  }
  for (i = (imin(Nr,Nc)-1);i >= 0;i--) {
    l = i+1;
    g = w[i];
    for (j = l;j < Nc;j++) a[I(i,Nc,j)] = 0.0;
    if (g) {
      g = 1.0 / g;
      for (j = l;j < Nc;j++) {
	s = 0.0;
	for (k = l;k < Nr;k++) s +=  a[I(k,Nc,i)] * a[I(k,Nc,j)];
	f = (s / a[I(i,Nc,i)]) * g;
	for (k = i;k < Nr;k++) a[I(k,Nc,j)] += f * a[I(k,Nc,i)];
      }
      for (j = i;j < Nc;j++) a[I(j,Nc,i)] *= g;
    } else for (j = i;j < Nr;j++) a[I(j,Nc,i)] = 0.0;
    ++a[I(i,Nc,i)];
  }
  for (k = (Nc-1);k >= 0;k--) {
    for (its = 0;its < 30;its++) {
      flag = 1;
      for (l = (k-1);l >= 0;l--) {
	nm = l - 1;
	if ((fabs(rv1[l]) + anorm)  == anorm) {
	  flag = 0;
	  break;
	}
	if ((fabs(w[nm]) + anorm)  == anorm) break;
      }
      if (flag) {
	c = 0.0;
	s = 1.0;
	for (i = l;i < k;i++) {
	  f = s * rv1[i];
	  rv1[i] = c * rv1[i];
	  if ((fabs(f) + anorm)  == anorm) break;
	  g = w[i];
	  h = pythag(f,g);
	  w[i] = h;
	  h    = 1.0 / h;
	  c    = g * h;
	  s    = -f * h;
	  for (j = 0;j < Nr;j++) {
	    y = a[I(j,Nc,nm)];
	    z = a[I(j,Nc,i)];
	    a[I(j,Nc,nm)] = y * c + z * s;
	    a[I(j,Nc,i)]  = z * c - y * s;
	  }
	}
      }
      z = w[k];
      if (l  == k) {
	if (z < 0.0) {
	  w[k]  =  -z;
	  for (j = 1;j < Nc;j++) v[I(j,Nc,k)] = -v[I(j,Nc,k)];
	}
	break;
      }
      if (its  == 30) {
	printf("svdd --- no convergence in 30 svdcmp iterations\n");
	return;
      }
      x  = w[l];
      nm = k - 1;
      y  = w[nm];
      g  = rv1[nm];
      h  = rv1[k];
      f  = ((y-z) * (y+z) + (g-h) * (g+h)) / (2.0 * h * y);
      g  = pythag(f,1.0);
      f  = ((x-z) * (x+z) + h * ((y / (f + dsign(g,f))) - h)) / x;
      c  = 1.0;
      s  = 1.0;
      for (j = l;j < Nc;j++) {
	i = j + 1;
	g = rv1[i];
	y = w[i];
	h = s * g;
	g = c * g;
	z = pythag(f,h);
	rv1[j] = z;
	c      = f / z;
	s      = h / z;
	f      = x * c + g * s;
	g      = g * c - x * s;
	h      = y * s;
	y     *= c;
	for (jj = 0;jj < Nc;jj++) {
	  x = v[I(jj,Nc,j)];
	  z = v[I(jj,Nc,i)];
	  v[I(jj,Nc,j)] = x * c + z * s;
	  v[I(jj,Nc,i)] = z * c - x * s;
	}
	z = pythag(f,h);
	w[j] = z;
	if (z) {
	  z = 1.0 / z;
	  c = f * z;
	  s = h * z;
	}
	f = c * g + s * y;
	x = c * y - s * g;
	for (jj = 0;jj < Nr;jj++) {
	  y = a[I(jj,Nc,j)];
	  z = a[I(jj,Nc,i)];
	  a[I(jj,Nc,j)] = y * c + z * s;
	  a[I(jj,Nc,i)] = z * c - y * s;
	}
      }
      rv1[l] = 0.0;
      rv1[k] = f;
      w[k]   = x;
    }
  }
  dvec_free(rv1);
}

void svdb(double *u, double *w, double *v, int Nr, int Nc, double *b, 
	  double *x)
{
  int    jj;
  int    j;
  int    i;
  double s;
  double *tmp;

  tmp = dvec_get(Nc);

  for (j = 0;j < Nc;j++) {

    s = 0.0;

    if (w[j]) {
      for (i = 0;i < Nr;i++) s += u[I(i,Nc,j)] * b[i];
      s /= w[j];
    }
    tmp[j] = s;
  }
  for (j = 0;j < Nc;j++) {
    s = 0.0;
    for (jj = 0;jj < Nc;jj++) s +=  v[I(j,Nc,jj)] * tmp[jj];
    x[j] = s;
  }
  dvec_free(tmp);
}

double pythag(double a, double b)
{
  double absa;
  double absb;

  absa = fabs(a);
  absb = fabs(b);

  if (absa > absb) return absa * sqrt(1.0 + dsqr(absb/absa));
  else             return (absb == 0.0 ? 0.0 : absb * 
			   sqrt(1.0 + dsqr(absa/absb)));
}
