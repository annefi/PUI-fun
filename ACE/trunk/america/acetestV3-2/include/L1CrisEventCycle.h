/* $Id: L1CrisEventCycle.h,v 1.3 1997/09/11 00:37:38 jeff Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisEventCycle.h,v $ */
/* $Author: jeff $ */
/* $Date: 1997/09/11 00:37:38 $ */
/* $Revision: 1.3 $ */

#include "hdfi.h"
#include "CrisConstants.h"

struct L1CrisEventCycle
{
   uint32 ClockCycle;
   uint32 Second1996;
   uint32 microsecond;
   uint16 NumberNormalEventBytes[MAX_CRIS_EVT_AGE];
   uint16 NumberEvents;
   uint8  EventBuffer[SIZE_CRIS_EVENT_BUFFER];
   uint8  ContinuationFlag;
};


/* Definition:                                                       */
/*    ClockCycle = S/C clock of the first minor frame of the cycle   */
/*                 in which CRIS processed the event                 */
/*    NumberNormalEventBytes = Number of bytes used for normal event */
/*                             processing from each of the cycles    */
/*                             that can contribute events to this    */
/*                             structure.                            */
/*    NumberEvents = Number of events stored in the event buffer     */
/*    EventBuffer = Event buffer                                     */
/*    ContinuationFlag = Flag indicating events from this cycle are  */
/*                       continued in the next structure             */
/*                                                                   */
/* Note: Each event in the event buffer is preceded by two bytes.    */
/*       The first is the relative age of the event in cycles.  The  */
/*       second is the minor frame in which the first byte of the    */
/*       event was transmitted.                                      */
