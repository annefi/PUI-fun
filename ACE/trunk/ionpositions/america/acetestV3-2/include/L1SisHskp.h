/* $Id: L1SisHskp.h,v 1.2 1997/09/11 16:50:59 jeff Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisHskp.h,v $ */
/* $Author: jeff $ */
/* $Date: 1997/09/11 16:50:59 $ */
/* $Revision: 1.2 $ */

#include "hdfi.h"
#include "SisConstants.h"

struct L1SisHskp
{
   uint32 ClockCycle;
   uint32 Second1996;
   uint32 microsecond;
   uint32 CycleNumber;
   uint16 CommandTableIndex;
   uint16 MonitorP4V;
   uint16 MonitorP5V;
   uint16 MonitorP7V;
   uint16 MonitorM7V;
   uint16 MonitorP13V;
   uint16 MonitorM13V;
   uint16 MonitorP19V;
   uint16 MonitorCurrentA;
   uint16 MonitorCurrentB;
   uint16 TemperatureMotherBoard;
   uint16 TemperatureAnalogBoard;
   uint16 TemperaturePostRegBoard;
   uint16 TemperatureLogicBoard;
   uint16 TemperatureLvpsBoard;
   uint16 TemperatureHvpsBoard;
   uint16 TemperatureM1aBoard;
   uint16 TemperatureM2bBoard;
   uint16 TemperatureT12aBoard;
   uint16 TemperatureT34aBoard;
   uint16 TemperatureT56aBoard;
   uint16 TemperatureT78aBoard;
   uint16 TemperatureT12bBoard;
   uint16 TemperatureT34bBoard;
   uint16 TemperatureT56bBoard;
   uint16 TemperatureT78bBoard;
   uint16 PostDcT1a;
   uint16 PostDcT2a;
   uint16 PostDcT3a;
   uint16 PostDcT4a;
   uint16 PostDcT5a;
   uint16 PostDcT6a;
   uint16 PostDcT7a;
   uint16 PostDcT8a;
   uint16 PostDcT1b;
   uint16 PostDcT2b;
   uint16 PostDcT3b;
   uint16 PostDcT4b;
   uint16 PostDcT5b;
   uint16 PostDcT6b;
   uint16 PostDcT7b;
   uint16 PostDcT8b;
   uint8  StatusTelemetrySide;
   uint8  StatusRefreshEnable;
   uint8  StatusHeatAuto;
   uint8  StatusHeatLevel;
   uint8  QualityCycleNumber;
   uint8  QualityCommandTableIndex;
   uint8  QualityMonitorP4V;
   uint8  QualityMonitorP5V;
   uint8  QualityMonitorP7V;
   uint8  QualityMonitorM7V;
   uint8  QualityMonitorP13V;
   uint8  QualityMonitorM13V;
   uint8  QualityMonitorP19V;
   uint8  QualityMonitorCurrentA;
   uint8  QualityMonitorCurrentB;
   uint8  QualityTemperatureMotherBoard;
   uint8  QualityTemperatureAnalogBoard;
   uint8  QualityTemperaturePostRegBoard;
   uint8  QualityTemperatureLogicBoard;
   uint8  QualityTemperatureLvpsBoard;
   uint8  QualityTemperatureHvpsBoard;
   uint8  QualityTemperatureM1aBoard;
   uint8  QualityTemperatureM2bBoard;
   uint8  QualityTemperatureT12aBoard;
   uint8  QualityTemperatureT34aBoard;
   uint8  QualityTemperatureT56aBoard;
   uint8  QualityTemperatureT78aBoard;
   uint8  QualityTemperatureT12bBoard;
   uint8  QualityTemperatureT34bBoard;
   uint8  QualityTemperatureT56bBoard;
   uint8  QualityTemperatureT78bBoard;
   uint8  QualityPostDcT1a;
   uint8  QualityPostDcT2a;
   uint8  QualityPostDcT3a;
   uint8  QualityPostDcT4a;
   uint8  QualityPostDcT5a;
   uint8  QualityPostDcT6a;
   uint8  QualityPostDcT7a;
   uint8  QualityPostDcT8a;
   uint8  QualityPostDcT1b;
   uint8  QualityPostDcT2b;
   uint8  QualityPostDcT3b;
   uint8  QualityPostDcT4b;
   uint8  QualityPostDcT5b;
   uint8  QualityPostDcT6b;
   uint8  QualityPostDcT7b;
   uint8  QualityPostDcT8b;
   uint8  QualityStatusTelemetrySide;
   uint8  QualityStatusRefreshEnable;
   uint8  QualityStatusHeatAuto;
   uint8  QualityStatusHeatLevel;
};


/* Definition:                                                       */
/*    ClockCycle = S/C clock of the first minor frame of the cycle   */
/*                                                                   */
/* Note: Quality bits are defined in the table below.  If the field  */
/*       which the quality byte is trying to characterize contains   */
/*       multiple bytes, the quality byte associated with the field  */
/*       is the logical "or" of the individual quality bytes.        */
/*                                                                   */
/* Quality bits:                                                     */
/*    0x01 = Format ID error                                         */
/*    0x02 = Minor/major counter error                               */
/*    0x04 = S/C clock error                                         */
/*    0x08 = Sync bit error                                          */
/*    0x10 = Command table index error                               */
/*    0x20 = Cycle number error                                      */
/*    0x40 = Level 0 quality bit                                     */
/*    0x80 = Level 1 quality bit                                     */
