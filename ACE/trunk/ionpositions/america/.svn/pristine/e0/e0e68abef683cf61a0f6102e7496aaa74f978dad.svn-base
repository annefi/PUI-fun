/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_dtlm.h,v 1.1 1997/01/16 17:31:06 jeff Exp  */

#include "s3_dtlm.h"
#include "df.h"

int32 vgrp_id_s3_dtlm;
static int32 vdata_id_s3_dtlm;

  /* 502 is the size of s3_dtlm.h + 1 added line */
char Vgrp_descrp_sshdtlm[502];

/****----  init create function  ----****/

int32 init_cr_s3_dtlm(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_dtlm();

  void print_s3_dtlm_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_dtlm = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_dtlm_error("init_cr_s3_dtlm -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_dtlm, "VG_sshdtlm"); 
  Vsetclass(vgrp_id_s3_dtlm, "VG_S3_DTLM");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_sshdtlm" )) ==FAIL) {
    print_s3_dtlm_error("init_cr_s3_dtlm -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_dtlm(Vgrp_descrp_sshdtlm);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_dtlm_error("init_cr_s3_dtlm -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_sshdtlm, sizeof(Vgrp_descrp_sshdtlm))) ==FAIL) {
    print_s3_dtlm_error("init_cr_s3_dtlm -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_dtlm = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_dtlm_error("init_cr_s3_dtlm -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_dtlm, "sshdtlm");
  VSsetclass(vdata_id_s3_dtlm, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_dtlm, vdata_id_s3_dtlm)) ==FAIL) {
    print_s3_dtlm_error("init_cr_s3_dtlm -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_dtlm, "sctime", DFNT_UINT32, (1) )) {
    print_s3_dtlm_error("init_cr_s3_dtlm -> VSfdefine: Couldn't define sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dtlm, "QAC", DFNT_UINT32, (1) )) {
    print_s3_dtlm_error("init_cr_s3_dtlm -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dtlm, "buf", DFNT_UINT8, (60*34) )) {
    print_s3_dtlm_error("init_cr_s3_dtlm -> VSfdefine: Couldn't define buf");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_dtlm,"sctime, QAC, buf")){
    print_s3_dtlm_error("init_cr_s3_dtlm -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_dtlm(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_dtlm(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_dtlm(struct sshdtlm sshdtlm_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_dtlm_error();
void pack_s3_dtlm();

  odata = (uint8 *) malloc(sizeof(struct sshdtlm));
  pack_s3_dtlm(odata, &sshdtlm_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_dtlm, recnum)==-1) {
		print_s3_dtlm_error("write_s3_dtlm -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_dtlm, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_dtlm_error("write_s3_dtlm -> VSwrite: Couldn't write data.");

  memset(&sshdtlm_struc, 0, sizeof(struct sshdtlm));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_dtlm()
{
  VSdetach(vdata_id_s3_dtlm);
  Vdetach(vgrp_id_s3_dtlm);
}

/*----     init access function    ----*/

int32 init_acc_s3_dtlm(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_dtlm_error();


  if ((vdata_ref = VSfind(hdf_fp, "sshdtlm")) <= 0 ) {
    print_s3_dtlm_error("init_acc_s3_dtlm -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_dtlm = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_dtlm_error("init_acc_s3_dtlm -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_dtlm, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_dtlm,"sctime, QAC, buf")) {
      print_s3_dtlm_error("init_acc_s3_dtlm -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_dtlm(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_dtlm(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_dtlm(struct sshdtlm *sshdtlm_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_dtlm_error();
void unpack_s3_dtlm();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct sshdtlm));
  VSinquire(vdata_id_s3_dtlm, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_dtlm, recnum_rd)==FAIL) {
          print_s3_dtlm_error("read_s3_dtlm -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_dtlm, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_dtlm_error("read_s3_dtlm -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_dtlm(odata, sshdtlm_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_dtlm()
{
  VSdetach(vdata_id_s3_dtlm);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_dtlm(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_dtlm_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_sshdtlm" )) ==FAIL)
    print_s3_dtlm_error("rd_Vgrp_s3_dtlm -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_dtlm_error("rd_Vgrp_s3_dtlm -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_dtlm_error("rd_Vgrp_s3_dtlm -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_dtlm_error("rd_Vgrp_s3_dtlm -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_sshdtlm, HDstrlen(Vgrp_descrp_sshdtlm)) ==FAIL)
    print_s3_dtlm_error("rd_Vgrp_s3_dtlm -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_sshdtlm);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_dtlm_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_s3dpu_dtlm.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_dtlm(uint8 *data, struct sshdtlm *sshdtlm_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &sshdtlm_ptr->sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sshdtlm_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sshdtlm_ptr->buf[0], ((1)*(60*34)) );
   ptr+= ((1)*(60*34));
}

/*----   unpack function    ----*/

void unpack_s3_dtlm(uint8 *data, struct sshdtlm *sshdtlm_ptr)
{
int32 ptr=0;

   memcpy(&sshdtlm_ptr->sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sshdtlm_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sshdtlm_ptr->buf[0], data+ptr,  ((1)*(60*34)) );
   ptr+= ((1)*(60*34));
}
int32 get_vgrp_id_s3_dtlm() {return(vgrp_id_s3_dtlm);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_dtlm(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_dtlm.h' is shown below, it was used to create the data in the Vgroup named 'VG_sshdtlm'.\n\n");
  strcat(wr_strval,"/* Id: s3_dtlm.h,v 1.1 1997/01/16 17:31:06 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct sshdtlm{\n");
  strcat(wr_strval,"  uint32 sctime;           /* 32 bit spacecraft time             */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint32 QAC;              /* =1 if missing data, =0 otherwise */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint8 buf[60*34];           /* 34 bytes of hk, including header */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
