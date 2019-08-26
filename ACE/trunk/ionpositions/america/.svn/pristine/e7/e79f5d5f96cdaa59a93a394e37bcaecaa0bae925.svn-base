/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_sdiag.h,v 1.4 1998/12/07 18:12:39 ad Exp  */

#include "s3_sdiag.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_s3_sdiag;
static int32 vdata_id_s3_sdiag;

static int32 sds_id_s3_sdiag1;

  /* 1747 is the size of s3_sdiag.h + 1 added line */
char Vgrp_descrp_sdiag[1747];

/****----  init create function  ----****/

int32 init_cr_s3_sdiag(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_s3_sdiag();

  void print_s3_sdiag_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_sdiag = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_sdiag_error("init_cr_s3_sdiag -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_sdiag, "VG_sdiag"); 
  Vsetclass(vgrp_id_s3_sdiag, "VG_S3_SDIAG");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_sdiag" )) ==FAIL) {
    print_s3_sdiag_error("init_cr_s3_sdiag -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_sdiag(Vgrp_descrp_sdiag);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_sdiag_error("init_cr_s3_sdiag -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_sdiag, sizeof(Vgrp_descrp_sdiag))) ==FAIL) {
    print_s3_sdiag_error("init_cr_s3_sdiag -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_sdiag = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_sdiag_error("init_cr_s3_sdiag -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_sdiag, "sdiag");
  VSsetclass(vdata_id_s3_sdiag, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_sdiag, vdata_id_s3_sdiag)) ==FAIL) {
    print_s3_sdiag_error("init_cr_s3_sdiag -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_sdiag, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_sdiag_error("init_cr_s3_sdiag -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_sdiag, "sctime_collection", DFNT_FLOAT64, (1) )) {
    print_s3_sdiag_error("init_cr_s3_sdiag -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_sdiag, "QAC", DFNT_UINT16, (1) )) {
    print_s3_sdiag_error("init_cr_s3_sdiag -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_sdiag, "concat", DFNT_UINT16, (1) )) {
    print_s3_sdiag_error("init_cr_s3_sdiag -> VSfdefine: Couldn't define concat");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_sdiag, "numevts", DFNT_UINT16, (1) )) {
    print_s3_sdiag_error("init_cr_s3_sdiag -> VSfdefine: Couldn't define numevts");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_sdiag, "numevtsedb", DFNT_UINT16, (1) )) {
    print_s3_sdiag_error("init_cr_s3_sdiag -> VSfdefine: Couldn't define numevtsedb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_sdiag, "edb", DFNT_UINT16, (1) )) {
    print_s3_sdiag_error("init_cr_s3_sdiag -> VSfdefine: Couldn't define edb");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_sdiag,"sctime_readout, sctime_collection, QAC, concat, numevts, numevtsedb, edb")){
    print_s3_sdiag_error("init_cr_s3_sdiag -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 4;
  dim_sizes[2] = SEP_DIAG_CYCLEN;
  if((sds_id_s3_sdiag1 = SDcreate(sd_id, "sdiag_DIAG", DFNT_UINT16, rank, dim_sizes)) == FAIL)
    print_s3_sdiag_error("init_cr_s3_sdiag -> SDcreate: Couldn't create sdiag_DIAG");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_s3_sdiag1)) == FAIL)
    print_s3_sdiag_error("init_cr_s3_sdiag -> SDidtoref: Couldn't get ref for sdiag_DIAG");

  if((Vaddtagref(vgrp_id_s3_sdiag, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_s3_sdiag_error("init_cr_s3_sdiag -> Vaddtagref: Couldn't add SDS sdiag_DIAG to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_sdiag(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_sdiag(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_sdiag(struct sdiag sdiag_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_s3_sdiag_error();
void pack_s3_sdiag();

  odata = (uint8 *) malloc(sizeof(struct sdiag));
  pack_s3_sdiag(odata, &sdiag_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_s3_sdiag, recnum)==-1) {
		print_s3_sdiag_error("write_s3_sdiag -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_sdiag, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_sdiag_error("write_s3_sdiag -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = 4;
  edges[2] = SEP_DIAG_CYCLEN;
  if (SDwritedata(sds_id_s3_sdiag1,start,NULL,edges, (VOIDP)(sdiag_struc.DIAG)) ==FAIL)
    print_s3_sdiag_error("write_s3_sdiag -> SDwritedata: Problem writing DIAG data.");

  memset(&sdiag_struc, 0, sizeof(struct sdiag));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_sdiag()
{
  VSdetach(vdata_id_s3_sdiag);
  Vdetach(vgrp_id_s3_sdiag);
  SDendaccess(sds_id_s3_sdiag1);
}

/*----     init access function    ----*/

int32 init_acc_s3_sdiag(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_sdiag_error();

  if((sds_index1=SDnametoindex(sd_id, "sdiag_DIAG" )) ==FAIL) {
      print_s3_sdiag_error("init_acc_s3_sdiag -> SDnametoindex: Couldn't find sdiag_DIAG");
      return(-1);
  }
  if((sds_id_s3_sdiag1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_s3_sdiag_error("init_acc_s3_sdiag -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "sdiag")) <= 0 ) {
    print_s3_sdiag_error("init_acc_s3_sdiag -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_sdiag = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_sdiag_error("init_acc_s3_sdiag -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_sdiag, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_sdiag,"sctime_readout, sctime_collection, QAC, concat, numevts, numevtsedb, edb")) {
      print_s3_sdiag_error("init_acc_s3_sdiag -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_sdiag(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_sdiag(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_sdiag(struct sdiag *sdiag_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_sdiag_error();
void unpack_s3_sdiag();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct sdiag));
  VSinquire(vdata_id_s3_sdiag, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_sdiag, recnum_rd)==FAIL) {
          print_s3_sdiag_error("read_s3_sdiag -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = 4;
  edges[2] = SEP_DIAG_CYCLEN;

  if(SDreaddata(sds_id_s3_sdiag1,start,NULL,edges, (VOIDP)(sdiag_struc->DIAG )) ==FAIL) {
    print_s3_sdiag_error("read_s3_sdiag -> SDreaddata: Couldn't read DIAG");
    retval = -1;
  }
  if(VSread(vdata_id_s3_sdiag, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_sdiag_error("read_s3_sdiag -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_sdiag(odata, sdiag_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_sdiag()
{
  VSdetach(vdata_id_s3_sdiag);
  SDendaccess(sds_id_s3_sdiag1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_sdiag(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_sdiag_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_sdiag" )) ==FAIL)
    print_s3_sdiag_error("rd_Vgrp_s3_sdiag -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_sdiag_error("rd_Vgrp_s3_sdiag -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_sdiag_error("rd_Vgrp_s3_sdiag -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_sdiag_error("rd_Vgrp_s3_sdiag -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_sdiag, HDstrlen(Vgrp_descrp_sdiag)) ==FAIL)
    print_s3_sdiag_error("rd_Vgrp_s3_sdiag -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_sdiag);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_sdiag_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_sepica_sdiag.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_sdiag(uint8 *data, struct sdiag *sdiag_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &sdiag_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sdiag_ptr->sctime_collection, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &sdiag_ptr->QAC, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sdiag_ptr->concat, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sdiag_ptr->numevts, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sdiag_ptr->numevtsedb, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sdiag_ptr->edb, ((2)*(1)) );
   ptr+= ((2)*(1));
}

/*----   unpack function    ----*/

void unpack_s3_sdiag(uint8 *data, struct sdiag *sdiag_ptr)
{
int32 ptr=0;

   memcpy(&sdiag_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sdiag_ptr->sctime_collection, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&sdiag_ptr->QAC, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sdiag_ptr->concat, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sdiag_ptr->numevts, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sdiag_ptr->numevtsedb, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sdiag_ptr->edb, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
}
int32 get_vgrp_id_s3_sdiag() {return(vgrp_id_s3_sdiag);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_sdiag(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_sdiag.h' is shown below, it was used to create the data in the Vgroup named 'VG_sdiag'.\n\n");
  strcat(wr_strval,"/* Id: s3_sdiag.h,v 1.4 1998/12/07 18:12:39 ad Exp $	     */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define SEP_DIAG_CYCLEN    88 \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define SEP_DIAG_CYCPERSR  60  /* number of diag collection cycles per Science Rec */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* sctime_readout: spacecraft clock of first minor frame of the EDB */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* sctime_collection: diag data are collected over 1 spin and output */\n");
  strcat(wr_strval,"/* during the next spin. There are 60 diag collection cycles per SR. */\n");
  strcat(wr_strval,"/* sctime_collection contains the time of the start of the  */\n");
  strcat(wr_strval,"/* collection cycle (spin), in spacecraft clock time units */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct sdiag{\n");
  strcat(wr_strval,"	uint32 sctime_readout;	/* 32 bit spacecraft time  */\n");
  strcat(wr_strval,"	float64 sctime_collection; /* spacecraft time, sub-second resolution */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint16 QAC;	/* number of missing frames in this EDB */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint16  concat; /* Sequence number for this structure will be */\n");
  strcat(wr_strval,"		        /* greater than 1 for cases where the number of */\n");
  strcat(wr_strval,"		        /* events in the EDB exceeds SEP_PHA_MAX. In these */\n");
  strcat(wr_strval,"                        /* cases, concat will count down from N to 1, where N */\n");
  strcat(wr_strval,"                        /* is the total number of spha structures for the */\n");
  strcat(wr_strval,"                        /* current EDB. */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint16 numevts; /* Number of diag events in this structure. */\n");
  strcat(wr_strval,"                        /* Should be SEP_DIAG_MAX when concat > 1. */\n");
  strcat(wr_strval,"                        /* When concat == 1, numevts <= SEP_DIAG_MAX */\n");
  strcat(wr_strval,"			\n");
  strcat(wr_strval,"        uint16 numevtsedb; /* Number of diag events in the whole EDB */\n");
  strcat(wr_strval,"	\n");
  strcat(wr_strval,"	uint16 edb; /* sequence number of EDB in Science Record (0-59) */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint16 DIAG[4][SEP_DIAG_CYCLEN]; /* engineering data */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
