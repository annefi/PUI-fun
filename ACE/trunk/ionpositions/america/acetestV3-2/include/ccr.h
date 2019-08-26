/* $Id: ccr.h,v 1.4 1998/10/20 22:30:09 asc Exp $ */
#include "hdfi.h"

/* The values here are used to convert the S/C clock values into seconds */
/* since the S/C EPOCH, which was a short time after ACE launch */
/* S/C_EPOCH_TIME = SC_clock * SLOPE + OFFSET */

/* The offset between S/C_EPOCH and ACE_EPOCH is 52069704.604 seconds */
/* ACE_EPOCH is seconds since Jan 1, 1996 */

/* the start and end variables indicate the range of validity of the */
/* slope and offset data. Generally, the ACE Flight Dynamics team will */
/* generate a new set of parameters for each 24-hour period */

struct ccr_entry {
    uint32   start;    /* Start of range in S/C clock ticks */
    uint32   end;      /* End of range in S/C clock ticks */
    float64  slope;    /* slope for linear fit */
    float64  offset;   /* offset for linear fit */
    uint8    cdh;      /* =1: C&DH A, =2: C&DH B, error otherwise */
    uint16   year;     /* 4 digit year for product */
    uint16   doy;      /* Day of Year for product */
};
