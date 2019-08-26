# ---------------------------------------------------------------------------
#   adapted from datatypes.h (by Simon Hefti (hefti@umich.edu))
#   by Lars Berger (berger@physik.uni-kiel.de)
#  -------------------------------------------------------------------------

from numpy import *

BYTE=uint8

#typedef char str256[256];
#typedef char str80[80];

# --- file --- 
"""
class FST(object): 
  FILE   *fp                          #  file pointer 
  str256 pan                          #  path and filename: pan 
  char   zmode[8]                     #  mode string for fopen 
  int    is_req                       #  flag: is required 
  int    is_open                      #  flag: is open
  int    do_rewind                    #  flag: rewind file upon opening 

"""
# --- point ---
class PST(object):
  def __init__(self):
      dx=0.
      dy=0.
      dz=0.


# --- ellipse ---
class EST(object): 
  def __init__(self):
      stp0=PST() # x0, y0 
      stsa=PST() # semi-axis (.dx --> a, .dy --> b)
      sts2=PST() # second set of two semi-axis. Used for a-symmetric
                 # ellipses. In this case, stsa is valid, if
                 # x < x0 or y < y0, and sts2 otherwise 
      dphi=0.    # rotation in xy-plane 


class ELL(object):
  def __init__(self):
      dx0=0.
      dy0=0.
      da1=0.  # semi-axis 
      da2=0.
      db1=0.  # semi-axis 
      db2=0.
      dphi=0. # tilt 

# --- handy square ---
#static double dsqrarg;
#define DSQR(a) ((dsqrarg=(a)) == 0.0 ? 0.0 : dsqrarg*dsqrarg)

 
# --- Pi --- 
DPI=pi

# --- deg->rad --- 
DTOR=(DPI/180.0)

