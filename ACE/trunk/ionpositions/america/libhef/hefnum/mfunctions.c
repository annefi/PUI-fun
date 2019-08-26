/* ---------------------------------------------------------------------------
   mfunctions --- Matrix functions
   by Hefti (hef), University of Michigan (hefti@umich.edu)
   $Id: mfunctions.c,v 1.1.1.1 2000/06/02 13:37:22 jraines Exp $
   -------------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "libhef.h"

#define SWAP(a,b) {temp=(a);(a)=(b);(b)=temp;}



/*  --------------------------------------------------------------------[<]---
    minv --- matrix inversion using Gauss' scheme (Nc x Nc matrices)
    --------------------------------------------------------------------[>]-*/
int minv(double *a, int Nc)
{
  int    *indxc,*indxr,*ipiv;
  int    i,icol,irow,j,k,l,ll;
  double big,dum,pivinv,temp;

  indxc = ivec_get(Nc);
  indxr = ivec_get(Nc);
  ipiv  = ivec_get(Nc);

  for(j = 0;j < Nc;j++) ipiv[j] = 0;

  for(i = 0;i < Nc; i++) {
    big = 0.0;
    for(j = 0;j < Nc; j++)
      if(ipiv[j] != 1)
	for(k = 0;k < Nc; k++) {
	  if( ipiv[k] == 0 ) {
	    if(fabs(a[I(j,Nc,k)]) >= big) {
	      big  = fabs(a[I(j,Nc,k)]);
	      irow = j;
	      icol = k;
	    }
	  } else if(ipiv[k] > 1) {
	    printf("minv --- Singular Matrix-1\n");
	    return(1);
	  }
	}
    ++(ipiv[icol]);
    if (irow != icol) {
      for(l = 0;l < Nc; l++) SWAP(a[I(irow,Nc,l)],a[I(icol,Nc,l)]);
    }

    indxr[i] = irow;
    indxc[i] = icol;

    if (a[I(icol,Nc,icol)] == 0.0) {
      printf("minv --- Singular Matrix-2\n");
      return(2);
    }

    pivinv = 1.0 / a[I(icol,Nc,icol)];

    a[I(icol,Nc,icol)] = 1.0;

    for (l = 0;l < Nc; l++) a[I(icol,Nc,l)] *= pivinv;

    for (ll = 0;ll < Nc; ll++)
      if (ll != icol) {
	dum = a[I(ll,Nc,icol)];
	a[I(ll,Nc,icol)] = 0.0;
	for (l = 0;l < Nc;l++) a[I(ll,Nc,l)] -= a[I(icol,Nc,l)] * dum;
      }
  }

  for (l = Nc-1; l >= 0; l--) {
    if (indxr[l] != indxc[l])
      for (k = 0;k < Nc;k++)
	SWAP(a[I(k,Nc,indxr[l])],a[I(k,Nc,indxc[l])]);
  }
  
  ivec_free(ipiv);
  ivec_free(indxr);
  ivec_free(indxc);

  return(0);
}

#undef SWAP
