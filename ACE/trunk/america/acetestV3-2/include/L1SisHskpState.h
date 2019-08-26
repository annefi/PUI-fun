/* $Id: L1SisHskpState.h,v 1.1 1997/08/11 03:10:14 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisHskpState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 03:10:14 $ */
/* $Revision: 1.1 $ */

#define NAGE      MAX_SIS_EVT_AGE
#define NHSKP     NUM_SIS_HSKP_BYTES
#define NMNF      NUM_SIS_MNFS_PER_CYCLE

#define NDEFAULT  NHSKP*NMNF
#define NRECORD   MAX_SIS_EVT_AGE + SIZE_SIS_CYCLE_QUEUE

struct L1SisHskpState {
             uint32 NumberCyclesExamined;
             uint32 NumberRecords;
             uint32 NumberRecordsWritten;
   struct L1SisHskp hskp[NRECORD];
};

#undef NAGE
#undef NHSKP
#undef NMNF

#undef NDEFAULT
#undef NRECORD
