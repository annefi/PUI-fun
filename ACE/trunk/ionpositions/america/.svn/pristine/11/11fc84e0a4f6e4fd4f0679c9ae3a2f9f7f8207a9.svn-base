/* ---------------------------------------------------------------------------
   bittools.c --- utilities for bit handling
   (c) 1997-1999 Simon Hefti (hefti@umich.edu)
   $Id: bittools.c,v 1.1.1.1 2000/06/02 13:37:19 jraines Exp $
   ------------------------------------------------------------------------ */

static char* rcsid =\
"bittools.c 1.4 Tue, 17 Mar 1998 12:04:33 -0500 hefti";

#include <math.h>
#include <stdlib.h>

#include "acetools.h"

/*  --------------------------------------------------------------------------
    getbits --- given a long variable (PHA data), extract bits. 
    ------------------------------------------------------------------------*/
int getbits(long in, int pos, int length)
{
  /* long means 32 bits */
  return( (int)( (in >> (31-pos+1-length)) & ~(~0 << length)));
}

/*  --------------------------------------------------------------------------
    comp12n --- Decompress compressed STOF telemetetry
    ------------------------------------------------------------------------*/
double comp12n(int exponent, int mantisse)
{
  if (exponent<0)
      return 1;

  return (exponent>0)*exp(exponent*0.693147181)*0.5*(256+mantisse)
         + (exponent==0)*mantisse;
}

/*  --------------------------------------------------------------------------
    decmpa --- DeCompression Table A
    ------------------------------------------------------------------------*/
long decmpa(int Compressed)
{
  static int rangecheckerror_reported = 0;

  int	Exp4 = 0;
  int   Man4 = 0;
  
  long  decompressed = 0L;

  /* -------------------------------------------------------------------------
  ** Range Checking of input.
  ** -----------------------------------------------------------------------*/

  if( Compressed > 254 ) {
    if( rangecheckerror_reported == 0 ) {
      rangecheckerror_reported = 1;
      printf("bittools:decmpa --- Table overflow with %3d (returning -2)\n",
	     Compressed);
    }
    return(-2);
  }
  
  if( Compressed < 0 ) {
    if( rangecheckerror_reported == 0 ) {
      rangecheckerror_reported = 1;
      printf("bittools:decmpa --- Table underflow with %3d (returning -1)\n",
	     Compressed);
    }
    return(-1);
  }
  
  /* -------------------------------------------------------------------------
  ** Get the bits.
  ** -----------------------------------------------------------------------*/
  
  Exp4 = Compressed / 16;
  Man4 = Compressed % 16;
  
  /* -------------------------------------------------------------------------
  ** Decompress....
  ** -----------------------------------------------------------------------*/
    
  if( Exp4 == 0 ) decompressed = Man4;
  if( Exp4 >  0 ) decompressed = (16 + Man4)* (1L << (Exp4 -  1));
  
  /* -------------------------------------------------------------------------
  ** ...and don't forget to return the result.
  ** -----------------------------------------------------------------------*/

  return(decompressed);
}

/*  --------------------------------------------------------------------------
    decmpc --- DeCompression Table C
    ------------------------------------------------------------------------*/
long decmpc(int Compressed)
{
  static int rangecheckerror_reported = 0;

  int	Exp4 = 0;
  int   Man4 = 0;

  int   Exp5 = 0;
  int	Man3 = 0;

  int   Bit6and7 = 0;
  
  long  decompressed = 0L;
  
  long  ltmp = 0L;
  long  ltmp2 = 0L;
  
  /* -------------------------------------------------------------------------
  ** Range Checking of input.
  ** -----------------------------------------------------------------------*/

  if( Compressed > 254 ) {
    if( rangecheckerror_reported == 0 ) {
      rangecheckerror_reported = 1;
      printf("bittools:decmpc --- Table overflow with %3d (returning -2)\n",
	     Compressed);
    }
    return(-2);
  }
  
  if( Compressed < 0 ) {
    if( rangecheckerror_reported == 0 ) {
      rangecheckerror_reported = 1;
      printf("bittools:decmpc --- Table underflow with %3d (returning -1)\n",
	     Compressed);
    }
    return(-1);
  }

  /* -------------------------------------------------------------------------
  ** Get the bits.
  ** -----------------------------------------------------------------------*/

  ltmp = (long)Compressed;
  
  Bit6and7 = getbits(ltmp, 24 + 0, 2);
    
  decompressed = -3L;

  /* -------------------------------------------------------------------------
  ** Decompress....
  ** -----------------------------------------------------------------------*/

  if( Bit6and7 == 3 ) {
    /* -----------------------------------------------------------------------
    ** in this case we have 5 bits exponent, 3 bits manitissa
    ** ---------------------------------------------------------------------*/
    
    Exp5 = getbits(ltmp, 24 + 0, 5);
    Man3 = getbits(ltmp, 24 + 5, 3);
    
    ltmp2 = 1L;

    if( Exp5 >= 12) {
      decompressed = ( 8 + Man3) * (1L << (Exp5 - 12));
    }
  }
  if( Bit6and7 < 3 ) {
    /* -----------------------------------------------------------------------
    ** in this case we have 4 bits exponent, 4 bits manitissa (as for Table A)
    ** ---------------------------------------------------------------------*/
    
    Exp4 = getbits(ltmp, 24 + 0, 4);
    Man4 = getbits(ltmp, 24 + 4, 4);

    if( Exp4 == 0 ) decompressed = Man4;

    if( Exp4 >  0 ) {
      decompressed = (16 + Man4) * (1L << (Exp4 -  1) );
    }
  }
  
  return(decompressed);
}
