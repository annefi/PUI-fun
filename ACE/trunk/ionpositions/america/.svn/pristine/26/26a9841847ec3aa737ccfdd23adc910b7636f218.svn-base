/* $Id: L1SisDacOffset0State.h,v 1.1 1997/08/11 03:05:18 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisDacOffset0State.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 03:05:18 $ */
/* $Revision: 1.1 $ */

#define NRECORD   MAX_SIS_EVT_AGE + SIZE_SIS_CYCLE_QUEUE

struct L1SisDacOffset0State {
                   uint32  NumberCyclesExamined;
                   uint32  NumberRecords;
                   uint32  NumberRecordsWritten;
   struct L1SisDacOffset0  matrix[NRECORD];
   struct L1SisDacOffset0  PreviousMatrix;
};

#undef NRECORD
