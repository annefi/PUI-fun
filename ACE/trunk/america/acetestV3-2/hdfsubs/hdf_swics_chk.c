/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_chk.h,v 1.2 1997/05/06 18:06:01 jeff Exp  */

#include "s3_chk.h"
#include "df.h"

int32 vgrp_id_s3_chk;
static int32 vdata_id_s3_chk;

  /* 2082 is the size of s3_chk.h + 1 added line */
char Vgrp_descrp_csmhk[2082];

/****----  init create function  ----****/

int32 init_cr_s3_chk(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_chk();

  void print_s3_chk_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_chk = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_chk_error("init_cr_s3_chk -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_chk, "VG_csmhk"); 
  Vsetclass(vgrp_id_s3_chk, "VG_S3_CHK");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_csmhk" )) ==FAIL) {
    print_s3_chk_error("init_cr_s3_chk -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_chk(Vgrp_descrp_csmhk);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_chk_error("init_cr_s3_chk -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_csmhk, sizeof(Vgrp_descrp_csmhk))) ==FAIL) {
    print_s3_chk_error("init_cr_s3_chk -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_chk = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_chk_error("init_cr_s3_chk -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_chk, "csmhk");
  VSsetclass(vdata_id_s3_chk, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_chk, vdata_id_s3_chk)) ==FAIL) {
    print_s3_chk_error("init_cr_s3_chk -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_chk, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "sctime_collection", DFNT_UINT32, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "QAC", DFNT_UINT32, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "GRP282V", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define GRP282V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "GR20V", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define GR20V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "GRP10V", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define GRP10V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "GRP5V", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define GRP5V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "GRM5V", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define GRM5V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "SPARE1", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define SPARE1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "GR1T", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define GR1T");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "GR2T", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define GR2T");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "GRP281I", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define GRP281I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "GRP282I", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define GRP282I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "GRP5I", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define GRP5I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "GR20I", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define GR20I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "GRPAPS", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define GRPAPS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "SPARE2", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define SPARE2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "GRDPPSL", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define GRDPPSL");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "GRDPPSH", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define GRDPPSH");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "SPARE3", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define SPARE3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "PAC7", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define PAC7");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "PA1T", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define PA1T");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "PA2T", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define PA2T");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "PAP5V", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define PAP5V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "PAP5I", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define PAP5I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "PAM5V", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define PAM5V");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "PAM5I", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define PAM5I");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "PAMCP", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define PAMCP");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_chk, "FLAGS", DFNT_UINT8, (1) )) {
    print_s3_chk_error("init_cr_s3_chk -> VSfdefine: Couldn't define FLAGS");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_chk,"sctime_readout, sctime_collection, QAC, GRP282V, GR20V, GRP10V, GRP5V, GRM5V, SPARE1, GR1T, GR2T, GRP281I, GRP282I, GRP5I, GR20I, GRPAPS, SPARE2, GRDPPSL, GRDPPSH, SPARE3, PAC7, PA1T, PA2T, PAP5V, PAP5I, PAM5V, PAM5I, PAMCP, FLAGS")){
    print_s3_chk_error("init_cr_s3_chk -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_chk(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_chk(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_chk(struct csmhk csmhk_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_chk_error();
void pack_s3_chk();

  odata = (uint8 *) malloc(sizeof(struct csmhk));
  pack_s3_chk(odata, &csmhk_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_chk, recnum)==-1) {
		print_s3_chk_error("write_s3_chk -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_chk, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_chk_error("write_s3_chk -> VSwrite: Couldn't write data.");

  memset(&csmhk_struc, 0, sizeof(struct csmhk));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_chk()
{
  VSdetach(vdata_id_s3_chk);
  Vdetach(vgrp_id_s3_chk);
}

/*----     init access function    ----*/

int32 init_acc_s3_chk(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_chk_error();


  if ((vdata_ref = VSfind(hdf_fp, "csmhk")) <= 0 ) {
    print_s3_chk_error("init_acc_s3_chk -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_chk = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_chk_error("init_acc_s3_chk -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_chk, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_chk,"sctime_readout, sctime_collection, QAC, GRP282V, GR20V, GRP10V, GRP5V, GRM5V, SPARE1, GR1T, GR2T, GRP281I, GRP282I, GRP5I, GR20I, GRPAPS, SPARE2, GRDPPSL, GRDPPSH, SPARE3, PAC7, PA1T, PA2T, PAP5V, PAP5I, PAM5V, PAM5I, PAMCP, FLAGS")) {
      print_s3_chk_error("init_acc_s3_chk -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_chk(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_chk(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_chk(struct csmhk *csmhk_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_chk_error();
void unpack_s3_chk();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct csmhk));
  VSinquire(vdata_id_s3_chk, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_chk, recnum_rd)==FAIL) {
          print_s3_chk_error("read_s3_chk -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_chk, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_chk_error("read_s3_chk -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_chk(odata, csmhk_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_chk()
{
  VSdetach(vdata_id_s3_chk);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_chk(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_chk_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_csmhk" )) ==FAIL)
    print_s3_chk_error("rd_Vgrp_s3_chk -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_chk_error("rd_Vgrp_s3_chk -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_chk_error("rd_Vgrp_s3_chk -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_chk_error("rd_Vgrp_s3_chk -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_csmhk, HDstrlen(Vgrp_descrp_csmhk)) ==FAIL)
    print_s3_chk_error("rd_Vgrp_s3_chk -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_csmhk);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_chk_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swics_chk.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_chk(uint8 *data, struct csmhk *csmhk_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &csmhk_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &csmhk_ptr->sctime_collection, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &csmhk_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &csmhk_ptr->GRP282V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->GR20V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->GRP10V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->GRP5V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->GRM5V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->SPARE1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->GR1T, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->GR2T, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->GRP281I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->GRP282I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->GRP5I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->GR20I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->GRPAPS, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->SPARE2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->GRDPPSL, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->GRDPPSH, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->SPARE3, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->PAC7, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->PA1T, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->PA2T, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->PAP5V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->PAP5I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->PAM5V, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->PAM5I, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->PAMCP, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &csmhk_ptr->FLAGS, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_s3_chk(uint8 *data, struct csmhk *csmhk_ptr)
{
int32 ptr=0;

   memcpy(&csmhk_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&csmhk_ptr->sctime_collection, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&csmhk_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&csmhk_ptr->GRP282V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->GR20V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->GRP10V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->GRP5V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->GRM5V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->SPARE1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->GR1T, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->GR2T, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->GRP281I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->GRP282I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->GRP5I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->GR20I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->GRPAPS, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->SPARE2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->GRDPPSL, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->GRDPPSH, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->SPARE3, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->PAC7, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->PA1T, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->PA2T, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->PAP5V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->PAP5I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->PAM5V, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->PAM5I, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->PAMCP, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&csmhk_ptr->FLAGS, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_s3_chk() {return(vgrp_id_s3_chk);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_chk(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_chk.h' is shown below, it was used to create the data in the Vgroup named 'VG_csmhk'.\n\n");
  strcat(wr_strval,"/* Id: s3_chk.h,v 1.2 1997/05/06 18:06:01 jeff Exp $ */\n");
  strcat(wr_strval,"#include  \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"        struct csmhk {\n");
  strcat(wr_strval,"             uint32  sctime_readout;     /* 32 bit spacecraft time  */\n");
  strcat(wr_strval,"             uint32  sctime_collection;  /* 32 bit spacecraft time  */\n");
  strcat(wr_strval,"             uint32  QAC;        /* number of missing frame in this SR*/\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"             uint8 GRP282V;       /*  GND  +28V Sec.     */\n");
  strcat(wr_strval,"             uint8 GR20V;         /*  GND  20V  AC       */\n");
  strcat(wr_strval,"             uint8 GRP10V;        /*  GND  +10V          */\n");
  strcat(wr_strval,"             uint8 GRP5V;         /*  GND  +5V           */\n");
  strcat(wr_strval,"             uint8 GRM5V;         /*  GND  -5V           */\n");
  strcat(wr_strval,"             uint8 SPARE1;        /*  Spare              */\n");
  strcat(wr_strval,"             uint8 GR1T;          /*  GND  Thermistor 1  */\n");
  strcat(wr_strval,"             uint8 GR2T;          /*  GND  Thermister 2  */\n");
  strcat(wr_strval,"             uint8 GRP281I;       /*  GND  +28V I Prim.  */\n");
  strcat(wr_strval,"             uint8 GRP282I;       /*  GND  +28V I Sec.   */\n");
  strcat(wr_strval,"             uint8 GRP5I;         /*  GND  +5V  I        */\n");
  strcat(wr_strval,"             uint8 GR20I;         /*  GND  20V  AC I     */\n");
  strcat(wr_strval,"             uint8 GRPAPS;        /*  GND  PAPS          */ \n");
  strcat(wr_strval,"             uint8 SPARE2;        /*  Spare              */\n");
  strcat(wr_strval,"             uint8 GRDPPSL;       /*  GND  DPPS Low      */\n");
  strcat(wr_strval,"             uint8 GRDPPSH;       /*  GND  DPPS High     */ \n");
  strcat(wr_strval,"             uint8 SPARE3;        /*  Spare              */\n");
  strcat(wr_strval,"             uint8 PAC7;          /*  PAPS Synch C7      */\n");
  strcat(wr_strval,"             uint8 PA1T;          /*  PAPS Thermistor 1  */\n");
  strcat(wr_strval,"             uint8 PA2T;          /*  PAPS Thermistor 2  */\n");
  strcat(wr_strval,"             uint8 PAP5V;         /*  PAPS +5V           */\n");
  strcat(wr_strval,"             uint8 PAP5I;         /*  PAPS +5V I         */\n");
  strcat(wr_strval,"             uint8 PAM5V;         /*  PAPS -5V           */\n");
  strcat(wr_strval,"             uint8 PAM5I;         /*  PAPS -5V I         */\n");
  strcat(wr_strval,"             uint8 PAMCP;         /*  PAPS MCP Bias      */\n");
  strcat(wr_strval,"             uint8 FLAGS;         /*  Flags (DPPS Gain,..*/\n");
  strcat(wr_strval,"}; \n");
  return(0);
}
