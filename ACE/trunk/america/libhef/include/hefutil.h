/* ---------------------------------------------------------------------------
   hefutil.h --- header file for collection of tools
   (c) 1998-1999 Simon Hefti (hefti@umich.edu)
   $Id: hefutil.h,v 1.1.1.1 2000/06/02 13:37:22 jraines Exp $
   ------------------------------------------------------------------------ */

#include <stdio.h>
#include <stdarg.h> /* perr */

#ifndef HEFUTILH
#define HEFUTILH

/*      SUBROUTINE ARNAUD_SHARE(XZ,XTE,X,XRECO,XRTOT) */
void arnaud_share__(long *XZ, double *XTE, double X[],
		  double XRECO[], double XRTOT[]);

void arnaud_wrapper(long lZ, double dT, double adn[30],
		    double adC[30], double adR[30]);

#define PEEYORE 0
#define PNOVICE 1
#define PEXPERT 2

int hperr(FILE *fp, int ilevel, char *fmt, ...);
int perr_setlevel(int ilevel);

#endif
