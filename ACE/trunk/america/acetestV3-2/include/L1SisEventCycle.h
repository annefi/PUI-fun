/* $Id: L1SisEventCycle.h,v 1.3 1997/09/11 16:50:59 jeff Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisEventCycle.h,v $ */
/* $Author: jeff $ */
/* $Date: 1997/09/11 16:50:59 $ */
/* $Revision: 1.3 $ */

#include "hdfi.h"
#include "SisConstants.h"

struct L1SisEventCycle
{
   uint32 ClockCycle;
   uint32 Second1996;
   uint32 microsecond;
   uint16 NumberNormalEventBytes[MAX_SIS_EVT_AGE];
   uint16 NumberEvents;
   uint8  EventBuffer[SIZE_SIS_EVENT_BUFFER];
   uint8  ContinuationFlag;
};


/* Definition:                                                       */
/*    ClockCycle = S/C clock of the first minor frame of the cycle   */
/*                 in which SIS processed the events                 */
/*    NumberNormalEventBytes = Number of bytes in each of the cycles */
/*                             that is used for normal event         */
/*                             transmision                           */
/*    NumberEvents = Number of events stored in the event buffer     */
/*    EventBuffer = Event buffer                                     */
/*    ContinuationFlag = Flag indicating events from this cycle are  */
/*                       continued in the next structure             */
/*                                                                   */
/* Note: Each event in the event buffer is preceded by two bytes.    */
/*       The first is the relative age of the event.  The second is  */
/*       minor frame in which the first byte of the event was        */
/*       transmitted.                                                */
