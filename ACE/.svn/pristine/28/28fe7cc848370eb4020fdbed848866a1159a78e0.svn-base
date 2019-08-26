"""
 ---------------------------------------------------------------------------
  bittools.c --- utilities for bit handling
  (c) 1997-1999 Simon Hefti (hefti@umich.edu)
  $Id: bittools.c,v 1.1.1.1 2000/06/02 13:37:19 jraines Exp $
 ---------------------------------------------------------------------------
""" 

from numpy import int32

#  --------------------------------------------------------------------------
#    getbits --- given a long variable (PHA data), extract bits. 
#    ------------------------------------------------------------------------

def getbits(inn,pos,lenght):
  # inn = long means 32 bits 
  return int( (inn >> (31-pos+1-lenght)) & ~(~0 << lenght))

#  --------------------------------------------------------------------------
#    comp12n --- Decompress compressed STOF telemetetry
#  --------------------------------------------------------------------------
def comp12n(exponent,mantisse):
  if exponent<0:
      return 1
  return (exponent>0)*exp(exponent*0.693147181)*0.5*(256+mantisse) + (exponent==0)*mantisse

#  --------------------------------------------------------------------------
#    decmpa --- DeCompression Table A
#  --------------------------------------------------------------------------
def decmpa(Compressed):
  rangecheckerror_reported = 0

  Exp4 = 0
  Man4 = 0
  decompressed = int32(0)

  # -------------------------------------------------------------------------
  # Range Checking of input.
  # -------------------------------------------------------------------------

  if (Compressed > 254):
      if rangecheckerror_reported == 0:
          rangecheckerror_reported = 1;
          #print "bittools:decmpa --- Table overflow with %3d (returning -2)\n"%(Compressed)
      return -2
  
  if (Compressed < 0):
      if (rangecheckerror_reported == 0):
          rangecheckerror_reported = 1
          #print "bittools:decmpa --- Table underflow with %3d (returning -1)\n"%(Compressed)
      return -1
  
  # -------------------------------------------------------------------------
  # Get the bits.
  # -------------------------------------------------------------------------
  
  Exp4 = Compressed / 16
  Man4 = Compressed % 16
  
  # -------------------------------------------------------------------------
  # Decompress....
  # -------------------------------------------------------------------------
    

  if (Exp4 == 0):
        decompressed = int32(Man4)
  if (Exp4 >  0):
        decompressed = int32((16 + Man4)* (int32(1) << (Exp4 -  1)))
  
  # -------------------------------------------------------------------------
  # ...and don't forget to return the result.
  # -------------------------------------------------------------------------

  #print decompressed
  return decompressed


#  --------------------------------------------------------------------------
#   decmpc --- DeCompression Table C
#  --------------------------------------------------------------------------
def decmpc(Compressed):
  rangecheckerror_reported = 0;

  Exp4 = 0
  Man4 = 0

  Exp5 = 0
  Man3 = 0

  Bit6and7 = 0
  
  decompressed = int32(0)
  
  ltmp = int32(0)
  ltmp2 = int32(0)
  
  # -------------------------------------------------------------------------
  # Range Checking of input.
  # -------------------------------------------------------------------------

  if (Compressed > 254):
    if (rangecheckerror_reported == 0):
      rangecheckerror_reported = 1
      print  "bittools:decmpc --- Table overflow with %3d (returning -2)\n"%(Compressed)
    return -2

  if (Compressed < 0):
    if (rangecheckerror_reported == 0):
      rangecheckerror_reported = 1
      print "bittools:decmpc --- Table underflow with %3d (returning -1)\n"%(Compressed)
    return -1

  # -------------------------------------------------------------------------
  # Get the bits.
  # -------------------------------------------------------------------------

  ltmp = int32(Compressed)
  
  Bit6and7 = getbits(ltmp, 24 + 0, 2)
    
  decompressed = int32(-3)

  # -------------------------------------------------------------------------
  # Decompress....
  # -------------------------------------------------------------------------

  if (Bit6and7 == 3):
    # -----------------------------------------------------------------------
    # in this case we have 5 bits exponent, 3 bits manitissa
    # -----------------------------------------------------------------------
    
    Exp5 = getbits(ltmp, 24 + 0, 5)
    Man3 = getbits(ltmp, 24 + 5, 3)
    
    ltmp2 = int32(1)

    if (Exp5 >= 12):
      decompressed = int32(( 8 + Man3) * (int32(1) << (Exp5 - 12)))

  if (Bit6and7 < 3):
    # -----------------------------------------------------------------------
    # in this case we have 4 bits exponent, 4 bits manitissa (as for Table A)
    # -----------------------------------------------------------------------
    
    Exp4 = getbits(ltmp, 24 + 0, 4)
    Man4 = getbits(ltmp, 24 + 4, 4)

    if (Exp4 == 0):
      decompressed = int32(Man4)

    if (Exp4 > 0):
      decompressed = int32((16 + Man4) * (int32(1) << (Exp4 -  1) ))
  
  return decompressed 
