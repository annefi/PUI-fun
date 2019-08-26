/* --------------------------------------------------------------- <Prolog> --
   heffile.c --- collection of file utilities
   (c) Simon Hefti (hef), University of Michigan (hefti@umich.edu)
   $Id: heffile.c,v 1.1.1.1 2000/06/02 13:37:20 jraines Exp $
   ------------------------------------------------------------- </Prolog> -*/

#include <stdio.h>

#include "heffile.h"

/*  --------------------------------------------------------------------[<]---
    Function: hefopen
    Synopsis: open a file
    --------------------------------------------------------------------[>]-*/
int hefopen(FST *fst)
{
  fst->fp = fopen(fst->pan,fst->zmode);
  if(!fst->fp) {
    printf("hefopen --- Cannot open %s.\n",fst->pan);
    return(1);
  }
  else {
    fst->is_open = 1;
    printf("hefopen --- file %s is open.\n",fst->pan);
    return(0);
  }

  return(1);
}

/*  --------------------------------------------------------------------[<]---
    Function: hefclose
    Synopsis: close a file
    --------------------------------------------------------------------[>]-*/
int hefclose(FST *fst)
{
  int itmp = 0;

  itmp = fclose(fst->fp);
  fst->is_open = 0;

  return(0);
}
