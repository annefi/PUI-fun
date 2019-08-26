/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.40 1997/10/08 01:13:48 jeff Exp $ */

/* The include file used to create this file is: */
/* $Id: mag_avgvec_in.h,v 1.1 1997/09/11 17:07:06 jeff Exp $ */

#include "mag_avgvec.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_mag_avgvec_in;
static int32 vdata_id_mag_avgvec_in;

static int32 sds_id_mag_avgvec_in1;

  /* 678 is the size of mag_avgvec.h + 1 added line */
char Vgrp_descrp_MagAvgVec[678];

/****----  init create function  ----****/

int32 init_cr_mag_avgvec_in(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_mag_avgvec_in();

  void print_mag_avgvec_in_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_mag_avgvec_in = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_mag_avgvec_in_error("init_cr_mag_avgvec_in -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_mag_avgvec_in, "VG_MagAvgVec"); 
  Vsetclass(vgrp_id_mag_avgvec_in, "VG_mag_avgvec_in");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_MagAvgVec" )) ==FAIL) {
    print_mag_avgvec_in_error("init_cr_mag_avgvec_in -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_mag_avgvec_in(Vgrp_descrp_MagAvgVec);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_mag_avgvec_in_error("init_cr_mag_avgvec_in -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_MagAvgVec, sizeof(Vgrp_descrp_MagAvgVec))) ==FAIL) {
    print_mag_avgvec_in_error("init_cr_mag_avgvec_in -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_mag_avgvec_in = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_mag_avgvec_in_error("init_cr_mag_avgvec_in -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_mag_avgvec_in, "MagAvgVec");
  VSsetclass(vdata_id_mag_avgvec_in, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_mag_avgvec_in, vdata_id_mag_avgvec_in)) ==FAIL) {
    print_mag_avgvec_in_error("init_cr_mag_avgvec_in -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_mag_avgvec_in, "sctime_readout", DFNT_UINT32, (1) )) {
    print_mag_avgvec_in_error("init_cr_mag_avgvec_in -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_avgvec_in, "sctime_collection", DFNT_UINT32, (1) )) {
    print_mag_avgvec_in_error("init_cr_mag_avgvec_in -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_avgvec_in, "QAC", DFNT_UINT32, (1) )) {
    print_mag_avgvec_in_error("init_cr_mag_avgvec_in -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }

  if (VSsetfields(vdata_id_mag_avgvec_in,"sctime_readout, sctime_collection, QAC")){
    print_mag_avgvec_in_error("init_cr_mag_avgvec_in -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = MAGAVGDIM;
  dim_sizes[2] = MAGNUMAVG;
  if((sds_id_mag_avgvec_in1 = SDcreate(sd_id, "MagAvgVec_avgvec", DFNT_FLOAT64, rank, dim_sizes)) == FAIL)
    print_mag_avgvec_in_error("init_cr_mag_avgvec_in -> SDcreate: Couldn't create MagAvgVec_avgvec");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_mag_avgvec_in1)) == FAIL)
    print_mag_avgvec_in_error("init_cr_mag_avgvec_in -> SDidtoref: Couldn't get ref for MagAvgVec_avgvec");

  if((Vaddtagref(vgrp_id_mag_avgvec_in, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_mag_avgvec_in_error("init_cr_mag_avgvec_in -> Vaddtagref: Couldn't add SDS MagAvgVec_avgvec to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_mag_avgvec_in(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_mag_avgvec_in(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_mag_avgvec_in(struct MagAvgVec MagAvgVec_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_mag_avgvec_in_error();
void pack_mag_avgvec_in();

  odata = (uint8 *) malloc(sizeof(struct MagAvgVec));
  pack_mag_avgvec_in(odata, &MagAvgVec_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_mag_avgvec_in, recnum)==-1) {
		print_mag_avgvec_in_error("write_mag_avgvec_in -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_mag_avgvec_in, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_mag_avgvec_in_error("write_mag_avgvec_in -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = MAGAVGDIM;
  edges[2] = MAGNUMAVG;
  if (SDwritedata(sds_id_mag_avgvec_in1,start,NULL,edges, (VOIDP)(MagAvgVec_struc.avgvec)) ==FAIL)
    print_mag_avgvec_in_error("write_mag_avgvec_in -> SDwritedata: Problem writing avgvec data.");

  memset(&MagAvgVec_struc, 0, sizeof(struct MagAvgVec));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_mag_avgvec_in()
{
  VSdetach(vdata_id_mag_avgvec_in);
  Vdetach(vgrp_id_mag_avgvec_in);
  SDendaccess(sds_id_mag_avgvec_in1);
}

/*----     init access function    ----*/

int32 init_acc_mag_avgvec_in(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_mag_avgvec_in_error();

   if((sds_index1=SDnametoindex(sd_id, "MagAvgVec_avgvec" )) ==FAIL) {
      print_mag_avgvec_in_error("init_acc_mag_avgvec_in -> SDnametoindex: Couldn't find MagAvgVec_avgvec");
      return(-1);
  }
  if((sds_id_mag_avgvec_in1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_mag_avgvec_in_error("init_acc_mag_avgvec_in -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "MagAvgVec")) <=0) {
    print_mag_avgvec_in_error("init_acc_mag_avgvec_in -> VSfind: Found no vdata of specified type");
    return(0);
  }
  if ((vdata_id_mag_avgvec_in = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_mag_avgvec_in_error("init_acc_mag_avgvec_in -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_mag_avgvec_in, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_mag_avgvec_in,"sctime_readout, sctime_collection, QAC")) {
      print_mag_avgvec_in_error("init_acc_mag_avgvec_in -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_mag_avgvec_in(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_mag_avgvec_in(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_mag_avgvec_in(struct MagAvgVec *MagAvgVec_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
static int32 last_recnum = -1;
int32 maxrec;
int32 retval = 0;
uint8 *odata;

void print_mag_avgvec_in_error();
void unpack_mag_avgvec_in();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct MagAvgVec));
  VSinquire(vdata_id_mag_avgvec_in, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_mag_avgvec_in, recnum_rd)==FAIL) {
          print_mag_avgvec_in_error("read_mag_avgvec_in -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = MAGAVGDIM;
  edges[2] = MAGNUMAVG;

  if(SDreaddata(sds_id_mag_avgvec_in1,start,NULL,edges, (VOIDP)(MagAvgVec_struc->avgvec )) ==FAIL) {
    print_mag_avgvec_in_error("read_mag_avgvec_in -> SDreaddata: Couldn't read avgvec");
    retval = -1;
  }
  if(VSread(vdata_id_mag_avgvec_in, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_mag_avgvec_in_error("read_mag_avgvec_in -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_mag_avgvec_in(odata, MagAvgVec_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_mag_avgvec_in()
{
  VSdetach(vdata_id_mag_avgvec_in);
  SDendaccess(sds_id_mag_avgvec_in1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_mag_avgvec_in(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_mag_avgvec_in_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_MagAvgVec" )) ==FAIL)
    print_mag_avgvec_in_error("rd_Vgrp_mag_avgvec_in -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_mag_avgvec_in_error("rd_Vgrp_mag_avgvec_in -> ANnumann: Couldn't get number of annotations.");

printf("1numann= %d \n", num_ann);
    ann_list = HDmalloc(num_ann * sizeof(int32));
printf("1ann_list= %d \n", ann_list);
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_mag_avgvec_in_error("rd_Vgrp_mag_avgvec_in -> ANannlist: Couldn't");

printf("2numann= %d \n", num_ann);
printf("2ann_list= %d \n", ann_list);
  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_mag_avgvec_in_error("rd_Vgrp_mag_avgvec_in -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_MagAvgVec, HDstrlen(Vgrp_descrp_MagAvgVec)) ==FAIL)
    print_mag_avgvec_in_error("rd_Vgrp_mag_avgvec_in -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_MagAvgVec);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_mag_avgvec_in_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_mag_avgvec_in.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_mag_avgvec_in(uint8 *data, struct MagAvgVec *MagAvgVec_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &MagAvgVec_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &MagAvgVec_ptr->sctime_collection, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &MagAvgVec_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_mag_avgvec_in(uint8 *data, struct MagAvgVec *MagAvgVec_ptr)
{
int32 ptr=0;

   memcpy(&MagAvgVec_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&MagAvgVec_ptr->sctime_collection, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&MagAvgVec_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_mag_avgvec_in() {return(vgrp_id_mag_avgvec_in);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_mag_avgvec_in(char *wr_strval)
{
  strcat(wr_strval, "The file 'mag_avgvec.h' is shown below, it was used to create the data in the Vgroup named 'VG_MagAvgVec'.\n\n");
  strcat(wr_strval,"/* $Id: mag_avgvec.h,v 1.1 1997/09/11 17:07:06 jeff Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define MAGNUMAVG 16\n");
  strcat(wr_strval,"#define MAGAVGDIM 3\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct MagAvgVec\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 sctime_readout;         /* 32 bit spacecraft readout time    */\n");
  strcat(wr_strval,"  uint32 sctime_collection;      /* 32 bit spacecraft collection time    */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint32 QAC;              /* number of missing frame in this cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  float64 avgvec[MAGAVGDIM][MAGNUMAVG];  /* magnetic vector  */\n");
  strcat(wr_strval,"		/* 1 second average in payload coordinates */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
