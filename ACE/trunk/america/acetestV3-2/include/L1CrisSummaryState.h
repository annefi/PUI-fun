/* $Id: L1CrisSummaryState.h,v 1.1 1997/08/11 02:47:54 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisSummaryState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 02:47:54 $ */
/* $Revision: 1.1 $ */

#define NRECORD  SIZE_CRIS_SUMMARY_QUEUE

struct L1CrisSummaryState {
                 uint32  NumberSubsetsExamined;
                 uint32  NumberRecords;
                 uint32  NumberRecordsWritten;
   struct L1CrisSummary  summary[NRECORD];
};

#undef NRECORD
