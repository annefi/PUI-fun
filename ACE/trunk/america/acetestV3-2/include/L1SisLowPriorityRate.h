/* $Id: L1SisLowPriorityRate.h,v 1.3 1997/09/11 16:50:59 jeff Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisLowPriorityRate.h,v $ */
/* $Author: jeff $ */
/* $Date: 1997/09/11 16:50:59 $ */
/* $Revision: 1.3 $ */

#include "hdfi.h"
#include "SisConstants.h"

struct L1SisLowPriorityRate
{
   uint32 ClockCycle;
   uint32 Second1996;
   uint32 microsecond;
   uint16 RejcntsM1a;
   uint16 RejcntsM1ha;
   uint16 RejcntsM2a;
   uint16 RejcntsM2ha;
   uint16 RejcntsT1a;
   uint16 RejcntsT2a;
   uint16 RejcntsT3a;
   uint16 RejcntsT4a;
   uint16 RejcntsT5a;
   uint16 RejcntsT6a;
   uint16 RejcntsT7a;
   uint16 RejcntsT8a;
   uint16 RejcntsM12a;
   uint16 RejcntsMora;
   uint16 RejcntsHora;
   uint16 RejcntsHiza;
   uint16 RejcntsMaybeHiza;
   uint16 RejcntsZ2a;
   uint16 RejcntsMaybeZ2a;
   uint16 RejcntsMaybeZ1a;
   uint16 RejcntsM1b;
   uint16 RejcntsM1hb;
   uint16 RejcntsM2b;
   uint16 RejcntsM2hb;
   uint16 RejcntsT1b;
   uint16 RejcntsT2b;
   uint16 RejcntsT3b;
   uint16 RejcntsT4b;
   uint16 RejcntsT5b;
   uint16 RejcntsT6b;
   uint16 RejcntsT7b;
   uint16 RejcntsT8b;
   uint16 RejcntsM12b;
   uint16 RejcntsMorb;
   uint16 RejcntsHorb;
   uint16 RejcntsHizb;
   uint16 RejcntsMaybeHizb;
   uint16 RejcntsZ2b;
   uint16 RejcntsMaybeZ2b;
   uint16 RejcntsMaybeZ1b;
   uint16 RejcntsRejFast;
   uint16 RejcntsStimCoin;
   uint16 RejcntsHazard;
   uint16 RejcntsAdc2a;
   uint16 RejcntsAdc3a;
   uint16 RejcntsAdc2b;
   uint16 RejcntsAdc3b;
   uint16 RejcntsCoinRate0;
   uint16 RejcntsCoinRate1;
   uint16 VldcntsM1a;
   uint16 VldcntsM1ha;
   uint16 VldcntsM2a;
   uint16 VldcntsM2ha;
   uint16 VldcntsT1a;
   uint16 VldcntsT2a;
   uint16 VldcntsT3a;
   uint16 VldcntsT4a;
   uint16 VldcntsT5a;
   uint16 VldcntsT6a;
   uint16 VldcntsT7a;
   uint16 VldcntsT8a;
   uint16 VldcntsM12a;
   uint16 VldcntsMora;
   uint16 VldcntsHora;
   uint16 VldcntsHiza;
   uint16 VldcntsMaybeHiza;
   uint16 VldcntsZ2a;
   uint16 VldcntsMaybeZ2a;
   uint16 VldcntsMaybeZ1a;
   uint16 VldcntsM1b;
   uint16 VldcntsM1hb;
   uint16 VldcntsM2b;
   uint16 VldcntsM2hb;
   uint16 VldcntsT1b;
   uint16 VldcntsT2b;
   uint16 VldcntsT3b;
   uint16 VldcntsT4b;
   uint16 VldcntsT5b;
   uint16 VldcntsT6b;
   uint16 VldcntsT7b;
   uint16 VldcntsT8b;
   uint16 VldcntsM12b;
   uint16 VldcntsMorb;
   uint16 VldcntsHorb;
   uint16 VldcntsHizb;
   uint16 VldcntsMaybeHizb;
   uint16 VldcntsZ2b;
   uint16 VldcntsMaybeZ2b;
   uint16 VldcntsMaybeZ1b;
   uint16 VldcntsRejFast;
   uint16 VldcntsStimCoin;
   uint16 VldcntsHazard;
   uint16 VldcntsAdc2a;
   uint16 VldcntsAdc3a;
   uint16 VldcntsAdc2b;
   uint16 VldcntsAdc3b;
   uint16 VldcntsCoinRate0;
   uint16 VldcntsCoinRate1;
   uint16 EventBuffer[NUM_SIS_EVT_BUFFERS];
   uint16 clasacc[NUM_SIS_EVT_CLASSES];
   uint16 clastot[NUM_SIS_EVT_CLASSES];
   uint16 livetim;
   uint16 helivet;
   uint16 hylivet;
   uint16 ntagint;
   uint16 nvldint;
   uint16 nevproc;
   uint16 nrtproc;
   uint16 nbadid;
   uint16 ncebful;
   uint16 nrebful;
   uint16 nhdwrej;
   uint16 NumberEvents[NUM_SIS_EVT_BUFFERS][NUM_SIS_EVT_CLASSES];
   uint8  QualityRejcntsM1a;
   uint8  QualityRejcntsM1ha;
   uint8  QualityRejcntsM2a;
   uint8  QualityRejcntsM2ha;
   uint8  QualityRejcntsT1a;
   uint8  QualityRejcntsT2a;
   uint8  QualityRejcntsT3a;
   uint8  QualityRejcntsT4a;
   uint8  QualityRejcntsT5a;
   uint8  QualityRejcntsT6a;
   uint8  QualityRejcntsT7a;
   uint8  QualityRejcntsT8a;
   uint8  QualityRejcntsM12a;
   uint8  QualityRejcntsMora;
   uint8  QualityRejcntsHora;
   uint8  QualityRejcntsHiza;
   uint8  QualityRejcntsMaybeHiza;
   uint8  QualityRejcntsZ2a;
   uint8  QualityRejcntsMaybeZ2a;
   uint8  QualityRejcntsMaybeZ1a;
   uint8  QualityRejcntsM1b;
   uint8  QualityRejcntsM1hb;
   uint8  QualityRejcntsM2b;
   uint8  QualityRejcntsM2hb;
   uint8  QualityRejcntsT1b;
   uint8  QualityRejcntsT2b;
   uint8  QualityRejcntsT3b;
   uint8  QualityRejcntsT4b;
   uint8  QualityRejcntsT5b;
   uint8  QualityRejcntsT6b;
   uint8  QualityRejcntsT7b;
   uint8  QualityRejcntsT8b;
   uint8  QualityRejcntsM12b;
   uint8  QualityRejcntsMorb;
   uint8  QualityRejcntsHorb;
   uint8  QualityRejcntsHizb;
   uint8  QualityRejcntsMaybeHizb;
   uint8  QualityRejcntsZ2b;
   uint8  QualityRejcntsMaybeZ2b;
   uint8  QualityRejcntsMaybeZ1b;
   uint8  QualityRejcntsRejFast;
   uint8  QualityRejcntsStimCoin;
   uint8  QualityRejcntsHazard;
   uint8  QualityRejcntsAdc2a;
   uint8  QualityRejcntsAdc3a;
   uint8  QualityRejcntsAdc2b;
   uint8  QualityRejcntsAdc3b;
   uint8  QualityRejcntsCoinRate0;
   uint8  QualityRejcntsCoinRate1;
   uint8  QualityVldcntsM1a;
   uint8  QualityVldcntsM1ha;
   uint8  QualityVldcntsM2a;
   uint8  QualityVldcntsM2ha;
   uint8  QualityVldcntsT1a;
   uint8  QualityVldcntsT2a;
   uint8  QualityVldcntsT3a;
   uint8  QualityVldcntsT4a;
   uint8  QualityVldcntsT5a;
   uint8  QualityVldcntsT6a;
   uint8  QualityVldcntsT7a;
   uint8  QualityVldcntsT8a;
   uint8  QualityVldcntsM12a;
   uint8  QualityVldcntsMora;
   uint8  QualityVldcntsHora;
   uint8  QualityVldcntsHiza;
   uint8  QualityVldcntsMaybeHiza;
   uint8  QualityVldcntsZ2a;
   uint8  QualityVldcntsMaybeZ2a;
   uint8  QualityVldcntsMaybeZ1a;
   uint8  QualityVldcntsM1b;
   uint8  QualityVldcntsM1hb;
   uint8  QualityVldcntsM2b;
   uint8  QualityVldcntsM2hb;
   uint8  QualityVldcntsT1b;
   uint8  QualityVldcntsT2b;
   uint8  QualityVldcntsT3b;
   uint8  QualityVldcntsT4b;
   uint8  QualityVldcntsT5b;
   uint8  QualityVldcntsT6b;
   uint8  QualityVldcntsT7b;
   uint8  QualityVldcntsT8b;
   uint8  QualityVldcntsM12b;
   uint8  QualityVldcntsMorb;
   uint8  QualityVldcntsHorb;
   uint8  QualityVldcntsHizb;
   uint8  QualityVldcntsMaybeHizb;
   uint8  QualityVldcntsZ2b;
   uint8  QualityVldcntsMaybeZ2b;
   uint8  QualityVldcntsMaybeZ1b;
   uint8  QualityVldcntsRejFast;
   uint8  QualityVldcntsStimCoin;
   uint8  QualityVldcntsHazard;
   uint8  QualityVldcntsAdc2a;
   uint8  QualityVldcntsAdc3a;
   uint8  QualityVldcntsAdc2b;
   uint8  QualityVldcntsAdc3b;
   uint8  QualityVldcntsCoinRate0;
   uint8  QualityVldcntsCoinRate1;
   uint8  QualityEventBuffer[NUM_SIS_EVT_BUFFERS];
   uint8  QualityClasacc[NUM_SIS_EVT_CLASSES];
   uint8  QualityClastot[NUM_SIS_EVT_CLASSES];
   uint8  QualityLivetim;
   uint8  QualityHelivet;
   uint8  QualityHylivet;
   uint8  QualityNtagint;
   uint8  QualityNvldint;
   uint8  QualityNevproc;
   uint8  QualityNrtproc;
   uint8  QualityNbadid;
   uint8  QualityNcebful;
   uint8  QualityNrebful;
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
