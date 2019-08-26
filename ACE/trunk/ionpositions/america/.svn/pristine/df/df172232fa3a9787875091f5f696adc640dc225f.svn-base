/* $Id: L1CrisLowPriorityRate.h,v 1.3 1997/09/11 00:37:38 jeff Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisLowPriorityRate.h,v $ */
/* $Author: jeff $ */
/* $Date: 1997/09/11 00:37:38 $ */
/* $Revision: 1.3 $ */

#include "hdfi.h"
#include "CrisConstants.h"

struct L1CrisLowPriorityRate
{
   uint32 ClockCycle;
   uint32 Second1996;
   uint32 microsecond;
   uint32 stmco;
   uint32 stmoff;
   uint32 z1ab;
   uint32 z2ab;
   uint32 z_gt_2ab;
   uint32 z1cd;
   uint32 z2cd;
   uint32 z_gt_2cd;
   uint32 hazard;
   uint32 gh;
   uint32 mor;
   uint32 hor;
   uint32 adc2ab;
   uint32 mnrgab;
   uint32 adc2cd;
   uint32 mnrgcd;
   uint32 e1a;
   uint32 e1b;
   uint32 e2ab;
   uint32 e3ab;
   uint32 e4ab;
   uint32 e5ab;
   uint32 e6ab;
   uint32 e7ab;
   uint32 e8ab;
   uint32 e9ab;
   uint32 g2ab;
   uint32 g3ab;
   uint32 g4ab;
   uint32 g5ab;
   uint32 g6ab;
   uint32 g7ab;
   uint32 e1c;
   uint32 e1d;
   uint32 e2cd;
   uint32 e3cd;
   uint32 e4cd;
   uint32 e5cd;
   uint32 e6cd;
   uint32 e7cd;
   uint32 e8cd;
   uint32 e9cd;
   uint32 g2cd;
   uint32 g3cd;
   uint32 g4cd;
   uint32 g5cd;
   uint32 g6cd;
   uint32 g7cd;
   uint32 EventBuffer[NUM_CRIS_EVT_BUFFERS];
   uint32 livetim;
   uint32 helivet;
   uint32 hylivet;
   uint32 trg0rat;
   uint32 trg1rat;
   uint32 trg01;
   uint32 ntagint;
   uint32 nvldint;
   uint32 nevproc;
   uint32 nrtproc;
   uint32 nsfterr;
   uint32 nbadid;
   uint32 ncebful;
   uint32 nrebful;
   uint32 nmacsys;
   uint32 nhdwrej;
   uint16 NumberEvents[NUM_CRIS_EVT_BUFFERS];
   uint8  QualityStmco;
   uint8  QualityStmoff;
   uint8  QualityZ1ab;
   uint8  QualityZ2ab;
   uint8  QualityZ_gt_2ab;
   uint8  QualityZ1cd;
   uint8  QualityZ2cd;
   uint8  QualityZ_gt_2cd;
   uint8  QualityHazard;
   uint8  QualityGh;
   uint8  QualityMor;
   uint8  QualityHor;
   uint8  QualityAdc2ab;
   uint8  QualityMnrgab;
   uint8  QualityAdc2cd;
   uint8  QualityMnrgcd;
   uint8  QualityE1a;
   uint8  QualityE1b;
   uint8  QualityE2ab;
   uint8  QualityE3ab;
   uint8  QualityE4ab;
   uint8  QualityE5ab;
   uint8  QualityE6ab;
   uint8  QualityE7ab;
   uint8  QualityE8ab;
   uint8  QualityE9ab;
   uint8  QualityG2ab;
   uint8  QualityG3ab;
   uint8  QualityG4ab;
   uint8  QualityG5ab;
   uint8  QualityG6ab;
   uint8  QualityG7ab;
   uint8  QualityE1c;
   uint8  QualityE1d;
   uint8  QualityE2cd;
   uint8  QualityE3cd;
   uint8  QualityE4cd;
   uint8  QualityE5cd;
   uint8  QualityE6cd;
   uint8  QualityE7cd;
   uint8  QualityE8cd;
   uint8  QualityE9cd;
   uint8  QualityG2cd;
   uint8  QualityG3cd;
   uint8  QualityG4cd;
   uint8  QualityG5cd;
   uint8  QualityG6cd;
   uint8  QualityG7cd;
   uint8  QualityEventBuffer[NUM_CRIS_EVT_BUFFERS];
   uint8  QualityLivetim;
   uint8  QualityHelivet;
   uint8  QualityHylivet;
   uint8  QualityTrg0rat;
   uint8  QualityTrg1rat;
   uint8  QualityTrg01;
   uint8  QualityNtagint;
   uint8  QualityNvldint;
   uint8  QualityNevproc;
   uint8  QualityNrtproc;
   uint8  QualityNsfterr;
   uint8  QualityNbadid;
   uint8  QualityNcebful;
   uint8  QualityNrebful;
   uint8  QualityNmacsys;
   uint8  QualityNhdwrej;
   uint8  QualityNumberEvents;
};


/* Definition:                                                       */
/*    ClockCycle = Adjusted S/C clock of the first minor frame of    */
/*                 the cycle in which the rate was accumulated.      */
/*                 The value 256 is subtracted from the S/C clock of */
/*                 the first minor frame of the cycle in which the   */
/*                 low priority rates were readout.                  */
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
