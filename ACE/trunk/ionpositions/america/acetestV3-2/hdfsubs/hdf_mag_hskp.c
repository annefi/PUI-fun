/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: mag_hskp.h,v 1.9 1997/09/04 23:27:42 jeff Exp  */

#include "mag_hskp.h"
#include "df.h"

int32 vgrp_id_mag_hskp;
static int32 vdata_id_mag_hskp;

  /* 2759 is the size of mag_hskp.h + 1 added line */
char Vgrp_descrp_MagHskpSet[2759];

/****----  init create function  ----****/

int32 init_cr_mag_hskp(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_mag_hskp();

  void print_mag_hskp_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_mag_hskp = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_mag_hskp_error("init_cr_mag_hskp -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_mag_hskp, "VG_MagHskpSet"); 
  Vsetclass(vgrp_id_mag_hskp, "VG_MAG_HSKP");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_MagHskpSet" )) ==FAIL) {
    print_mag_hskp_error("init_cr_mag_hskp -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_mag_hskp(Vgrp_descrp_MagHskpSet);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_mag_hskp_error("init_cr_mag_hskp -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_MagHskpSet, sizeof(Vgrp_descrp_MagHskpSet))) ==FAIL) {
    print_mag_hskp_error("init_cr_mag_hskp -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_mag_hskp = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_mag_hskp, "MagHskpSet");
  VSsetclass(vdata_id_mag_hskp, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_mag_hskp, vdata_id_mag_hskp)) ==FAIL) {
    print_mag_hskp_error("init_cr_mag_hskp -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_mag_hskp, "sctime_readout", DFNT_UINT32, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "sctime_collection", DFNT_UINT32, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "QAC", DFNT_UINT32, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "QACarr", DFNT_UINT8, (16) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define QACarr");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "st1a", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define st1a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "st2a", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define st2a");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "st3", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define st3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "st4", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define st4");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "st5", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define st5");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "st6", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define st6");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "pctemp", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define pctemp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "cmon", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define cmon");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "st1b", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define st1b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "st2b", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define st2b");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "hk1", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define hk1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "hk2", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define hk2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "hk3", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define hk3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "hk4", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define hk4");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "hk5", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define hk5");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "sync", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define sync");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "st", DFNT_UINT16, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define st");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "in_temp", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define in_temp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "out_temp", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define out_temp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "in_pwrlvl", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define in_pwrlvl");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "out_pwrlvl", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define out_pwrlvl");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "current", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define current");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "SenIntTempPosY", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define SenIntTempPosY");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "SenIntTempNegY", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define SenIntTempNegY");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_hskp, "MagPowBits", DFNT_UINT8, (1) )) {
    print_mag_hskp_error("init_cr_mag_hskp -> VSfdefine: Couldn't define MagPowBits");
    retval = -1;
  }

  if (VSsetfields(vdata_id_mag_hskp,"sctime_readout, sctime_collection, QAC, QACarr, st1a, st2a, st3, st4, st5, st6, pctemp, cmon, st1b, st2b, hk1, hk2, hk3, hk4, hk5, sync, st, in_temp, out_temp, in_pwrlvl, out_pwrlvl, current, SenIntTempPosY, SenIntTempNegY, MagPowBits")){
    print_mag_hskp_error("init_cr_mag_hskp -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_mag_hskp(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_mag_hskp(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_mag_hskp(struct MagHskpSet MagHskpSet_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_mag_hskp_error();
void pack_mag_hskp();

  odata = (uint8 *) malloc(sizeof(struct MagHskpSet));
  pack_mag_hskp(odata, &MagHskpSet_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_mag_hskp, recnum)==-1) {
		print_mag_hskp_error("write_mag_hskp -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_mag_hskp, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_mag_hskp_error("write_mag_hskp -> VSwrite: Couldn't write data.");

  memset(&MagHskpSet_struc, 0, sizeof(struct MagHskpSet));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_mag_hskp()
{
  VSdetach(vdata_id_mag_hskp);
  Vdetach(vgrp_id_mag_hskp);
}

/*----     init access function    ----*/

int32 init_acc_mag_hskp(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_mag_hskp_error();


  if ((vdata_ref = VSfind(hdf_fp, "MagHskpSet")) <= 0 ) {
    print_mag_hskp_error("init_acc_mag_hskp -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_mag_hskp = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_mag_hskp_error("init_acc_mag_hskp -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_mag_hskp, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_mag_hskp,"sctime_readout, sctime_collection, QAC, QACarr, st1a, st2a, st3, st4, st5, st6, pctemp, cmon, st1b, st2b, hk1, hk2, hk3, hk4, hk5, sync, st, in_temp, out_temp, in_pwrlvl, out_pwrlvl, current, SenIntTempPosY, SenIntTempNegY, MagPowBits")) {
      print_mag_hskp_error("init_acc_mag_hskp -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_mag_hskp(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_mag_hskp(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_mag_hskp(struct MagHskpSet *MagHskpSet_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_mag_hskp_error();
void unpack_mag_hskp();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct MagHskpSet));
  VSinquire(vdata_id_mag_hskp, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_mag_hskp, recnum_rd)==FAIL) {
          print_mag_hskp_error("read_mag_hskp -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_mag_hskp, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_mag_hskp_error("read_mag_hskp -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_mag_hskp(odata, MagHskpSet_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_mag_hskp()
{
  VSdetach(vdata_id_mag_hskp);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_mag_hskp(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_mag_hskp_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_MagHskpSet" )) ==FAIL)
    print_mag_hskp_error("rd_Vgrp_mag_hskp -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_mag_hskp_error("rd_Vgrp_mag_hskp -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_mag_hskp_error("rd_Vgrp_mag_hskp -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_mag_hskp_error("rd_Vgrp_mag_hskp -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_MagHskpSet, HDstrlen(Vgrp_descrp_MagHskpSet)) ==FAIL)
    print_mag_hskp_error("rd_Vgrp_mag_hskp -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_MagHskpSet);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_mag_hskp_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_mag_hskp.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_mag_hskp(uint8 *data, struct MagHskpSet *MagHskpSet_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &MagHskpSet_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->sctime_collection, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->QACarr[0], ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(data+ptr, &MagHskpSet_ptr->st1a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->st2a, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->st3, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->st4, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->st5, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->st6, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->pctemp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->cmon, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->st1b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->st2b, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->hk1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->hk2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->hk3, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->hk4, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->hk5, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->sync, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->st, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->in_temp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->out_temp, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->in_pwrlvl, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->out_pwrlvl, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->current, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->SenIntTempPosY, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->SenIntTempNegY, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &MagHskpSet_ptr->MagPowBits, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_mag_hskp(uint8 *data, struct MagHskpSet *MagHskpSet_ptr)
{
int32 ptr=0;

   memcpy(&MagHskpSet_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&MagHskpSet_ptr->sctime_collection, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&MagHskpSet_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&MagHskpSet_ptr->QACarr[0], data+ptr,  ((1)*(16)) );
   ptr+= ((1)*(16));
   memcpy(&MagHskpSet_ptr->st1a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->st2a, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->st3, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->st4, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->st5, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->st6, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->pctemp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->cmon, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->st1b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->st2b, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->hk1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->hk2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->hk3, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->hk4, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->hk5, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->sync, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->st, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&MagHskpSet_ptr->in_temp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->out_temp, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->in_pwrlvl, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->out_pwrlvl, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->current, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->SenIntTempPosY, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->SenIntTempNegY, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&MagHskpSet_ptr->MagPowBits, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_mag_hskp() {return(vgrp_id_mag_hskp);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_mag_hskp(char *wr_strval)
{
  strcpy(wr_strval, "The file 'mag_hskp.h' is shown below, it was used to create the data in the Vgroup named 'VG_MagHskpSet'.\n\n");
  strcat(wr_strval,"/* Id: mag_hskp.h,v 1.9 1997/09/04 23:27:42 jeff Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct MagHskpSet\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 sctime_readout;           /* 32 bit spacecraft readout time  */\n");
  strcat(wr_strval,"  uint32 sctime_collection;        /* 32 bit spacecraft collection time  */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint32 QAC;              /* number of missing frames in this cycle */\n");
  strcat(wr_strval,"  uint8 QACarr[16]; /* each entry corresponds to a single minor frame */\n");
  strcat(wr_strval,"		    /* if value =0 frame is OK.  =1 frame contains fill data*/\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint8 st1a;            /* status byte 1, minor frame 1         */\n");
  strcat(wr_strval,"  uint8 st2a;            /* status byte 2, minor frame 2         */\n");
  strcat(wr_strval,"  uint8 st3;             /* status byte 3                        */\n");
  strcat(wr_strval,"  uint8 st4;             /* status byte 4                        */\n");
  strcat(wr_strval,"  uint8 st5;             /* status byte 5                        */\n");
  strcat(wr_strval,"  uint8 st6;             /* status byte 6                        */\n");
  strcat(wr_strval,"  uint8 pctemp;          /* power converter temperature status   */\n");
  strcat(wr_strval,"  uint8 cmon;            /* current monitor reading status       */\n");
  strcat(wr_strval,"  uint8 st1b;            /* status byte 1, minor frame 9         */\n");
  strcat(wr_strval,"  uint8 st2b;            /* status byte 2, minor frame 10        */\n");
  strcat(wr_strval,"  uint8 hk1;             /* housekeeping byte 1                  */\n");
  strcat(wr_strval,"  uint8 hk2;             /* housekeeping byte 2                  */\n");
  strcat(wr_strval,"  uint8 hk3;             /* housekeeping byte 3                  */\n");
  strcat(wr_strval,"  uint8 hk4;             /* housekeeping byte 4                  */\n");
  strcat(wr_strval,"  uint8 hk5;             /* housekeeping byte 5                  */\n");
  strcat(wr_strval,"  uint8 sync;            /* sync byte, TBD                       */\n");
  strcat(wr_strval,"  uint16 st;             /* st byte(s), TBD                      */ \n");
  strcat(wr_strval,"  uint8 in_temp;         /* inboard temperature                  */\n");
  strcat(wr_strval,"  uint8 out_temp;        /* outboard temperature                 */\n");
  strcat(wr_strval,"  uint8 in_pwrlvl;       /* inboard heater power level           */\n");
  strcat(wr_strval,"  uint8 out_pwrlvl;      /* outboard heater power level          */\n");
  strcat(wr_strval,"  uint8 current;         /* MAG current                          */\n");
  strcat(wr_strval,"  uint8 SenIntTempPosY;  /* MAG +Y Sensor Interface Temp         */\n");
  strcat(wr_strval,"  uint8 SenIntTempNegY;  /* MAG -Y Sensor Interface Temp         */\n");
  strcat(wr_strval,"  uint8 MagPowBits;      /* MAG Power/Ordinance Bits */\n");
  strcat(wr_strval,"				/* 7 - Main Sys Power A -       Bit pos  15 */\n");
  strcat(wr_strval,"				/* 6 - Main Sys Power B -       Bit pos  16 */\n");
  strcat(wr_strval,"				/* 5 - Main Int Heaters -       Bit pos  19 */\n");
  strcat(wr_strval,"				/* 4 - Main Interface Heater -  Bit pos  56 */\n");
  strcat(wr_strval,"				/* 3 - Main Boom Y Axis Arm  -  Bit pos  67 */\n");
  strcat(wr_strval,"				/* 2 - Backup Boom Y Axis Arm-  Bit pos  72 */\n");
  strcat(wr_strval,"				/* 1 - Unused -                             */\n");
  strcat(wr_strval,"				/* 0 - Unused -                             */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
