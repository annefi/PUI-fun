
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "gnuplot_plugin.h"

extern void geometrie_();
extern void  swxeff_(float*resprob,
		  float*e,
		  float*z,
		  float*m,
                  float*ladung,
		  char*element,
		  float*C1,
		  float*C2,
		  float*C3,
		  float*pf1,
		  float*pf2,
		  float*Ethr,
		  float*fwhm,
		  float*thick,
		  float*defl,
                  float*probmode,
                  float*auxpar1,
                  float*auxpar2,
                  float*auxpar3);

void *gnuplot_init(struct value (*exfn)(int, struct value *, void *))
{
  char *element;
  static char elem[3];

  element = get_string_arg();
  if (!element)
    {
      fprintf(stderr, 
	      "Element name required\n");
      return NULL;
    }

  strncpy(elem, element, 3);

  fprintf(stderr, "swxeff_gpt: initializing for element %s\n", elem);

  geometrie_();

  fprintf(stderr, "swxeff_gpt: initialized for element %s\n", elem);

  return elem;
}

struct value gnuplot_default(int n, struct value *a, void *p)
{
  struct value r;
  float resprob,e,z,m,ladung,C1,C2,C3,pf1,pf2,Ethr,fwhm,thick,defl,probmode,auxpar1,auxpar2,auxpar3;
  char *elem = p;

  r.type = CMPLX;
  r.v.cmplx_val.imag = 0;
  r.v.cmplx_val.real = 0;

  if (n != 17)
    {
      fprintf(stderr, "swxeff must be called with 17 arguments, got %d\n", n);
      return r;
    }

  e     = RVAL(a[0]);
  z     = RVAL(a[1]);
  m     = RVAL(a[2]);
  ladung= RVAL(a[3]);
  C1    = RVAL(a[4]);
  C2    = RVAL(a[5]);
  C3    = RVAL(a[6]);
  pf1   = RVAL(a[7]);
  pf2   = RVAL(a[8]);
  Ethr  = RVAL(a[9]);
  fwhm  = RVAL(a[10]);
  thick = RVAL(a[11]);
  defl  = RVAL(a[12]);
  probmode  = RVAL(a[13]);
  auxpar1 = RVAL(a[14]);
  auxpar2 = RVAL(a[15]);
  auxpar3 = RVAL(a[16]);
  
//  printf ("%G\n",e);

/*  fprintf(stderr, 
	  "resprob(%G %G %G %G %G %G %G %G %G %G) = ",
	  e,z,m,C1,C2,C3,pf1,pf2,Ethr,fwhm,thick,defl);
*/
  swxeff_(&resprob, &e, &z, &m, &ladung, elem, &C1, &C2, &C3,
       &pf1, &pf2, &Ethr, &fwhm, &thick, &defl, &probmode,
       &auxpar1, &auxpar2, &auxpar3);

  r.v.cmplx_val.real = resprob;

  //  fprintf(stderr, "%g\n", r.v.cmplx_val.real);

  return r;
}
