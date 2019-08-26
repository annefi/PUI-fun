/* ---------------------------------------------------------------------------
   arnaud_wrapper --- interface Peter Wurz' Arnaud-Rothenflug routines
   $Id: arnaud_wrapper.c,v 1.1.1.1 2000/06/02 13:37:26 jraines Exp $
   1998 by Hefti, University of Michigan (hefti@umich.edu)
   ------------------------------------------------------------------------ */

#include <stdio.h>
#include <hefutil.h>


void arnaud_wrapper(long lZ, double dT, double adn[30],
		    double adC[30], double adR[30])
{
  arnaud_share__(&lZ,&dT,adn,adC,adR);
}
