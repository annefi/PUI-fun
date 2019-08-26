/* $Id: L1SisCommandTable.h,v 1.3 1997/09/11 16:50:59 jeff Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisCommandTable.h,v $ */
/* $Author: jeff $ */
/* $Date: 1997/09/11 16:50:59 $ */
/* $Revision: 1.3 $ */

#include "hdfi.h"
#include "SisConstants.h"

struct L1SisCommandTable
{
   uint32 ClockMinorFrame0;
   uint32 ClockMinorFrame1;
   uint32 Second1996MinorFrame0;
   uint32 MicrosecondMinorFrame0;
   uint32 Second1996MinorFrame1;
   uint32 MicrosecondMinorFrame1;
   uint16 NumberCommandEchoes;
   uint16 coinmsk;
   int16  stbfon;
   uint16 leakint;
   uint8  hkbltim[2];
   int16  oadjflg;
   int16  vrefflg;
   int16  scycflg;
   uint16 mtarget;
   uint16 mscale;
   uint16 mbounds[2];
   uint16 mnav[2];
   uint16 aulkflg;
   int16  ttpflg;
   uint16 rnglim;
   uint16 claslim[2];
   int16  audgflg;
   uint16 audglim;
   uint16 samplim;
   uint16 heflg;
   uint16 hyflg;
   uint16 hetlim;
   uint16 hytlim;
   uint8  htcmd[4];
   uint16 stmask;
   uint8  ecmd[2];
   uint16 hiprcmd[36];
   uint8  sdacval[26];
   uint8  sdacsiz[26];
   uint8  dacval0[42];
   uint8  dacsiz0[42];
   uint8  dacval1[6];
   uint8  dacsiz1[6];
   uint8  hdisc2[8];
   uint8  hdisc0[8];
   uint8  mdisc2[8];
   uint8  mdisc0[8];
   uint8  adcen[8];
   uint8  gdiscen[8];
   uint8  mdiscen[8];
   uint8  hdiscen[8];
   uint8  dirbits[32];
   uint8  calen[64];
   uint8  compen[64];
   uint8  clasmap[32];
   uint16 imthresh[4];
   uint8  imflag[2];
   uint8  im0arr[20];
   uint8  im1arr[20];
   uint8  strplim[4];
   uint16 mcntlim[4];
   uint16 anglim[2];
   uint16 cnoc1[8];
   uint16 cnoc2[8];
   uint16 stimeid;
   uint8  eidmap[512];
   uint16 nbadstp;
   uint16 badstrp[16];
   uint8  QualityCoinmsk;
   uint8  QualityStbfon;
   uint8  QualityLeakint;
   uint8  QualityHkbltim[2];
   uint8  QualityOadjflg;
   uint8  QualityVrefflg;
   uint8  QualityScycflg;
   uint8  QualityMtarget;
   uint8  QualityMscale;
   uint8  QualityMbounds[2];
   uint8  QualityMnav[2];
   uint8  QualityAulkflg;
   uint8  QualityTtpflg;
   uint8  QualityRnglim;
   uint8  QualityClaslim[2];
   uint8  QualityAudgflg;
   uint8  QualityAudglim;
   uint8  QualitySamplim;
   uint8  QualityHeflg;
   uint8  QualityHyflg;
   uint8  QualityHetlim;
   uint8  QualityHytlim;
   uint8  QualityHtcmd[4];
   uint8  QualityStmask;
   uint8  QualityEcmd[2];
   uint8  QualityHiprcmd[36];
   uint8  QualitySdacval[26];
   uint8  QualitySdacsiz[26];
   uint8  QualityDacval0[42];
   uint8  QualityDacsiz0[42];
   uint8  QualityDacval1[6];
   uint8  QualityDacsiz1[6];
   uint8  QualityHdisc2[8];
   uint8  QualityHdisc0[8];
   uint8  QualityMdisc2[8];
   uint8  QualityMdisc0[8];
   uint8  QualityAdcen[8];
   uint8  QualityGdiscen[8];
   uint8  QualityMdiscen[8];
   uint8  QualityHdiscen[8];
   uint8  QualityDirbits[32];
   uint8  QualityCalen[64];
   uint8  QualityCompen[64];
   uint8  QualityClasmap[32];
   uint8  QualityImthresh[4];
   uint8  QualityImflag[2];
   uint8  QualityIm0arr[20];
   uint8  QualityIm1arr[20];
   uint8  QualityStrplim[4];
   uint8  QualityMcntlim[4];
   uint8  QualityAnglim[2];
   uint8  QualityCnoc1[8];
   uint8  QualityCnoc2[8];
   uint8  QualityStimeid;
   uint8  QualityEidmap[512];
   uint8  QualityNbadstp;
   uint8  QualityBadstrp[16];
};


/* Definition:                                                       */
/*    ClockMinorFrame0 = S/C clock of the start of the instrument    */
/*                       cycle that contains the first byte of the   */
/*                       command table                               */
/*    ClockMinorFrame1 = S/C clock of the end of the instrument      */
/*                       cycle that contains the last byte of the    */
/*                       command table                               */
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
