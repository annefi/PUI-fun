/* $Id: L1CrisHighPriorityRateState.h,v 1.1 1997/08/11 02:44:56 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisHighPriorityRateState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 02:44:56 $ */
/* $Revision: 1.1 $ */

#define NSAMPLE   NUM_CRIS_HIGH_PRIORITY_SAMPLES
#define NRECORD   (NSAMPLE * (MAX_CRIS_EVT_AGE+SIZE_CRIS_CYCLE_QUEUE))

struct L1CrisHighPriorityRateState {
                          uint32  NumberCyclesExamined;
                          uint32  NumberRecords;
                          uint32  NumberRecordsWritten;
   struct L1CrisHighPriorityRate  rate[NRECORD];
};

#undef NSAMPLE
#undef NRECORD
