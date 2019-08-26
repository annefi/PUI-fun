/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_mhk.h,v 1.2 1997/05/06 19:11:02 jeff Exp  */

#include "s3_mhk.h"
#include "df.h"

int32 vgrp_id_s3_mhk;
static int32 vdata_id_s3_mhk;

  /* 2518 is the size of s3_mhk.h + 1 added line */
char Vgrp_descrp_ssmhk[2518];

/****----  init create function  ----****/

int32 init_cr_s3_mhk(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_mhk();

  void print_s3_mhk_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_mhk = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_mhk_error("init_cr_s3_mhk -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_mhk, "VG_ssmhk"); 
  Vsetclass(vgrp_id_s3_mhk, "VG_S3_MHK");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_ssmhk" )) ==FAIL) {
    print_s3_mhk_error("init_cr_s3_mhk -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_mhk(Vgrp_descrp_ssmhk);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_mhk_error("init_cr_s3_mhk -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_ssmhk, sizeof(Vgrp_descrp_ssmhk))) ==FAIL) {
    print_s3_mhk_error("init_cr_s3_mhk -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_mhk = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_mhk, "ssmhk");
  VSsetclass(vdata_id_s3_mhk, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_mhk, vdata_id_s3_mhk)) ==FAIL) {
    print_s3_mhk_error("init_cr_s3_mhk -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_mhk, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "sctime_collection", DFNT_UINT32, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "QAC", DFNT_UINT32, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "GRP282V", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define GRP282V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "GRP9V", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define GRP9V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "GRP5V", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define GRP5V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "GRM5V", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define GRM5V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "GRM12V", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define GRM12V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "GR1T", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define GR1T");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "GR2T", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define GR2T");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "SPARE1", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define SPARE1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "GRP281I", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define GRP281I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "GRP282I", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define GRP282I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "GRP5I", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define GRP5I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "SPARE2", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define SPARE2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "SPARE3", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define SPARE3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "SPARE4", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define SPARE4");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "GRWAVEEQ", DFNT_UINT16, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define GRWAVEEQ");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "GRVF", DFNT_UINT16, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define GRVF");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "VFP28V", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define VFP28V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "VFP9V", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define VFP9V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "VFP6V", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define VFP6V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "VFP5V", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define VFP5V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "VFM5V", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define VFM5V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "VFM12V", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define VFM12V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "VF1T", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define VF1T");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "VF2T", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define VF2T");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "VFP28I", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define VFP28I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "VFP6I", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define VFP6I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "VFP5I", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define VFP5I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "VFM5I", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define VFM5I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "VFSTART", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define VFSTART");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "SPARE5", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define SPARE5");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "VFSTOP", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define VFSTOP");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "VFHPS", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define VFHPS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mhk, "STATE", DFNT_UINT8, (1) )) {
    print_s3_mhk_error("init_cr_s3_mhk -> VSfdefine: Couldn't define STATE");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_mhk,"sctime_readout, sctime_collection, QAC, GRP282V, GRP9V, GRP5V, GRM5V, GRM12V, GR1T, GR2T, SPARE1, GRP281I, GRP282I, GRP5I, SPARE2, SPARE3, SPARE4, GRWAVEEQ, GRVF, VFP28V, VFP9V, VFP6V, VFP5V, VFM5V, VFM12V, VF1T, VF2T, VFP28I, VFP6I, VFP5I, VFM5I, VFSTART, SPARE5, VFSTOP, VFHPS, STATE")){
    print_s3_mhk_error("init_cr_s3_mhk -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_mhk(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_mhk(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_mhk(struct ssmhk ssmhk_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_mhk_error();
void pack_s3_mhk();

  odata = (uint8 *) malloc(sizeof(struct ssmhk));
  pack_s3_mhk(odata, &ssmhk_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_mhk, recnum)==-1) {
		print_s3_mhk_error("write_s3_mhk -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_mhk, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_mhk_error("write_s3_mhk -> VSwrite: Couldn't write data.");

  memset(&ssmhk_struc, 0, sizeof(struct ssmhk));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_mhk()
{
  VSdetach(vdata_id_s3_mhk);
  Vdetach(vgrp_id_s3_mhk);
}

/*----     init access function    ----*/

int32 init_acc_s3_mhk(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_mhk_error();


  if ((vdata_ref = VSfind(hdf_fp, "ssmhk")) <= 0 ) {
    print_s3_mhk_error("init_acc_s3_mhk -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_mhk = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_mhk_error("init_acc_s3_mhk -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_mhk, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_mhk,"sctime_readout, sctime_collection, QAC, GRP282V, GRP9V, GRP5V, GRM5V, GRM12V, GR1T, GR2T, SPARE1, GRP281I, GRP282I, GRP5I, SPARE2, SPARE3, SPARE4, GRWAVEEQ, GRVF, VFP28V, VFP9V, VFP6V, VFP5V, VFM5V, VFM12V, VF1T, VF2T, VFP28I, VFP6I, VFP5I, VFM5I, VFSTART, SPARE5, VFSTOP, VFHPS, STATE")) {
      print_s3_mhk_error("init_acc_s3_mhk -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_mhk(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_mhk(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_mhk(struct ssmhk *ssmhk_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_mhk_error();
void unpack_s3_mhk();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct ssmhk));
  VSinquire(vdata_id_s3_mhk, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_mhk, recnum_rd)==FAIL) {
          print_s3_mhk_error("read_s3_mhk -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_mhk, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_mhk_error("read_s3_mhk -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_mhk(odata, ssmhk_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_mhk()
{
  VSdetach(vdata_id_s3_mhk);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_mhk(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_mhk_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_ssmhk" )) ==FAIL)
    print_s3_mhk_error("rd_Vgrp_s3_mhk -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_mhk_error("rd_Vgrp_s3_mhk -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_mhk_error("rd_Vgrp_s3_mhk -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_mhk_error("rd_Vgrp_s3_mhk -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_ssmhk, HDstrlen(Vgrp_descrp_ssmhk)) ==FAIL)
    print_s3_mhk_error("rd_Vgrp_s3_mhk -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_ssmhk);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_mhk_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swims_mhk.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_mhk(uint8 *data, struct ssmhk *ssmhk_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &ssmhk_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ssmhk_ptr->sctime_collection, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ssmhk_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ssmhk_ptr->GRP282V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->GRP9V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->GRP5V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->GRM5V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->GRM12V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->GR1T, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->GR2T, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->SPARE1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->GRP281I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->GRP282I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->GRP5I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->SPARE2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->SPARE3, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->SPARE4, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->GRWAVEEQ, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &ssmhk_ptr->GRVF, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &ssmhk_ptr->VFP28V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->VFP9V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->VFP6V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->VFP5V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->VFM5V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->VFM12V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->VF1T, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->VF2T, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->VFP28I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->VFP6I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->VFP5I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->VFM5I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->VFSTART, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->SPARE5, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->VFSTOP, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->VFHPS, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ssmhk_ptr->STATE, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_s3_mhk(uint8 *data, struct ssmhk *ssmhk_ptr)
{
int32 ptr=0;

   memcpy(&ssmhk_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ssmhk_ptr->sctime_collection, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ssmhk_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ssmhk_ptr->GRP282V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->GRP9V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->GRP5V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->GRM5V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->GRM12V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->GR1T, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->GR2T, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->SPARE1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->GRP281I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->GRP282I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->GRP5I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->SPARE2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->SPARE3, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->SPARE4, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->GRWAVEEQ, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&ssmhk_ptr->GRVF, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&ssmhk_ptr->VFP28V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->VFP9V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->VFP6V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->VFP5V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->VFM5V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->VFM12V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->VF1T, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->VF2T, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->VFP28I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->VFP6I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->VFP5I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->VFM5I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->VFSTART, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->SPARE5, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->VFSTOP, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->VFHPS, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ssmhk_ptr->STATE, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_s3_mhk() {return(vgrp_id_s3_mhk);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_mhk(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_mhk.h' is shown below, it was used to create the data in the Vgroup named 'VG_ssmhk'.\n\n");
  strcat(wr_strval,"/* Id: s3_mhk.h,v 1.2 1997/05/06 19:11:02 jeff Exp $ */\n");
  strcat(wr_strval,"#include  \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"        struct ssmhk {\n");
  strcat(wr_strval,"             uint32  sctime_readout;      /*  32 bit  spacecraft  time  */\n");
  strcat(wr_strval,"             uint32  sctime_collection;      /*  32 bit  spacecraft  time  */\n");
  strcat(wr_strval,"             uint32  QAC;         /*  number of missing frames in this SR */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"             uint8 GRP282V;       /*  GND  +28V Sec.     */\n");
  strcat(wr_strval,"             uint8 GRP9V;         /*  GND  +9V           */\n");
  strcat(wr_strval,"             uint8 GRP5V;         /*  GND  +5V           */\n");
  strcat(wr_strval,"             uint8 GRM5V;         /*  GND  -5V           */\n");
  strcat(wr_strval,"             uint8 GRM12V;        /*  GND  -12V          */\n");
  strcat(wr_strval,"             uint8 GR1T;          /*  GND  Thermistor 1  */\n");
  strcat(wr_strval,"             uint8 GR2T;          /*  GND  Thermistor 2  */\n");
  strcat(wr_strval,"             uint8 SPARE1;        /*  Spare              */\n");
  strcat(wr_strval,"             uint8 GRP281I;       /*  GND  +28V Prim.    */\n");
  strcat(wr_strval,"             uint8 GRP282I;       /*  GND  +28V Sec.     */\n");
  strcat(wr_strval,"             uint8 GRP5I;         /*  GND  +5V  I        */\n");
  strcat(wr_strval,"             uint8 SPARE2;        /*  Spare              */\n");
  strcat(wr_strval,"             uint8 SPARE3;        /*  Spare              */\n");
  strcat(wr_strval,"             uint8 SPARE4;        /*  Spare              */\n");
  strcat(wr_strval,"            uint16 GRWAVEEQ;      /*  GND  Wave  E/q     */\n");
  strcat(wr_strval,"            uint16 GRVF;          /*  GND  VF            */\n");
  strcat(wr_strval,"             uint8 VFP28V;        /*  VF  +28V           */\n");
  strcat(wr_strval,"             uint8 VFP9V;         /*  VF  +9V            */\n");
  strcat(wr_strval,"             uint8 VFP6V;         /*  VF  +6V            */\n");
  strcat(wr_strval,"             uint8 VFP5V;         /*  VF  +5V            */\n");
  strcat(wr_strval,"             uint8 VFM5V;         /*  VF  -5V            */\n");
  strcat(wr_strval,"             uint8 VFM12V;        /*  VF  -12V           */\n");
  strcat(wr_strval,"             uint8 VF1T;          /*  VF  Thermistor 1   */\n");
  strcat(wr_strval,"             uint8 VF2T;          /*  VF  Thermistor 2   */  \n");
  strcat(wr_strval,"             uint8 VFP28I;        /*  VF  +28V I         */\n");
  strcat(wr_strval,"             uint8 VFP6I;         /*  VF  +6V  I         */\n");
  strcat(wr_strval,"             uint8 VFP5I;         /*  VF  +5V  I         */\n");
  strcat(wr_strval,"             uint8 VFM5I;         /*  VF  -5V  I         */\n");
  strcat(wr_strval,"             uint8 VFSTART;       /*  VF  Start MCP      */\n");
  strcat(wr_strval,"             uint8 SPARE5;        /*  Spare              */\n");
  strcat(wr_strval,"             uint8 VFSTOP;        /*  VF  Stop MCP       */\n");
  strcat(wr_strval,"             uint8 VFHPS;         /*  VF  HVPS           */\n");
  strcat(wr_strval,"             uint8 STATE;          /*  Digital Status     */\n");
  strcat(wr_strval,"}; \n");
  return(0);
}
