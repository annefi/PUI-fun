/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: epam.h,v 1.8 1997/08/06 19:51:21 jeff Exp  */

#include "epam.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_epam_data;
static int32 vdata_id_epam_data;

static int32 sds_id_epam_data1, sds_id_epam_data2, sds_id_epam_data3;

  /* 4149 is the size of epam.h + 1 added line */
char Vgrp_descrp_EpamData[4149];

/****----  init create function  ----****/

int32 init_cr_epam_data(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1, sds_ref_w2, sds_ref_w3;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_epam_data();

  void print_epam_data_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_epam_data = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_epam_data_error("init_cr_epam_data -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_epam_data, "VG_EpamData"); 
  Vsetclass(vgrp_id_epam_data, "VG_EPAM");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_EpamData" )) ==FAIL) {
    print_epam_data_error("init_cr_epam_data -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_epam_data(Vgrp_descrp_EpamData);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_epam_data_error("init_cr_epam_data -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_EpamData, sizeof(Vgrp_descrp_EpamData))) ==FAIL) {
    print_epam_data_error("init_cr_epam_data -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_epam_data = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_epam_data_error("init_cr_epam_data -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_epam_data, "EpamData");
  VSsetclass(vdata_id_epam_data, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_epam_data, vdata_id_epam_data)) ==FAIL) {
    print_epam_data_error("init_cr_epam_data -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_epam_data, "sctime_readout", DFNT_UINT32, (1) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "sctime_collection", DFNT_UINT32, (1) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "QAC", DFNT_UINT32, (1) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "QACarr", DFNT_UINT8, (NUMFRM) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define QACarr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "PhaseAng", DFNT_UINT16, (NUMFRM) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define PhaseAng");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "Cal", DFNT_UINT8, (8) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define Cal");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "Ref10", DFNT_UINT8, (2) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define Ref10");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "Mon10", DFNT_UINT8, (2) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define Mon10");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "Mon6", DFNT_UINT8, (2) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define Mon6");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "Bias", DFNT_UINT8, (2) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define Bias");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "AmpTemp", DFNT_UINT8, (2) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define AmpTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "MFSATemp", DFNT_UINT8, (2) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define MFSATemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "DetTemp", DFNT_UINT8, (2) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define DetTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "YTemp", DFNT_UINT8, (2) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define YTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "InCur", DFNT_UINT8, (8) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define InCur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "E1Temp", DFNT_UINT8, (8) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define E1Temp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "Sen2ATemp", DFNT_UINT8, (8) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define Sen2ATemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "Sen2BTemp", DFNT_UINT8, (8) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define Sen2BTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "DeckTemp", DFNT_UINT8, (8) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define DeckTemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "Cur", DFNT_UINT8, (8) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define Cur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "HtrCur", DFNT_UINT8, (8) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define HtrCur");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_data, "PowBits", DFNT_UINT8, (8) )) {
    print_epam_data_error("init_cr_epam_data -> VSfdefine: Couldn't define PowBits");
    retval = -1;
  }

  if (VSsetfields(vdata_id_epam_data,"sctime_readout, sctime_collection, QAC, QACarr, PhaseAng, Cal, Ref10, Mon10, Mon6, Bias, AmpTemp, MFSATemp, DetTemp, YTemp, InCur, E1Temp, Sen2ATemp, Sen2BTemp, DeckTemp, Cur, HtrCur, PowBits")){
    print_epam_data_error("init_cr_epam_data -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = NUMFRM;
  dim_sizes[2] = BYTMIN;
  if((sds_id_epam_data1 = SDcreate(sd_id, "EpamData_data", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_epam_data_error("init_cr_epam_data -> SDcreate: Couldn't create EpamData_data");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_epam_data1)) == FAIL)
    print_epam_data_error("init_cr_epam_data -> SDidtoref: Couldn't get ref for EpamData_data");

  if((Vaddtagref(vgrp_id_epam_data, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_epam_data_error("init_cr_epam_data -> Vaddtagref: Couldn't add SDS EpamData_data to Vgrp");

  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 2;
  dim_sizes[2] = 8;
  if((sds_id_epam_data2 = SDcreate(sd_id, "EpamData_SunPulLat", DFNT_UINT16, rank, dim_sizes)) == FAIL)
    print_epam_data_error("init_cr_epam_data -> SDcreate: Couldn't create EpamData_SunPulLat");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w2 = SDidtoref(sds_id_epam_data2)) == FAIL)
    print_epam_data_error("init_cr_epam_data -> SDidtoref: Couldn't get ref for EpamData_SunPulLat");

  if((Vaddtagref(vgrp_id_epam_data, DFTAG_NDG, sds_ref_w2)) == FAIL)
    print_epam_data_error("init_cr_epam_data -> Vaddtagref: Couldn't add SDS EpamData_SunPulLat to Vgrp");

  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 2;
  dim_sizes[2] = 8;
  if((sds_id_epam_data3 = SDcreate(sd_id, "EpamData_SunPulDat", DFNT_UINT32, rank, dim_sizes)) == FAIL)
    print_epam_data_error("init_cr_epam_data -> SDcreate: Couldn't create EpamData_SunPulDat");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w3 = SDidtoref(sds_id_epam_data3)) == FAIL)
    print_epam_data_error("init_cr_epam_data -> SDidtoref: Couldn't get ref for EpamData_SunPulDat");

  if((Vaddtagref(vgrp_id_epam_data, DFTAG_NDG, sds_ref_w3)) == FAIL)
    print_epam_data_error("init_cr_epam_data -> Vaddtagref: Couldn't add SDS EpamData_SunPulDat to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_epam_data(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_epam_data(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_epam_data(struct EpamData EpamData_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_epam_data_error();
void pack_epam_data();

  odata = (uint8 *) malloc(sizeof(struct EpamData));
  pack_epam_data(odata, &EpamData_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_epam_data, recnum)==-1) {
		print_epam_data_error("write_epam_data -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_epam_data, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_epam_data_error("write_epam_data -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = NUMFRM;
  edges[2] = BYTMIN;
  if (SDwritedata(sds_id_epam_data1,start,NULL,edges, (VOIDP)(EpamData_struc.data)) ==FAIL)
    print_epam_data_error("write_epam_data -> SDwritedata: Problem writing data data.");

  edges[1] = 2;
  edges[2] = 8;
  if (SDwritedata(sds_id_epam_data2,start,NULL,edges, (VOIDP)(EpamData_struc.SunPulLat)) ==FAIL)
    print_epam_data_error("write_epam_data -> SDwritedata: Problem writing SunPulLat data.");

  edges[1] = 2;
  edges[2] = 8;
  if (SDwritedata(sds_id_epam_data3,start,NULL,edges, (VOIDP)(EpamData_struc.SunPulDat)) ==FAIL)
    print_epam_data_error("write_epam_data -> SDwritedata: Problem writing SunPulDat data.");

  memset(&EpamData_struc, 0, sizeof(struct EpamData));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_epam_data()
{
  VSdetach(vdata_id_epam_data);
  Vdetach(vgrp_id_epam_data);
  SDendaccess(sds_id_epam_data1);
  SDendaccess(sds_id_epam_data2);
  SDendaccess(sds_id_epam_data3);
}

/*----     init access function    ----*/

int32 init_acc_epam_data(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  static int32 sds_index2;
  static int32 sds_index3;
  int32 vdata_ref;
  int32 num_rec;

  void print_epam_data_error();

  if((sds_index1=SDnametoindex(sd_id, "EpamData_data" )) ==FAIL) {
      print_epam_data_error("init_acc_epam_data -> SDnametoindex: Couldn't find EpamData_data");
      return(-1);
  }
  if((sds_id_epam_data1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_epam_data_error("init_acc_epam_data -> SDselect: Couldn't select sds_index1");
      return(-1);
  }
  if((sds_index2=SDnametoindex(sd_id, "EpamData_SunPulLat" )) ==FAIL) {
      print_epam_data_error("init_acc_epam_data -> SDnametoindex: Couldn't find EpamData_SunPulLat");
      return(-1);
  }
  if((sds_id_epam_data2=SDselect(sd_id, sds_index2)) ==FAIL) {
      print_epam_data_error("init_acc_epam_data -> SDselect: Couldn't select sds_index2");
      return(-1);
  }
  if((sds_index3=SDnametoindex(sd_id, "EpamData_SunPulDat" )) ==FAIL) {
      print_epam_data_error("init_acc_epam_data -> SDnametoindex: Couldn't find EpamData_SunPulDat");
      return(-1);
  }
  if((sds_id_epam_data3=SDselect(sd_id, sds_index3)) ==FAIL) {
      print_epam_data_error("init_acc_epam_data -> SDselect: Couldn't select sds_index3");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "EpamData")) <= 0 ) {
    print_epam_data_error("init_acc_epam_data -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_epam_data = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_epam_data_error("init_acc_epam_data -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_epam_data, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_epam_data,"sctime_readout, sctime_collection, QAC, QACarr, PhaseAng, Cal, Ref10, Mon10, Mon6, Bias, AmpTemp, MFSATemp, DetTemp, YTemp, InCur, E1Temp, Sen2ATemp, Sen2BTemp, DeckTemp, Cur, HtrCur, PowBits")) {
      print_epam_data_error("init_acc_epam_data -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_epam_data(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_epam_data(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_epam_data(struct EpamData *EpamData_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_epam_data_error();
void unpack_epam_data();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct EpamData));
  VSinquire(vdata_id_epam_data, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_epam_data, recnum_rd)==FAIL) {
          print_epam_data_error("read_epam_data -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = NUMFRM;
  edges[2] = BYTMIN;

  if(SDreaddata(sds_id_epam_data1,start,NULL,edges, (VOIDP)(EpamData_struc->data )) ==FAIL) {
    print_epam_data_error("read_epam_data -> SDreaddata: Couldn't read data");
    retval = -1;
  }
  edges[1] = 2;
  edges[2] = 8;

  if(SDreaddata(sds_id_epam_data2,start,NULL,edges, (VOIDP)(EpamData_struc->SunPulLat )) ==FAIL) {
    print_epam_data_error("read_epam_data -> SDreaddata: Couldn't read SunPulLat");
    retval = -1;
  }
  edges[1] = 2;
  edges[2] = 8;

  if(SDreaddata(sds_id_epam_data3,start,NULL,edges, (VOIDP)(EpamData_struc->SunPulDat )) ==FAIL) {
    print_epam_data_error("read_epam_data -> SDreaddata: Couldn't read SunPulDat");
    retval = -1;
  }
  if(VSread(vdata_id_epam_data, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_epam_data_error("read_epam_data -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_epam_data(odata, EpamData_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_epam_data()
{
  VSdetach(vdata_id_epam_data);
  SDendaccess(sds_id_epam_data1);
  SDendaccess(sds_id_epam_data2);
  SDendaccess(sds_id_epam_data3);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_epam_data(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_epam_data_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_EpamData" )) ==FAIL)
    print_epam_data_error("rd_Vgrp_epam_data -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_epam_data_error("rd_Vgrp_epam_data -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_epam_data_error("rd_Vgrp_epam_data -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_epam_data_error("rd_Vgrp_epam_data -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_EpamData, HDstrlen(Vgrp_descrp_EpamData)) ==FAIL)
    print_epam_data_error("rd_Vgrp_epam_data -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_EpamData);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_epam_data_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_epam_data.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_epam_data(uint8 *data, struct EpamData *EpamData_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &EpamData_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &EpamData_ptr->sctime_collection, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &EpamData_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &EpamData_ptr->QACarr[0], ((1)*(NUMFRM)) );
   ptr+= ((1)*(NUMFRM));
   memcpy(data+ptr, &EpamData_ptr->PhaseAng[0], ((2)*(NUMFRM)) );
   ptr+= ((2)*(NUMFRM));
   memcpy(data+ptr, &EpamData_ptr->Cal[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &EpamData_ptr->Ref10[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &EpamData_ptr->Mon10[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &EpamData_ptr->Mon6[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &EpamData_ptr->Bias[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &EpamData_ptr->AmpTemp[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &EpamData_ptr->MFSATemp[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &EpamData_ptr->DetTemp[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &EpamData_ptr->YTemp[0], ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(data+ptr, &EpamData_ptr->InCur[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &EpamData_ptr->E1Temp[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &EpamData_ptr->Sen2ATemp[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &EpamData_ptr->Sen2BTemp[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &EpamData_ptr->DeckTemp[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &EpamData_ptr->Cur[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &EpamData_ptr->HtrCur[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &EpamData_ptr->PowBits[0], ((1)*(8)) );
   ptr+= ((1)*(8));
}

/*----   unpack function    ----*/

void unpack_epam_data(uint8 *data, struct EpamData *EpamData_ptr)
{
int32 ptr=0;

   memcpy(&EpamData_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&EpamData_ptr->sctime_collection, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&EpamData_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&EpamData_ptr->QACarr[0], data+ptr,  ((1)*(NUMFRM)) );
   ptr+= ((1)*(NUMFRM));
   memcpy(&EpamData_ptr->PhaseAng[0], data+ptr,  ((2)*(NUMFRM)) );
   ptr+= ((2)*(NUMFRM));
   memcpy(&EpamData_ptr->Cal[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&EpamData_ptr->Ref10[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&EpamData_ptr->Mon10[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&EpamData_ptr->Mon6[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&EpamData_ptr->Bias[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&EpamData_ptr->AmpTemp[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&EpamData_ptr->MFSATemp[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&EpamData_ptr->DetTemp[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&EpamData_ptr->YTemp[0], data+ptr,  ((1)*(2)) );
   ptr+= ((1)*(2));
   memcpy(&EpamData_ptr->InCur[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&EpamData_ptr->E1Temp[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&EpamData_ptr->Sen2ATemp[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&EpamData_ptr->Sen2BTemp[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&EpamData_ptr->DeckTemp[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&EpamData_ptr->Cur[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&EpamData_ptr->HtrCur[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&EpamData_ptr->PowBits[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
}
int32 get_vgrp_id_epam_data() {return(vgrp_id_epam_data);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_epam_data(char *wr_strval)
{
  strcpy(wr_strval, "The file 'epam.h' is shown below, it was used to create the data in the Vgroup named 'VG_EpamData'.\n\n");
  strcat(wr_strval,"/* Id: epam.h,v 1.8 1997/08/06 19:51:21 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define NUMFRM 128  /* number of minor frames in a cycle */\n");
  strcat(wr_strval,"#define BYTMIN 21   /* number of bytes of epam data per minor frame */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* reported every 8 major frames (128 minor frames)*/\n");
  strcat(wr_strval,"/* some items are subcommed, hence there are only 2 of them in 8 frames */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct EpamData\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 sctime_readout;      /* 32 bit spacecraft time at readout */\n");
  strcat(wr_strval,"  uint32 sctime_collection;   /* 32 bit spacecraft time at collection*/\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint32 QAC;	  /* indicates the number of missing frame in this cycle */\n");
  strcat(wr_strval,"  uint8 QACarr[NUMFRM]; /* each entry corresponds to a single minor frame */\n");
  strcat(wr_strval,"		    /* if value =0 frame is OK.  =1 frame contains fill data*/\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint8 data[NUMFRM][BYTMIN]; /* 21 bytes data per minor frame */\n");
  strcat(wr_strval,"				/* 128 minor frames per cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* sunpulse data */\n");
  strcat(wr_strval,"  uint16 PhaseAng[NUMFRM];   /* Phase angle for each frame in this cycle*/\n");
  strcat(wr_strval,"  uint16 SunPulLat[2][8];     /* sun pulse latched at mn frm 0&8 [2] */\n");
  strcat(wr_strval,"			     /* over the 8 [8] major frame cycle */\n");
  strcat(wr_strval,"  uint32 SunPulDat[2][8];    /* Sun sensor data */\n");
  strcat(wr_strval,"		/* bits 31-24 : unused */\n");
  strcat(wr_strval,"		/* bits 23-20 : Mnr frame */\n");
  strcat(wr_strval,"		/* bits 19-10 : sub secont count (684.75 cnts=1 sec)*/\n");
  strcat(wr_strval,"		/* bits  9- 8 : ID bits, 00=err,01=top,10=side,11=neither */\n");
  strcat(wr_strval,"		/* bits  7- 0 : Y angle measurment (Grey code) */\n");
  strcat(wr_strval,"		/* */\n");
  strcat(wr_strval,"		/*   From C&DH Specification (mf0:index1=0, mf8:index1=1) */\n");
  strcat(wr_strval,"		/* For the time tag in Science minor frame 0: for a minor */\n");
  strcat(wr_strval,"		/* frame ID of 0, the sun pulse would have occured in the */\n");
  strcat(wr_strval,"		/* current major frame.  For a minor frame ID of 1 to 15, */\n");
  strcat(wr_strval,"		/* the sun pulse would have occured in the previous major */\n");
  strcat(wr_strval,"		/* frame */\n");
  strcat(wr_strval,"		/* For the time tag in Science minor frame 8: for a minor */\n");
  strcat(wr_strval,"		/* frame ID of 0-8, the sun pulse would have occured in the */\n");
  strcat(wr_strval,"		/* current major frame.  For a minor frame ID of 9 to 15, */\n");
  strcat(wr_strval,"		/* the sun pulse would have occured in the previous major */\n");
  strcat(wr_strval,"		/* frame */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* Housekeeping data is here */\n");
  strcat(wr_strval,"  uint8 Cal[8];                    /* int/ext cal readout                  */\n");
  strcat(wr_strval,"  uint8 Ref10[2];                  /* +10V Ref Monitor                     */\n");
  strcat(wr_strval,"  uint8 Mon10[2];                  /* +10V Monitor                         */\n");
  strcat(wr_strval,"  uint8 Mon6[2];                   /* +6V Monitor                          */\n");
  strcat(wr_strval,"  uint8 Bias[2];                   /* Detector Bias Voltage Monitor        */\n");
  strcat(wr_strval,"  uint8 AmpTemp[2];                /* Log Amp D Temperature                */\n");
  strcat(wr_strval,"  uint8 MFSATemp[2];               /* MFSA Log Amp D Temperature           */\n");
  strcat(wr_strval,"  uint8 DetTemp[2];                /* Detector D Temperature               */\n");
  strcat(wr_strval,"  uint8 YTemp[2];                  /* EPAM 2B Yoke Temperature             */\n");
  strcat(wr_strval,"  uint8 InCur[8];                  /* input current monitor                */\n");
  strcat(wr_strval,"  uint8 E1Temp[8];                 /* epam 1 electronics temp.             */\n");
  strcat(wr_strval,"  uint8 Sen2ATemp[8];              /* epam 2a sensor temp.                 */\n");
  strcat(wr_strval,"  uint8 Sen2BTemp[8];              /* epam 2b sensor temp.                 */\n");
  strcat(wr_strval,"  uint8 DeckTemp[8];               /* Instrument Deck Temp near EPAM       */\n");
  strcat(wr_strval,"  uint8 Cur[8];                    /* epam current                         */\n");
  strcat(wr_strval,"  uint8 HtrCur[8];                 /* epam heater current                  */\n");
  strcat(wr_strval,"  uint8 PowBits[8];                /* power switching and ordinance bits   */\n");
  strcat(wr_strval,"  /*--- EPAM power switching and ordinance bits ---*/\n");
  strcat(wr_strval,"  /*--- bit position 7: Interface Heater   at position 10 of 112 bits ---*/\n");
  strcat(wr_strval,"  /*--- bit position 6: Internal Heaters   at position 11 of 112 bits ---*/\n");
  strcat(wr_strval,"  /*--- bit position 5: Main System Power  at position 28 of 112 bits ---*/\n");
  strcat(wr_strval,"  /*--- bit position 4: PyroArm (LEMS 30)  at position 56 of 112 bits ---*/\n");
  strcat(wr_strval,"  /*--- bit position 3: PyroArm (LEMS 120) at position 57 of 112 bits ---*/\n");
  strcat(wr_strval,"  /*--- bit position 2: PyroArm (CD)       at position 58 of 112 bits ---*/\n");
  strcat(wr_strval,"  /*--- bit position 1: 0                                             ---*/\n");
  strcat(wr_strval,"  /*--- bit position 0: 0                                             ---*/\n");
  strcat(wr_strval,"};\n");
  return(0);
}
