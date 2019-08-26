/* $Id: L1CrisHighPriorityRate.h,v 1.2 1997/09/11 00:37:38 jeff Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisHighPriorityRate.h,v $ */
/* $Author: jeff $ */
/* $Date: 1997/09/11 00:37:38 $ */
/* $Revision: 1.2 $ */

#include "hdfi.h"
#include "CrisConstants.h"

struct L1CrisHighPriorityRate
{
   uint32 ClockMinorFrame;
   uint32 Second1996;
   uint32 microsecond;
   uint32 hp[NUM_CRIS_HIGH_PRIORITY_RATES];
   uint8  QualityHp[NUM_CRIS_HIGH_PRIORITY_RATES];
};


/* Definition:                                                       */
/*    ClockMinorFrame = S/C clock of the minor frame in which the    */
/*                      high priority rate accumulation began        */
/*    hp = high priority rates                                       */
/*    QualityHp = Quality data flags for high priority rates         */
/*                                                                   */
/* Note: All rates are decompressed.                                 */
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
