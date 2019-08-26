/* $Id: L1SisCommandTableState.h,v 1.1 1997/08/11 03:03:10 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisCommandTableState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 03:03:10 $ */
/* $Revision: 1.1 $ */

#define NBYTE    NUM_SIS_CMD_TAB_BYTES
#define NRECORD  SIZE_SIS_CMD_TAB_QUEUE

struct L1SisCommandTableState {
                     uint32  NumberCyclesExamined;
                     uint32  NumberRecords;   
                     uint32  NumberRecordsWritten;   
   struct L1SisCommandTable  CommandTable[NRECORD];
                     uint32  ClockMinorFrame0;
                     uint32  ClockMinorFrame1;
                     uint32  ResetNumber;  
                      uint8  CurrentCommandTable[NBYTE];
                      uint8  PreviousCommandTable[NBYTE];
                      uint8  quality[NBYTE];
};

#undef NBYTE
#undef NRECORD
