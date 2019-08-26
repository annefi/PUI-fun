/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: aosr.h,v 1.8 1998/10/20 22:26:40 asc Exp  */

#include "aosr.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_aosr;
static int32 vdata_id_aosr;

static int32 sds_id_aosr1;

  /* 3221 is the size of aosr.h + 1 added line */
char Vgrp_descrp_attorb_entry[3221];

/****----  init create function  ----****/

int32 init_cr_aosr(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_aosr();

  void print_aosr_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_aosr = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_aosr_error("init_cr_aosr -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_aosr, "VG_attorb_entry"); 
  Vsetclass(vgrp_id_aosr, "VG_AOSR");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_attorb_entry" )) ==FAIL) {
    print_aosr_error("init_cr_aosr -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_aosr(Vgrp_descrp_attorb_entry);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_aosr_error("init_cr_aosr -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_attorb_entry, sizeof(Vgrp_descrp_attorb_entry))) ==FAIL) {
    print_aosr_error("init_cr_aosr -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_aosr = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_aosr_error("init_cr_aosr -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_aosr, "attorb_entry");
  VSsetclass(vdata_id_aosr, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_aosr, vdata_id_aosr)) ==FAIL) {
    print_aosr_error("init_cr_aosr -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_aosr, "sctime", DFNT_UINT32, (1) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "istp_time", DFNT_INT32, (2) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define istp_time");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "UT_time", DFNT_CHAR8, (13) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define UT_time");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "state", DFNT_UINT8, (1) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define state");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "att_J2GCI", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define att_J2GCI");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "att_RTN", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define att_RTN");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "att_GSE", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define att_GSE");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "att_GSM", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define att_GSM");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "att_HSEb", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define att_HSEb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "att_HSEa", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define att_HSEa");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "att_HS", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define att_HS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "spin_J2GCI", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define spin_J2GCI");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "spin_RTN", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define spin_RTN");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "spin_GSE", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define spin_GSE");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "spin_GSM", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define spin_GSM");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "spin_HSEb", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define spin_HSEb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "spin_HSEa", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define spin_HSEa");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "spin_HS", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define spin_HS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "pos_J2GCI", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define pos_J2GCI");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "pos_GSE", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define pos_GSE");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "pos_GSM", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define pos_GSM");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "pos_HSEb", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define pos_HSEb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "pos_HSEa", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define pos_HSEa");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "pos_HS", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define pos_HS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "vel_J2GCI", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define vel_J2GCI");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "vel_GSE", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define vel_GSE");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "vel_GSM", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define vel_GSM");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "vel_HSEb", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define vel_HSEb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "vel_HSEa", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define vel_HSEa");
    retval = -1;
  }
  if (VSfdefine(vdata_id_aosr, "vel_HS", DFNT_FLOAT64, (3) )) {
    print_aosr_error("init_cr_aosr -> VSfdefine: Couldn't define vel_HS");
    retval = -1;
  }

  if (VSsetfields(vdata_id_aosr,"sctime, istp_time, UT_time, state, att_J2GCI, att_RTN, att_GSE, att_GSM, att_HSEb, att_HSEa, att_HS, spin_J2GCI, spin_RTN, spin_GSE, spin_GSM, spin_HSEb, spin_HSEa, spin_HS, pos_J2GCI, pos_GSE, pos_GSM, pos_HSEb, pos_HSEa, pos_HS, vel_J2GCI, vel_GSE, vel_GSM, vel_HSEb, vel_HSEa, vel_HS")){
    print_aosr_error("init_cr_aosr -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 3;
  dim_sizes[2] = 3;
  if((sds_id_aosr1 = SDcreate(sd_id, "attorb_entry_pri2bdy", DFNT_FLOAT64, rank, dim_sizes)) == FAIL)
    print_aosr_error("init_cr_aosr -> SDcreate: Couldn't create attorb_entry_pri2bdy");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_aosr1)) == FAIL)
    print_aosr_error("init_cr_aosr -> SDidtoref: Couldn't get ref for attorb_entry_pri2bdy");

  if((Vaddtagref(vgrp_id_aosr, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_aosr_error("init_cr_aosr -> Vaddtagref: Couldn't add SDS attorb_entry_pri2bdy to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_aosr(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_aosr(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_aosr(struct attorb_entry attorb_entry_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_aosr_error();
void pack_aosr();

  odata = (uint8 *) malloc(sizeof(struct attorb_entry));
  pack_aosr(odata, &attorb_entry_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_aosr, recnum)==-1) {
		print_aosr_error("write_aosr -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_aosr, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_aosr_error("write_aosr -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = 3;
  edges[2] = 3;
  if (SDwritedata(sds_id_aosr1,start,NULL,edges, (VOIDP)(attorb_entry_struc.pri2bdy)) ==FAIL)
    print_aosr_error("write_aosr -> SDwritedata: Problem writing pri2bdy data.");

  memset(&attorb_entry_struc, 0, sizeof(struct attorb_entry));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_aosr()
{
  VSdetach(vdata_id_aosr);
  Vdetach(vgrp_id_aosr);
  SDendaccess(sds_id_aosr1);
}

/*----     init access function    ----*/

int32 init_acc_aosr(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_aosr_error();

  if((sds_index1=SDnametoindex(sd_id, "attorb_entry_pri2bdy" )) ==FAIL) {
      print_aosr_error("init_acc_aosr -> SDnametoindex: Couldn't find attorb_entry_pri2bdy");
      return(-1);
  }
  if((sds_id_aosr1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_aosr_error("init_acc_aosr -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "attorb_entry")) <= 0 ) {
    print_aosr_error("init_acc_aosr -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_aosr = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_aosr_error("init_acc_aosr -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_aosr, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_aosr,"sctime, istp_time, UT_time, state, att_J2GCI, att_RTN, att_GSE, att_GSM, att_HSEb, att_HSEa, att_HS, spin_J2GCI, spin_RTN, spin_GSE, spin_GSM, spin_HSEb, spin_HSEa, spin_HS, pos_J2GCI, pos_GSE, pos_GSM, pos_HSEb, pos_HSEa, pos_HS, vel_J2GCI, vel_GSE, vel_GSM, vel_HSEb, vel_HSEa, vel_HS")) {
      print_aosr_error("init_acc_aosr -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_aosr(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_aosr(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_aosr(struct attorb_entry *attorb_entry_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_aosr_error();
void unpack_aosr();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct attorb_entry));
  VSinquire(vdata_id_aosr, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_aosr, recnum_rd)==FAIL) {
          print_aosr_error("read_aosr -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = 3;
  edges[2] = 3;

  if(SDreaddata(sds_id_aosr1,start,NULL,edges, (VOIDP)(attorb_entry_struc->pri2bdy )) ==FAIL) {
    print_aosr_error("read_aosr -> SDreaddata: Couldn't read pri2bdy");
    retval = -1;
  }
  if(VSread(vdata_id_aosr, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_aosr_error("read_aosr -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_aosr(odata, attorb_entry_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_aosr()
{
  VSdetach(vdata_id_aosr);
  SDendaccess(sds_id_aosr1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_aosr(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_aosr_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_attorb_entry" )) ==FAIL)
    print_aosr_error("rd_Vgrp_aosr -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_aosr_error("rd_Vgrp_aosr -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_aosr_error("rd_Vgrp_aosr -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_aosr_error("rd_Vgrp_aosr -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_attorb_entry, HDstrlen(Vgrp_descrp_attorb_entry)) ==FAIL)
    print_aosr_error("rd_Vgrp_aosr -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_attorb_entry);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_aosr_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_aosr.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_aosr(uint8 *data, struct attorb_entry *attorb_entry_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &attorb_entry_ptr->sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &attorb_entry_ptr->istp_time[0], ((4)*(2)) );
   ptr+= ((4)*(2));
   memcpy(data+ptr, &attorb_entry_ptr->UT_time[0], ((1)*(13)) );
   ptr+= ((1)*(13));
   memcpy(data+ptr, &attorb_entry_ptr->state, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &attorb_entry_ptr->att_J2GCI[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->att_RTN[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->att_GSE[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->att_GSM[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->att_HSEb[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->att_HSEa[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->att_HS[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->spin_J2GCI[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->spin_RTN[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->spin_GSE[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->spin_GSM[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->spin_HSEb[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->spin_HSEa[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->spin_HS[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->pos_J2GCI[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->pos_GSE[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->pos_GSM[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->pos_HSEb[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->pos_HSEa[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->pos_HS[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->vel_J2GCI[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->vel_GSE[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->vel_GSM[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->vel_HSEb[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->vel_HSEa[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &attorb_entry_ptr->vel_HS[0], ((8)*(3)) );
   ptr+= ((8)*(3));
}

/*----   unpack function    ----*/

void unpack_aosr(uint8 *data, struct attorb_entry *attorb_entry_ptr)
{
int32 ptr=0;

   memcpy(&attorb_entry_ptr->sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&attorb_entry_ptr->istp_time[0], data+ptr,  ((4)*(2)) );
   ptr+= ((4)*(2));
   memcpy(&attorb_entry_ptr->UT_time[0], data+ptr,  ((1)*(13)) );
   ptr+= ((1)*(13));
   memcpy(&attorb_entry_ptr->state, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&attorb_entry_ptr->att_J2GCI[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->att_RTN[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->att_GSE[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->att_GSM[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->att_HSEb[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->att_HSEa[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->att_HS[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->spin_J2GCI[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->spin_RTN[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->spin_GSE[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->spin_GSM[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->spin_HSEb[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->spin_HSEa[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->spin_HS[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->pos_J2GCI[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->pos_GSE[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->pos_GSM[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->pos_HSEb[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->pos_HSEa[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->pos_HS[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->vel_J2GCI[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->vel_GSE[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->vel_GSM[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->vel_HSEb[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->vel_HSEa[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&attorb_entry_ptr->vel_HS[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
}
int32 get_vgrp_id_aosr() {return(vgrp_id_aosr);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_aosr(char *wr_strval)
{
  strcpy(wr_strval, "The file 'aosr.h' is shown below, it was used to create the data in the Vgroup named 'VG_attorb_entry'.\n\n");
  strcat(wr_strval,"/* Id: aosr.h,v 1.8 1998/10/20 22:26:40 asc Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct attorb_entry {\n");
  strcat(wr_strval,"    uint32   sctime;      /* time of measurement in Spacecraft clock ticks */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    int32    istp_time[2]; /* time of measurement in ISTP format. */\n");
  strcat(wr_strval,"                           /* First entry is YEARDAYOFYEAR, eg: 1998201 for */\n");
  strcat(wr_strval,"			   /* day 201 of 1998. Second entry is the millisecond of */\n");
  strcat(wr_strval,"			   /* the day */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    char8    UT_time[13];  /* A character string containing UT time of */\n");
  strcat(wr_strval,"                           /* the measurement */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    float64  pri2bdy[3][3];    /* Primary to body rotation matrix */\n");
  strcat(wr_strval,"                               /* NOT IMPLEMENTED */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    uint8    state;    /* state status.  {Beg/end}_{pass/manuever} */\n");
  strcat(wr_strval,"                       /* The data is collected under one of the following */\n");
  strcat(wr_strval,"		       /* four conditions: */\n");
  strcat(wr_strval,"                       /* state = 1 - Beginning of DSN telemetry pass */\n");
  strcat(wr_strval,"                       /* state = 2 - End of DSN telemetry pass */\n");
  strcat(wr_strval,"                       /* state = 3 - Beginning of spacecraft maneuver */\n");
  strcat(wr_strval,"                       /* state = 4 - End of spacecraft maneuver */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    /* attitude data. Attitude vectors are normalized to unity */\n");
  strcat(wr_strval,"    /* See ASC web page for definitions of coordinate systems */\n");
  strcat(wr_strval,"    float64  att_J2GCI[3]; /* attitude direction cosines in J2000 */\n");
  strcat(wr_strval,"    float64  att_RTN[3]; /* attitude direction cosines in RTN */\n");
  strcat(wr_strval,"    float64  att_GSE[3]; /* attitude direction cosines in GSE */\n");
  strcat(wr_strval,"    float64  att_GSM[3]; /* attitude direction cosines in GSM */\n");
  strcat(wr_strval,"    float64  att_HSEb[3]; /* attitude direction cosines in HSEb */\n");
  strcat(wr_strval,"    float64  att_HSEa[3]; /* attitude direction cosines in HSEa */\n");
  strcat(wr_strval,"    float64  att_HS[3]; /* attitude direction cosines in HS */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    /* spin-rate data */\n");
  strcat(wr_strval,"    float64  spin_J2GCI[3]; /* spin rate vector in J2000, rad/sec */\n");
  strcat(wr_strval,"    float64  spin_RTN[3]; /* spin rate vector in RTN, rad/sec */\n");
  strcat(wr_strval,"    float64  spin_GSE[3]; /* spin rate vector in GSE, rad/sec */\n");
  strcat(wr_strval,"    float64  spin_GSM[3]; /* spin rate vector in GSM, rad/sec */\n");
  strcat(wr_strval,"    float64  spin_HSEb[3]; /* spin rate vector in HSEb, rad/sec */\n");
  strcat(wr_strval,"    float64  spin_HSEa[3]; /* spin rate vector in HSEa, rad/sec */\n");
  strcat(wr_strval,"    float64  spin_HS[3]; /* spin rate vector in HS, rad/sec */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    /* spacecraft position data */\n");
  strcat(wr_strval,"    float64  pos_J2GCI[3]; /* S/C position in J2000, km */\n");
  strcat(wr_strval,"    float64  pos_GSE[3]; /* S/C position in GSE, km */\n");
  strcat(wr_strval,"    float64  pos_GSM[3]; /* S/C position in GSM, km */\n");
  strcat(wr_strval,"    float64  pos_HSEb[3]; /* S/C position in HSEb, km */\n");
  strcat(wr_strval,"    float64  pos_HSEa[3]; /* S/C position in HSEa, km NOT IMPLEMENTED */\n");
  strcat(wr_strval,"    float64  pos_HS[3]; /* S/C position in HS, km */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    /* spacecraft velocity data */\n");
  strcat(wr_strval,"    float64  vel_J2GCI[3]; /* S/C velocity in J2000, km/s */\n");
  strcat(wr_strval,"    float64  vel_GSE[3]; /* S/C velocity in GSE, km/s */\n");
  strcat(wr_strval,"    float64  vel_GSM[3]; /* S/C velocity in GSM, km/s */\n");
  strcat(wr_strval,"    float64  vel_HSEb[3]; /* S/C velocity in HSEb, km/s NOT IMPLEMENTED */\n");
  strcat(wr_strval,"    float64  vel_HSEa[3]; /* S/C velocity in HSEa, km/s NOT IMPLEMENTED */\n");
  strcat(wr_strval,"    float64  vel_HS[3]; /* S/C velocity in HS, km/s NOT IMPLEMENTED */\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  return(0);
}
