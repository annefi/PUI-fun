/* $Id: epam_brconst.h,v 1.8 2002/02/19 22:10:30 ad Exp $ */

#include "hdfi.h"

#define EPAMRATES 8

/* rate indicies, {0,1,2,3,4,5,6,7} = {P1,P3,P5,P7,DE1,DE4,W1,fp6p} */

static uint16 epam_rn[EPAMRATES][8]=       /* rate number locations */
{ 23,131,203,452,0,0,0,0,
 25,133,205,454,0,0,0,0,
 211,460,0,0,0,0,0,0,
 213,462,0,0,0,0,0,0,
 218,301,384,467,0,0,0,0,
 221,304,387,470,0,0,0,0,
 163,246,329,412,195,278,361,444,
 157,240,323,406,189,272,355,438};

/* number of values per rate per spin pair */
static uint8 epam_rs[EPAMRATES]={4,4,2,2,4,4,8,8};

/* width of energy band in kev */
static uint16 epam_eb[EPAMRATES]={18, 75, 270, 850, 15, 140, 486, 459};

/* geometry factors (cm^2 - sr) */
static float32 epam_geom[EPAMRATES]={.428, .428, .428, .428, .14, .14, .103, .397};
