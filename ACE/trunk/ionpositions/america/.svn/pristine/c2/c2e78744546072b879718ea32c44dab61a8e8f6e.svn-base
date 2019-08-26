/* $Id: L1CrisSubset.h,v 1.2 1997/09/11 00:37:38 jeff Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisSubset.h,v $ */
/* $Author: jeff $ */
/* $Date: 1997/09/11 00:37:38 $ */
/* $Revision: 1.2 $ */

#include "hdfi.h"
#include "CrisConstants.h"

struct L1CrisSubset
{
   uint32 ClockMinorFrame;
   uint32 Second1996;
   uint32 microsecond;
   uint8  FormatId;
   uint8  MajorFrameCount;
   uint8  MinorFrameCount;
   uint8  quality;
   uint8  MainBusVoltage;
   uint8  CrisCurrent;
   uint8  CrisInternalTemperature1;
   uint8  CrisInternalTemperature2;
   uint8  CrisInterfaceTemperature;
   uint8  CrisData[NUM_CRIS_TELEMETRY_BYTES];
};


/* Definition:                                                       */
/*    ClockMinorFrame = S/C clock of the minor frame                 */
/*    Second1996 = Time of the minor frame in seconds since 00:00:00 */
/*                 of January 1, 1996                                */
/*    microsecond = Microseconds of the time of the minor frame      */
/*    FormatId = Format of the minor frame                           */
/*    MajorFrameCount = Major frame count of the minor frame         */
/*    MinorFrameCount = Minor frame count of the minor frame         */
/*    quality = Quality flag associated with the minor frame         */
/*              0x01 = Format ID error                               */
/*              0x02 = Minor/major counter error                     */
/*              0x04 = S/C clock error                               */
/*              0x08 = Sync bit error                                */
/*              0x10 = Command table index error                     */
/*              0x20 = Cycle number error                            */
/*              0x40 = Level 0 quality bit                           */
/*              0x80 = Level 1 quality bit                           */
/*    MainBusVoltage = Main bus voltage value (255=no data)          */
/*    CrisCurrent = CRIS I/F & survial heater current (255=no data)  */
/*    CrisInternalTemperature1 =                                     */
/*                         CRIS internal temperature 1 (255=no data) */
/*    CrisInternalTemperature2 =                                     */
/*                         CRIS internal temperature 2 (255=no data) */
/*    CrisInterfaceTemperature =                                     */
/*                         CRIS interface temperature (255=no data)  */
/*    CrisData = CRIS data                                           */

/* Note: This structure is only written when the instrument is in    */
/*       diagnostic mode and/or command response mode.               */
