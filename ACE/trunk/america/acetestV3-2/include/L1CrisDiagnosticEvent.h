/* $Id: L1CrisDiagnosticEvent.h,v 1.2 1997/09/11 16:50:59 jeff Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisDiagnosticEvent.h,v $ */
/* $Author: jeff $ */
/* $Date: 1997/09/11 16:50:59 $ */
/* $Revision: 1.2 $ */

#include "hdfi.h"
#include "CrisConstants.h"

struct L1CrisDiagnosticEvent
{
   uint32 ClockMinorFrame0;
   uint32 ClockMinorFrame1;
   uint32 Second1996MinorFrame0;
   uint32 MicrosecondMinorFrame0;
   uint32 Second1996MinorFrame1;
   uint32 MicrosecondMinorFrame1;
   uint16 RawStack[NUM_CRIS_RAW_STACK_EVT_BYTES/2];
   uint16 SoftEvent[NUM_CRIS_RAW_SOFT_EVT_BYTES/2];
   uint8  NormalEvent[MAX_NUM_CRIS_EVENT_BYTES];
   uint8  ContinuationFlag;
};


/* Definition:                                                       */
/*    ClockMinorFrame = S/C clock of the minor frame containing the  */
/*                      start of the diagnostic event                */
/*    RawStack = Raw stack event portion of the diagnostic event     */
/*    SoftEvent = Raw SOFT event portion of the diagnostic event     */
/*    NormalEvent = Normal event portion of the diagnostic event     */
/*    ContinuationFlag = Flag indicating the SOFT portion of the     */
/*                       event is continued in the next cycle        */
