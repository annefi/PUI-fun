/* --------------------------------------------------------------- <Prolog> --
   Name:      datatypes.h
   Title:     Frequently used data types and definitions
   Author:    Simon Hefti (hef), University of Michigan
              hefti@umich.edu
   $Id: datatypes.h,v 1.1.1.1 2000/06/02 13:37:20 jraines Exp $
  -------------------------------------------------------------- </Prolog> -*/

#include <stdio.h>

#ifndef DATATYPESH
#define DATATYPESH

#define BYTE unsigned char                     /* Frequently used data type */
typedef char str256[256];
typedef char str80[80];

/* --- file --- */
typedef struct FST {
  FILE   *fp;                                             /* file pointer */
  str256 pan;                                   /* path and filename: pan */
  char   zmode[8];                               /* mode string for fopen */
  int    is_req;                                     /* flag: is required */
  int    is_open;                                        /* flag: is open */
  int    do_rewind;                     /* flag: rewind file upon opening */
} FST;

/* --- point --- */
typedef struct PST {
  double dx;
  double dy;
  double dz;
} PST;

/* --- ellipse --- */
typedef struct EST {
  PST    stp0; /* x0, y0 */
  PST    stsa; /* semi-axis */
  double dphi; /* rotation in xy-plane */
} EST;



/* --- handy square --- */
/*
static double dsqrarg;
#define DSQR(a) ((dsqrarg=(a)) == 0.0 ? 0.0 : dsqrarg*dsqrarg)
*/
 
/* --- Pi --- */
#define DPI 3.14159265359

/* --- deg->rad --- */
#define DTOR (DPI/180.0)

#endif
