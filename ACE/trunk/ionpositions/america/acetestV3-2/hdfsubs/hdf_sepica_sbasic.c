/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_sbasic.h,v 1.6 1998/12/07 18:12:39 ad Exp  */

#include "s3_sbasic.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_s3_sbasic;
static int32 vdata_id_s3_sbasic;

static int32 sds_id_s3_sbasic1;

  /* 1612 is the size of s3_sbasic.h + 1 added line */
char Vgrp_descrp_sbasic[1612];

/****----  init create function  ----****/

int32 init_cr_s3_sbasic(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_s3_sbasic();

  void print_s3_sbasic_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_sbasic = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_sbasic_error("init_cr_s3_sbasic -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_sbasic, "VG_sbasic"); 
  Vsetclass(vgrp_id_s3_sbasic, "VG_S3_SBASIC");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_sbasic" )) ==FAIL) {
    print_s3_sbasic_error("init_cr_s3_sbasic -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_sbasic(Vgrp_descrp_sbasic);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_sbasic_error("init_cr_s3_sbasic -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_sbasic, sizeof(Vgrp_descrp_sbasic))) ==FAIL) {
    print_s3_sbasic_error("init_cr_s3_sbasic -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_sbasic = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_sbasic_error("init_cr_s3_sbasic -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_sbasic, "sbasic");
  VSsetclass(vdata_id_s3_sbasic, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_sbasic, vdata_id_s3_sbasic)) ==FAIL) {
    print_s3_sbasic_error("init_cr_s3_sbasic -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_sbasic, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_sbasic_error("init_cr_s3_sbasic -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_sbasic, "sctime_collection", DFNT_FLOAT64, (1) )) {
    print_s3_sbasic_error("init_cr_s3_sbasic -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_sbasic, "QAC", DFNT_UINT32, (1) )) {
    print_s3_sbasic_error("init_cr_s3_sbasic -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_sbasic, "FILL", DFNT_UINT16, (SBAS_NFILL) )) {
    print_s3_sbasic_error("init_cr_s3_sbasic -> VSfdefine: Couldn't define FILL");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_sbasic,"sctime_readout, sctime_collection, QAC, FILL")){
    print_s3_sbasic_error("init_cr_s3_sbasic -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = SBAS_N;
  dim_sizes[2] = SBAS_S;
  if((sds_id_s3_sbasic1 = SDcreate(sd_id, "sbasic_BASIC", DFNT_UINT16, rank, dim_sizes)) == FAIL)
    print_s3_sbasic_error("init_cr_s3_sbasic -> SDcreate: Couldn't create sbasic_BASIC");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_s3_sbasic1)) == FAIL)
    print_s3_sbasic_error("init_cr_s3_sbasic -> SDidtoref: Couldn't get ref for sbasic_BASIC");

  if((Vaddtagref(vgrp_id_s3_sbasic, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_s3_sbasic_error("init_cr_s3_sbasic -> Vaddtagref: Couldn't add SDS sbasic_BASIC to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_sbasic(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_sbasic(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_sbasic(struct sbasic sbasic_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_s3_sbasic_error();
void pack_s3_sbasic();

  odata = (uint8 *) malloc(sizeof(struct sbasic));
  pack_s3_sbasic(odata, &sbasic_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_s3_sbasic, recnum)==-1) {
		print_s3_sbasic_error("write_s3_sbasic -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_sbasic, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_sbasic_error("write_s3_sbasic -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = SBAS_N;
  edges[2] = SBAS_S;
  if (SDwritedata(sds_id_s3_sbasic1,start,NULL,edges, (VOIDP)(sbasic_struc.BASIC)) ==FAIL)
    print_s3_sbasic_error("write_s3_sbasic -> SDwritedata: Problem writing BASIC data.");

  memset(&sbasic_struc, 0, sizeof(struct sbasic));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_sbasic()
{
  VSdetach(vdata_id_s3_sbasic);
  Vdetach(vgrp_id_s3_sbasic);
  SDendaccess(sds_id_s3_sbasic1);
}

/*----     init access function    ----*/

int32 init_acc_s3_sbasic(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_sbasic_error();

  if((sds_index1=SDnametoindex(sd_id, "sbasic_BASIC" )) ==FAIL) {
      print_s3_sbasic_error("init_acc_s3_sbasic -> SDnametoindex: Couldn't find sbasic_BASIC");
      return(-1);
  }
  if((sds_id_s3_sbasic1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_s3_sbasic_error("init_acc_s3_sbasic -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "sbasic")) <= 0 ) {
    print_s3_sbasic_error("init_acc_s3_sbasic -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_sbasic = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_sbasic_error("init_acc_s3_sbasic -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_sbasic, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_sbasic,"sctime_readout, sctime_collection, QAC, FILL")) {
      print_s3_sbasic_error("init_acc_s3_sbasic -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_sbasic(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_sbasic(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_sbasic(struct sbasic *sbasic_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_sbasic_error();
void unpack_s3_sbasic();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct sbasic));
  VSinquire(vdata_id_s3_sbasic, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_sbasic, recnum_rd)==FAIL) {
          print_s3_sbasic_error("read_s3_sbasic -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = SBAS_N;
  edges[2] = SBAS_S;

  if(SDreaddata(sds_id_s3_sbasic1,start,NULL,edges, (VOIDP)(sbasic_struc->BASIC )) ==FAIL) {
    print_s3_sbasic_error("read_s3_sbasic -> SDreaddata: Couldn't read BASIC");
    retval = -1;
  }
  if(VSread(vdata_id_s3_sbasic, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_sbasic_error("read_s3_sbasic -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_sbasic(odata, sbasic_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_sbasic()
{
  VSdetach(vdata_id_s3_sbasic);
  SDendaccess(sds_id_s3_sbasic1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_sbasic(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_sbasic_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_sbasic" )) ==FAIL)
    print_s3_sbasic_error("rd_Vgrp_s3_sbasic -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_sbasic_error("rd_Vgrp_s3_sbasic -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_sbasic_error("rd_Vgrp_s3_sbasic -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_sbasic_error("rd_Vgrp_s3_sbasic -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_sbasic, HDstrlen(Vgrp_descrp_sbasic)) ==FAIL)
    print_s3_sbasic_error("rd_Vgrp_s3_sbasic -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_sbasic);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_sbasic_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_sepica_sbasic.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_sbasic(uint8 *data, struct sbasic *sbasic_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &sbasic_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sbasic_ptr->sctime_collection, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &sbasic_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sbasic_ptr->FILL[0], ((2)*(SBAS_NFILL)) );
   ptr+= ((2)*(SBAS_NFILL));
}

/*----   unpack function    ----*/

void unpack_s3_sbasic(uint8 *data, struct sbasic *sbasic_ptr)
{
int32 ptr=0;

   memcpy(&sbasic_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sbasic_ptr->sctime_collection, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&sbasic_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sbasic_ptr->FILL[0], data+ptr,  ((2)*(SBAS_NFILL)) );
   ptr+= ((2)*(SBAS_NFILL));
}
int32 get_vgrp_id_s3_sbasic() {return(vgrp_id_s3_sbasic);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_sbasic(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_sbasic.h' is shown below, it was used to create the data in the Vgroup named 'VG_sbasic'.\n\n");
  strcat(wr_strval,"/* Id: s3_sbasic.h,v 1.6 1998/12/07 18:12:39 ad Exp $	     */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* SEPICA Basic rates */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define SBAS_N     16  /* number of basic rates */\n");
  strcat(wr_strval,"#define SBAS_S     8  /* number of sectors */\n");
  strcat(wr_strval,"#define SBAS_CYC   12  /* number of cycles per SR = 60 / 5 */\n");
  strcat(wr_strval,"#define SBAS_NFILL 2  /* amount of fill data per cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval," /* total size (in bytes) of SBAS data (including slack) in a full SR */\n");
  strcat(wr_strval,"#define SBAS_TSZ   2340  \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval," /* size (in bytes) of SMON cycle (including slack) */\n");
  strcat(wr_strval,"#define SBAS_CSZ   SBAS_TSZ/SBAS_CYC \n");
  strcat(wr_strval,"#define SBAS_ESZ   SBAS_TSZ/60  /* size (in bytes) of SBAS area in EDB */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* Basic rates are collected over 5 spins and output during the next */\n");
  strcat(wr_strval,"/* 5 spins(or edb's). There are 12 basic rate collection cycles per */\n");
  strcat(wr_strval,"/* Science Record */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* sctime_readout: spacecraft clock of first minor frame of the */\n");
  strcat(wr_strval,"/* first edb of the basic rate output cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* sctime_collection:  time of the start of the first spin in the */\n");
  strcat(wr_strval,"/* collection cycle, in spacecraft clock time units */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* sbasic structure contains basic rates for 1 5-spin collection cycle */\n");
  strcat(wr_strval,"struct sbasic{\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"   uint32 sctime_readout;	/* 32 bit spacecraft time  */\n");
  strcat(wr_strval,"   float64 sctime_collection; /* spacecraft time, sub-second resolution */\n");
  strcat(wr_strval,"   uint32 QAC;	/* number of frames of missing data in this 5-spin cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"   uint16 BASIC[SBAS_N][SBAS_S];/* 16 Basic rates, 8 sectors */\n");
  strcat(wr_strval,"   uint16 FILL[SBAS_NFILL];    /*  Fill data  */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
