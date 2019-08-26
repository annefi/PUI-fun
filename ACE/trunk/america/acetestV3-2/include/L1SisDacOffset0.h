/* $Id: L1SisDacOffset0.h,v 1.2 1997/09/11 16:50:59 jeff Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisDacOffset0.h,v $ */
/* $Author: jeff $ */
/* $Date: 1997/09/11 16:50:59 $ */
/* $Revision: 1.2 $ */

#include "hdfi.h"
#include "SisConstants.h"

struct L1SisDacOffset0
{
   uint32 ClockCycle;
   uint32 Second1996;
   uint32 microsecond;
   uint16 M1aGndCoarseDac[NUM_SIS_MATRIX_STRIPS];
   uint16 M1aHvCoarseDac[NUM_SIS_MATRIX_STRIPS];
   uint16 M2aGndCoarseDac[NUM_SIS_MATRIX_STRIPS];
   uint16 M2aHvCoarseDac[NUM_SIS_MATRIX_STRIPS];
   uint16 M1bGndCoarseDac[NUM_SIS_MATRIX_STRIPS];
   uint16 M1bHvCoarseDac[NUM_SIS_MATRIX_STRIPS];
   uint16 M2bGndCoarseDac[NUM_SIS_MATRIX_STRIPS];
   uint16 M2bHvCoarseDac[NUM_SIS_MATRIX_STRIPS];
   uint8  M1aGndOffset[NUM_SIS_MATRIX_STRIPS];
   uint8  M1aHvOffset[NUM_SIS_MATRIX_STRIPS];
   uint8  M2aGndOffset[NUM_SIS_MATRIX_STRIPS];
   uint8  M2aHvOffset[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM1aGndCoarseDac[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM1aHvCoarseDac[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM2aGndCoarseDac[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM2aHvCoarseDac[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM1bGndCoarseDac[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM1bHvCoarseDac[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM2bGndCoarseDac[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM2bHvCoarseDac[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM1aGndOffset[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM1aHvOffset[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM2aGndOffset[NUM_SIS_MATRIX_STRIPS];
   uint8  QualityM2aHvOffset[NUM_SIS_MATRIX_STRIPS];
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
