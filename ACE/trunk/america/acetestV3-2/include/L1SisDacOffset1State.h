/* $Id: L1SisDacOffset1State.h,v 1.1 1997/08/11 03:05:36 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisDacOffset1State.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 03:05:36 $ */
/* $Revision: 1.1 $ */

#define NRECORD   MAX_SIS_EVT_AGE + SIZE_SIS_CYCLE_QUEUE

struct L1SisDacOffset1State {
                   uint32  NumberCyclesExamined;
                   uint32  NumberRecords;
                   uint32  NumberRecordsWritten;
   struct L1SisDacOffset1  matrix[NRECORD];
   struct L1SisDacOffset1  PreviousMatrix;
};

#undef NRECORD
