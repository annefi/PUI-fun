/* $Id: L1CrisCommandEchoState.h,v 1.1 1997/08/11 02:39:37 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisCommandEchoState.h,v $ */
/* $Author: rgr $ */
/* $Date: 1997/08/11 02:39:37 $ */
/* $Revision: 1.1 $ */

#define NRECORD     SIZE_CRIS_CMD_ECHO_QUEUE
#define NTELEMETRY  NUM_CRIS_TELEMETRY_BYTES

struct L1CrisCommandEchoState {
                     uint32  NumberSubsetsExamined;
                     uint32  NumberRecords;
                     uint32  NumberRecordsWritten;
                      uint8  mnf[NTELEMETRY];
   struct L1CrisCommandEcho  echo[NRECORD];
};

#undef NRECORD
#undef NTELEMETRY
