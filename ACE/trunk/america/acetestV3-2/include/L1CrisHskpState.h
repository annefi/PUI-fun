/* $Id: L1CrisHskpState.h,v 1.1 1997/08/11 02:45:42 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisHskpState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 02:45:42 $ */
/* $Revision: 1.1 $ */


#define NRECORD   MAX_CRIS_EVT_AGE + SIZE_CRIS_CYCLE_QUEUE

struct L1CrisHskpState {
              uint32 NumberCyclesExamined;
              uint32 NumberRecords;
              uint32 NumberRecordsWritten;
   struct L1CrisHskp hskp[NRECORD];
};

#undef NRECORD
