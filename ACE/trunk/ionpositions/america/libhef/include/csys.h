/* ---------------------------------------------------------------------------
   csys.h --- core system
   1998 by Hefti, University of Michigan (hefti@umich.edu)
   $Id: csys.h,v 1.1.1.1 2000/06/02 13:37:22 jraines Exp $
   -------------------------------------------------------------------------*/

#ifndef CSYSH
#define CSYSH

int    I(int ir, int Nc, int ic);
int    I3(int ir, int Nc, int ic, int ip, int Nr);
int    crng(int i, int il, int ih, char *rnam);
void   dvec_free (double *v);
double *dvec_get (long n);
int    *ivec_get (long n);
void   ivec_free (int *v);
long   *lvec_get (long n);
void   lvec_free (long *v);

char   *libhefrev(void);

#endif
