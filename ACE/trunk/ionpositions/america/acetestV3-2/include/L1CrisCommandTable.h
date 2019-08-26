/* $Id: L1CrisCommandTable.h,v 1.4 1998/05/08 23:15:29 rgr Exp $ */

/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisCommandTable.h,v $ */
/* $Author: rgr $ */
/* $Date: 1998/05/08 23:15:29 $ */
/* $Revision: 1.4 $ */

#include "hdfi.h"

struct L1CrisCommandTable
{
   uint32 ClockMinorFrame0;
   uint32 ClockMinorFrame1;
   uint32 Second1996MinorFrame0;
   uint32 MicrosecondMinorFrame0;
   uint32 Second1996MinorFrame1;
   uint32 MicrosecondMinorFrame1;
   uint16 NumberCommandEchoes;
   uint8  ecmd[6];
   uint16 phadisc;
   uint16 audgflg;
   uint16 audglim;
   uint16 valcflg;
   uint16 samplim;
   uint16 heflg;
   uint16 hyflg;
   uint16 preoflg;
   uint16 hetlim;
   uint16 hytlim;
   uint16 htcmd[8];
   uint16 rcmd;
   uint16 qctime;
   uint16 ledtime;
   uint16 sfmisc;
   uint16 camsel;
   uint16 iilima;
   uint16 iilimb;
   uint16  iilims[4];
   int16  lsarr[20];
   int16  loarr[20];
   uint16 laymax;
   uint16 remmax;
   uint8  b_xoff[2];
   uint16 rngmsk[2];
   uint8  bparams[20];
   uint16 twotelen;
   uint16 gphaen;
   uint16 stbfon;
   uint16 ncenbox;
   uint16 b_cenbox[64];
   uint16 iilim;
   uint16 iignct;
   uint16 iignrf;
   uint16 sftdisc;
   uint16 sftrig0;
   uint16 sftrig1;
   uint16 cdscoff;
   uint16 tdscoff;
   uint16 srgbits[2];
   uint8  dacvals[52];
   uint8  dacsize[52];
   uint8  hdisc2[12];
   uint8  hdisc1[12];
   uint8  hdisc0[12];
   uint8  mdisc2[12];
   uint8  mdisc1[12];
   uint8  mdisc0[12];
   uint8  adcen[12];
   uint8  gdiscen[12];
   uint8  mdiscen[12];
   uint8  hdiscen[12];
   uint16 cnoc1[7];
   uint16 cnoc2[7];
   uint16 ihiprr0;
   uint16 ihiprr1;
   uint16 stimeid;
   uint8  eidmap[256];
   uint8  QualityEcmd[6];
   uint8  QualityPhadisc;
   uint8  QualityAudgflg;
   uint8  QualityAudglim;
   uint8  QualityValcflg;
   uint8  QualitySamplim;
   uint8  QualityHeflg;
   uint8  QualityHyflg;
   uint8  QualityPreoflg;
   uint8  QualityHetlim;
   uint8  QualityHytlim;
   uint8  QualityHtcmd[8];
   uint8  QualityRcmd;
   uint8  QualityQctime;
   uint8  QualityLedtime;
   uint8  QualitySfmisc;
   uint8  QualityCamsel;
   uint8  QualityIilima;
   uint8  QualityIilimb;
   uint8  QualityIilims[4];
   uint8  QualityLsarr[20];
   uint8  QualityLoarr[20];
   uint8  QualityLaymax;
   uint8  QualityRemmax;
   uint8  QualityB_xoff[2];
   uint8  QualityRngmsk[2];
   uint8  QualityBparams[20];
   uint8  QualityTwotelen;
   uint8  QualityGphaen;
   uint8  QualityStbfon;
   uint8  QualityNcenbox;
   uint8  QualityB_cenbox[64];
   uint8  QualityIilim;
   uint8  QualityIignct;
   uint8  QualityIignrf;
   uint8  QualitySftdisc;
   uint8  QualitySftrig0;
   uint8  QualitySftrig1;
   uint8  QualityCdscoff;
   uint8  QualityTdscoff;
   uint8  QualitySrgbits[2];
   uint8  QualityDacvals[52];
   uint8  QualityDacsize[52];
   uint8  QualityHdisc2[12];
   uint8  QualityHdisc1[12];
   uint8  QualityHdisc0[12];
   uint8  QualityMdisc2[12];
   uint8  QualityMdisc1[12];
   uint8  QualityMdisc0[12];
   uint8  QualityAdcen[12];
   uint8  QualityGdiscen[12];
   uint8  QualityMdiscen[12];
   uint8  QualityHdiscen[12];
   uint8  QualityCnoc1[7];
   uint8  QualityCnoc2[7];
   uint8  QualityIhiprr0;
   uint8  QualityIhiprr1;
   uint8  QualityStimeid;
   uint8  QualityEidmap[256];
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
