/* $Id: uleis_evnt.h,v 1.8 1997/06/11 17:09:21 jeff Exp $ */

#include "hdfi.h"

#define U_BYT_EVNT_SIZE    21		/* 21 bytes per event */
#define U_EVNT_NUM         14		/* number of 12 bit events */
#define U_EVTSECTR          6 		/* 6 events per sector */
#define U_SECTRS            8		/* 8 sectors, 0-7 */
#define U_SPINS            10 		/* 10 spins, 1-10 */
 

struct UEvntSet
{
  uint32 output_sctime;		/* time for beginning of data output cycle */
  uint32 collect_sctime;	/* time for beginning of data collection */
  uint32 QAC;			/* number of bad frames in this cycle */

   /* Events: 10 spins, 8 sectors, 6 events, event num (14) */
  uint16 event[U_SPINS][U_SECTRS][U_EVTSECTR][U_EVNT_NUM];
};
