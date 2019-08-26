/*
  File: anciltest.h

  Description:
   ACE Ancillary Data extraction library.  Functions in this library
   read ACE orbit and attitude data (O/A) in a variety of coordinate
   systems for a given cycle time. 

  Author(s): Jim Raines (jmr)

  Method:
   The O/A data is typically updated several times per day only.  The
   low level routines used by this library (provided by the ACE
   Science Center) interpolate the O/A data for a given cycle time.

   Details of this data and coordinate systems are available at the
   ACE Science Center website (http://www.srl.caltech.edu/ACE/ASC as
   of this writing).
    
  Revision controlled by CVS:
  $Id: libace_ancil.h,v 1.2 2003/10/17 16:01:53 jraines Exp $

  Major Modification History:
    06Jun2003   jmr   initial coding
    18Sep2003   jmr   added HSEb functions and more documentaion

*/


/* h2i-begin */
/* %title "ACE Ancillary Data Extraction Library", before, pre */
/* %module libace_ancil */
/* %style before, skip=1 */
/* h2i-end */

#include <math.h>
#include <memory.h>
#include <string.h>
#include <time.h>
#include "hdfi.h"           /* using HDF variable definitions */
#include "aosr.h"
#include "ccr.h"
#include "df.h"
#include "mfhdf.h"

/* --- prototypes for functions in ancil_subs.c --- */
int32 ACE_aosr(float64 scclock, struct attorb_entry *aosr_struct);
int32 init_ACEancillary(); 
float64 ACEepoch_to_SCclock(float64);

/* h2i-begin */
/* %section "Overview", after */
/* 
   Functions in this library read ACE orbit and attitude data (O/A) in
   a variety of coordinate systems for a given cycle time.  Of note:
   The O/A data is typically updated several times per day only.  The
   low level routines used by this library (provided by the ACE
   Science Center) interpolate the O/A data for a given cycle time.

   Details of this data and coordinate systems are available at the
   ACE Science Center website (http://www.srl.caltech.edu/ACE/ASC as
   of this writing).
*/


/* %section "General Functions" */
/* Read ACE O/A ancillary data
   Reads entire ancillary file into memory for extraction with other functions
   in this section.  The 'ancillary_file' is typically ACE_ANCIL.DAT with the
   pathname appended.

*/
long int a3goa_read(char *ancillary_file);
/*long int a3goa_read();*/

/* h2i-end */
/* get o/a structure -- libancil user does not call directly */ 
struct attorb_entry* a3goa(double);
//void print_aosr();
void print_aosr(struct attorb_entry aosr);
/* h2i-begin */

/* %section "Coordinate-specific functions" */
/* %subsection "Geocentric Solar Ecliptic (GSE) Coordinates" */
/* Geocentric Solar Ecliptic (GSE) Coordinates
   Coordinates are centered at the Earth.
   x -- points toward the Sun along the Earth-Sun line
   z -- points toward ecliptic north pole (same dir. as Earth's North pole), 
        normal to the orbital plane (ecliptic) of the Earth
   y -- normal to x and z, points so that rotating x into y points along z
        via the right hand rule.  (This makes a right-handed coordinate 
	system.) 
*/
/* %subsubsection "GSE Attitude Cosines" */
/* get attitude cosine with respect to GSE x */
extern float a3goa_att_GSE_x(double);

/* get attitude cosine with respect to GSE y */
extern float a3goa_att_GSE_y(double);

/* get attitude cosine with respect to GSE z */
extern float a3goa_att_GSE_z(double);

/* %subsubsection "GSE Position Components" */
/* get GSE x component of position */
extern float a3goa_pos_GSE_x(double ss1970);

/* get GSE y component of position */
extern float a3goa_pos_GSE_y(double ss1970);

/* get GSE z component of position */
extern float a3goa_pos_GSE_z(double ss1970);


/* %subsubsection "GSE Velocity Components" */
/* get GSE x component of velocity */
extern float a3goa_vel_GSE_x(double ss1970);

/* get GSE y component of velocity */
extern float a3goa_vel_GSE_y(double ss1970);

/* get GSE z component of velocity */
extern float a3goa_vel_GSE_z(double ss1970);

/* %subsubsection "GSE Spin Components" */
/* get GSE x component of spin */
extern float a3goa_spin_GSE_x(double ss1970);

/* get GSE y component of spin */
extern float a3goa_spin_GSE_y(double ss1970);

/* get GSE z component of spin */
extern float a3goa_spin_GSE_z(double ss1970);

/* %subsection "Heliocentric Solar Ecliptic (Earth Oriented) (HSEb) Coordinates" */
/* Heliocentric Solar Ecliptic (Earth Oriented) (HSEb) Coordinates
   Coordinates are centered at the Sun.
   x -- points toward the Earth along the Earth-Sun line
   z -- points toward ecliptic north pole (same dir. as Earth's North pole), 
        normal to the orbital plane (ecliptic) of the Earth
   y -- normal to x and z, points so that rotating x into y points along z
        via the right hand rule.  (This makes a right-handed coordinate 
	system.)

   Note: Velocity not implemented in these coordinates.
*/
/* %subsubsection "HSEb Attitude Cosines" */
/* get HSEb x attitude cosine */
extern float a3goa_att_HSEb_x(double ss1970);
/* get HSEb y attitude cosine */
extern float a3goa_att_HSEb_y(double ss1970);
/* get HSEb z attitude cosine */
extern float a3goa_att_HSEb_z(double ss1970);

/* %subsubsection "HSEb Position Components" */
/* get HSEb x component of position */
extern float a3goa_pos_HSEb_x(double ss1970);
/* get HSEb y component of position */
extern float a3goa_pos_HSEb_y(double ss1970);
/* get HSEb z component of position */
extern float a3goa_pos_HSEb_z(double ss1970);

/* %subsubsection "HSEb Spin Components" */
/* get HSEb x component of spin */
extern float a3goa_spin_HSEb_x(double ss1970);
/* get HSEb y component of spin */
extern float a3goa_spin_HSEb_y(double ss1970);
/* get HSEb z component of spin */
extern float a3goa_spin_HSEb_z(double ss1970);

/* %subsection "Radial Tangential Normal (RTN) Coordinates" */
/* Radial Tangential Normal (RTN) Coordinates
   Spacecraft centered coordinate system. 
   r = Sun to Spacecraft unit vector 
   t = (Omega x r) / | (Omega x r) |
       where Omega is Sun's spin axis (in J2000 GCI)
   n completes the right-handed triad 
*/
/* %subsubsection "RTN Attitude Cosines" */
/* get RTN attitude cosine with respect to r */
extern float a3goa_att_RTN_r(double ss1970);

/* get RTN attitude cosine with respect to t */
extern float a3goa_att_RTN_t(double ss1970);

/* get RTN attitude cosine with respect to n */
extern float a3goa_att_RTN_n(double ss1970) ;

/* %subsubsection "RTN Spin (rad/sec)" */
/* get RTN r component of spin */
extern float a3goa_spin_RTN_r(double ss1970);
/* get RTN t component of spin */
extern float a3goa_spin_RTN_t(double ss1970);
/* get RTN n component of spin */
extern float a3goa_spin_RTN_n(double ss1970);


/* h2i-end */

