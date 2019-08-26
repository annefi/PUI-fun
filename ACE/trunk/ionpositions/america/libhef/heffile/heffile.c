/* ---------------------------------------------------------------------------
   heffile.c --- collection of file utilities
   (c) 1998-1999 Simon Hefti (hefti@umich.edu)
   $Id: heffile.c,v 1.1.1.1 2000/06/02 13:37:22 jraines Exp $
   ------------------------------------------------------------------------ */

#include <stdio.h>

#include "heffile.h"

/*  --------------------------------------------------------------------------
    hefopen --- open a file
    ------------------------------------------------------------------------*/
int hefopen(FST *fst)
{
  fst->fp = fopen(fst->pan,fst->zmode);
  if(!fst->fp) {
    printf("hefopen --- Cannot open %s (%s).\n",fst->pan,fst->zmode);
    return(1);
  }
  else {
    fst->is_open = 1;
    printf("hefopen --- file %s is open (%s).\n",fst->pan,fst->zmode);
    return(0);
  }

  return(1);
}

/*  --------------------------------------------------------------------------
    hefclose --- close a file
    ----------------------------------------------------------------------- */
int hefclose(FST *fst)
{
  int itmp = 0;

  if( fst->is_open ) {
    itmp = fclose(fst->fp);
    fst->is_open = 0;
    printf("hefclose --- file %s closed.\n",fst->pan);
  }

  return(0);
}

/* ---------------------------------------------------------------------------
   reset_filest --- set tags of file structure to default values.
   ------------------------------------------------------------------------ */
void reset_filest(FST *fsp)
{
  fsp->fp        = NULL;
  strcpy(fsp->pan,"NULL");
  strcpy(fsp->zmode,"r");
  fsp->is_req    = 0;
  fsp->is_open   = 0;
  fsp->do_rewind = 0;

  return;
}
