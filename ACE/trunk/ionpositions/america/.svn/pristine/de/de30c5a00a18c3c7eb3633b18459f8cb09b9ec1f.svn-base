/* $Id: L1CrisDiagEventState.h,v 1.1 1997/08/11 02:41:37 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisDiagEventState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 02:41:37 $ */
/* $Revision: 1.1 $ */

#define NDIAG       MAX_NUM_CRIS_DIAG_BYTES
#define NRECORD     SIZE_CRIS_DIAG_EVENT_QUEUE
#define NTELEMETRY  NUM_CRIS_TELEMETRY_BYTES

struct L1CrisDiagEventState {
                         uint32  NumberSubsetsExamined;
                         uint32  NumberRecords;
                         uint32  NumberRecordsWritten;
                         uint32  NumberBytes;
                         uint32  ClockMinorFrame0;
                         uint32  ClockMinorFrame1;
                          uint8  DiagBuffer[NDIAG + NTELEMETRY];
                          uint8  mnf[NTELEMETRY];
   struct L1CrisDiagnosticEvent  diag[NRECORD];
};

#undef NDIAG
#undef NRECORD
#undef NTELEMETRY
