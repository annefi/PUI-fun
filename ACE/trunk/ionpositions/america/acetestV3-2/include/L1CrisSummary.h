/* $Id: L1CrisSummary.h,v 1.3 1997/09/11 00:37:38 jeff Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisSummary.h,v $ */
/* $Author: jeff $ */
/* $Date: 1997/09/11 00:37:38 $ */
/* $Revision: 1.3 $ */

#include "hdfi.h"
#include "CrisConstants.h"

struct L1CrisSummary
{
   uint32  ClockMinorFrame;
   uint32  Second1996;
   uint32  microsecond;
    uint8  FormatId;
    uint8  MajorFrameCount;
    uint8  MinorFrameCount;
    uint8  quality;
    uint8  MainBusVoltage;
    uint8  CrisCurrent;
    uint8  CrisInternalTemperature1;
    uint8  CrisInternalTemperature2;
    uint8  CrisInterfaceTemperature;
    uint8  CrisHskp[NUM_CRIS_HSKP_BYTES];
};


/* Definition:                                                       */
/*    ClockMinorFrame = S/C clock of the minor frame                 */
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
/*    CrisInternalTemperature1 = CRIS internal temperature 1         */
/*                              (255=no data)                        */
/*    CrisInternalTemperature2 = CRIS internal temperature 2         */
/*                              (255=no data)                        */
/*    CrisInterfaceTemperature = CRIS interface temperature          */
/*                              (255=no data)                        */
/*    CrisHskp = Housekeeping/rate bytes from CRIS telemetry         */
