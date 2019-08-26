/* $Id: uleis_stat_tlm.h,v 1.5 1998/03/24 19:06:51 asc Exp $*/

#include "hdfi.h"

#define U_STAT_TLM_SIZE    125		/* Status TLM length 125 bytes */

struct UStatTLMSet
{

  uint32 output_sctime;		/* time for beginning of data output cycle */
  uint32 collect_sctime;	/* time for beginning of data collection */
  uint32 QAC;			/* number of bad frames in this cycle */

  uint16 stattlmtime_offset;	/* offset for output_sctime for Status TLM */

     /* Status TLM: 125 bytes */
  uint8  StatusTLM[U_STAT_TLM_SIZE];

};
