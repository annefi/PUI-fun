/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_shk3.h,v 1.2 1998/12/07 18:12:39 ad Exp  */

#include "s3_shk3.h"
#include "df.h"

int32 vgrp_id_s3_shk3;
static int32 vdata_id_s3_shk3;

  /* 1790 is the size of s3_shk3.h + 1 added line */
char Vgrp_descrp_sshshk3[1790];

/****----  init create function  ----****/

int32 init_cr_s3_shk3(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_shk3();

  void print_s3_shk3_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_shk3 = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_shk3_error("init_cr_s3_shk3 -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_shk3, "VG_sshshk3"); 
  Vsetclass(vgrp_id_s3_shk3, "VG_S3_SHK3");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_sshshk3" )) ==FAIL) {
    print_s3_shk3_error("init_cr_s3_shk3 -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_shk3(Vgrp_descrp_sshshk3);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_shk3_error("init_cr_s3_shk3 -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_sshshk3, sizeof(Vgrp_descrp_sshshk3))) ==FAIL) {
    print_s3_shk3_error("init_cr_s3_shk3 -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_shk3 = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_shk3, "sshshk3");
  VSsetclass(vdata_id_s3_shk3, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_shk3, vdata_id_s3_shk3)) ==FAIL) {
    print_s3_shk3_error("init_cr_s3_shk3 -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_shk3, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "sctime_collection", DFNT_FLOAT64, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "QAC", DFNT_UINT32, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "HKSECTOR", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define HKSECTOR");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN1MODE", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN1MODE");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN1BASE", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN1BASE");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN1LOGIC", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN1LOGIC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN1PCY", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN1PCY");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN1PCZ", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN1PCZ");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN1SSD", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN1SSD");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN1BANK", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN1BANK");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN1BLOCK", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN1BLOCK");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN1DATA", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN1DATA");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN2MODE", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN2MODE");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN2BASE", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN2BASE");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN2LOGIC", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN2LOGIC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN2PCY", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN2PCY");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN2PCZ", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN2PCZ");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN2SSD", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN2SSD");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN2BANK", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN2BANK");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN2BLOCK", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN2BLOCK");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN2DATA", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN2DATA");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN3MODE", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN3MODE");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN3BASE", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN3BASE");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN3LOGIC", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN3LOGIC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN3PCY", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN3PCY");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN3PCZ", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN3PCZ");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN3SSD", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN3SSD");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN3BANK", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN3BANK");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN3BLOCK", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN3BLOCK");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_shk3, "FAN3DATA", DFNT_UINT8, (1) )) {
    print_s3_shk3_error("init_cr_s3_shk3 -> VSfdefine: Couldn't define FAN3DATA");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_shk3,"sctime_readout, sctime_collection, QAC, HKSECTOR, FAN1MODE, FAN1BASE, FAN1LOGIC, FAN1PCY, FAN1PCZ, FAN1SSD, FAN1BANK, FAN1BLOCK, FAN1DATA, FAN2MODE, FAN2BASE, FAN2LOGIC, FAN2PCY, FAN2PCZ, FAN2SSD, FAN2BANK, FAN2BLOCK, FAN2DATA, FAN3MODE, FAN3BASE, FAN3LOGIC, FAN3PCY, FAN3PCZ, FAN3SSD, FAN3BANK, FAN3BLOCK, FAN3DATA")){
    print_s3_shk3_error("init_cr_s3_shk3 -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_shk3(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_shk3(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_shk3(struct sshshk3 sshshk3_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_shk3_error();
void pack_s3_shk3();

  odata = (uint8 *) malloc(sizeof(struct sshshk3));
  pack_s3_shk3(odata, &sshshk3_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_shk3, recnum)==-1) {
		print_s3_shk3_error("write_s3_shk3 -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_shk3, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_shk3_error("write_s3_shk3 -> VSwrite: Couldn't write data.");

  memset(&sshshk3_struc, 0, sizeof(struct sshshk3));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_shk3()
{
  VSdetach(vdata_id_s3_shk3);
  Vdetach(vgrp_id_s3_shk3);
}

/*----     init access function    ----*/

int32 init_acc_s3_shk3(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_shk3_error();


  if ((vdata_ref = VSfind(hdf_fp, "sshshk3")) <= 0 ) {
    print_s3_shk3_error("init_acc_s3_shk3 -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_shk3 = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_shk3_error("init_acc_s3_shk3 -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_shk3, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_shk3,"sctime_readout, sctime_collection, QAC, HKSECTOR, FAN1MODE, FAN1BASE, FAN1LOGIC, FAN1PCY, FAN1PCZ, FAN1SSD, FAN1BANK, FAN1BLOCK, FAN1DATA, FAN2MODE, FAN2BASE, FAN2LOGIC, FAN2PCY, FAN2PCZ, FAN2SSD, FAN2BANK, FAN2BLOCK, FAN2DATA, FAN3MODE, FAN3BASE, FAN3LOGIC, FAN3PCY, FAN3PCZ, FAN3SSD, FAN3BANK, FAN3BLOCK, FAN3DATA")) {
      print_s3_shk3_error("init_acc_s3_shk3 -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_shk3(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_shk3(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_shk3(struct sshshk3 *sshshk3_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_shk3_error();
void unpack_s3_shk3();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct sshshk3));
  VSinquire(vdata_id_s3_shk3, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_shk3, recnum_rd)==FAIL) {
          print_s3_shk3_error("read_s3_shk3 -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_shk3, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_shk3_error("read_s3_shk3 -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_shk3(odata, sshshk3_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_shk3()
{
  VSdetach(vdata_id_s3_shk3);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_shk3(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_shk3_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_sshshk3" )) ==FAIL)
    print_s3_shk3_error("rd_Vgrp_s3_shk3 -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_shk3_error("rd_Vgrp_s3_shk3 -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_shk3_error("rd_Vgrp_s3_shk3 -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_shk3_error("rd_Vgrp_s3_shk3 -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_sshshk3, HDstrlen(Vgrp_descrp_sshshk3)) ==FAIL)
    print_s3_shk3_error("rd_Vgrp_s3_shk3 -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_sshshk3);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_shk3_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_sepica_shk3.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_shk3(uint8 *data, struct sshshk3 *sshshk3_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &sshshk3_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sshshk3_ptr->sctime_collection, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &sshshk3_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sshshk3_ptr->HKSECTOR, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN1MODE, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN1BASE, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN1LOGIC, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN1PCY, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN1PCZ, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN1SSD, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN1BANK, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN1BLOCK, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN1DATA, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN2MODE, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN2BASE, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN2LOGIC, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN2PCY, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN2PCZ, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN2SSD, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN2BANK, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN2BLOCK, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN2DATA, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN3MODE, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN3BASE, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN3LOGIC, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN3PCY, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN3PCZ, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN3SSD, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN3BANK, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN3BLOCK, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshshk3_ptr->FAN3DATA, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_s3_shk3(uint8 *data, struct sshshk3 *sshshk3_ptr)
{
int32 ptr=0;

   memcpy(&sshshk3_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sshshk3_ptr->sctime_collection, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&sshshk3_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sshshk3_ptr->HKSECTOR, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN1MODE, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN1BASE, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN1LOGIC, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN1PCY, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN1PCZ, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN1SSD, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN1BANK, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN1BLOCK, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN1DATA, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN2MODE, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN2BASE, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN2LOGIC, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN2PCY, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN2PCZ, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN2SSD, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN2BANK, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN2BLOCK, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN2DATA, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN3MODE, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN3BASE, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN3LOGIC, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN3PCY, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN3PCZ, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN3SSD, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN3BANK, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN3BLOCK, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshshk3_ptr->FAN3DATA, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_s3_shk3() {return(vgrp_id_s3_shk3);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_shk3(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_shk3.h' is shown below, it was used to create the data in the Vgroup named 'VG_sshshk3'.\n\n");
  strcat(wr_strval,"/* Id: s3_shk3.h,v 1.2 1998/12/07 18:12:39 ad Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct sshshk3{\n");
  strcat(wr_strval,"	uint32 sctime_readout;	/* first minor frame of readout cycle, */\n");
  strcat(wr_strval,"	                        /* 32 bit spacecraft clock time */\n");
  strcat(wr_strval,"	float64 sctime_collection; /* time of the start of the first spin in the */\n");
  strcat(wr_strval,"	                           /* 5-spin cycle. sub-second resolution */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint32 QAC; /* number of missing minor frames in the 5-spin cycle  */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint8 HKSECTOR;	/* Housekeeping Sector    */\n");
  strcat(wr_strval,"	uint8 FAN1MODE;	/* Fan 1 Mode   */\n");
  strcat(wr_strval,"	uint8 FAN1BASE;	/* Fan 1 Baseline Subtr.  */\n");
  strcat(wr_strval,"	uint8 FAN1LOGIC;	/* Fan 1 SSD Logic  */\n");
  strcat(wr_strval,"	uint8 FAN1PCY;	/* Fan 1 Valid PC  */\n");
  strcat(wr_strval,"	uint8 FAN1PCZ;	/* Fan 1 Valid PC  */\n");
  strcat(wr_strval,"	uint8 FAN1SSD;	/* Fan 1 Valid SSD  */\n");
  strcat(wr_strval,"	uint8 FAN1BANK;	/* Fan 1 Memory Bank  */\n");
  strcat(wr_strval,"	uint8 FAN1BLOCK;	/* Fan 1 Memory Block  */\n");
  strcat(wr_strval,"	uint8 FAN1DATA;	/* Fan 1 Data Selected  */\n");
  strcat(wr_strval,"	uint8 FAN2MODE;	/* Fan 2 Mode   */\n");
  strcat(wr_strval,"	uint8 FAN2BASE;	/* Fan 2 Baseline Subtr.  */\n");
  strcat(wr_strval,"	uint8 FAN2LOGIC;	/* Fan 2 SSD Logic  */\n");
  strcat(wr_strval,"	uint8 FAN2PCY;	/* Fan 2 Valid PC  */\n");
  strcat(wr_strval,"	uint8 FAN2PCZ;	/* Fan 2 Valid PC  */\n");
  strcat(wr_strval,"	uint8 FAN2SSD;	/* Fan 2 Valid SSD  */\n");
  strcat(wr_strval,"	uint8 FAN2BANK;	/* Fan 2 Memory Bank  */\n");
  strcat(wr_strval,"	uint8 FAN2BLOCK;	/* Fan 2 Memory Block  */\n");
  strcat(wr_strval,"	uint8 FAN2DATA;	/* Fan 2 Data Selected  */\n");
  strcat(wr_strval,"	uint8 FAN3MODE;	/* Fan 3 Mode   */\n");
  strcat(wr_strval,"	uint8 FAN3BASE;	/* Fan 3 Baseline Subtr.  */\n");
  strcat(wr_strval,"	uint8 FAN3LOGIC;	/* Fan 3 SSD Logic  */\n");
  strcat(wr_strval,"	uint8 FAN3PCY;	/* Fan 3 Valid PC  */\n");
  strcat(wr_strval,"	uint8 FAN3PCZ;	/* Fan 3 Valid PC  */\n");
  strcat(wr_strval,"	uint8 FAN3SSD;	/* Fan 3 Valid SSD  */\n");
  strcat(wr_strval,"	uint8 FAN3BANK;	/* Fan 3 Memory Bank  */\n");
  strcat(wr_strval,"	uint8 FAN3BLOCK;	/* Fan 3 Memory Block  */\n");
  strcat(wr_strval,"	uint8 FAN3DATA;	/* Fan 3 Data Selected  */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
