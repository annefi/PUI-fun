/* $Id: L1SisCommandEchoState.h,v 1.1 1997/08/11 03:02:29 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisCommandEchoState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 03:02:29 $ */
/* $Revision: 1.1 $ */

#define NRECORD     SIZE_SIS_CMD_ECHO_QUEUE
#define NTELEMETRY  NUM_SIS_TELEMETRY_BYTES

struct L1SisCommandEchoState {
                    uint32  NumberSubsetsExamined;
                    uint32  NumberRecords;
                    uint32  NumberRecordsWritten;
                     uint8  mnf[NTELEMETRY];
   struct L1SisCommandEcho  echo[NRECORD];
};

#undef NRECORD
#undef NTELEMETRY
