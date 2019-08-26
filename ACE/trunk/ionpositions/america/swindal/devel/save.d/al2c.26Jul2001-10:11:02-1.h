/* File: al2c.h

   Description: 
     Header file for al2c project.

   Author:
     Jim Raines, 23Feb2001

   This file is controlled by the Concurent Version System (CVS):
   $Id:$

   Major Modification History: (keep this last section)

*/

#include "libsms.h"

/* definition of PHA structure data type */
typedef struct pha {
  double scet;                       // spacecraft event time 
  double epq;              // Energy Per charge value in keV/e
  double tof;      // time of flight in nanoseconds
  double energy;   // energy in keV      
  int sector;      // sector of PHA (1/8 of circle)
  int detector;    // detector of PHA
  int range;       // range of PHA (goes with BR, 0-2)
  int br[3];               // basic rates
  int npharng[4];          // npha with a range of third index
  double tcr;              // triple coincidence rate
  double mmch;                     // mass in channel units
  double mm;       // mass in physical units
  double mqch;                     // m/q in channel units
  double mq;       // m/q in physical units
  float hspeed;                    // H+ speed
  double weight;           // pha weights
  float asp;           // aspect angle - FIX: read in, do not hardcode

} PHA;

/* global variables */
struct globalVariables {

} g; 
