/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_dspare_contr.h,v 1.3 1998/01/30 19:51:03 hemple Exp  */

#include "s3_dspare_contr.h"
#include "df.h"

int32 vgrp_id_s3_dspare_contr;
static int32 vdata_id_s3_dspare_contr;

  /* 1277 is the size of s3_dspare_contr.h + 1 added line */
char Vgrp_descrp_s3s_dspare_contr[1277];

/****----  init create function  ----****/

int32 init_cr_s3_dspare_contr(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_dspare_contr();

  void print_s3_dspare_contr_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_dspare_contr = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_dspare_contr, "VG_s3s_dspare_contr"); 
  Vsetclass(vgrp_id_s3_dspare_contr, "VG_S3_DSPARE_CONTR");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_s3s_dspare_contr" )) ==FAIL) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_dspare_contr(Vgrp_descrp_s3s_dspare_contr);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_s3s_dspare_contr, sizeof(Vgrp_descrp_s3s_dspare_contr))) ==FAIL) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_dspare_contr = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_dspare_contr, "s3s_dspare_contr");
  VSsetclass(vdata_id_s3_dspare_contr, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_dspare_contr, vdata_id_s3_dspare_contr)) ==FAIL) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_dspare_contr, "sctime", DFNT_UINT32, (1) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "Mode", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define Mode");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "Delay", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define Delay");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "Lim30k", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define Lim30k");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "Lim30k_delta", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define Lim30k_delta");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "Lim2k", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define Lim2k");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "Lim2k_delta", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define Lim2k_delta");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "Lim75", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define Lim75");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "Lim75_delta", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define Lim75_delta");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "PhaThres_low", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define PhaThres_low");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "PhaThres_hi", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define PhaThres_hi");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "PressCtrl_1", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define PressCtrl_1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "PressCtrl_2", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define PressCtrl_2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "PressCmd_1", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define PressCmd_1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "PressCmd_2", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define PressCmd_2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "PressCmd_3", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define PressCmd_3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "Mode_Cmd", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define Mode_Cmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "Delay_Cmd", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define Delay_Cmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "Lim30k_Cmd", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define Lim30k_Cmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "Lim30k_delta_Cmd", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define Lim30k_delta_Cmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "Lim2k_Cmd", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define Lim2k_Cmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "Lim2k_delta_Cmd", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define Lim2k_delta_Cmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "Lim75_Cmd", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define Lim75_Cmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "Lim75_delta_Cmd", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define Lim75_delta_Cmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "PhaThres_low_Cmd", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define PhaThres_low_Cmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "PhaThres_hi_Cmd", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define PhaThres_hi_Cmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "PressCtrl_1_Cmd", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define PressCtrl_1_Cmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "PressCtrl_2_Cmd", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define PressCtrl_2_Cmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "PressCmd_1_Cmd", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define PressCmd_1_Cmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "PressCmd_2_Cmd", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define PressCmd_2_Cmd");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dspare_contr, "PressCmd_3_Cmd", DFNT_INT16, (3) )) {
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSfdefine: Couldn't define PressCmd_3_Cmd");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_dspare_contr,"sctime, Mode, Delay, Lim30k, Lim30k_delta, Lim2k, Lim2k_delta, Lim75, Lim75_delta, PhaThres_low, PhaThres_hi, PressCtrl_1, PressCtrl_2, PressCmd_1, PressCmd_2, PressCmd_3, Mode_Cmd, Delay_Cmd, Lim30k_Cmd, Lim30k_delta_Cmd, Lim2k_Cmd, Lim2k_delta_Cmd, Lim75_Cmd, Lim75_delta_Cmd, PhaThres_low_Cmd, PhaThres_hi_Cmd, PressCtrl_1_Cmd, PressCtrl_2_Cmd, PressCmd_1_Cmd, PressCmd_2_Cmd, PressCmd_3_Cmd")){
    print_s3_dspare_contr_error("init_cr_s3_dspare_contr -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_dspare_contr(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_dspare_contr(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_dspare_contr(struct s3s_dspare_contr s3s_dspare_contr_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_dspare_contr_error();
void pack_s3_dspare_contr();

  odata = (uint8 *) malloc(sizeof(struct s3s_dspare_contr));
  pack_s3_dspare_contr(odata, &s3s_dspare_contr_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_dspare_contr, recnum)==-1) {
		print_s3_dspare_contr_error("write_s3_dspare_contr -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_dspare_contr, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_dspare_contr_error("write_s3_dspare_contr -> VSwrite: Couldn't write data.");

  memset(&s3s_dspare_contr_struc, 0, sizeof(struct s3s_dspare_contr));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_dspare_contr()
{
  VSdetach(vdata_id_s3_dspare_contr);
  Vdetach(vgrp_id_s3_dspare_contr);
}

/*----     init access function    ----*/

int32 init_acc_s3_dspare_contr(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_dspare_contr_error();


  if ((vdata_ref = VSfind(hdf_fp, "s3s_dspare_contr")) <= 0 ) {
    print_s3_dspare_contr_error("init_acc_s3_dspare_contr -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_dspare_contr = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_dspare_contr_error("init_acc_s3_dspare_contr -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_dspare_contr, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_dspare_contr,"sctime, Mode, Delay, Lim30k, Lim30k_delta, Lim2k, Lim2k_delta, Lim75, Lim75_delta, PhaThres_low, PhaThres_hi, PressCtrl_1, PressCtrl_2, PressCmd_1, PressCmd_2, PressCmd_3, Mode_Cmd, Delay_Cmd, Lim30k_Cmd, Lim30k_delta_Cmd, Lim2k_Cmd, Lim2k_delta_Cmd, Lim75_Cmd, Lim75_delta_Cmd, PhaThres_low_Cmd, PhaThres_hi_Cmd, PressCtrl_1_Cmd, PressCtrl_2_Cmd, PressCmd_1_Cmd, PressCmd_2_Cmd, PressCmd_3_Cmd")) {
      print_s3_dspare_contr_error("init_acc_s3_dspare_contr -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_dspare_contr(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_dspare_contr(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_dspare_contr(struct s3s_dspare_contr *s3s_dspare_contr_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_dspare_contr_error();
void unpack_s3_dspare_contr();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct s3s_dspare_contr));
  VSinquire(vdata_id_s3_dspare_contr, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_dspare_contr, recnum_rd)==FAIL) {
          print_s3_dspare_contr_error("read_s3_dspare_contr -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_dspare_contr, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_dspare_contr_error("read_s3_dspare_contr -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_dspare_contr(odata, s3s_dspare_contr_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_dspare_contr()
{
  VSdetach(vdata_id_s3_dspare_contr);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_dspare_contr(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_dspare_contr_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_s3s_dspare_contr" )) ==FAIL)
    print_s3_dspare_contr_error("rd_Vgrp_s3_dspare_contr -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_dspare_contr_error("rd_Vgrp_s3_dspare_contr -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_dspare_contr_error("rd_Vgrp_s3_dspare_contr -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_dspare_contr_error("rd_Vgrp_s3_dspare_contr -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_s3s_dspare_contr, HDstrlen(Vgrp_descrp_s3s_dspare_contr)) ==FAIL)
    print_s3_dspare_contr_error("rd_Vgrp_s3_dspare_contr -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_s3s_dspare_contr);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_dspare_contr_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_s3dspare_contr.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_dspare_contr(uint8 *data, struct s3s_dspare_contr *s3s_dspare_contr_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &s3s_dspare_contr_ptr->sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->Mode[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->Delay[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->Lim30k[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->Lim30k_delta[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->Lim2k[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->Lim2k_delta[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->Lim75[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->Lim75_delta[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->PhaThres_low[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->PhaThres_hi[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->PressCtrl_1[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->PressCtrl_2[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->PressCmd_1[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->PressCmd_2[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->PressCmd_3[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->Mode_Cmd[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->Delay_Cmd[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->Lim30k_Cmd[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->Lim30k_delta_Cmd[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->Lim2k_Cmd[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->Lim2k_delta_Cmd[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->Lim75_Cmd[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->Lim75_delta_Cmd[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->PhaThres_low_Cmd[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->PhaThres_hi_Cmd[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->PressCtrl_1_Cmd[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->PressCtrl_2_Cmd[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->PressCmd_1_Cmd[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->PressCmd_2_Cmd[0], ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(data+ptr, &s3s_dspare_contr_ptr->PressCmd_3_Cmd[0], ((2)*(3)) );
   ptr+= ((2)*(3));
}

/*----   unpack function    ----*/

void unpack_s3_dspare_contr(uint8 *data, struct s3s_dspare_contr *s3s_dspare_contr_ptr)
{
int32 ptr=0;

   memcpy(&s3s_dspare_contr_ptr->sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&s3s_dspare_contr_ptr->Mode[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->Delay[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->Lim30k[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->Lim30k_delta[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->Lim2k[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->Lim2k_delta[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->Lim75[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->Lim75_delta[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->PhaThres_low[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->PhaThres_hi[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->PressCtrl_1[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->PressCtrl_2[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->PressCmd_1[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->PressCmd_2[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->PressCmd_3[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->Mode_Cmd[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->Delay_Cmd[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->Lim30k_Cmd[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->Lim30k_delta_Cmd[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->Lim2k_Cmd[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->Lim2k_delta_Cmd[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->Lim75_Cmd[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->Lim75_delta_Cmd[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->PhaThres_low_Cmd[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->PhaThres_hi_Cmd[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->PressCtrl_1_Cmd[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->PressCtrl_2_Cmd[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->PressCmd_1_Cmd[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->PressCmd_2_Cmd[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
   memcpy(&s3s_dspare_contr_ptr->PressCmd_3_Cmd[0], data+ptr,  ((2)*(3)) );
   ptr+= ((2)*(3));
}
int32 get_vgrp_id_s3_dspare_contr() {return(vgrp_id_s3_dspare_contr);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_dspare_contr(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_dspare_contr.h' is shown below, it was used to create the data in the Vgroup named 'VG_s3s_dspare_contr'.\n\n");
  strcat(wr_strval,"/* Id: s3_dspare_contr.h,v 1.3 1998/01/30 19:51:03 hemple Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct s3s_dspare_contr{\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"uint32 sctime;             /* 32bit spacecraft time */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* SEPICA control words, from EDB's 3,23,43 */\n");
  strcat(wr_strval,"int16 Mode[3];		   /* mode */\n");
  strcat(wr_strval,"int16 Delay[3];		   /* power off delay */\n");
  strcat(wr_strval,"int16 Lim30k[3];	   /* 30 kV limit/delta */\n");
  strcat(wr_strval,"int16 Lim30k_delta[3];\n");
  strcat(wr_strval,"int16 Lim2k[3];		   /* 2 kV limit/delta */\n");
  strcat(wr_strval,"int16 Lim2k_delta[3];\n");
  strcat(wr_strval,"int16 Lim75[3];		   /* 75 V limit/delta */\n");
  strcat(wr_strval,"int16 Lim75_delta[3];\n");
  strcat(wr_strval,"int16 PhaThres_low[3];	   /* PHA threshold */\n");
  strcat(wr_strval,"int16 PhaThres_hi[3];		\n");
  strcat(wr_strval,"int16 PressCtrl_1[3];	   /* pressure control */\n");
  strcat(wr_strval,"int16 PressCtrl_2[3];\n");
  strcat(wr_strval,"int16 PressCmd_1[3];	   /* pressures */\n");
  strcat(wr_strval,"int16 PressCmd_2[3];\n");
  strcat(wr_strval,"int16 PressCmd_3[3];\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"int16 Mode_Cmd[3];\n");
  strcat(wr_strval,"int16 Delay_Cmd[3];\n");
  strcat(wr_strval,"int16 Lim30k_Cmd[3];\n");
  strcat(wr_strval,"int16 Lim30k_delta_Cmd[3];\n");
  strcat(wr_strval,"int16 Lim2k_Cmd[3];\n");
  strcat(wr_strval,"int16 Lim2k_delta_Cmd[3];\n");
  strcat(wr_strval,"int16 Lim75_Cmd[3];\n");
  strcat(wr_strval,"int16 Lim75_delta_Cmd[3];\n");
  strcat(wr_strval,"int16 PhaThres_low_Cmd[3];\n");
  strcat(wr_strval,"int16 PhaThres_hi_Cmd[3];\n");
  strcat(wr_strval,"int16 PressCtrl_1_Cmd[3];\n");
  strcat(wr_strval,"int16 PressCtrl_2_Cmd[3];\n");
  strcat(wr_strval,"int16 PressCmd_1_Cmd[3];\n");
  strcat(wr_strval,"int16 PressCmd_2_Cmd[3];\n");
  strcat(wr_strval,"int16 PressCmd_3_Cmd[3];\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  return(0);
}
