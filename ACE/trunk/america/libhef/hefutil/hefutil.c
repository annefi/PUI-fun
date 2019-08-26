/* ---------------------------------------------------------------------------
   hefutil.c --- tools
   (c) 1999 Simon Hefti (hefti@umich.edu)
   $Id: hefutil.c,v 1.1.1.1 2000/06/02 13:37:28 jraines Exp $
   ------------------------------------------------------------------------ */

#include "hefutil.h"

static int perr_rank = PEEYORE;

/*  --------------------------------------------------------------------------
    hperr --- complain
    ----------------------------------------------------------------------- */
int hperr(FILE *fp, int ilevel, char *fmt, ...)
{
  va_list ap; /* points to each unnamed arg in turn */
  char   *p;
  char   *sval;
  int    ival;
  double dval;

  if( perr_rank <= ilevel ) {

    va_start(ap,fmt); /* make ap point to 1st unnamend arg */
    for( p = fmt; *p; p++) {
      if(*p != '%') {
	putc(*p,fp);
	continue;
      }
      switch (*++p) {
      case 'd':
	ival = va_arg(ap,int);
	fprintf(fp,"%d",ival);
	break;
      case 'f':
	dval = va_arg(ap,double);
	printf("%f",dval);
	break;
      case 's':
	for(sval = va_arg(ap,char *); *sval; sval++) {
	  putc(*sval,fp);
	}
	break;
      default:
	putc(*p,fp);
	break;
      }
    }
    va_end(ap);
  }

  return(1);
}

/*  --------------------------------------------------------------------------
    perr_setlevel --- set level for perr (EEYORE,NOVICE,EXPERT)
    ----------------------------------------------------------------------- */
int perr_setlevel(int ilevel)
{
  if( (ilevel >= 0) && (ilevel <= 3) ) {
    perr_rank = ilevel;
  } else {
    perr_rank = PEEYORE;
  }
  return(0);
}

