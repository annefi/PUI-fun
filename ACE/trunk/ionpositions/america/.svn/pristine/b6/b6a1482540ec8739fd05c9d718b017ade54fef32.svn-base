/* ---------------------------------------------------------------------------
   arnaud_test --- test C interface arnaud_wrapper
   $Id: arnaud_test.c,v 1.1.1.1 2000/06/02 13:37:26 jraines Exp $
   1998 by Hefti, University of Michigan (hefti@umich.edu)
   ------------------------------------------------------------------------ */

#include <stdio.h>
#include <hefutil.h>


int main(void)
{
  int    i;
  long   lZ = 26;
  double dT = 1.0e6;
  double adn[30];
  double adC[30];
  double adR[30];

  printf("Call wrapper\n");
  arnaud_wrapper(lZ,dT,adn,adC,adR);

  printf("Result for Z = %ld, T = %g\n",lZ,dT);
  printf(" i n_i C_i R_i\n");
  for(i = 0; i <= lZ; i++ ) {
    printf("%2d %.3g %.3g %.3g\n",
	   i,adn[i],adC[i],adR[i]);
  }
  return(0);
}
