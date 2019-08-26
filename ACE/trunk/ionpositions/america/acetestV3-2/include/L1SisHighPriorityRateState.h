/* $Id: L1SisHighPriorityRateState.h,v 1.1 1997/08/11 03:09:36 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisHighPriorityRateState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 03:09:36 $ */
/* $Revision: 1.1 $ */

#define NSAMPLE   NUM_SIS_HIGH_PRIORITY_SAMPLES
#define NRECORD   (NSAMPLE * (MAX_SIS_EVT_AGE + SIZE_SIS_CYCLE_QUEUE))

struct L1SisHighPriorityRateState {
                         uint32  NumberCyclesExamined;
                         uint32  NumberRecords;
                         uint32  NumberRecordsWritten;
   struct L1SisHighPriorityRate  rate[NRECORD];
};

#undef NSAMPLE
#undef NRECORD
