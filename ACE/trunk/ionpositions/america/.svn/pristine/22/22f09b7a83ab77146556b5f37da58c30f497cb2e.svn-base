/* $Id: uleis_dump.h,v 1.6 1997/05/09 22:04:40 steves Exp $ */

#include "hdfi.h"

#define U_DUMP_SIZE    125	/* Memory dump size in bytes */

struct UDumpSet
{
  uint32 output_sctime;		/* time for beginning of data output cycle */
  uint32 collect_sctime;	/* time for beginning of data collection */
  uint32 QAC;			/* number of bad frames in this cycle */

  uint16 dumptime_offset;	/* offset for output_sctime for dump */
  uint8 dump[U_DUMP_SIZE];      /* dump: 125 bytes */

};
