/* $Id: uleis_br_db.h,v 1.2 1998/12/09 00:30:48 steves Exp $ */
/* The variables and arrays below are assigned values from the files */
/* in the ~asc/aceprog/uleis_br_db directory */

#include "hdfi.h"

struct UleisDB
{
  float64 begin_time_in_sec; /* seconds since Jan 1 1970 */
  float64 end_time_in_sec;  /* seconds since Jan 1 1970 */

/*H,H, 3He, 4He,4He, O,O, Fe,Fe by Rate_assignment, Detectors, Efficiency(Avg)*/
  float64 species[9][3];

/*ULEIS Detector Geometry Factors vs. Iris settings (i.e. motor position)*/
/* D1, D2, D3, D4, D5, D6, D7 by Iris settings of: 100%, 25%, 6%, 1% */
  float64 detector[7][4];

};
