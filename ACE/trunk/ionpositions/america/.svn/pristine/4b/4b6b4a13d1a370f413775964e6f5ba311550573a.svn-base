/* $Id: L1SisDiagEventState.h,v 1.1 1997/08/11 03:06:15 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisDiagEventState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 03:06:15 $ */
/* $Revision: 1.1 $ */

#define NDIAG       MAX_NUM_SIS_DIAG_BYTES
#define NRECORD     SIZE_SIS_DIAG_EVENT_QUEUE
#define NTELEMETRY  NUM_SIS_TELEMETRY_BYTES

struct L1SisDiagEventState {
                        uint32  NumberSubsetsExamined;
                        uint32  NumberRecords;
                        uint32  NumberRecordsWritten;
                        uint32  NumberBytes;
                        uint32  ClockMinorFrame0;
                        uint32  ClockMinorFrame1;
                         uint8  DiagBuffer[NDIAG + NTELEMETRY];
                         uint8  mnf[NTELEMETRY];
   struct L1SisDiagnosticEvent  diag[NRECORD];
};

#undef NDIAG
#undef NRECORD
#undef NTELEMETRY
