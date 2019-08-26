/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_mbasic.h,v 1.3 1997/05/07 23:15:42 jeff Exp  */

#include "s3_mbasic.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_s3_mbasic;
static int32 vdata_id_s3_mbasic;

static int32 sds_id_s3_mbasic1;

  /* 894 is the size of s3_mbasic.h + 1 added line */
char Vgrp_descrp_mbasic[894];

/****----  init create function  ----****/

int32 init_cr_s3_mbasic(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_s3_mbasic();

  void print_s3_mbasic_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_mbasic = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_mbasic_error("init_cr_s3_mbasic -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_mbasic, "VG_mbasic"); 
  Vsetclass(vgrp_id_s3_mbasic, "VG_S3_MBASIC");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_mbasic" )) ==FAIL) {
    print_s3_mbasic_error("init_cr_s3_mbasic -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_mbasic(Vgrp_descrp_mbasic);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_mbasic_error("init_cr_s3_mbasic -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_mbasic, sizeof(Vgrp_descrp_mbasic))) ==FAIL) {
    print_s3_mbasic_error("init_cr_s3_mbasic -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_mbasic = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_mbasic_error("init_cr_s3_mbasic -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_mbasic, "mbasic");
  VSsetclass(vdata_id_s3_mbasic, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_mbasic, vdata_id_s3_mbasic)) ==FAIL) {
    print_s3_mbasic_error("init_cr_s3_mbasic -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_mbasic, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_mbasic_error("init_cr_s3_mbasic -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mbasic, "sctime_collection", DFNT_UINT32, (1) )) {
    print_s3_mbasic_error("init_cr_s3_mbasic -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_mbasic, "QAC", DFNT_UINT32, (1) )) {
    print_s3_mbasic_error("init_cr_s3_mbasic -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_mbasic,"sctime_readout, sctime_collection, QAC")){
    print_s3_mbasic_error("init_cr_s3_mbasic -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = MBAS_CYC;
  dim_sizes[2] = MBAS_CSZ;
  if((sds_id_s3_mbasic1 = SDcreate(sd_id, "mbasic_BASIC", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_s3_mbasic_error("init_cr_s3_mbasic -> SDcreate: Couldn't create mbasic_BASIC");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_s3_mbasic1)) == FAIL)
    print_s3_mbasic_error("init_cr_s3_mbasic -> SDidtoref: Couldn't get ref for mbasic_BASIC");

  if((Vaddtagref(vgrp_id_s3_mbasic, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_s3_mbasic_error("init_cr_s3_mbasic -> Vaddtagref: Couldn't add SDS mbasic_BASIC to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_mbasic(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_mbasic(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_mbasic(struct mbasic mbasic_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_s3_mbasic_error();
void pack_s3_mbasic();

  odata = (uint8 *) malloc(sizeof(struct mbasic));
  pack_s3_mbasic(odata, &mbasic_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_s3_mbasic, recnum)==-1) {
		print_s3_mbasic_error("write_s3_mbasic -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_mbasic, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_mbasic_error("write_s3_mbasic -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = MBAS_CYC;
  edges[2] = MBAS_CSZ;
  if (SDwritedata(sds_id_s3_mbasic1,start,NULL,edges, (VOIDP)(mbasic_struc.BASIC)) ==FAIL)
    print_s3_mbasic_error("write_s3_mbasic -> SDwritedata: Problem writing BASIC data.");

  memset(&mbasic_struc, 0, sizeof(struct mbasic));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_mbasic()
{
  VSdetach(vdata_id_s3_mbasic);
  Vdetach(vgrp_id_s3_mbasic);
  SDendaccess(sds_id_s3_mbasic1);
}

/*----     init access function    ----*/

int32 init_acc_s3_mbasic(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_mbasic_error();

  if((sds_index1=SDnametoindex(sd_id, "mbasic_BASIC" )) ==FAIL) {
      print_s3_mbasic_error("init_acc_s3_mbasic -> SDnametoindex: Couldn't find mbasic_BASIC");
      return(-1);
  }
  if((sds_id_s3_mbasic1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_s3_mbasic_error("init_acc_s3_mbasic -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "mbasic")) <= 0 ) {
    print_s3_mbasic_error("init_acc_s3_mbasic -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_mbasic = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_mbasic_error("init_acc_s3_mbasic -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_mbasic, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_mbasic,"sctime_readout, sctime_collection, QAC")) {
      print_s3_mbasic_error("init_acc_s3_mbasic -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_mbasic(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_mbasic(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_mbasic(struct mbasic *mbasic_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_mbasic_error();
void unpack_s3_mbasic();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct mbasic));
  VSinquire(vdata_id_s3_mbasic, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_mbasic, recnum_rd)==FAIL) {
          print_s3_mbasic_error("read_s3_mbasic -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = MBAS_CYC;
  edges[2] = MBAS_CSZ;

  if(SDreaddata(sds_id_s3_mbasic1,start,NULL,edges, (VOIDP)(mbasic_struc->BASIC )) ==FAIL) {
    print_s3_mbasic_error("read_s3_mbasic -> SDreaddata: Couldn't read BASIC");
    retval = -1;
  }
  if(VSread(vdata_id_s3_mbasic, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_mbasic_error("read_s3_mbasic -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_mbasic(odata, mbasic_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_mbasic()
{
  VSdetach(vdata_id_s3_mbasic);
  SDendaccess(sds_id_s3_mbasic1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_mbasic(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_mbasic_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_mbasic" )) ==FAIL)
    print_s3_mbasic_error("rd_Vgrp_s3_mbasic -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_mbasic_error("rd_Vgrp_s3_mbasic -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_mbasic_error("rd_Vgrp_s3_mbasic -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_mbasic_error("rd_Vgrp_s3_mbasic -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_mbasic, HDstrlen(Vgrp_descrp_mbasic)) ==FAIL)
    print_s3_mbasic_error("rd_Vgrp_s3_mbasic -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_mbasic);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_mbasic_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swims_mbasic.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_mbasic(uint8 *data, struct mbasic *mbasic_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &mbasic_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &mbasic_ptr->sctime_collection, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &mbasic_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_s3_mbasic(uint8 *data, struct mbasic *mbasic_ptr)
{
int32 ptr=0;

   memcpy(&mbasic_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&mbasic_ptr->sctime_collection, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&mbasic_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_s3_mbasic() {return(vgrp_id_s3_mbasic);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_mbasic(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_mbasic.h' is shown below, it was used to create the data in the Vgroup named 'VG_mbasic'.\n\n");
  strcat(wr_strval,"/* Id: s3_mbasic.h,v 1.3 1997/05/07 23:15:42 jeff Exp $ */\n");
  strcat(wr_strval,"#include  \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* #define swims_basic_cyclen   32             32*1.0          */\n");
  strcat(wr_strval,"/* #define swims_basic_cycpersr 60                             */\n");
  strcat(wr_strval,"#define  MBAS_CYC  60                 /* number of cycles per SR= 60/1   */\n");
  strcat(wr_strval,"#define  MBAS_TSZ  1920               /* total size in bytes             */\n");
  strcat(wr_strval,"#define  MBAS_CSZ  MBAS_TSZ/MBAS_CYC \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct mbasic  {\n");
  strcat(wr_strval,"           uint32  sctime_readout;      /*  32 bit  spacecraft  time  */\n");
  strcat(wr_strval,"           uint32  sctime_collection;      /*  32 bit  spacecraft  time  */\n");
  strcat(wr_strval,"           uint32  QAC;         /*  number of missing frames in this SR */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"           uint8  BASIC[MBAS_CYC][MBAS_CSZ]; \n");
  strcat(wr_strval,"};\n");
  return(0);
}
