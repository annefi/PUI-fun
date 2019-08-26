/*
  File: swindal.h

  Description:
    Main header file for Solar WINd Data Analysis Library (swindal) package.

  Author: Jim Raines,  5Apr2001

  Method:
    References:
    1.  Techniques for Analysis of Data from Time-of-Flight
    Instruments, N. Schwadron, et. al., available at
    http://solar-heliospheric.engin.umich.edu/publications.html, 2000.

  Major Modification History:
    

*/

// C/C++ 
#include <stl.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include <fstream>

// Template Numerical Toolkit (TNT)
#include "tnt/tnt.h"
#include "tnt/cmat.h"
#include "tnt/vec.h"
#include "tnt/region1d.h"

// swindal classes
#include "Ion.h"
#include "AnalysisData.h"
#include "Pha.h"
#include "MeasurementArray.h"
#include "BoxRates.h"
#include "SpillRates.h"
#include "ProbRates.h"
#include "DistFunc.h"

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

// calculates solar wind speed from count-weighed average E/q
extern "C" double swspeed (double [], int [], float, float);

long int incrementYdoy(long int);

// calculates inverse of TNT matrix using Singular Value Decomp. from 
// Numerical Recipes in C.
TNT::Matrix<float> Invert(TNT::Matrix<float> A);

// (E/q,tofch,esdch) -> (mass, m/q)
// (uses libhef funtions which read constants from file)
int eqte2mmq(float eq, float pav, int tofch, int esdch,
		double& mm, double& mq);

// another way of converting (E/q,tofch,esdch) -> (mass, m/q)
// (uses hardcoded functions and constants)
extern "C" void mmqbyhand(double eq, double pav, int tch, int ech, 
			  double *mm, double *mq);
/* ----------------------------------------------------------------------------
			   Global Variables
	  These are given their initial value by initSwindal
   ----------------------------------------------------------------------------
*/


/* Global debugging level:  (each level includes all messages from prev.)
     0 -> almost zero messages, only critical warnings
     1 -> few messages but enough to see data flow, more warnings
     2 -> 
     3 -> dump values on a per edb basis 
     4 -> dump values inside loops (could be thousands of lines)
  */
extern int gDbgLvl;

/* Starting year and day of year in yyyydoy format */
extern long gStartYdoy;

/* Stop year and day of year in yyyydoy format */
extern long gStopYdoy;

/* Current LV1 filename, including path */
extern string gCurLv1File;

/* total data accumulation time 
   note: This is not exactly cycle times read.  See MeasurementArray::fill .
*/
extern float gAccumTime;

/* software version */
extern string gVersion;

/* build date and time concatenated */
extern string gBuildInfo;
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
	 e/q function.)
*/
const int FIRSTEDB = 2;  

/* dimensions in tof and esd space */
const int MAXTOFCH = 1024;
const int MAXESDCH = 256;

/* dimensions in mass and m/q space */
const int NMCH = 122;   // number of mass channels
const int NQCH = 124;   // number of m/q channels

/* Controls resolution of method, by controlling number of measured
   channels per bin in the measurement matrix.
   1 => full resolution
   2 => 2 ch/bin; 1/2 maximum resolution
   ...
   
   NOT CURRENTLY USED
*/
const int CHANNELS_PER_BIN = 2;

/* control TNT bounds checking */
#ifndef DEBUG
#define TNT_NO_BOUNDS_CHECK
#endif

