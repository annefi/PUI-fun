/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: uleis_statblk_trl.h,v 1.8 1997/11/15 00:00:24 steves Exp  */

#include "uleis_statblk_trl.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_uleis_statblk_trl;
static int32 vdata_id_uleis_statblk_trl;

static int32 sds_id_uleis_statblk_trl1;

  /* 7679 is the size of uleis_statblk_trl.h + 1 added line */
char Vgrp_descrp_UStatBlkTrlSet[7679];

/****----  init create function  ----****/

int32 init_cr_uleis_statblk_trl(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_uleis_statblk_trl();

  void print_uleis_statblk_trl_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_uleis_statblk_trl = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_uleis_statblk_trl, "VG_UStatBlkTrlSet"); 
  Vsetclass(vgrp_id_uleis_statblk_trl, "VG_ULEIS_STATBLK_TRL");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_UStatBlkTrlSet" )) ==FAIL) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_uleis_statblk_trl(Vgrp_descrp_UStatBlkTrlSet);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_UStatBlkTrlSet, sizeof(Vgrp_descrp_UStatBlkTrlSet))) ==FAIL) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_uleis_statblk_trl = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_uleis_statblk_trl, "UStatBlkTrlSet");
  VSsetclass(vdata_id_uleis_statblk_trl, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_uleis_statblk_trl, vdata_id_uleis_statblk_trl)) ==FAIL) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_uleis_statblk_trl, "output_sctime", DFNT_UINT32, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define output_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "collect_sctime", DFNT_UINT32, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define collect_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "QAC", DFNT_UINT32, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "chk_sum_chk", DFNT_UINT8, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define chk_sum_chk");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Sync", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Sync");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "SoftwareID", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define SoftwareID");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MinFrCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MinFrCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "CmdAccCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define CmdAccCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "CmdRejCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define CmdRejCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "CmdEcho", DFNT_UINT32, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define CmdEcho");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "RejCmdEcho", DFNT_UINT32, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define RejCmdEcho");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "CmdSide1IntrCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define CmdSide1IntrCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "CmdSide2IntrCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define CmdSide2IntrCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "CodePagNum", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define CodePagNum");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "SunSectrID", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define SunSectrID");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "SpinCntReg", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define SpinCntReg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "WatchdogCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define WatchdogCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "RamPag1TestRslts", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define RamPag1TestRslts");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "RamPag2TestRslts", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define RamPag2TestRslts");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "EEPROMCksum", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define EEPROMCksum");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "TimerIntrCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define TimerIntrCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "CurTLMSide", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define CurTLMSide");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "DefTLMSide", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define DefTLMSide");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MemPekVal", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MemPekVal");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MemPekPagNum", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MemPekPagNum");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MemPekAddr", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MemPekAddr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MemPokVal", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MemPokVal");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MemPokPagNum", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MemPokPagNum");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MemPokAddr", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MemPokAddr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MemDmpPagNum", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MemDmpPagNum");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MemDmpAddrPntr", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MemDmpAddrPntr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "OutputPort0PokVal", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define OutputPort0PokVal");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "OutputPort1PokVal", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define OutputPort1PokVal");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "OutputPort2PokVal", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define OutputPort2PokVal");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "OutputPort6PokVal", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define OutputPort6PokVal");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "InputPort0Val", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define InputPort0Val");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "InputPort1Val", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define InputPort1Val");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "InputPort2Val", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define InputPort2Val");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "InputPort6Val", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define InputPort6Val");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "EEPROMPag3Stat", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define EEPROMPag3Stat");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "EEPROMPag67Stat", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define EEPROMPag67Stat");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "CtrlWord2CmdStat", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define CtrlWord2CmdStat");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MemLdSiz", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MemLdSiz");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MemLdPag", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MemLdPag");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MemLdAddr", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MemLdAddr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MemLdCksum", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MemLdCksum");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MemLdComCksum", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MemLdComCksum");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MemLdCksumErrCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MemLdCksumErrCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "AECmdErrCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define AECmdErrCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "AECmdIntrCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define AECmdIntrCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MajFrCntx8", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MajFrCntx8");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Spn1SpnCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Spn1SpnCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Spn2SpnCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Spn2SpnCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Spn3SpnCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Spn3SpnCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Spn4SpnCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Spn4SpnCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Spn5SpnCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Spn5SpnCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Spn6SpnCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Spn6SpnCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Spn7SpnCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Spn7SpnCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Spn8SpnCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Spn8SpnCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Spn9SpnCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Spn9SpnCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Spn10SpnCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Spn10SpnCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "CumSpnCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define CumSpnCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "EvntCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define EvntCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Spn1MinFrCnt", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Spn1MinFrCnt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "HVAutFlg", DFNT_UINT8, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define HVAutFlg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "HVActFlg", DFNT_UINT8, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define HVActFlg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "PHAFrzFlg", DFNT_UINT8, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define PHAFrzFlg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "SSDEnaFlg", DFNT_UINT8, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define SSDEnaFlg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "AEAutoResetEnaFlg", DFNT_UINT8, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define AEAutoResetEnaFlg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "CalModFlg", DFNT_UINT8, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define CalModFlg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "TOFFlg", DFNT_UINT8, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define TOFFlg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "AETlltlBits", DFNT_UINT8, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define AETlltlBits");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MotrAutFlg", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MotrAutFlg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MotrPwrFlg", DFNT_UINT8, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MotrPwrFlg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MotrFid", DFNT_UINT8, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MotrFid");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MotrPostn", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MotrPostn");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Rt1MinSectr", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Rt1MinSectr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Rt1MinSpn", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Rt1MinSpn");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Rt1HiSecErrLim", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Rt1HiSecErrLim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Rt1LoSecErrLim", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Rt1LoSecErrLim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Rt1HiSpnErrLim", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Rt1HiSpnErrLim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Rt1LoSpnErrLim", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Rt1LoSpnErrLim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Rt1Indx", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Rt1Indx");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Rt2MinSectr", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Rt2MinSectr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Rt2MinSpn", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Rt2MinSpn");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Rt2HiSecErrLim", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Rt2HiSecErrLim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Rt2LoSecErrLim", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Rt2LoSecErrLim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Rt2HiSpnErrLim", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Rt2HiSpnErrLim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Rt2LoSpnErrLim", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Rt2LoSpnErrLim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "Rt2Indx", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define Rt2Indx");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MtrErrFlg", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MtrErrFlg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MtrMotnFlg", DFNT_UINT8, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MtrMotnFlg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "EvntRdoutFmt", DFNT_UINT8, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define EvntRdoutFmt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "MUXSelMd", DFNT_UINT8, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define MUXSelMd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "VS1Enab", DFNT_UINT8, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define VS1Enab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "VS2Enab", DFNT_UINT8, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define VS2Enab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "VS1VS2Enab", DFNT_UINT8, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define VS1VS2Enab");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "PHARnkSpn1Sec1", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define PHARnkSpn1Sec1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "PHARnkSpn1Sec2", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define PHARnkSpn1Sec2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "PHARnkSpn1Sec3", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define PHARnkSpn1Sec3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "PHARnkSpn1Sec4", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define PHARnkSpn1Sec4");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "PHARnkSpn1Sec5", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define PHARnkSpn1Sec5");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "PHARnkSpn1Sec6", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define PHARnkSpn1Sec6");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "PHARnkSpn1Sec7", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define PHARnkSpn1Sec7");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "PHARnkSpn1Sec8", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define PHARnkSpn1Sec8");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_statblk_trl, "SciRecCksum", DFNT_UINT16, (1) )) {
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSfdefine: Couldn't define SciRecCksum");
    retval = -1;
  }

  if (VSsetfields(vdata_id_uleis_statblk_trl,"output_sctime, collect_sctime, QAC, chk_sum_chk, Sync, SoftwareID, MinFrCnt, CmdAccCnt, CmdRejCnt, CmdEcho, RejCmdEcho, CmdSide1IntrCnt, CmdSide2IntrCnt, CodePagNum, SunSectrID, SpinCntReg, WatchdogCnt, RamPag1TestRslts, RamPag2TestRslts, EEPROMCksum, TimerIntrCnt, CurTLMSide, DefTLMSide, MemPekVal, MemPekPagNum, MemPekAddr, MemPokVal, MemPokPagNum, MemPokAddr, MemDmpPagNum, MemDmpAddrPntr, OutputPort0PokVal, OutputPort1PokVal, OutputPort2PokVal, OutputPort6PokVal, InputPort0Val, InputPort1Val, InputPort2Val, InputPort6Val, EEPROMPag3Stat, EEPROMPag67Stat, CtrlWord2CmdStat, MemLdSiz, MemLdPag, MemLdAddr, MemLdCksum, MemLdComCksum, MemLdCksumErrCnt, AECmdErrCnt, AECmdIntrCnt, MajFrCntx8, Spn1SpnCnt, Spn2SpnCnt, Spn3SpnCnt, Spn4SpnCnt, Spn5SpnCnt, Spn6SpnCnt, Spn7SpnCnt, Spn8SpnCnt, Spn9SpnCnt, Spn10SpnCnt, CumSpnCnt, EvntCnt, Spn1MinFrCnt, HVAutFlg, HVActFlg, PHAFrzFlg, SSDEnaFlg, AEAutoResetEnaFlg, CalModFlg, TOFFlg, AETlltlBits, MotrAutFlg, MotrPwrFlg, MotrFid, MotrPostn, Rt1MinSectr, Rt1MinSpn, Rt1HiSecErrLim, Rt1LoSecErrLim, Rt1HiSpnErrLim, Rt1LoSpnErrLim, Rt1Indx, Rt2MinSectr, Rt2MinSpn, Rt2HiSecErrLim, Rt2LoSecErrLim, Rt2HiSpnErrLim, Rt2LoSpnErrLim, Rt2Indx, MtrErrFlg, MtrMotnFlg, EvntRdoutFmt, MUXSelMd, VS1Enab, VS2Enab, VS1VS2Enab, PHARnkSpn1Sec1, PHARnkSpn1Sec2, PHARnkSpn1Sec3, PHARnkSpn1Sec4, PHARnkSpn1Sec5, PHARnkSpn1Sec6, PHARnkSpn1Sec7, PHARnkSpn1Sec8, SciRecCksum")){
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 16;
  dim_sizes[2] = 3;
  if((sds_id_uleis_statblk_trl1 = SDcreate(sd_id, "UStatBlkTrlSet_HK_ADC", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> SDcreate: Couldn't create UStatBlkTrlSet_HK_ADC");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_uleis_statblk_trl1)) == FAIL)
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> SDidtoref: Couldn't get ref for UStatBlkTrlSet_HK_ADC");

  if((Vaddtagref(vgrp_id_uleis_statblk_trl, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_uleis_statblk_trl_error("init_cr_uleis_statblk_trl -> Vaddtagref: Couldn't add SDS UStatBlkTrlSet_HK_ADC to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_uleis_statblk_trl(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_uleis_statblk_trl(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_uleis_statblk_trl(struct UStatBlkTrlSet UStatBlkTrlSet_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_uleis_statblk_trl_error();
void pack_uleis_statblk_trl();

  odata = (uint8 *) malloc(sizeof(struct UStatBlkTrlSet));
  pack_uleis_statblk_trl(odata, &UStatBlkTrlSet_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_uleis_statblk_trl, recnum)==-1) {
		print_uleis_statblk_trl_error("write_uleis_statblk_trl -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_uleis_statblk_trl, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_uleis_statblk_trl_error("write_uleis_statblk_trl -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = 16;
  edges[2] = 3;
  if (SDwritedata(sds_id_uleis_statblk_trl1,start,NULL,edges, (VOIDP)(UStatBlkTrlSet_struc.HK_ADC)) ==FAIL)
    print_uleis_statblk_trl_error("write_uleis_statblk_trl -> SDwritedata: Problem writing HK_ADC data.");

  memset(&UStatBlkTrlSet_struc, 0, sizeof(struct UStatBlkTrlSet));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_uleis_statblk_trl()
{
  VSdetach(vdata_id_uleis_statblk_trl);
  Vdetach(vgrp_id_uleis_statblk_trl);
  SDendaccess(sds_id_uleis_statblk_trl1);
}

/*----     init access function    ----*/

int32 init_acc_uleis_statblk_trl(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_uleis_statblk_trl_error();

  if((sds_index1=SDnametoindex(sd_id, "UStatBlkTrlSet_HK_ADC" )) ==FAIL) {
      print_uleis_statblk_trl_error("init_acc_uleis_statblk_trl -> SDnametoindex: Couldn't find UStatBlkTrlSet_HK_ADC");
      return(-1);
  }
  if((sds_id_uleis_statblk_trl1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_uleis_statblk_trl_error("init_acc_uleis_statblk_trl -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "UStatBlkTrlSet")) <= 0 ) {
    print_uleis_statblk_trl_error("init_acc_uleis_statblk_trl -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_uleis_statblk_trl = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_uleis_statblk_trl_error("init_acc_uleis_statblk_trl -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_uleis_statblk_trl, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_uleis_statblk_trl,"output_sctime, collect_sctime, QAC, chk_sum_chk, Sync, SoftwareID, MinFrCnt, CmdAccCnt, CmdRejCnt, CmdEcho, RejCmdEcho, CmdSide1IntrCnt, CmdSide2IntrCnt, CodePagNum, SunSectrID, SpinCntReg, WatchdogCnt, RamPag1TestRslts, RamPag2TestRslts, EEPROMCksum, TimerIntrCnt, CurTLMSide, DefTLMSide, MemPekVal, MemPekPagNum, MemPekAddr, MemPokVal, MemPokPagNum, MemPokAddr, MemDmpPagNum, MemDmpAddrPntr, OutputPort0PokVal, OutputPort1PokVal, OutputPort2PokVal, OutputPort6PokVal, InputPort0Val, InputPort1Val, InputPort2Val, InputPort6Val, EEPROMPag3Stat, EEPROMPag67Stat, CtrlWord2CmdStat, MemLdSiz, MemLdPag, MemLdAddr, MemLdCksum, MemLdComCksum, MemLdCksumErrCnt, AECmdErrCnt, AECmdIntrCnt, MajFrCntx8, Spn1SpnCnt, Spn2SpnCnt, Spn3SpnCnt, Spn4SpnCnt, Spn5SpnCnt, Spn6SpnCnt, Spn7SpnCnt, Spn8SpnCnt, Spn9SpnCnt, Spn10SpnCnt, CumSpnCnt, EvntCnt, Spn1MinFrCnt, HVAutFlg, HVActFlg, PHAFrzFlg, SSDEnaFlg, AEAutoResetEnaFlg, CalModFlg, TOFFlg, AETlltlBits, MotrAutFlg, MotrPwrFlg, MotrFid, MotrPostn, Rt1MinSectr, Rt1MinSpn, Rt1HiSecErrLim, Rt1LoSecErrLim, Rt1HiSpnErrLim, Rt1LoSpnErrLim, Rt1Indx, Rt2MinSectr, Rt2MinSpn, Rt2HiSecErrLim, Rt2LoSecErrLim, Rt2HiSpnErrLim, Rt2LoSpnErrLim, Rt2Indx, MtrErrFlg, MtrMotnFlg, EvntRdoutFmt, MUXSelMd, VS1Enab, VS2Enab, VS1VS2Enab, PHARnkSpn1Sec1, PHARnkSpn1Sec2, PHARnkSpn1Sec3, PHARnkSpn1Sec4, PHARnkSpn1Sec5, PHARnkSpn1Sec6, PHARnkSpn1Sec7, PHARnkSpn1Sec8, SciRecCksum")) {
      print_uleis_statblk_trl_error("init_acc_uleis_statblk_trl -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_uleis_statblk_trl(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_uleis_statblk_trl(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_uleis_statblk_trl(struct UStatBlkTrlSet *UStatBlkTrlSet_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_uleis_statblk_trl_error();
void unpack_uleis_statblk_trl();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct UStatBlkTrlSet));
  VSinquire(vdata_id_uleis_statblk_trl, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_uleis_statblk_trl, recnum_rd)==FAIL) {
          print_uleis_statblk_trl_error("read_uleis_statblk_trl -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = 16;
  edges[2] = 3;

  if(SDreaddata(sds_id_uleis_statblk_trl1,start,NULL,edges, (VOIDP)(UStatBlkTrlSet_struc->HK_ADC )) ==FAIL) {
    print_uleis_statblk_trl_error("read_uleis_statblk_trl -> SDreaddata: Couldn't read HK_ADC");
    retval = -1;
  }
  if(VSread(vdata_id_uleis_statblk_trl, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_uleis_statblk_trl_error("read_uleis_statblk_trl -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_uleis_statblk_trl(odata, UStatBlkTrlSet_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_uleis_statblk_trl()
{
  VSdetach(vdata_id_uleis_statblk_trl);
  SDendaccess(sds_id_uleis_statblk_trl1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_uleis_statblk_trl(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_uleis_statblk_trl_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_UStatBlkTrlSet" )) ==FAIL)
    print_uleis_statblk_trl_error("rd_Vgrp_uleis_statblk_trl -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_uleis_statblk_trl_error("rd_Vgrp_uleis_statblk_trl -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_uleis_statblk_trl_error("rd_Vgrp_uleis_statblk_trl -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_uleis_statblk_trl_error("rd_Vgrp_uleis_statblk_trl -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_UStatBlkTrlSet, HDstrlen(Vgrp_descrp_UStatBlkTrlSet)) ==FAIL)
    print_uleis_statblk_trl_error("rd_Vgrp_uleis_statblk_trl -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_UStatBlkTrlSet);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_uleis_statblk_trl_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_uleis_statblk_trl.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_uleis_statblk_trl(uint8 *data, struct UStatBlkTrlSet *UStatBlkTrlSet_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &UStatBlkTrlSet_ptr->output_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->collect_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->chk_sum_chk, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Sync, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->SoftwareID, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MinFrCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->CmdAccCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->CmdRejCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->CmdEcho, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->RejCmdEcho, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->CmdSide1IntrCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->CmdSide2IntrCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->CodePagNum, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->SunSectrID, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->SpinCntReg, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->WatchdogCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->RamPag1TestRslts, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->RamPag2TestRslts, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->EEPROMCksum, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->TimerIntrCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->CurTLMSide, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->DefTLMSide, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MemPekVal, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MemPekPagNum, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MemPekAddr, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MemPokVal, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MemPokPagNum, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MemPokAddr, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MemDmpPagNum, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MemDmpAddrPntr, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->OutputPort0PokVal, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->OutputPort1PokVal, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->OutputPort2PokVal, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->OutputPort6PokVal, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->InputPort0Val, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->InputPort1Val, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->InputPort2Val, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->InputPort6Val, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->EEPROMPag3Stat, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->EEPROMPag67Stat, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->CtrlWord2CmdStat, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MemLdSiz, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MemLdPag, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MemLdAddr, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MemLdCksum, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MemLdComCksum, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MemLdCksumErrCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->AECmdErrCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->AECmdIntrCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MajFrCntx8, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Spn1SpnCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Spn2SpnCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Spn3SpnCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Spn4SpnCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Spn5SpnCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Spn6SpnCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Spn7SpnCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Spn8SpnCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Spn9SpnCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Spn10SpnCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->CumSpnCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->EvntCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Spn1MinFrCnt, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->HVAutFlg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->HVActFlg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->PHAFrzFlg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->SSDEnaFlg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->AEAutoResetEnaFlg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->CalModFlg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->TOFFlg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->AETlltlBits, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MotrAutFlg, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MotrPwrFlg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MotrFid, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MotrPostn, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Rt1MinSectr, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Rt1MinSpn, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Rt1HiSecErrLim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Rt1LoSecErrLim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Rt1HiSpnErrLim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Rt1LoSpnErrLim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Rt1Indx, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Rt2MinSectr, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Rt2MinSpn, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Rt2HiSecErrLim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Rt2LoSecErrLim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Rt2HiSpnErrLim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Rt2LoSpnErrLim, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->Rt2Indx, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MtrErrFlg, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MtrMotnFlg, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->EvntRdoutFmt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->MUXSelMd, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->VS1Enab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->VS2Enab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->VS1VS2Enab, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->PHARnkSpn1Sec1, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->PHARnkSpn1Sec2, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->PHARnkSpn1Sec3, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->PHARnkSpn1Sec4, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->PHARnkSpn1Sec5, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->PHARnkSpn1Sec6, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->PHARnkSpn1Sec7, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->PHARnkSpn1Sec8, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UStatBlkTrlSet_ptr->SciRecCksum, ((2)*(1)) );
   ptr+= ((2)*(1));
}

/*----   unpack function    ----*/

void unpack_uleis_statblk_trl(uint8 *data, struct UStatBlkTrlSet *UStatBlkTrlSet_ptr)
{
int32 ptr=0;

   memcpy(&UStatBlkTrlSet_ptr->output_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&UStatBlkTrlSet_ptr->collect_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&UStatBlkTrlSet_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&UStatBlkTrlSet_ptr->chk_sum_chk, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Sync, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->SoftwareID, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MinFrCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->CmdAccCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->CmdRejCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->CmdEcho, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&UStatBlkTrlSet_ptr->RejCmdEcho, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&UStatBlkTrlSet_ptr->CmdSide1IntrCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->CmdSide2IntrCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->CodePagNum, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->SunSectrID, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->SpinCntReg, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->WatchdogCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->RamPag1TestRslts, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->RamPag2TestRslts, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->EEPROMCksum, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->TimerIntrCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->CurTLMSide, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->DefTLMSide, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MemPekVal, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MemPekPagNum, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MemPekAddr, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MemPokVal, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MemPokPagNum, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MemPokAddr, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MemDmpPagNum, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MemDmpAddrPntr, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->OutputPort0PokVal, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->OutputPort1PokVal, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->OutputPort2PokVal, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->OutputPort6PokVal, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->InputPort0Val, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->InputPort1Val, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->InputPort2Val, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->InputPort6Val, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->EEPROMPag3Stat, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->EEPROMPag67Stat, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->CtrlWord2CmdStat, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MemLdSiz, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MemLdPag, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MemLdAddr, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MemLdCksum, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MemLdComCksum, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MemLdCksumErrCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->AECmdErrCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->AECmdIntrCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MajFrCntx8, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Spn1SpnCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Spn2SpnCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Spn3SpnCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Spn4SpnCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Spn5SpnCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Spn6SpnCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Spn7SpnCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Spn8SpnCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Spn9SpnCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Spn10SpnCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->CumSpnCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->EvntCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Spn1MinFrCnt, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->HVAutFlg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UStatBlkTrlSet_ptr->HVActFlg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UStatBlkTrlSet_ptr->PHAFrzFlg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UStatBlkTrlSet_ptr->SSDEnaFlg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UStatBlkTrlSet_ptr->AEAutoResetEnaFlg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UStatBlkTrlSet_ptr->CalModFlg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UStatBlkTrlSet_ptr->TOFFlg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UStatBlkTrlSet_ptr->AETlltlBits, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MotrAutFlg, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MotrPwrFlg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MotrFid, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MotrPostn, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Rt1MinSectr, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Rt1MinSpn, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Rt1HiSecErrLim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Rt1LoSecErrLim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Rt1HiSpnErrLim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Rt1LoSpnErrLim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Rt1Indx, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Rt2MinSectr, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Rt2MinSpn, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Rt2HiSecErrLim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Rt2LoSecErrLim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Rt2HiSpnErrLim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Rt2LoSpnErrLim, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->Rt2Indx, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MtrErrFlg, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MtrMotnFlg, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UStatBlkTrlSet_ptr->EvntRdoutFmt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UStatBlkTrlSet_ptr->MUXSelMd, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UStatBlkTrlSet_ptr->VS1Enab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UStatBlkTrlSet_ptr->VS2Enab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UStatBlkTrlSet_ptr->VS1VS2Enab, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&UStatBlkTrlSet_ptr->PHARnkSpn1Sec1, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->PHARnkSpn1Sec2, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->PHARnkSpn1Sec3, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->PHARnkSpn1Sec4, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->PHARnkSpn1Sec5, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->PHARnkSpn1Sec6, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->PHARnkSpn1Sec7, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->PHARnkSpn1Sec8, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UStatBlkTrlSet_ptr->SciRecCksum, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
}
int32 get_vgrp_id_uleis_statblk_trl() {return(vgrp_id_uleis_statblk_trl);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_uleis_statblk_trl(char *wr_strval)
{
  strcpy(wr_strval, "The file 'uleis_statblk_trl.h' is shown below, it was used to create the data in the Vgroup named 'VG_UStatBlkTrlSet'.\n\n");
  strcat(wr_strval,"/* Id: uleis_statblk_trl.h,v 1.8 1997/11/15 00:00:24 steves Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define U_MAJFRM              8		/* 8 major frames (0-7) */\n");
  strcat(wr_strval,"#define U_STATBLK_SIZE       14		/* Status block of 14 bytes */\n");
  strcat(wr_strval,"#define U_TRL_SIZE           128	/* Status trailer of 128 bytes */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct UStatBlkTrlSet\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 output_sctime;		/* time for beginning of data output cycle */\n");
  strcat(wr_strval,"  uint32 collect_sctime;	/* time for beginning of data collection */\n");
  strcat(wr_strval,"  uint32 QAC;			/* number of bad frames in this cycle */\n");
  strcat(wr_strval,"  uint8 chk_sum_chk;	      /* 0 means chk_sum test passed; 1 means failed */\n");
  strcat(wr_strval,"                              /*   also in uleis_hskp.h                      */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"     /* Status Block: 8 major frames, 14 bytes */\n");
  strcat(wr_strval,"/*  uint8 statblock[U_MAJFRM][U_STATBLK_SIZE];*/\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"     /* Status Trailer: 128 bytes */\n");
  strcat(wr_strval,"/*  uint8 trailer[U_TRL_SIZE];*/\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* variable set */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"     /* Status Block: 112 bytes */\n");
  strcat(wr_strval,"  uint16 Sync;               /*Status Block 0   Byte  1- 2 */ /* = FAFE */ \n");
  strcat(wr_strval,"  uint16 SoftwareID;                         /* Byte  3- 4 */\n");
  strcat(wr_strval,"  uint16 MinFrCnt;                           /* Byte  5- 6 */\n");
  strcat(wr_strval,"  uint16 CmdAccCnt;                          /* Byte  7- 8 */\n");
  strcat(wr_strval,"  uint16 CmdRejCnt;                          /* Byte  9-10 */\n");
  strcat(wr_strval,"  uint32 CmdEcho;                            /* Byte 11-14 */\n");
  strcat(wr_strval,"  uint32 RejCmdEcho;         /*Status Block 1   Byte  1- 4 */\n");
  strcat(wr_strval,"  uint16 CmdSide1IntrCnt;                    /* Byte  5- 6 */\n");
  strcat(wr_strval,"  uint16 CmdSide2IntrCnt;                    /* Byte  7- 8 */\n");
  strcat(wr_strval,"  uint16 CodePagNum;                         /* Byte  9-10 */\n");
  strcat(wr_strval,"  uint16 SunSectrID;                         /* Byte 11-12 */\n");
  strcat(wr_strval,"  uint16 SpinCntReg;                         /* Byte 13-14 */\n");
  strcat(wr_strval,"  uint16 WatchdogCnt;        /*Status Block 2   Byte  1- 2 */\n");
  strcat(wr_strval,"  uint16 RamPag1TestRslts;                   /* Byte  3- 4 */\n");
  strcat(wr_strval,"  uint16 RamPag2TestRslts;                   /* Byte  5- 6 */\n");
  strcat(wr_strval,"  uint16 EEPROMCksum;                        /* Byte  7- 8 */\n");
  strcat(wr_strval,"  uint16 TimerIntrCnt;                       /* Byte  9-10 */\n");
  strcat(wr_strval,"  uint16 CurTLMSide;                         /* Byte 11-12 */\n");
  strcat(wr_strval,"  uint16 DefTLMSide;                         /* Byte 13-14 */\n");
  strcat(wr_strval,"  uint16 MemPekVal;          /*Status Block 3   Byte  1- 2 */\n");
  strcat(wr_strval,"  uint16 MemPekPagNum;                       /* Byte  3- 4 */\n");
  strcat(wr_strval,"  uint16 MemPekAddr;                         /* Byte  5- 6 */\n");
  strcat(wr_strval,"  uint16 MemPokVal;                          /* Byte  7- 8 */\n");
  strcat(wr_strval,"  uint16 MemPokPagNum;                       /* Byte  9-10 */\n");
  strcat(wr_strval,"  uint16 MemPokAddr;                         /* Byte 11-12 */\n");
  strcat(wr_strval,"  uint16 MemDmpPagNum;                       /* Byte 13-14 */\n");
  strcat(wr_strval,"  uint16 MemDmpAddrPntr;     /*Status Block 4   Byte  1- 2 */\n");
  strcat(wr_strval,"  uint16 OutputPort0PokVal;                  /* Byte  3- 4 */\n");
  strcat(wr_strval,"  uint16 OutputPort1PokVal;                  /* Byte  5- 6 */\n");
  strcat(wr_strval,"  uint16 OutputPort2PokVal;                  /* Byte  7- 8 */\n");
  strcat(wr_strval,"  uint16 OutputPort6PokVal;                  /* Byte  9-10 */\n");
  strcat(wr_strval,"  uint16 InputPort0Val;                      /* Byte 11-12 */\n");
  strcat(wr_strval,"  uint16 InputPort1Val;                      /* Byte 13-14 */\n");
  strcat(wr_strval,"  uint16 InputPort2Val;      /*Status Block 5   Byte  1- 2 */\n");
  strcat(wr_strval,"  uint16 InputPort6Val;                      /* Byte  3- 4 */\n");
  strcat(wr_strval,"  uint16 EEPROMPag3Stat;                     /* Byte  5- 6 */\n");
  strcat(wr_strval,"  uint16 EEPROMPag67Stat;                    /* Byte  7- 8 */\n");
  strcat(wr_strval,"  uint16 CtrlWord2CmdStat;                   /* Byte  9-10 */\n");
  strcat(wr_strval,"  uint16 MemLdSiz;                           /* Byte 11-12 */\n");
  strcat(wr_strval,"  uint16 MemLdPag;                           /* Byte 13-14 */\n");
  strcat(wr_strval,"  uint16 MemLdAddr;          /*Status Block 6   Byte  1- 2 */\n");
  strcat(wr_strval,"  uint16 MemLdCksum;                         /* Byte  3- 4 */\n");
  strcat(wr_strval,"  uint16 MemLdComCksum;                      /* Byte  5- 6 */\n");
  strcat(wr_strval,"  uint16 MemLdCksumErrCnt;                   /* Byte  7- 8 */\n");
  strcat(wr_strval,"  uint16 AECmdErrCnt;                        /* Byte  9-10 */\n");
  strcat(wr_strval,"  uint16 AECmdIntrCnt;                       /* Byte 11-12 */\n");
  strcat(wr_strval,"  uint16 MajFrCntx8;                         /* Byte 13-14 */\n");
  strcat(wr_strval,"  uint16 Spn1SpnCnt;         /*Status Block 7   Byte  1- 2 */\n");
  strcat(wr_strval,"  uint16 Spn2SpnCnt;                         /* Byte  3- 4 */\n");
  strcat(wr_strval,"  uint16 Spn3SpnCnt;                         /* Byte  5- 6 */\n");
  strcat(wr_strval,"  uint16 Spn4SpnCnt;                         /* Byte  7- 8 */\n");
  strcat(wr_strval,"  uint16 Spn5SpnCnt;                         /* Byte  9-10 */\n");
  strcat(wr_strval,"  uint16 Spn6SpnCnt;                         /* Byte 11-12 */\n");
  strcat(wr_strval,"  uint16 Spn7SpnCnt;                         /* Byte 13-14 */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"     /* Status Trailer: 128 bytes 	(as of 4/7/97) */\n");
  strcat(wr_strval,"  uint16 Spn8SpnCnt;        /*Status Trailer   Byte   1-  2 */\n");
  strcat(wr_strval,"  uint16 Spn9SpnCnt;                        /* Byte   3-  4 */\n");
  strcat(wr_strval,"  uint16 Spn10SpnCnt;                       /* Byte   5-  6 */\n");
  strcat(wr_strval,"  uint16 CumSpnCnt;                         /* Byte   7-  8 */\n");
  strcat(wr_strval,"  uint16 EvntCnt;                           /* Byte   9- 10 */\n");
  strcat(wr_strval,"  uint16 Spn1MinFrCnt;                      /* Byte  11- 12 */\n");
  strcat(wr_strval,"  uint8  HVAutFlg;                          /* Byte  13     */\n");
  strcat(wr_strval,"  uint8  HVActFlg;                          /* Byte  14     */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint8  HK_ADC[16][3];                     /* Byte  15- 62 */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint8  PHAFrzFlg;			    /* Byte  63     0=dsabl,1=enbl*/\n");
  strcat(wr_strval,"  uint8  SSDEnaFlg;                         /* Byte  64     */\n");
  strcat(wr_strval,"  uint8  AEAutoResetEnaFlg;                 /* Byte  65     */\n");
  strcat(wr_strval,"  uint8  CalModFlg;                         /* Byte  66     */\n");
  strcat(wr_strval,"  uint8  TOFFlg;                            /* Byte  67     22=TOF1,24=TOF2*/\n");
  strcat(wr_strval,"  uint8  AETlltlBits;                       /* Byte  68     */\n");
  strcat(wr_strval,"  uint16 MotrAutFlg;                        /* Byte  69- 70 */\n");
  strcat(wr_strval,"  uint8  MotrPwrFlg;                        /* Byte  71     0=off,nonzero=on*/\n");
  strcat(wr_strval,"  uint8  MotrFid;                           /* Byte  72     */\n");
  strcat(wr_strval,"  uint16 MotrPostn;                         /* Byte  73- 74 */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint16 Rt1MinSectr;                       /* Byte  75- 76 */\n");
  strcat(wr_strval,"  uint16 Rt1MinSpn;                         /* Byte  77- 78 */\n");
  strcat(wr_strval,"  uint16 Rt1HiSecErrLim;                    /* Byte  79- 80 */\n");
  strcat(wr_strval,"  uint16 Rt1LoSecErrLim;                    /* Byte  81- 82 */\n");
  strcat(wr_strval,"  uint16 Rt1HiSpnErrLim;                    /* Byte  83- 84 */\n");
  strcat(wr_strval,"  uint16 Rt1LoSpnErrLim;                    /* Byte  85- 86 */\n");
  strcat(wr_strval,"  uint16 Rt1Indx;                           /* Byte  87- 88 */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint16 Rt2MinSectr;                       /* Byte 89-90   */\n");
  strcat(wr_strval,"  uint16 Rt2MinSpn;                         /* Byte 91-92   */\n");
  strcat(wr_strval,"  uint16 Rt2HiSecErrLim;                    /* Byte 93-94   */\n");
  strcat(wr_strval,"  uint16 Rt2LoSecErrLim;                    /* Byte 95-96   */\n");
  strcat(wr_strval,"  uint16 Rt2HiSpnErrLim;                    /* Byte 97-98   */\n");
  strcat(wr_strval,"  uint16 Rt2LoSpnErrLim;                    /* Byte 99-100  */\n");
  strcat(wr_strval,"  uint16 Rt2Indx;                           /* Byte 101-102 */\n");
  strcat(wr_strval,"  uint16 MtrErrFlg;                         /* Byte 103-104 */\n");
  strcat(wr_strval,"  uint8  MtrMotnFlg;                        /* Byte 105     0=No Motion*/\n");
  strcat(wr_strval,"  uint8  EvntRdoutFmt;                      /* Byte 106     */\n");
  strcat(wr_strval,"  uint8  MUXSelMd;                          /* Byte 107     */\n");
  strcat(wr_strval,"  uint8  VS1Enab;                           /* Byte 108     */\n");
  strcat(wr_strval,"  uint8  VS2Enab;                           /* Byte 109     */\n");
  strcat(wr_strval,"  uint8  VS1VS2Enab;                        /* Byte 110     */\n");
  strcat(wr_strval,"  uint16 PHARnkSpn1Sec1;                    /* Byte 111-112 */\n");
  strcat(wr_strval,"  uint16 PHARnkSpn1Sec2;                    /* Byte 113-114 */\n");
  strcat(wr_strval,"  uint16 PHARnkSpn1Sec3;                    /* Byte 115-116 */\n");
  strcat(wr_strval,"  uint16 PHARnkSpn1Sec4;                    /* Byte 117-118 */\n");
  strcat(wr_strval,"  uint16 PHARnkSpn1Sec5;                    /* Byte 119-120 */\n");
  strcat(wr_strval,"  uint16 PHARnkSpn1Sec6;                    /* Byte 121-122 */\n");
  strcat(wr_strval,"  uint16 PHARnkSpn1Sec7;                    /* Byte 123-124 */\n");
  strcat(wr_strval,"  uint16 PHARnkSpn1Sec8;                    /* Byte 125-126 */\n");
  strcat(wr_strval,"  /* 16-bit sum of first 7999 words */\n");
  strcat(wr_strval,"  uint16 SciRecCksum;                       /* Byte 127-128 */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"}; \n");
  return(0);
}
