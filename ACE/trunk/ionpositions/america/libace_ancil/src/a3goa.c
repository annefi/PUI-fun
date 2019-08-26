/*
  File: a3goa.c

  Description: 

  ACE S3 Get Orbit and Attitude.  These are libancil-specific functions
  that get ACE spacecraft orbit and attitude (oa).

  Author(s): Jim Raines (jmr)

  Method:
    Uses the anciltest part of the acetest package (V3.2) from the ACE
    Science Center.
    
  Revision controlled by CVS:
  $Id: a3goa.c,v 1.2 2003/10/17 16:01:53 jraines Exp $

  Major Modification History:
    06Jun2003   jmr   initial coding

*/

#include <stdio.h>
#include <string.h>
#include "libace_ancil.h"

struct attorb_entry* a3goa(double ss1970){
  char thisprog[] = "libace_ancil::a3goa";
  int32 retval;

  int32 offset;
  float64 ss1996;

  float64 scclock;

  static struct attorb_entry aosr_struct;

  int DbgLvl = 0;  // debugging level
  /* --- convert to ACE Epoch, seconds since 1996 --- */
  /* compute offset in seconds
                                v---leap days         */
  offset = ((1996 - 1970)*365 + 6)*24*60*60;
  ss1996 = (float)ss1970 - (float)offset;

  /* convert to spacecraft clock */
  if ((scclock = ACEepoch_to_SCclock(ss1996)) == -1.0){
    printf("%s -F- ACE epoch out of bounds\n", thisprog);
    //return;
  }
  else {
    if (DbgLvl) printf("%s -I- S/C clock = %f\n", thisprog, scclock);
  }

  /* get AOSR structure */
  if((retval=ACE_aosr(scclock, &aosr_struct)) == -1){
     fprintf(stdout,"%s -F- scclock out of bounds\n", thisprog);
  }
  else {
     if(retval==1)
       fprintf(stdout,"Warning: spacecraft maneuvering\n");
     if (DbgLvl) print_aosr(aosr_struct);
  }

  return (&aosr_struct);
}

void print_aosr(struct attorb_entry aosr)
{
    fprintf(stdout,"\n");
    fprintf(stdout,"time = %lu\n",aosr.sctime);
    fprintf(stdout,"ISTP time = %ld, %ld\n",aosr.istp_time[0],aosr.istp_time[1]);
    /* new code */
    fprintf(stdout,"UT_time = %s\n",aosr.UT_time);
    fprintf(stdout,"status = %d\n",aosr.state);
    fprintf(stdout,"attJ   = %22.10e %22.10e %22.10e\n",
        aosr.att_J2GCI[0],aosr.att_J2GCI[1],aosr.att_J2GCI[2]);
    fprintf(stdout,"attRTN = %22.10e %22.10e %22.10e\n",
        aosr.att_RTN[0],aosr.att_RTN[1],aosr.att_RTN[2]);
    fprintf(stdout,"attGSE = %22.10e %22.10e %22.10e\n",
        aosr.att_GSE[0],aosr.att_GSE[1],aosr.att_GSE[2]);
    fprintf(stdout,"attGSM = %22.10e %22.10e %22.10e\n",
        aosr.att_GSM[0],aosr.att_GSM[1],aosr.att_GSM[2]);
    fprintf(stdout,"attHSEb = %22.10e %22.10e %22.10e\n",
        aosr.att_HSEb[0],aosr.att_HSEb[1],aosr.att_HSEb[2]);
    fprintf(stdout,"attHS = %22.10e %22.10e %22.10e\n",
        aosr.att_HS[0],aosr.att_HS[1],aosr.att_HS[2]);

    fprintf(stdout,"spinJ  = %22.10e %22.10e %22.10e\n",
        aosr.spin_J2GCI[0],aosr.spin_J2GCI[1],aosr.spin_J2GCI[2]);
    fprintf(stdout,"spinRTN= %22.10e %22.10e %22.10e\n",
        aosr.spin_RTN[0],aosr.spin_RTN[1],aosr.spin_RTN[2]);
    fprintf(stdout,"spinGSE= %22.10e %22.10e %22.10e\n",
        aosr.spin_GSE[0],aosr.spin_GSE[1],aosr.spin_GSE[2]);

    fprintf(stdout,"posJ   = %22.10e %22.10e %22.10e\n",
        aosr.pos_J2GCI[0],aosr.pos_J2GCI[1],aosr.pos_J2GCI[2]);
    fprintf(stdout,"posGSE = %22.10e %22.10e %22.10e\n",
        aosr.pos_GSE[0],aosr.pos_GSE[1],aosr.pos_GSE[2]);
    fprintf(stdout,"posGSM = %22.10e %22.10e %22.10e\n",
        aosr.pos_GSM[0],aosr.pos_GSM[1],aosr.pos_GSM[2]);
    fprintf(stdout,"posHSEb = %22.10e %22.10e %22.10e\n",
        aosr.pos_HSEb[0],aosr.pos_HSEb[1],aosr.pos_HSEb[2]);
    fprintf(stdout,"posHS = %22.10e %22.10e %22.10e\n",
        aosr.pos_HS[0],aosr.pos_HS[1],aosr.pos_HS[2]);
    fprintf(stdout,"velJ   = %22.10e %22.10e %22.10e\n",
        aosr.vel_J2GCI[0],aosr.vel_J2GCI[1],aosr.vel_J2GCI[2]);
    fprintf(stdout,"velGSE = %22.10e %22.10e %22.10e\n",
        aosr.vel_GSE[0],aosr.vel_GSE[1],aosr.vel_GSE[2]);
    fprintf(stdout,"velGSM = %22.10e %22.10e %22.10e\n",
        aosr.vel_GSM[0],aosr.vel_GSM[1],aosr.vel_GSM[2]);
    fprintf(stdout,"velHSEb = %22.10e %22.10e %22.10e\n",
        aosr.vel_HSEb[0],aosr.vel_HSEb[1],aosr.vel_HSEb[2]);
    fprintf(stdout,"velHS = %22.10e %22.10e %22.10e\n",
        aosr.vel_HS[0],aosr.vel_HS[1],aosr.vel_HS[2]);
    fprintf(stdout,"\n");
}

/*long int a3goa_read(){*/
long int a3goa_read(char *ancillary_file){
  /*return(init_ACEancillary(
    "/shrg1/ace/sw/src/acetest/anciltest/ACE_ANCIL.HDF"));*/
  return(init_ACEancillary(ancillary_file));
}

/* ----------------------------------------------------------------------
   O/A retrieval functions
   Note:  Each calls a3goa with a time and grabs the appropriate array element
   from the returned structure pointer.
   ---------------------------------------------------------------------- */

/* Geocentric Solar Ecliptic (GSE) Coordinates
   Coordinates are centered at the Earth.
   x -- points toward the Sun along the Earth-Sun line
   z -- points toward ecliptic north pole (same dir. as Earth's North pole), 
        normal to the orbital plane (ecliptic) of the Earth
   y -- normal to x and z, points so that rotating x into y points along z
        via the right hand rule.  (This makes a right-handed coordinate 
	system.) 
*/
/* Attitude coordinates */
float a3goa_att_GSE_x(double ss1970){
  return(a3goa(ss1970)->att_GSE[0]);
}

float a3goa_att_GSE_y(double ss1970) {
  return(a3goa(ss1970)->att_GSE[1]);
}

float a3goa_att_GSE_z(double ss1970) {
  return(a3goa(ss1970)->att_GSE[2]);
}


/* Position coordinates */
float a3goa_pos_GSE_x(double ss1970) {
  return(a3goa(ss1970)->pos_GSE[0]);
}

float a3goa_pos_GSE_y(double ss1970) {
  return(a3goa(ss1970)->pos_GSE[1]);
}

float a3goa_pos_GSE_z(double ss1970) {
  return(a3goa(ss1970)->pos_GSE[2]);
}


/* Velocity */
float a3goa_vel_GSE_x(double ss1970) {
  return(a3goa(ss1970)->vel_GSE[0]);
}

float a3goa_vel_GSE_y(double ss1970) {
  return(a3goa(ss1970)->vel_GSE[1]);
}

float a3goa_vel_GSE_z(double ss1970) {
  return(a3goa(ss1970)->vel_GSE[2]);
}

/* Spin */
float a3goa_spin_GSE_x(double ss1970) {
  return(a3goa(ss1970)->spin_GSE[0]);
}

float a3goa_spin_GSE_y(double ss1970) {
  return(a3goa(ss1970)->spin_GSE[1]);
}

float a3goa_spin_GSE_z(double ss1970) {
  return(a3goa(ss1970)->spin_GSE[2]);
}

/* Heliocentric Solar Ecliptic (Earth Oriented) (HSEb) Coordinates
   Coordinates are centered at the Sun.
   x -- points toward the Earth along the Earth-Sun line
   z -- points toward ecliptic north pole (same dir. as Earth's North pole), 
        normal to the orbital plane (ecliptic) of the Earth
   y -- normal to x and z, points so that rotating x into y points along z
        via the right hand rule.  (This makes a right-handed coordinate 
	system.) 
*/
/* Attitude coordinates */
float a3goa_att_HSEb_x(double ss1970){
  return(a3goa(ss1970)->att_HSEb[0]);
}

float a3goa_att_HSEb_y(double ss1970) {
  return(a3goa(ss1970)->att_HSEb[1]);
}

float a3goa_att_HSEb_z(double ss1970) {
  return(a3goa(ss1970)->att_HSEb[2]);
}


/* Position coordinates */
float a3goa_pos_HSEb_x(double ss1970) {
  return(a3goa(ss1970)->pos_HSEb[0]);
}

float a3goa_pos_HSEb_y(double ss1970) {
  return(a3goa(ss1970)->pos_HSEb[1]);
}

float a3goa_pos_HSEb_z(double ss1970) {
  return(a3goa(ss1970)->pos_HSEb[2]);
}


/* Spin */
float a3goa_spin_HSEb_x(double ss1970) {
  return(a3goa(ss1970)->spin_HSEb[0]);
}

float a3goa_spin_HSEb_y(double ss1970) {
  return(a3goa(ss1970)->spin_HSEb[1]);
}

float a3goa_spin_HSEb_z(double ss1970) {
  return(a3goa(ss1970)->spin_HSEb[2]);
}

/* Radial Tangential Normal (RTN) Coordinates
   Spacecraft centered coordinate system. 
   r = Sun to Spacecraft unit vector 
   t = (Omega x r) / | (Omega x r) |
       where Omega is Sun's spin axis (in J2000 GCI)
   n completes the right-handed triad 
*/
/* Attitude coordinates */
/* get RTN attitude cosine with respect to r */
float a3goa_att_RTN_r(double ss1970){
  return(a3goa(ss1970)->att_RTN[0]);
}

/* get RTN attitude cosine with respect to t */
float a3goa_att_RTN_t(double ss1970) {
  return(a3goa(ss1970)->att_RTN[1]);
}

/* get RTN attitude cosine with respect to n */
float a3goa_att_RTN_n(double ss1970) {
  return(a3goa(ss1970)->att_RTN[2]);
}


/* Spin coordinates */
/* get RTN spin r */
float a3goa_spin_RTN_r(double ss1970) {
  return(a3goa(ss1970)->spin_RTN[0]);
}

float a3goa_spin_RTN_t(double ss1970) {
  return(a3goa(ss1970)->spin_RTN[1]);
}

float a3goa_spin_RTN_n(double ss1970) {
  return(a3goa(ss1970)->spin_RTN[2]);
}

