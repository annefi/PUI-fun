/* --------------------------------------------------------------- <Prolog> --
   heffile.h --- header file for "file handling routines collection"
   (c) Simon Hefti (hef), University of Michigan (hefti@umich.edu)
   $Id: heffile.h,v 1.1.1.1 2000/06/02 13:37:20 jraines Exp $
   ------------------------------------------------------------- </Prolog> -*/

#include <stdio.h>
#include "datatypes.h"

#ifndef HEFFILEH
#define HEFFILEH

int hefopen  (FST *fst);
int hefclose (FST *fst);

#endif
