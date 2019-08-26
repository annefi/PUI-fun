/* $Id: L1CrisEventBlockState.h,v 1.2 1998/02/06 23:14:33 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisEventBlockState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1998/02/06 23:14:33 $ */
/* $Revision: 1.2 $ */

#define NAGE        MAX_CRIS_EVT_AGE
#define NBLOCK      MAX_CRIS_EVT_AGE + SIZE_CRIS_CYCLE_QUEUE
#define NMNF        NUM_CRIS_MNFS_PER_CYCLE
#define NTELEMETRY  NUM_CRIS_TELEMETRY_BYTES

#define NARRAY      NTELEMETRY*NMNF
#define NEVENT      NMNF*MAX_NUM_CRIS_EVENTS_PER_MNF

struct L1CrisEventBlock {
   uint32 ClockCycle;
   uint32 CycleNumber;
   uint32 ResetNumber;
   uint32 NumberVotes[NAGE];
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


struct L1CrisEventBlockState {
   uint32 NumberEventBlocks;
   struct L1CrisEventBlock block[NBLOCK];
   uint32 NumberEventCycles;
};

#undef NAGE
#undef NBLOCK
#undef NMNF
#undef NTELEMETRY

#undef NARRAY
#undef NEVENT
