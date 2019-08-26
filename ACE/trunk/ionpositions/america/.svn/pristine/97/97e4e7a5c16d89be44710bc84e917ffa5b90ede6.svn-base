/* $Id: L1SisLowPriorityRateState.h,v 1.2 2000/11/03 03:53:30 rgr Exp $ */

/* $Source: /users/asc/aceprog/include/RCS/L1SisLowPriorityRateState.h,v $ */
/* $Author: rgr $ */
/* $Date: 2000/11/03 03:53:30 $ */
/* $Revision: 1.2 $ */

#define NRECORD   MAX_SIS_EVT_AGE + SIZE_SIS_CYCLE_QUEUE

struct L1SisLowPriorityRateState {
                                uint32  NumberCyclesExamined;
                                uint32  NumberRecords;
                                uint32  NumberRecordsFilled;
                                uint32  NumberRecordsWritten;
                                uint32  NumberBrowseRecords;
   struct L1SisLowPriorityRateExtended  rate[NRECORD];
};

#undef NRECORD
