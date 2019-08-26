/* $Id: L1SisCycleState.h,v 1.1 1997/08/11 03:03:46 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisCycleState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 03:03:46 $ */
/* $Revision: 1.1 $ */

#define NCYCLE      SIZE_SIS_CYCLE_QUEUE
#define NHSKP       NUM_SIS_HSKP_BYTES
#define NMNF        NUM_SIS_MNFS_PER_CYCLE
#define NTELEMETRY  NUM_SIS_TELEMETRY_BYTES

struct L1SisCycleSummary {
   uint32 ClockCycle;
   uint32 CycleNumber;
   uint32 CtIndex;
   uint32 ResetNumber;
    uint8 cycle[NTELEMETRY * NMNF];
    uint8 quality[NTELEMETRY * NMNF];
};

struct L1SisCycleState {
    struct L1SisCycleSummary summary[NCYCLE];
                      uint32 NumberCyclesUnfiltered;
                      uint32 NumberCycles;
          struct L1SisSubset SubsetQueue[NMNF + 2];
                      uint32 NumberSubsets;
                      uint32 NumberQueuedSubsets;
                      uint32 IndexQueue;
                       uint8 DefaultValue[NHSKP*NMNF];
};

#undef NCYCLE
#undef NHSKP
#undef NMNF
#undef NTELEMETRY
