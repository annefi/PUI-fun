/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_cbasic.h,v 1.4 1999/09/01 21:22:19 ad Exp  */

#include "s3_cbasic.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_s3_cbasic;
static int32 vdata_id_s3_cbasic;

static int32 sds_id_s3_cbasic1;

  /* 941 is the size of s3_cbasic.h + 1 added line */
char Vgrp_descrp_cbasic[941];

/****----  init create function  ----****/

int32 init_cr_s3_cbasic(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_s3_cbasic();

  void print_s3_cbasic_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_cbasic = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_cbasic_error("init_cr_s3_cbasic -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_cbasic, "VG_cbasic"); 
  Vsetclass(vgrp_id_s3_cbasic, "VG_S3_CBASIC");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_cbasic" )) ==FAIL) {
    print_s3_cbasic_error("init_cr_s3_cbasic -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_cbasic(Vgrp_descrp_cbasic);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_cbasic_error("init_cr_s3_cbasic -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_cbasic, sizeof(Vgrp_descrp_cbasic))) ==FAIL) {
    print_s3_cbasic_error("init_cr_s3_cbasic -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_cbasic = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_cbasic_error("init_cr_s3_cbasic -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_cbasic, "cbasic");
  VSsetclass(vdata_id_s3_cbasic, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_cbasic, vdata_id_s3_cbasic)) ==FAIL) {
    print_s3_cbasic_error("init_cr_s3_cbasic -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_cbasic, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_cbasic_error("init_cr_s3_cbasic -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_cbasic, "sctime_collection", DFNT_UINT32, (1) )) {
    print_s3_cbasic_error("init_cr_s3_cbasic -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_cbasic, "QAC", DFNT_UINT32, (1) )) {
    print_s3_cbasic_error("init_cr_s3_cbasic -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_cbasic,"sctime_readout, sctime_collection, QAC")){
    print_s3_cbasic_error("init_cr_s3_cbasic -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = CBAS_CYC;
  dim_sizes[2] = CBAS_CSZ;
  if((sds_id_s3_cbasic1 = SDcreate(sd_id, "cbasic_BASIC", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_s3_cbasic_error("init_cr_s3_cbasic -> SDcreate: Couldn't create cbasic_BASIC");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_s3_cbasic1)) == FAIL)
    print_s3_cbasic_error("init_cr_s3_cbasic -> SDidtoref: Couldn't get ref for cbasic_BASIC");

  if((Vaddtagref(vgrp_id_s3_cbasic, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_s3_cbasic_error("init_cr_s3_cbasic -> Vaddtagref: Couldn't add SDS cbasic_BASIC to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_cbasic(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_cbasic(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_cbasic(struct cbasic cbasic_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_s3_cbasic_error();
void pack_s3_cbasic();

  odata = (uint8 *) malloc(sizeof(struct cbasic));
  pack_s3_cbasic(odata, &cbasic_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_s3_cbasic, recnum)==-1) {
		print_s3_cbasic_error("write_s3_cbasic -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_cbasic, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_cbasic_error("write_s3_cbasic -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = CBAS_CYC;
  edges[2] = CBAS_CSZ;
  if (SDwritedata(sds_id_s3_cbasic1,start,NULL,edges, (VOIDP)(cbasic_struc.BASIC)) ==FAIL)
    print_s3_cbasic_error("write_s3_cbasic -> SDwritedata: Problem writing BASIC data.");

  memset(&cbasic_struc, 0, sizeof(struct cbasic));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_cbasic()
{
  VSdetach(vdata_id_s3_cbasic);
  Vdetach(vgrp_id_s3_cbasic);
  SDendaccess(sds_id_s3_cbasic1);
}

/*----     init access function    ----*/

int32 init_acc_s3_cbasic(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_cbasic_error();

  if((sds_index1=SDnametoindex(sd_id, "cbasic_BASIC" )) ==FAIL) {
      print_s3_cbasic_error("init_acc_s3_cbasic -> SDnametoindex: Couldn't find cbasic_BASIC");
      return(-1);
  }
  if((sds_id_s3_cbasic1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_s3_cbasic_error("init_acc_s3_cbasic -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "cbasic")) <= 0 ) {
    print_s3_cbasic_error("init_acc_s3_cbasic -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_cbasic = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_cbasic_error("init_acc_s3_cbasic -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_cbasic, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_cbasic,"sctime_readout, sctime_collection, QAC")) {
      print_s3_cbasic_error("init_acc_s3_cbasic -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_cbasic(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_cbasic(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_cbasic(struct cbasic *cbasic_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_cbasic_error();
void unpack_s3_cbasic();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct cbasic));
  VSinquire(vdata_id_s3_cbasic, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_cbasic, recnum_rd)==FAIL) {
          print_s3_cbasic_error("read_s3_cbasic -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = CBAS_CYC;
  edges[2] = CBAS_CSZ;

  if(SDreaddata(sds_id_s3_cbasic1,start,NULL,edges, (VOIDP)(cbasic_struc->BASIC )) ==FAIL) {
    print_s3_cbasic_error("read_s3_cbasic -> SDreaddata: Couldn't read BASIC");
    retval = -1;
  }
  if(VSread(vdata_id_s3_cbasic, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_cbasic_error("read_s3_cbasic -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_cbasic(odata, cbasic_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_cbasic()
{
  VSdetach(vdata_id_s3_cbasic);
  SDendaccess(sds_id_s3_cbasic1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_cbasic(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_cbasic_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_cbasic" )) ==FAIL)
    print_s3_cbasic_error("rd_Vgrp_s3_cbasic -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_cbasic_error("rd_Vgrp_s3_cbasic -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_cbasic_error("rd_Vgrp_s3_cbasic -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_cbasic_error("rd_Vgrp_s3_cbasic -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_cbasic, HDstrlen(Vgrp_descrp_cbasic)) ==FAIL)
    print_s3_cbasic_error("rd_Vgrp_s3_cbasic -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_cbasic);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_cbasic_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swics_cbasic.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_cbasic(uint8 *data, struct cbasic *cbasic_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &cbasic_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &cbasic_ptr->sctime_collection, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &cbasic_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_s3_cbasic(uint8 *data, struct cbasic *cbasic_ptr)
{
int32 ptr=0;

   memcpy(&cbasic_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&cbasic_ptr->sctime_collection, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&cbasic_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_s3_cbasic() {return(vgrp_id_s3_cbasic);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_cbasic(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_cbasic.h' is shown below, it was used to create the data in the Vgroup named 'VG_cbasic'.\n\n");
  strcat(wr_strval,"/* Id: s3_cbasic.h,v 1.4 1999/09/01 21:22:19 ad Exp $           */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* SWICS basic rates */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include  \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define  CBAS_N    12                 /* number of basic rates, only 8 used? */\n");
  strcat(wr_strval,"#define  CBAS_S    8                  /* number of sectors */\n");
  strcat(wr_strval,"#define  CBAS_CYC  60                 /* number of cycles per SR= 60/1   */\n");
  strcat(wr_strval,"#define  CBAS_TSZ  ( CBAS_N*CBAS_S*CBAS_CYC ) /* total size in bytes 60x8x12     */\n");
  strcat(wr_strval,"#define  CBAS_CSZ  ( CBAS_N*CBAS_S )\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct cbasic  {\n");
  strcat(wr_strval,"           uint32  sctime_readout;      /*  32 bit  spacecraft  time  */\n");
  strcat(wr_strval,"           uint32  sctime_collection;   /*  32 bit  spacecraft  time  */\n");
  strcat(wr_strval,"           uint32  QAC;         /*number of missing frams in this SR  */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"           uint8  BASIC[CBAS_CYC][CBAS_CSZ]; \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"};\n");
  return(0);
}
