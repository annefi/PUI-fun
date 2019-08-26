/* $Id: L1SisSubset.h,v 1.2 1997/09/11 16:50:59 jeff Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisSubset.h,v $ */
/* $Author: jeff $ */
/* $Date: 1997/09/11 16:50:59 $ */
/* $Revision: 1.2 $ */

#include "hdfi.h"
#include "SisConstants.h"


struct L1SisSubset
{
   uint32 ClockMinorFrame;
   uint32 Second1996;
   uint32 microsecond;
   uint8  FormatId;
   uint8  MajorFrameCount;
   uint8  MinorFrameCount;
   uint8  quality;
   uint8  MainBusVoltage;
   uint8  SisCurrent;
   uint8  SisInternalTemperature1;
   uint8  SisInternalTemperature2;
   uint8  SisInterfaceTemperature;
   uint8  SisCoverTelltale;
   uint8  SisData[NUM_SIS_TELEMETRY_BYTES];
};


/* Definition:                                                       */
/*    ClockMinorFrame = S/C clock of the minor frame                 */
/*    Second1996 = Time of the minor frame in seconds since 00:00:00 */
/*                 of January 1, 1996                                */
/*    microsecond = Microseconds of the time of the minor frame      */
/*    FormatId = Format of the minor frame                           */
/*    MajorFrameCount = Major frame count of the minor frame         */
/*    MinorFrameCount = Minor frame count of the minor frame         */
/*    quality = Quality flag associated with the subset              */
/*              0x01 = Format ID error                               */
/*              0x02 = Minor/major counter error                     */
/*              0x04 = S/C clock error                               */
/*              0x08 = Sync bit error                                */
/*              0x10 = Command table index error                     */
/*              0x20 = Cycle number error                            */
/*              0x40 = Level 0 quality bit                           */
/*              0x80 = Level 1 quality bit                           */
/*    MainBusVoltage = Main bus voltage value (255=no data)          */
/*    SisCurrent = SIS I/F & survial heater current (255=no data)    */
/*    SisInternalTemperature1 = SIS internal temperature 1           */
/*                              (255=no data)                        */
/*    SisInternalTemperature2 = SIS internal temperature 2           */
/*                              (255=no data)                        */
/*    SisInterfaceTemperature = SIS interface temperature            */
/*                              (255=no data)                        */
/*    SisCoverTelltale = SIS cover telltale (255=no data)            */
/*    SisData = SIS data                                             */

/* Note: This structure is only written when the instrument is in    */
/*       diagnostic mode and/or command response mode.               */
