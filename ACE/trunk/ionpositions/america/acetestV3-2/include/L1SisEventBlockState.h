/* $Id: L1SisEventBlockState.h,v 1.2 1998/02/06 23:15:42 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisEventBlockState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1998/02/06 23:15:42 $ */
/* $Revision: 1.2 $ */

#define NAGE        MAX_SIS_EVT_AGE
#define NBLOCK      MAX_SIS_EVT_AGE + SIZE_SIS_CYCLE_QUEUE
#define NMNF        NUM_SIS_MNFS_PER_CYCLE
#define NTELEMETRY  NUM_SIS_TELEMETRY_BYTES

#define NARRAY      NTELEMETRY*NMNF
#define NEVENT      NMNF*MAX_NUM_SIS_EVENTS_PER_MNF

struct L1SisEventBlock {
   uint32 ClockCycle;
   uint32 CycleNumber;
   uint32 ResetNumber;
   uint16 NumberEventBytes;
   uint16 NumberEvents[NAGE];
   uint16 NumberEventsTotal;
   uint16 EventIndex[NEVENT];
   uint8  EventArray[NARRAY];
   uint8  EventAge[NEVENT];
   uint8  EventMnf[NEVENT];
   uint8  EventLocation[NEVENT];
   uint8  NumberBorrowedBytes;
};


struct L1SisEventBlockState {
   uint32 NumberEventBlocks;
   struct L1SisEventBlock block[NBLOCK];
   uint32 NumberEventCycles;
};

#undef NAGE
#undef NBLOCK
#undef NMNF
#undef NTELEMETRY
#undef NARRAY
#undef NEVENT
