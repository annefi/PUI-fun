/* ---------------------------------------------------------------------------
   tminv --- test matrix inversion
   by Hefti (hef), University of Michigan (hefti@umich.edu)
   $Id: tminv.c,v 1.1.1.1 2000/06/02 13:37:23 jraines Exp $
   -------------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "libhef.h"


int main(void)
{
  double ad1[2*2];                      /* matrix inversion */

  ad1[I(0,2,0)] = 1.0;
  ad1[I(0,2,1)] = 2.0;
  ad1[I(1,2,0)] = 2.0;
  ad1[I(1,2,1)] = 1.0;

  printf("matrixinversion --- test matrix inversion\n");
  printf("%7.2f %7.2f\n",ad1[I(0,2,0)],ad1[I(0,2,1)]);
  printf("%7.2f %7.2f\n",ad1[I(1,2,0)],ad1[I(1,2,1)]);

  printf("matrixinversoin --- call minv\n");

  minv(ad1,2);
  
  printf("%7.2f %7.2f\n",ad1[I(0,2,0)],ad1[I(0,2,1)]);
  printf("%7.2f %7.2f\n",ad1[I(1,2,0)],ad1[I(1,2,1)]);

  return(0);
}
