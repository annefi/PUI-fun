/* $Id: L1CrisCycleState.h,v 1.1 1997/08/11 02:41:04 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisCycleState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 02:41:04 $ */
/* $Revision: 1.1 $ */

#define NCYCLE      SIZE_CRIS_CYCLE_QUEUE
#define NHSKP       NUM_CRIS_HSKP_BYTES
#define NMNF        NUM_CRIS_MNFS_PER_CYCLE
#define NTELEMETRY  NUM_CRIS_TELEMETRY_BYTES

struct L1CrisCycleSummary {
   uint32 ClockCycle;
   uint32 CycleNumber;
   uint32 CtIndex;
   uint32 ResetNumber;
    uint8 cycle[NTELEMETRY * NMNF];
    uint8 quality[NTELEMETRY * NMNF];
};

struct L1CrisCycleState {
    struct L1CrisCycleSummary summary[NCYCLE];
                       uint32 NumberCyclesUnfiltered;
                       uint32 NumberCycles;
          struct L1CrisSubset SubsetQueue[NMNF + 2];
                       uint32 NumberSubsets;
                       uint32 NumberQueuedSubsets;
                       uint32 IndexQueue;
                        uint8 DefaultValue[NHSKP*NMNF];
};

#undef NCYCLE
#undef NHSKP
#undef NMNF
#undef NTELEMETRY
