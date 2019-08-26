/* ---------------------------------------------------------------------------
   csys --- core sytem for my lib (memory allocation etc)
   by Hefti (hef), University of Michigan (hefti@umich.edu)
   $Id: csys.c,v 1.1.1.1 2000/06/02 13:37:22 jraines Exp $
   -------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include "libhef.h"


/*  --------------------------------------------------------------------------
    I --- index function (2 D) (row,col)
    ------------------------------------------------------------------------*/
int I(int ir, int Nc, int ic)
{
  return(ir * Nc + ic);
}

/*  --------------------------------------------------------------------------
    I3 --- index function for arrays with 3 dim (row,col,plane)
    ------------------------------------------------------------------------*/
int I3(int ir, int Nc, int ic, int ip, int Nr)
{
  /*
  int   itmp;
  itmp = ip * (Nr * Nc) + I(ir,Nc,ic);
  printf("I3 --- %5d\n",itmp);
  if( (itmp < 0) || (itmp > 10247 ) ) {
    printf("I3 --- check boundary: %3d %3d %3d %3d %3d %5d\n",
	   ir,Nc,ic,ip,Nr,itmp);
  }
  */
  return(ip * (Nr * Nc) + I(ir,Nc,ic));
  /* return(0); */
}

/* ---------------------------------------------------------------------------
   crng --- check range: if not (il <= i <= ih) print warning for rnam
   -------------------------------------------------------------------------*/
int crng(int i, int il, int ih, char *rnam)
{
  int ires;

  ires = 0; /* no problem */
  if( (i < il) || (i > ih) ) {
    hperr(stderr,PNOVICE,"crng for %s --- %d is out-of-range.\n",rnam,i);
    ires = 1;
  }

  return(ires);
}


/*  --------------------------------------------------------------------------
    dvec_get --- allocate memory for (vec)tor of type (d)ouble
    ------------------------------------------------------------------------*/
double *dvec_get(long n)
{
  double *v;
  size_t sz;

  sz = (size_t) ((n)*sizeof(double));
  v=(double *)malloc(sz);

  if (!v) printf("dvec_get --- allocation failure (%10d)\n",sz);

  return v;
}

/*  --------------------------------------------------------------------------
    dvec_free --- free memory allocated by dvec_get.
    ------------------------------------------------------------------------*/
void dvec_free(double *v)
{
  free((char *) (v));
}

/*  --------------------------------------------------------------------------
    ivec_get --- allocate memory for (vec)tor of type (i)nt
    ------------------------------------------------------------------------*/
int *ivec_get(long n)
{
  int    *v;
  size_t sz;

  sz = (size_t) ((n)*sizeof(int));
  v=(int *)malloc(sz);

  if (!v) printf("ivec_get --- allocation failure (%10d)\n",sz);

  return v;
}

/*  --------------------------------------------------------------------------
    ivec_free --- free memory allocated by ivec_get.
    ------------------------------------------------------------------------*/
void ivec_free(int *v)
{
  free((char *) (v));
}

/*  --------------------------------------------------------------------------
    lvec_get --- allocate memory for (vec)tor of type (l)ong
    ------------------------------------------------------------------------*/
long *lvec_get(long n)
{
  long   *v;
  size_t sz;

  sz = (size_t) ((n)*sizeof(long));
  v=(long *)malloc(sz);

  if (!v) printf("lvec_get --- allocation failure (%10d)\n",sz);

  return v;
}

/*  --------------------------------------------------------------------------
    lvec_free --- free memory allocated by lvec_get.
    ------------------------------------------------------------------------*/
void lvec_free(long *v)
{
  free((char *) (v));
}


/*  --------------------------------------------------------------------------
    libhefrev --- revision of library
    ------------------------------------------------------------------------*/
char *libhefrev(void)
{
  return(LIBHEF_REVH);
}
