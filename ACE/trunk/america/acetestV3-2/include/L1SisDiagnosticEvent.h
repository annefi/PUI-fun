/* $Id: L1SisDiagnosticEvent.h,v 1.2 1997/09/11 16:50:59 jeff Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisDiagnosticEvent.h,v $ */
/* $Author: jeff $ */
/* $Date: 1997/09/11 16:50:59 $ */
/* $Revision: 1.2 $ */

#include "hdfi.h"
#include "SisConstants.h"

struct L1SisDiagnosticEvent
{
   uint32 ClockMinorFrame0;
   uint32 ClockMinorFrame1;
   uint32 Second1996MinorFrame0;
   uint32 MicrosecondMinorFrame0;
   uint32 Second1996MinorFrame1;
   uint32 MicrosecondMinorFrame1;
   uint16 RawStack[NUM_SIS_RAW_STACK_EVT_BYTES/2];
   uint8  NormalEvent[MAX_NUM_SIS_EVENT_BYTES];
};


/* Definition:                                                       */
/*    ClockMinorFrame0 = S/C clock of the minor frame containing     */
/*                       the start of the diagnostic event           */
/*    ClockMinorFrame1 = S/C clock of the minor frame containing     */
/*                       the end of the diagnostic event             */
/*    RawStack = Raw stack event portion of the diagnostic event     */
/*    NormalEvent = Normal event portion of the diagnostic event     */
