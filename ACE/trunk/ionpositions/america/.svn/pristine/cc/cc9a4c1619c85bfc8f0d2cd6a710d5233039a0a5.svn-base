/* $Id: L1SisDacOffset1.h,v 1.2 1997/09/11 16:50:59 jeff Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisDacOffset1.h,v $ */
/* $Author: jeff $ */
/* $Date: 1997/09/11 16:50:59 $ */
/* $Revision: 1.2 $ */

#include "hdfi.h"
#include "SisConstants.h"

struct L1SisDacOffset1
{
   uint32 ClockCycle;
   uint32 Second1996;
   uint32 microsecond;
   uint16 M1aGndFineDac[NUM_SIS_MATRIX_STRIPS];
   uint16 M1aHvFineDac[NUM_SIS_MATRIX_STRIPS];
   uint16 M2aGndFineDac[NUM_SIS_MATRIX_STRIPS];
   uint16 M2aHvFineDac[NUM_SIS_MATRIX_STRIPS];
   uint16 M1bGndFineDac[NUM_SIS_MATRIX_STRIPS];
   uint16 M1bHvFineDac[NUM_SIS_MATRIX_STRIPS];
   uint16 M2bGndFineDac[NUM_SIS_MATRIX_STRIPS];
   uint16 M2bHvFineDac[NUM_SIS_MATRIX_STRIPS];
   uint8  M1bGndOffset[NUM_SIS_MATRIX_STRIPS];
   uint8  M1bHvOffset[NUM_SIS_MATRIX_STRIPS];
   uint8  M2bGndOffset[NUM_SIS_MATRIX_STRIPS];
   uint8  M2bHvOffset[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM1aGndFineDac[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM1aHvFineDac[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM2aGndFineDac[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM2aHvFineDac[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM1bGndFineDac[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM1bHvFineDac[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM2bGndFineDac[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM2bHvFineDac[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM1bGndOffset[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM1bHvOffset[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM2bGndOffset[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM2bHvOffset[NUM_SIS_MATRIX_STRIPS];
};


/* Definition:                                                       */
/*    ClockCycle = Adjusted S/C clock.  The value 256 has been       */
/*                 subtracted from the S/C clock of the first minor  */
/*                 frame of the cycle in which the DAC and offsets   */
/*                 were readout.                                     */
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
