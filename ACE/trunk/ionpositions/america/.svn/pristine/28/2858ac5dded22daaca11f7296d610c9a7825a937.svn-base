/* --------------------------------------------------------------- <Prolog> --
   tlmfit.c --- test Levenberg-Marquardt-Fitting
   by Hefti (hef), University of Michigan (hefti@umich.edu)
   $Id: tlmfit.c,v 1.1.1.1 2000/06/02 13:37:23 jraines Exp $
   ------------------------------------------------------------- </Prolog> -*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "libhef.h"


int main(void)
{
  double adx[5];
  double ady[5];
  double adw[5];                        /* weight */
  double adg[3];                        /* guess */
  double ads[3];                        /* sigma of guess */
  double adt[3*5];                      /* dyda */

  double dtmp;

  int    i;

  adg[0] = 100.0;
  adg[1] = 333.0;
  adg[2] =  33.0;

  printf("true parameters\n");
  for(i = 0; i < 3; i++) printf("%10.3f ",adg[i]);
  printf("\n");

  printf("test sum: %.2f\n",asum(adg,0,3));
  printf("test sum: %.2f\n",asum(adg,0,1));
  printf("test sum: %.2f\n",asum(&adg[1],0,1));

  for(i = 0; i < 5; i++) {
    adx[i] = 100.0 * (i+1);
  }
  one_gauss(adx,ady,5,adg,3,adt);

  for(i = 0; i < 5; i++) {
    ady[i] += pow(-1.0,i) * 2.0;
    adw[i] =   1.0;
    printf("DBG: tlmfit --- %5.1f %5.2f %5.2f\n",adx[i],ady[i],adw[i]);
  }

  for(i = 0; i < 3; i++) {
    adg[i] += 10.0;
  }

  printf("estimated parameters\n");
  for(i = 0; i < 3; i++) printf("%10.3f ",adg[i]);
  printf("\n");

  cfit(adx,ady,adw,5,adg,ads,3,&dtmp,0,
       one_gauss,noconstraint);

  printf("fitted parameters\n");
  for(i = 0; i < 3; i++) printf("%10.3f ",adg[i]);
  printf("\n");

  return(0);
}
