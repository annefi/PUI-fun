/* $Id: uleis_rate.h,v 1.5 1997/04/10 22:19:24 steves Exp $ */

#include "hdfi.h"

#define U_SPINS               10 	/* 10 spins, 1-10 */
#define U_SPINPRS              5	/* 5 spin pairs 1-5 */
#define U_SECTRS               8	/* 8 sectors, 0-7 */
#define U_MTRX_RATE_SIZE      34	/* 34 bytes per sector */
#define U_MTRX_PRS_RATE_SIZE  42	/* 42 bytes per sector */
#define U_SNGL_RATE_SIZE      16        /* 16 2-byte items per sector */

struct URateSet
{
  uint32 output_sctime;		/* time for beginning of data output cycle */
  uint32 collect_sctime;	/* time for beginning of data collection */
  uint32 QAC;			/* number of bad frames in this cycle */

  /* Matrix rates: 34 bytes, 10 spins, 8 sectors */
  uint8 Matrx[U_MTRX_RATE_SIZE][U_SPINS][U_SECTRS];

  /* Matrix pair rates: 42 bytes, 5 spin pairs, 8 sectors */
  uint8 Matrx_prs[U_MTRX_PRS_RATE_SIZE][U_SPINPRS][U_SECTRS];

  /* Singles rates:  32 bytes, 5 spin pairs, 8 sectors */
  uint16 Single[U_SNGL_RATE_SIZE][U_SPINPRS][U_SECTRS];
};

