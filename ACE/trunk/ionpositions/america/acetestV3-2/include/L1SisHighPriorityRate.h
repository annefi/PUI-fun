/* $Id: L1SisHighPriorityRate.h,v 1.2 1997/09/11 16:50:59 jeff Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisHighPriorityRate.h,v $ */
/* $Author: jeff $ */
/* $Date: 1997/09/11 16:50:59 $ */
/* $Revision: 1.2 $ */

#include "hdfi.h"
#include "SisConstants.h"

struct L1SisHighPriorityRate
{
   uint32 ClockMinorFrame;
   uint32 Second1996;
   uint32 microsecond;
   uint16 hp[NUM_SIS_HIGH_PRIORITY_RATES];
   uint8  QualityHp[NUM_SIS_HIGH_PRIORITY_RATES];
};


/* Definition:                                                       */
/*    ClockMinorFrame = Adjusted S/C clock of the minor frame in     */
/*                      which the high priority rate accumulation    */
/*                      began                                        */
/*    hp = high priority rates                                       */
/*    QualityHp = Flags for missing high priority rates              */
/*                                                                   */
/* Note: All rates are compressed.                                   */
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
