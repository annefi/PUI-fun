/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: schskp.h,v 1.10 1997/08/01 17:11:35 jeff Exp  */

#include "schskp.h"
#include "df.h"

int32 vgrp_id_schskp;
static int32 vdata_id_schskp;

  /* 9995 is the size of schskp.h + 1 added line */
char Vgrp_descrp_SCHskpData[9995];

/****----  init create function  ----****/

int32 init_cr_schskp(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_schskp();

  void print_schskp_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_schskp = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_schskp_error("init_cr_schskp -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_schskp, "VG_SCHskpData"); 
  Vsetclass(vgrp_id_schskp, "VG_SCHSKP");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_SCHskpData" )) ==FAIL) {
    print_schskp_error("init_cr_schskp -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_schskp(Vgrp_descrp_SCHskpData);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_schskp_error("init_cr_schskp -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_SCHskpData, sizeof(Vgrp_descrp_SCHskpData))) ==FAIL) {
    print_schskp_error("init_cr_schskp -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_schskp = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_schskp_error("init_cr_schskp -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_schskp, "SCHskpData");
  VSsetclass(vdata_id_schskp, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_schskp, vdata_id_schskp)) ==FAIL) {
    print_schskp_error("init_cr_schskp -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_schskp, "sc_clk", DFNT_UINT32, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define sc_clk");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "TankA1Temp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define TankA1Temp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "TankA2Temp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define TankA2Temp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "TankB1Temp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define TankB1Temp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "TankB2Temp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define TankB2Temp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "LinesATemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define LinesATemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "LinesBTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define LinesBTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "LinesPosXTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define LinesPosXTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "LinesNegXTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define LinesNegXTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "StarTrkTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define StarTrkTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "InstDeckTemp1", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define InstDeckTemp1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "InstDeckTemp2", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define InstDeckTemp2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "InstDeckTemp3", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define InstDeckTemp3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "InstDeckTemp4", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define InstDeckTemp4");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "InstDeckTemp5", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define InstDeckTemp5");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "InstDeckTemp6", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define InstDeckTemp6");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "InstDeckTemp7", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define InstDeckTemp7");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "InstDeckTemp8", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define InstDeckTemp8");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "LastSPTT0", DFNT_UINT8, (3) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define LastSPTT0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "ScIFHeaterCur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define ScIFHeaterCur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "SunSnsrTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define SunSnsrTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "PosXSAPTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define PosXSAPTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "PosXSAPHTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define PosXSAPHTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "NegXSAPTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define NegXSAPTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "NegXSAPHTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define NegXSAPHTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "MagInTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define MagInTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "MagOutTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define MagOutTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "MagInHtrPwrLvl", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define MagInHtrPwrLvl");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "MagOutHtrPwrLvl", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define MagOutHtrPwrLvl");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "S3DPUPwrCvtVolt", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define S3DPUPwrCvtVolt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "PwrSubProACur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define PwrSubProACur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "PwrSubProBCur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define PwrSubProBCur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "AxialThrstCur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define AxialThrstCur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Channel25", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Channel25");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Channel26", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Channel26");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Channel20", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Channel20");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Channel30", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Channel30");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "DigTellLog0", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define DigTellLog0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "DigTellLog1", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define DigTellLog1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "data_2_1", DFNT_UINT8, (16) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define data_2_1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "MagSenIntTempPosY", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define MagSenIntTempPosY");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "MagSenIntTempNegY", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define MagSenIntTempNegY");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "data_2_2", DFNT_UINT8, (2) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define data_2_2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "data_3_1", DFNT_UINT8, (10) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define data_3_1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "MainBusCur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define MainBusCur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "MainBusVolt", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define MainBusVolt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "data_3_2", DFNT_UINT8, (8) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define data_3_2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "data_4_1", DFNT_UINT8, (20) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define data_4_1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "data_5_1", DFNT_UINT8, (20) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define data_5_1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "data_6_1", DFNT_UINT8, (20) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define data_6_1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "data_7_1", DFNT_UINT8, (20) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define data_7_1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "data_8_1", DFNT_UINT8, (17) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define data_8_1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "LastSPTT8", DFNT_UINT8, (3) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define LastSPTT8");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "SwepamE_8VPSMon", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define SwepamE_8VPSMon");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "SwepamE_HVMon1", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define SwepamE_HVMon1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "SwepamE_HVMon2", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define SwepamE_HVMon2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "SwepamI_8VPSMon", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define SwepamI_8VPSMon");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "SwepamI_HVMon1", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define SwepamI_HVMon1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "SwepamI_HVMon2", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define SwepamI_HVMon2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Epam_A1", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Epam_A1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Epam_A2", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Epam_A2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Epam_A3", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Epam_A3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Epam_A4", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Epam_A4");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Epam_LAN1", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Epam_LAN1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Epam_LAN2A", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Epam_LAN2A");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Epam_LAN2B", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Epam_LAN2B");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Uleis_LVPSVolt", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Uleis_LVPSVolt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Cris_IntTemp1", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Cris_IntTemp1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Cris_IntTemp2", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Cris_IntTemp2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Sis_IntTemp1", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Sis_IntTemp1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Sis_IntTemp2", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Sis_IntTemp2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "SunPulPhaAng0", DFNT_UINT16, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define SunPulPhaAng0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "data_10_1", DFNT_UINT8, (2) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define data_10_1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "data_10_2", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define data_10_2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Cris_Cur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Cris_Cur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Sis_Cur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Sis_Cur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Epam_Cur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Epam_Cur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Epam_HtrCur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Epam_HtrCur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Uleis_Cur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Uleis_Cur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Uleis_AnaEleLVPSCur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Uleis_AnaEleLVPSCur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "DCM1_Chan21", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define DCM1_Chan21");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Uleis_HtrCur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Uleis_HtrCur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "SwepamE_Cur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define SwepamE_Cur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "SwepamI_Cur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define SwepamI_Cur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Swims_Cur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Swims_Cur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Swics_Cur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Swics_Cur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Sepica_Cur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Sepica_Cur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Mag_Cur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Mag_Cur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "S3DPU_Cur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define S3DPU_Cur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "data_10_3", DFNT_UINT8, (2) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define data_10_3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "PowSwiOrdBit", DFNT_UINT8, (14) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define PowSwiOrdBit");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "data_11_1", DFNT_UINT8, (4) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define data_11_1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "S3DPU_ConSecCur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define S3DPU_ConSecCur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "PreTraCur", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define PreTraCur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Swims_IntTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Swims_IntTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Swics_IntTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Swics_IntTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Uleis_TelTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Uleis_TelTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Uleis_AnaEleTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Uleis_AnaEleTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Uleis_DPUTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Uleis_DPUTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "Sepica_IsoTanTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define Sepica_IsoTanTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "S3DPU_PowSupATemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define S3DPU_PowSupATemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "SwepamE_IntTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define SwepamE_IntTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "SwepamI_IntTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define SwepamI_IntTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "StarScan", DFNT_UINT8, (8) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define StarScan");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "TermBoardFuse1Temp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define TermBoardFuse1Temp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "data_12_1", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define data_12_1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "S3DPU_PowSupBTemp", DFNT_UINT8, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define S3DPU_PowSupBTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "CDH_HKdat", DFNT_UINT8, (48) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define CDH_HKdat");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "data_15_1", DFNT_UINT8, (10) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define data_15_1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "SunPulPhaAng8", DFNT_UINT16, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define SunPulPhaAng8");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "SelTelByt", DFNT_UINT8, (16) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define SelTelByt");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "SCIPhaAng", DFNT_UINT16, (16) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define SCIPhaAng");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "FormatID", DFNT_UINT8, (16) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define FormatID");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "CollForm", DFNT_UINT8, (16) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define CollForm");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "ADCPhaAng", DFNT_UINT16, (1) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define ADCPhaAng");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "SunSensor", DFNT_UINT16, (11) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define SunSensor");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "ADCXtrDat", DFNT_UINT8, (51) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define ADCXtrDat");
    retval = -1;
  }
  if (VSfdefine(vdata_id_schskp, "spare", DFNT_UINT8, (17) )) {
    print_schskp_error("init_cr_schskp -> VSfdefine: Couldn't define spare");
    retval = -1;
  }

  if (VSsetfields(vdata_id_schskp,"sc_clk, TankA1Temp, TankA2Temp, TankB1Temp, TankB2Temp, LinesATemp, LinesBTemp, LinesPosXTemp, LinesNegXTemp, StarTrkTemp, InstDeckTemp1, InstDeckTemp2, InstDeckTemp3, InstDeckTemp4, InstDeckTemp5, InstDeckTemp6, InstDeckTemp7, InstDeckTemp8, LastSPTT0, ScIFHeaterCur, SunSnsrTemp, PosXSAPTemp, PosXSAPHTemp, NegXSAPTemp, NegXSAPHTemp, MagInTemp, MagOutTemp, MagInHtrPwrLvl, MagOutHtrPwrLvl, S3DPUPwrCvtVolt, PwrSubProACur, PwrSubProBCur, AxialThrstCur, Channel25, Channel26, Channel20, Channel30, DigTellLog0, DigTellLog1, data_2_1, MagSenIntTempPosY, MagSenIntTempNegY, data_2_2, data_3_1, MainBusCur, MainBusVolt, data_3_2, data_4_1, data_5_1, data_6_1, data_7_1, data_8_1, LastSPTT8, SwepamE_8VPSMon, SwepamE_HVMon1, SwepamE_HVMon2, SwepamI_8VPSMon, SwepamI_HVMon1, SwepamI_HVMon2, Epam_A1, Epam_A2, Epam_A3, Epam_A4, Epam_LAN1, Epam_LAN2A, Epam_LAN2B, Uleis_LVPSVolt, Cris_IntTemp1, Cris_IntTemp2, Sis_IntTemp1, Sis_IntTemp2, SunPulPhaAng0, data_10_1, data_10_2, Cris_Cur, Sis_Cur, Epam_Cur, Epam_HtrCur, Uleis_Cur, Uleis_AnaEleLVPSCur, DCM1_Chan21, Uleis_HtrCur, SwepamE_Cur, SwepamI_Cur, Swims_Cur, Swics_Cur, Sepica_Cur, Mag_Cur, S3DPU_Cur, data_10_3, PowSwiOrdBit, data_11_1, S3DPU_ConSecCur, PreTraCur, Swims_IntTemp, Swics_IntTemp, Uleis_TelTemp, Uleis_AnaEleTemp, Uleis_DPUTemp, Sepica_IsoTanTemp, S3DPU_PowSupATemp, SwepamE_IntTemp, SwepamI_IntTemp, StarScan, TermBoardFuse1Temp, data_12_1, S3DPU_PowSupBTemp, CDH_HKdat, data_15_1, SunPulPhaAng8, SelTelByt, SCIPhaAng, FormatID, CollForm, ADCPhaAng, SunSensor, ADCXtrDat, spare")){
    print_schskp_error("init_cr_schskp -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_schskp(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_schskp(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_schskp(struct SCHskpData SCHskpData_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_schskp_error();
void pack_schskp();

  odata = (uint8 *) malloc(sizeof(struct SCHskpData));
  pack_schskp(odata, &SCHskpData_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_schskp, recnum)==-1) {
		print_schskp_error("write_schskp -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_schskp, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_schskp_error("write_schskp -> VSwrite: Couldn't write data.");

  memset(&SCHskpData_struc, 0, sizeof(struct SCHskpData));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_schskp()
{
  VSdetach(vdata_id_schskp);
  Vdetach(vgrp_id_schskp);
}

/*----     init access function    ----*/

int32 init_acc_schskp(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_schskp_error();


  if ((vdata_ref = VSfind(hdf_fp, "SCHskpData")) <= 0 ) {
    print_schskp_error("init_acc_schskp -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_schskp = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_schskp_error("init_acc_schskp -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_schskp, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_schskp,"sc_clk, TankA1Temp, TankA2Temp, TankB1Temp, TankB2Temp, LinesATemp, LinesBTemp, LinesPosXTemp, LinesNegXTemp, StarTrkTemp, InstDeckTemp1, InstDeckTemp2, InstDeckTemp3, InstDeckTemp4, InstDeckTemp5, InstDeckTemp6, InstDeckTemp7, InstDeckTemp8, LastSPTT0, ScIFHeaterCur, SunSnsrTemp, PosXSAPTemp, PosXSAPHTemp, NegXSAPTemp, NegXSAPHTemp, MagInTemp, MagOutTemp, MagInHtrPwrLvl, MagOutHtrPwrLvl, S3DPUPwrCvtVolt, PwrSubProACur, PwrSubProBCur, AxialThrstCur, Channel25, Channel26, Channel20, Channel30, DigTellLog0, DigTellLog1, data_2_1, MagSenIntTempPosY, MagSenIntTempNegY, data_2_2, data_3_1, MainBusCur, MainBusVolt, data_3_2, data_4_1, data_5_1, data_6_1, data_7_1, data_8_1, LastSPTT8, SwepamE_8VPSMon, SwepamE_HVMon1, SwepamE_HVMon2, SwepamI_8VPSMon, SwepamI_HVMon1, SwepamI_HVMon2, Epam_A1, Epam_A2, Epam_A3, Epam_A4, Epam_LAN1, Epam_LAN2A, Epam_LAN2B, Uleis_LVPSVolt, Cris_IntTemp1, Cris_IntTemp2, Sis_IntTemp1, Sis_IntTemp2, SunPulPhaAng0, data_10_1, data_10_2, Cris_Cur, Sis_Cur, Epam_Cur, Epam_HtrCur, Uleis_Cur, Uleis_AnaEleLVPSCur, DCM1_Chan21, Uleis_HtrCur, SwepamE_Cur, SwepamI_Cur, Swims_Cur, Swics_Cur, Sepica_Cur, Mag_Cur, S3DPU_Cur, data_10_3, PowSwiOrdBit, data_11_1, S3DPU_ConSecCur, PreTraCur, Swims_IntTemp, Swics_IntTemp, Uleis_TelTemp, Uleis_AnaEleTemp, Uleis_DPUTemp, Sepica_IsoTanTemp, S3DPU_PowSupATemp, SwepamE_IntTemp, SwepamI_IntTemp, StarScan, TermBoardFuse1Temp, data_12_1, S3DPU_PowSupBTemp, CDH_HKdat, data_15_1, SunPulPhaAng8, SelTelByt, SCIPhaAng, FormatID, CollForm, ADCPhaAng, SunSensor, ADCXtrDat, spare")) {
      print_schskp_error("init_acc_schskp -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_schskp(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_schskp(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_schskp(struct SCHskpData *SCHskpData_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_schskp_error();
void unpack_schskp();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct SCHskpData));
  VSinquire(vdata_id_schskp, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_schskp, recnum_rd)==FAIL) {
          print_schskp_error("read_schskp -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_schskp, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_schskp_error("read_schskp -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_schskp(odata, SCHskpData_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_schskp()
{
  VSdetach(vdata_id_schskp);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_schskp(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_schskp_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_SCHskpData" )) ==FAIL)
    print_schskp_error("rd_Vgrp_schskp -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_schskp_error("rd_Vgrp_schskp -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_schskp_error("rd_Vgrp_schskp -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_schskp_error("rd_Vgrp_schskp -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_SCHskpData, HDstrlen(Vgrp_descrp_SCHskpData)) ==FAIL)
    print_schskp_error("rd_Vgrp_schskp -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_SCHskpData);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_schskp_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_schskp.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_schskp(uint8 *data, struct SCHskpData *SCHskpData_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &SCHskpData_ptr->sc_clk, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->TankA1Temp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->TankA2Temp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->TankB1Temp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->TankB2Temp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->LinesATemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->LinesBTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->LinesPosXTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->LinesNegXTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->StarTrkTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->InstDeckTemp1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->InstDeckTemp2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->InstDeckTemp3, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->InstDeckTemp4, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->InstDeckTemp5, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->InstDeckTemp6, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->InstDeckTemp7, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->InstDeckTemp8, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->LastSPTT0[0], ((1)*(3)) );
   ptr+= ((1)*(3));
   memcpy(data+ptr, &SCHskpData_ptr->ScIFHeaterCur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->SunSnsrTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->PosXSAPTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->PosXSAPHTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->NegXSAPTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->NegXSAPHTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->MagInTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->MagOutTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->MagInHtrPwrLvl, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->MagOutHtrPwrLvl, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->S3DPUPwrCvtVolt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->PwrSubProACur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->PwrSubProBCur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->AxialThrstCur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Channel25, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Channel26, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Channel20, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Channel30, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->DigTellLog0, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->DigTellLog1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->data_2_1[0], ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(data+ptr, &SCHskpData_ptr->MagSenIntTempPosY, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->MagSenIntTempNegY, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->data_2_2[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &SCHskpData_ptr->data_3_1[0], ((1)*(10)) );
   ptr+= ((1)*(10));
   memcpy(data+ptr, &SCHskpData_ptr->MainBusCur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->MainBusVolt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->data_3_2[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &SCHskpData_ptr->data_4_1[0], ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(data+ptr, &SCHskpData_ptr->data_5_1[0], ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(data+ptr, &SCHskpData_ptr->data_6_1[0], ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(data+ptr, &SCHskpData_ptr->data_7_1[0], ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(data+ptr, &SCHskpData_ptr->data_8_1[0], ((1)*(17)) );
   ptr+= ((1)*(17));
   memcpy(data+ptr, &SCHskpData_ptr->LastSPTT8[0], ((1)*(3)) );
   ptr+= ((1)*(3));
   memcpy(data+ptr, &SCHskpData_ptr->SwepamE_8VPSMon, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->SwepamE_HVMon1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->SwepamE_HVMon2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->SwepamI_8VPSMon, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->SwepamI_HVMon1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->SwepamI_HVMon2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Epam_A1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Epam_A2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Epam_A3, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Epam_A4, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Epam_LAN1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Epam_LAN2A, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Epam_LAN2B, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Uleis_LVPSVolt, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Cris_IntTemp1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Cris_IntTemp2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Sis_IntTemp1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Sis_IntTemp2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->SunPulPhaAng0, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->data_10_1[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &SCHskpData_ptr->data_10_2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Cris_Cur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Sis_Cur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Epam_Cur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Epam_HtrCur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Uleis_Cur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Uleis_AnaEleLVPSCur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->DCM1_Chan21, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Uleis_HtrCur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->SwepamE_Cur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->SwepamI_Cur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Swims_Cur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Swics_Cur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Sepica_Cur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Mag_Cur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->S3DPU_Cur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->data_10_3[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &SCHskpData_ptr->PowSwiOrdBit[0], ((1)*(14)) );
   ptr+= ((1)*(14));
   memcpy(data+ptr, &SCHskpData_ptr->data_11_1[0], ((1)*(4)) );
   ptr+= ((1)*(4));
   memcpy(data+ptr, &SCHskpData_ptr->S3DPU_ConSecCur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->PreTraCur, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Swims_IntTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Swics_IntTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Uleis_TelTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Uleis_AnaEleTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Uleis_DPUTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->Sepica_IsoTanTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->S3DPU_PowSupATemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->SwepamE_IntTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->SwepamI_IntTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->StarScan[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &SCHskpData_ptr->TermBoardFuse1Temp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->data_12_1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->S3DPU_PowSupBTemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->CDH_HKdat[0], ((1)*(48)) );
   ptr+= ((1)*(48));
   memcpy(data+ptr, &SCHskpData_ptr->data_15_1[0], ((1)*(10)) );
   ptr+= ((1)*(10));
   memcpy(data+ptr, &SCHskpData_ptr->SunPulPhaAng8, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->SelTelByt[0], ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(data+ptr, &SCHskpData_ptr->SCIPhaAng[0], ((2)*(16)) );
   ptr+= ((2)*(16));
   memcpy(data+ptr, &SCHskpData_ptr->FormatID[0], ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(data+ptr, &SCHskpData_ptr->CollForm[0], ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(data+ptr, &SCHskpData_ptr->ADCPhaAng, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &SCHskpData_ptr->SunSensor[0], ((2)*(11)) );
   ptr+= ((2)*(11));
   memcpy(data+ptr, &SCHskpData_ptr->ADCXtrDat[0], ((1)*(51)) );
   ptr+= ((1)*(51));
   memcpy(data+ptr, &SCHskpData_ptr->spare[0], ((1)*(17)) );
   ptr+= ((1)*(17));
}

/*----   unpack function    ----*/

void unpack_schskp(uint8 *data, struct SCHskpData *SCHskpData_ptr)
{
int32 ptr=0;

   memcpy(&SCHskpData_ptr->sc_clk, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&SCHskpData_ptr->TankA1Temp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->TankA2Temp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->TankB1Temp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->TankB2Temp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->LinesATemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->LinesBTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->LinesPosXTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->LinesNegXTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->StarTrkTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->InstDeckTemp1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->InstDeckTemp2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->InstDeckTemp3, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->InstDeckTemp4, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->InstDeckTemp5, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->InstDeckTemp6, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->InstDeckTemp7, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->InstDeckTemp8, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->LastSPTT0[0], data+ptr,  ((1)*(3)) );
   ptr+= ((1)*(3));
   memcpy(&SCHskpData_ptr->ScIFHeaterCur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->SunSnsrTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->PosXSAPTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->PosXSAPHTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->NegXSAPTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->NegXSAPHTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->MagInTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->MagOutTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->MagInHtrPwrLvl, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->MagOutHtrPwrLvl, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->S3DPUPwrCvtVolt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->PwrSubProACur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->PwrSubProBCur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->AxialThrstCur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Channel25, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Channel26, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Channel20, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Channel30, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->DigTellLog0, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->DigTellLog1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->data_2_1[0], data+ptr,  ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(&SCHskpData_ptr->MagSenIntTempPosY, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->MagSenIntTempNegY, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->data_2_2[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&SCHskpData_ptr->data_3_1[0], data+ptr,  ((1)*(10)) );
   ptr+= ((1)*(10));
   memcpy(&SCHskpData_ptr->MainBusCur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->MainBusVolt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->data_3_2[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&SCHskpData_ptr->data_4_1[0], data+ptr,  ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(&SCHskpData_ptr->data_5_1[0], data+ptr,  ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(&SCHskpData_ptr->data_6_1[0], data+ptr,  ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(&SCHskpData_ptr->data_7_1[0], data+ptr,  ((1)*(20)) );
   ptr+= ((1)*(20));
   memcpy(&SCHskpData_ptr->data_8_1[0], data+ptr,  ((1)*(17)) );
   ptr+= ((1)*(17));
   memcpy(&SCHskpData_ptr->LastSPTT8[0], data+ptr,  ((1)*(3)) );
   ptr+= ((1)*(3));
   memcpy(&SCHskpData_ptr->SwepamE_8VPSMon, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->SwepamE_HVMon1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->SwepamE_HVMon2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->SwepamI_8VPSMon, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->SwepamI_HVMon1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->SwepamI_HVMon2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Epam_A1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Epam_A2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Epam_A3, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Epam_A4, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Epam_LAN1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Epam_LAN2A, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Epam_LAN2B, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Uleis_LVPSVolt, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Cris_IntTemp1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Cris_IntTemp2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Sis_IntTemp1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Sis_IntTemp2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->SunPulPhaAng0, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&SCHskpData_ptr->data_10_1[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&SCHskpData_ptr->data_10_2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Cris_Cur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Sis_Cur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Epam_Cur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Epam_HtrCur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Uleis_Cur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Uleis_AnaEleLVPSCur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->DCM1_Chan21, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Uleis_HtrCur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->SwepamE_Cur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->SwepamI_Cur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Swims_Cur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Swics_Cur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Sepica_Cur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Mag_Cur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->S3DPU_Cur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->data_10_3[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&SCHskpData_ptr->PowSwiOrdBit[0], data+ptr,  ((1)*(14)) );
   ptr+= ((1)*(14));
   memcpy(&SCHskpData_ptr->data_11_1[0], data+ptr,  ((1)*(4)) );
   ptr+= ((1)*(4));
   memcpy(&SCHskpData_ptr->S3DPU_ConSecCur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->PreTraCur, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Swims_IntTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Swics_IntTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Uleis_TelTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Uleis_AnaEleTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Uleis_DPUTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->Sepica_IsoTanTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->S3DPU_PowSupATemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->SwepamE_IntTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->SwepamI_IntTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->StarScan[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&SCHskpData_ptr->TermBoardFuse1Temp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->data_12_1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->S3DPU_PowSupBTemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&SCHskpData_ptr->CDH_HKdat[0], data+ptr,  ((1)*(48)) );
   ptr+= ((1)*(48));
   memcpy(&SCHskpData_ptr->data_15_1[0], data+ptr,  ((1)*(10)) );
   ptr+= ((1)*(10));
   memcpy(&SCHskpData_ptr->SunPulPhaAng8, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&SCHskpData_ptr->SelTelByt[0], data+ptr,  ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(&SCHskpData_ptr->SCIPhaAng[0], data+ptr,  ((2)*(16)) );
   ptr+= ((2)*(16));
   memcpy(&SCHskpData_ptr->FormatID[0], data+ptr,  ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(&SCHskpData_ptr->CollForm[0], data+ptr,  ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(&SCHskpData_ptr->ADCPhaAng, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&SCHskpData_ptr->SunSensor[0], data+ptr,  ((2)*(11)) );
   ptr+= ((2)*(11));
   memcpy(&SCHskpData_ptr->ADCXtrDat[0], data+ptr,  ((1)*(51)) );
   ptr+= ((1)*(51));
   memcpy(&SCHskpData_ptr->spare[0], data+ptr,  ((1)*(17)) );
   ptr+= ((1)*(17));
}
int32 get_vgrp_id_schskp() {return(vgrp_id_schskp);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_schskp(char *wr_strval)
{
  strcpy(wr_strval, "The file 'schskp.h' is shown below, it was used to create the data in the Vgroup named 'VG_SCHskpData'.\n\n");
  strcat(wr_strval,"/* Id: schskp.h,v 1.10 1997/08/01 17:11:35 jeff Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"/*--------------------------------------------------------------------*/\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* for Science format, 20 bytes per minor frame for 16 minor frames */\n");
  strcat(wr_strval,"/*   Selectable telemetry byte and Phase angle values ,             */\n");
  strcat(wr_strval,"/*   Format ID byte and Colletion format byte from every */\n");
  strcat(wr_strval,"/*   minor frame will also be accumulated                           */\n");
  strcat(wr_strval,"/* Total for science Format, 320 bytes + 16 bytes + 32 bytes        */\n");
  strcat(wr_strval,"/*   +16 bytes +16 bytes = 400  */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* for ADC format, 320 bytes + 51 \"extra\" bytes + 2 byte Sun Pulse  */\n");
  strcat(wr_strval,"/*   phase angle + 22 bytes Sun Sensor data + 17 bytes spare +      */\n");
  strcat(wr_strval,"/*   16 bytes Selectable telemetry byte + 32 bytes Phase angle      */\n");
  strcat(wr_strval,"/*   +16 Format ID +16 Colletion format */\n");
  strcat(wr_strval,"/* Total for ADC Format, 320 + 51 + 2 + 22 + 17 + 16 + 32 = 492 bytes */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* in ADC mode */\n");
  strcat(wr_strval,"/* Only the first Selectable telemtry byte, and the first Phase angle */\n");
  strcat(wr_strval,"/* will be reported, the rest 15 Selectable telemtry bytes and Phase */\n");
  strcat(wr_strval,"/* angle values will be zeroed                                       */\n");
  strcat(wr_strval,"/* Same for Format ID and Colletion format bytes */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* The values LastSPTT8, SunPulPhaAng{0/8}, will be zeroed for ADC format */\n");
  strcat(wr_strval,"/* LastSPTT0 will be the sun pulse time tag value in ADC format */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* Both formats will have the value of the S/C clock reported as well. */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct SCHskpData\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32  sc_clk;\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /*--- following 20 bytes hskp items appear in mn_frm 0 in sci_fmt ---*/\n");
  strcat(wr_strval,"  uint8 TankA1Temp;       /* Propellant Tank A1 Temperature */\n");
  strcat(wr_strval,"  uint8 TankA2Temp;       /* Propellant Tank A2 Temperature */\n");
  strcat(wr_strval,"  uint8 TankB1Temp;       /* Propellant Tank B1 Temperature */\n");
  strcat(wr_strval,"  uint8 TankB2Temp;       /* Propellant Tank B2 Temperature */\n");
  strcat(wr_strval,"  uint8 LinesATemp;       /* Internal Lines A Temperature   */\n");
  strcat(wr_strval,"  uint8 LinesBTemp;       /* Internal Lines B Temperature   */\n");
  strcat(wr_strval,"  uint8 LinesPosXTemp;    /* External Lines +X Temperature  */\n");
  strcat(wr_strval,"  uint8 LinesNegXTemp;    /* External Lines -X Temperature  */\n");
  strcat(wr_strval,"  uint8 StarTrkTemp;      /* Star Tracker Temperature       */\n");
  strcat(wr_strval,"  uint8 InstDeckTemp1;    /* Instrument Deck Temperature #1 */\n");
  strcat(wr_strval,"  uint8 InstDeckTemp2;    /* Instrument Deck Temperature #2 */\n");
  strcat(wr_strval,"  uint8 InstDeckTemp3;    /* Instrument Deck Temperature #3 */\n");
  strcat(wr_strval,"  uint8 InstDeckTemp4;    /* Instrument Deck Temperature #4 */\n");
  strcat(wr_strval,"  uint8 InstDeckTemp5;    /* Instrument Deck Temperature #5 */\n");
  strcat(wr_strval,"  uint8 InstDeckTemp6;    /* Instrument Deck Temperature #6 */\n");
  strcat(wr_strval,"  uint8 InstDeckTemp7;    /* Instrument Deck Temperature #7 */\n");
  strcat(wr_strval,"  uint8 InstDeckTemp8;    /* Instrument Deck Temperature #8 */\n");
  strcat(wr_strval,"  uint8 LastSPTT0[3];     /* 24 bits, Last SP TT=4 Mnr Frm, ... */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /*--- following 20 bytes hskp items appear in mn_frm 1 in sci_fmt ---*/\n");
  strcat(wr_strval,"  uint8 ScIFHeaterCur;    /* Spacecraft Specific I/F Heater Current */\n");
  strcat(wr_strval,"  uint8 SunSnsrTemp;      /* Sun Sensor (-X/-Y Side) Temperature */\n");
  strcat(wr_strval,"  uint8 PosXSAPTemp;      /* +X Solar Array Panel Temperature */\n");
  strcat(wr_strval,"  uint8 PosXSAPHTemp;     /* +X Solar Array Panel Hinge Temperature */\n");
  strcat(wr_strval,"  uint8 NegXSAPTemp;      /* -X Solar Array Panel Temperature */\n");
  strcat(wr_strval,"  uint8 NegXSAPHTemp;     /* -X Solar Array Panel Hinge Temperature */\n");
  strcat(wr_strval,"  uint8 MagInTemp;        /* Magnetometer Inboard Temperature */\n");
  strcat(wr_strval,"  uint8 MagOutTemp;       /* Magnetometer Outboard Temperature */\n");
  strcat(wr_strval,"  uint8 MagInHtrPwrLvl;   /* Mag Inboard Heater Power Level */\n");
  strcat(wr_strval,"  uint8 MagOutHtrPwrLvl;  /* Mag Outboard Heater Power Level */\n");
  strcat(wr_strval,"  uint8 S3DPUPwrCvtVolt;  /* S3 DPU Power Conveter Voltage */\n");
  strcat(wr_strval,"  uint8 PwrSubProACur;    /* Power Subsystem Processor A Current */\n");
  strcat(wr_strval,"  uint8 PwrSubProBCur;    /* Power Subsystem Processor B Current */\n");
  strcat(wr_strval,"  uint8 AxialThrstCur;    /* Axial Thruster Current */\n");
  strcat(wr_strval,"  uint8 Channel25;        /* 0-50mV Channel #25 */\n");
  strcat(wr_strval,"  uint8 Channel26;        /* 0-50mV Channel #26 */\n");
  strcat(wr_strval,"  uint8 Channel20;        /* 0-5V Channel #20 */\n");
  strcat(wr_strval,"  uint8 Channel30;        /* AD590 Channel #30 */\n");
  strcat(wr_strval,"  uint8 DigTellLog0;      /* Digital Telltale logic byte 0 */\n");
  strcat(wr_strval,"  uint8 DigTellLog1;      /* Digital Telltale logic byte 1 */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* --- next 20 bytes from min frame 2 -- */\n");
  strcat(wr_strval,"  uint8 data_2_1[16];		    /* first 16 bytes of min frm 2 hskp */\n");
  strcat(wr_strval,"  uint8 MagSenIntTempPosY;        /* Mag +Y Sensor interface temp */\n");
  strcat(wr_strval,"  uint8 MagSenIntTempNegY;        /* Mag -Y Sensor interface temp */\n");
  strcat(wr_strval,"  uint8 data_2_2[2];		    /* last 2 bytes of min frm 2 hskp */\n");
  strcat(wr_strval,"  /* --- next 20 bytes from min frame 3 -- */\n");
  strcat(wr_strval,"  uint8 data_3_1[10];		    /* 10 bytes of min frm 3 hskp */\n");
  strcat(wr_strval,"  uint8 MainBusCur;                 /* Main bus curent */\n");
  strcat(wr_strval,"  uint8 MainBusVolt;                /* Main bus voltage */\n");
  strcat(wr_strval,"  uint8 data_3_2[8];		    /* last 8 bytes of min frm 3 hskp */\n");
  strcat(wr_strval,"  /* --- next 20 bytes from min frame 4 -- */\n");
  strcat(wr_strval,"  uint8 data_4_1[20];		    /* 20 bytes of min frm 4 hskp */\n");
  strcat(wr_strval,"  /* --- next 20 bytes from min frame 5 -- */\n");
  strcat(wr_strval,"  uint8 data_5_1[20];		    /* 20 bytes of min frm 5 hskp */\n");
  strcat(wr_strval,"  /* --- next 20 bytes from min frame 6 -- */\n");
  strcat(wr_strval,"  uint8 data_6_1[20];		    /* 20 bytes of min frm 6 hskp */\n");
  strcat(wr_strval,"  /* --- next 20 bytes from min frame 7 -- */\n");
  strcat(wr_strval,"  uint8 data_7_1[20];		    /* 20 bytes of min frm 7 hskp */\n");
  strcat(wr_strval,"  /* --- next 20 bytes from min frame 8 -- */\n");
  strcat(wr_strval,"  uint8 data_8_1[17];		    /* 17 bytes of min frm 8 hskp */\n");
  strcat(wr_strval,"  uint8 LastSPTT8[3];              /* 24 bits, Last SP TT=4 Mnr Frm, ... */\n");
  strcat(wr_strval,"  /* --- next 20 bytes from min frame 9 -- */\n");
  strcat(wr_strval,"  uint8 SwepamE_8VPSMon;  /* SWEPAME +8 V Power Supply monitor */\n");
  strcat(wr_strval,"  uint8 SwepamE_HVMon1;   /* SWEPAME HVMON1-subcommed over 8 mj frames */\n");
  strcat(wr_strval,"  uint8 SwepamE_HVMon2;   /* SWEPAME HVMON2-subcommed over 8 mj frames */\n");
  strcat(wr_strval,"  uint8 SwepamI_8VPSMon;  /* SWEPAMI +8 V Power Supply monitor */\n");
  strcat(wr_strval,"  uint8 SwepamI_HVMon1;   /* SWEPAMI HVMON1-subcommed over 8 mj frames */\n");
  strcat(wr_strval,"  uint8 SwepamI_HVMon2;   /* SWEPAMI HVMON2-subcommed over 8 mj frames */\n");
  strcat(wr_strval,"  uint8 Epam_A1;          /* EPAM Analog A1, Int/Ext Cal Readout */\n");
  strcat(wr_strval,"  uint8 Epam_A2;          /* EPAM Analog A2, subcommed over 8 mj frames */\n");
  strcat(wr_strval,"  uint8 Epam_A3;          /* EPAM Analog A3, subcommed over 8 mj frames */\n");
  strcat(wr_strval,"  uint8 Epam_A4;          /* EPAM Analog A4, Input Current Monitor */\n");
  strcat(wr_strval,"  uint8 Epam_LAN1;        /* EPAM LAN 1, Electronics temp thermistor */\n");
  strcat(wr_strval,"  uint8 Epam_LAN2A;       /* EPAM LAN 2A, Electronics temp thermistor */\n");
  strcat(wr_strval,"  uint8 Epam_LAN2B;       /* EPAM LAN 2A, Sensor temp thermistor */\n");
  strcat(wr_strval,"  uint8 Uleis_LVPSVolt;   /* ULEIS LVPS Voltage */\n");
  strcat(wr_strval,"  uint8 Cris_IntTemp1;    /* CRIS Internal Temp #1 */\n");
  strcat(wr_strval,"  uint8 Cris_IntTemp2;    /* CRIS Internal Temp #2 */\n");
  strcat(wr_strval,"  uint8 Sis_IntTemp1;     /* SIS Internal Temp #1 */\n");
  strcat(wr_strval,"  uint8 Sis_IntTemp2;     /* SIS Internal Temp #2 */\n");
  strcat(wr_strval,"  uint16 SunPulPhaAng0;  /* Phase angle latched with Sun Pulse in mn frm 0 */\n");
  strcat(wr_strval,"  /* --- next 20 bytes from min frame 10 -- */\n");
  strcat(wr_strval,"  uint8 data_10_1[2];\n");
  strcat(wr_strval,"  uint8 data_10_2;     \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /*  unsigned DigTelSwiCha15:1; Digital telltale switch #15 */\n");
  strcat(wr_strval,"  /*  unsigned Sis_CovTell:1;    SIS Cover Telltale */\n");
  strcat(wr_strval,"  /*  unsigned S3DPU_PowConSelTell:1;  S3DPU power converter select TT */\n");
  strcat(wr_strval,"  /*  unsigned Swims_CovTell:1;  SWIMS cover Tell Tale */\n");
  strcat(wr_strval,"  /*  unsigned data_10_2:4; */\n");
  strcat(wr_strval,"  uint8 Cris_Cur;          /* CRIS current including detector bias */\n");
  strcat(wr_strval,"  uint8 Sis_Cur;           /* SIS current including detector bias */\n");
  strcat(wr_strval,"  uint8 Epam_Cur;          /* EPAM current */\n");
  strcat(wr_strval,"  uint8 Epam_HtrCur;       /* EPAM heater current */\n");
  strcat(wr_strval,"  uint8 Uleis_Cur;       /* ULEIS current */\n");
  strcat(wr_strval,"  uint8 Uleis_AnaEleLVPSCur;  /* ULEIS current, Analog Electronics LVPS  */\n");
  strcat(wr_strval,"  uint8 DCM1_Chan21;      /* DCM1 0-50mV channel 21 */\n");
  strcat(wr_strval,"  uint8 Uleis_HtrCur;      /* ULEIS Heater current */\n");
  strcat(wr_strval,"  uint8 SwepamE_Cur;      /* SWEPAM electron current */\n");
  strcat(wr_strval,"  uint8 SwepamI_Cur;      /* SWEPAM ion current */\n");
  strcat(wr_strval,"  uint8 Swims_Cur;      /* SWIMS current */\n");
  strcat(wr_strval,"  uint8 Swics_Cur;      /* SWICS current */\n");
  strcat(wr_strval,"  uint8 Sepica_Cur;      /* SEPICA current */\n");
  strcat(wr_strval,"  uint8 Mag_Cur;      /* MAG current (DPU A, DPU B, Heater) */\n");
  strcat(wr_strval,"  uint8 S3DPU_Cur;      /* S3DPU current  */\n");
  strcat(wr_strval,"  uint8 data_10_3[2];\n");
  strcat(wr_strval,"  /* --- next 20 bytes from min frame 11 -- */\n");
  strcat(wr_strval,"  uint8 PowSwiOrdBit[14];  /* Power switching and ordinance bits - may */\n");
  strcat(wr_strval,"			  /* decide to do all 112 items individually later */\n");
  strcat(wr_strval,"      /* unsigned S3DPU_IntABSel:1;  S^3 DPU Interface A/B Select */\n");
  strcat(wr_strval,"      /* data:7 */\n");
  strcat(wr_strval,"  uint8 data_11_1[4];\n");
  strcat(wr_strval,"  uint8 S3DPU_ConSecCur;  /* S3DPU Converter Secondary Current */\n");
  strcat(wr_strval,"  uint8 PreTraCur;       /* Pressure Transducer Current */\n");
  strcat(wr_strval,"  /* --- next 20 bytes from min frame 12 -- */\n");
  strcat(wr_strval,"  uint8 Swims_IntTemp;   /* SWIMS Internal Temp */\n");
  strcat(wr_strval,"  uint8 Swics_IntTemp;   /* SWICS Internal Temp */\n");
  strcat(wr_strval,"  uint8 Uleis_TelTemp;   /* ULEIS Telescope Temp */\n");
  strcat(wr_strval,"  uint8 Uleis_AnaEleTemp;   /* ULEIS Analog Electronics Temp */\n");
  strcat(wr_strval,"  uint8 Uleis_DPUTemp;   /* ULEIS DPU Temp */\n");
  strcat(wr_strval,"  uint8 Sepica_IsoTanTemp;   /* SEPICA Isobutane Tank temp */\n");
  strcat(wr_strval,"  uint8 S3DPU_PowSupATemp;   /* S^3 DPU Power supply A temp */\n");
  strcat(wr_strval,"  uint8 SwepamE_IntTemp;   /* SWEPAM Electron Internal Temp */\n");
  strcat(wr_strval,"  uint8 SwepamI_IntTemp;   /* SWEPAM Ion Internal Temp */\n");
  strcat(wr_strval,"  uint8 StarScan[8];      /* Star Scanner data */\n");
  strcat(wr_strval,"  uint8 TermBoardFuse1Temp;  \n");
  strcat(wr_strval,"  uint8 data_12_1;\n");
  strcat(wr_strval,"  uint8 S3DPU_PowSupBTemp;   /* S^3 DPU Power supply B temp */\n");
  strcat(wr_strval,"  /* --- next 48 bytes from min frame 13 14 & 15-- */\n");
  strcat(wr_strval,"  uint8 CDH_HKdat[48];\n");
  strcat(wr_strval,"  /* --- next 12 bytes from min frame 15-- */\n");
  strcat(wr_strval,"  uint8 data_15_1[10];\n");
  strcat(wr_strval,"  uint16 SunPulPhaAng8;  /* Phase angle latched with Sun Pulse in mn frm 8 */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* these total 80 bytes are Selectable Telemtry Byte, Format ID, */\n");
  strcat(wr_strval,"  /* Collection format and Science format phase angle data. */\n");
  strcat(wr_strval,"  /* ADC format will have only the first values, others are zeroed */\n");
  strcat(wr_strval,"  uint8  SelTelByt[16];   /* Selectable Telemtry Byte */\n");
  strcat(wr_strval,"  uint16 SCIPhaAng[16];   /* Science Format phase angle data */\n");
  strcat(wr_strval,"  uint8  FormatID[16];    /* FormatID:4, SunSenTop:1,SunSenSide:1,C&DH ID:2*/\n");
  strcat(wr_strval,"  uint8  CollForm[16];    /* CollFormat:1, mjfrm:3,mnfrm:4 */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* Found in ADC format only */\n");
  strcat(wr_strval,"  uint16 ADCPhaAng;  /* ADC format phase angle value */\n");
  strcat(wr_strval,"  uint16 SunSensor[11];  /* 11 sun sensor values */\n");
  strcat(wr_strval,"  uint8 ADCXtrDat[51];   /* 51 bytes of data found only in ADC format */\n");
  strcat(wr_strval,"  uint8 spare[17];       /* 17 bytes of unallocated data in ADC format */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"};\n");
  return(0);
}
