/* swindal.h -- main header file for swindal
   Jim Raines, 5Apr2001
 */

#include <stl.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <stdio.h>

// Template Numerical Toolkit (TNT)
#include "tnt/tnt.h"
#include "tnt/cmat.h"
#include "tnt/vec.h"
#include "tnt/region1d.h"

// swindal classes
#include "Ion.h"
#include "AnalysisData.h"
#include "Pha.h"
#include "Derivables.h"
#include "MeasurementArray.h"

/* ----------------------------------------------------------------------------
			   Global  Typedefs
   ----------------------------------------------------------------------------
*/

/* ----------------------------------------------------------------------------
			   Global Functions
   ----------------------------------------------------------------------------
*/

int initSwindal(void);
int loadPha(vector<Pha> *pha, int);
int boxClassify(vector<Pha> *pha, vector<Ion> *grp, Derivables *deriv);

// calculates solar wind speed from count-weighed average E/q
extern "C" double swspeed (double [], int [], float, float);

long int incrementYdoy(long int);
/* ----------------------------------------------------------------------------
			   Global Variables
	  These are given their initial value by initSwindal
   ----------------------------------------------------------------------------
*/


/* Global debugging level: 
     0 -> almost zero message
     1 -> few messages but enough to see data flow
     2 ->
     3 ->
     4 -> dump even minute details
  */
extern int gDbgLvl;

/* Starting year and day of year in yyyydoy format */
extern long gStartYdoy;

/* Stop year and day of year in yyyydoy format */
extern long gStopYdoy;

/* Current LV1 filename, including path */
extern string gCurLv1File;

/* ----------------------------------------------------------------------------
			   Global Constants
   ----------------------------------------------------------------------------
*/

/* maximum number of EDBs for array dim. and looping */
const int MAXEDB = 60;   

/* first EDB to read
   According to Simon Hefti: 
   EDB 0 is from last cycle 
   EDB 1 is voltage ramp up 
   EDB 2 should be first good one (still need to
         shift them back on (i.e., use nedb - 1 for
	 e/q function.
*/
const int FIRSTEDB = 2;  

/* dimensions in tof and esd space */
const int MAXTOFCH = 1024;
const int MAXESDCH = 256;

/* Controls resolution of method, by controlling number of measured
   channels per bin in the measurement matrix.
   1 => full resolution
   2 => 2 ch/bin; 1/2 maximum resolution
   ...
*/
const int CHANNELS_PER_BIN = 2;
