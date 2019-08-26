/* $Id: L1CrisLowPriorityRateState.h,v 1.1 1997/08/11 02:46:07 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisLowPriorityRateState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 02:46:07 $ */
/* $Revision: 1.1 $ */

#define NRECORD   MAX_CRIS_EVT_AGE + SIZE_CRIS_CYCLE_QUEUE

struct L1CrisLowPriorityRateState {
                          uint32  NumberCyclesExamined;
                          uint32  NumberRecords;
                          uint32  NumberRecordsFilled;
                          uint32  NumberRecordsWritten;
                          uint32  NumberBrowseRecords;
    struct L1CrisLowPriorityRate  rate[NRECORD];
};

#undef NRECORD
