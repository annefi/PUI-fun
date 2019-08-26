/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: uleis_rate.h,v 1.5 1997/04/10 22:19:24 steves Exp  */

#include "uleis_rate.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_uleis_rate;
static int32 vdata_id_uleis_rate;

static int32 sds_id_uleis_rate1, sds_id_uleis_rate2, sds_id_uleis_rate3;

  /* 1203 is the size of uleis_rate.h + 1 added line */
char Vgrp_descrp_URateSet[1203];

/****----  init create function  ----****/

int32 init_cr_uleis_rate(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1, sds_ref_w2, sds_ref_w3;
  int32 dim_sizes[4];
  int32 rank;

  int32 wr_Vgrp_desc_uleis_rate();

  void print_uleis_rate_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_uleis_rate = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_uleis_rate_error("init_cr_uleis_rate -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_uleis_rate, "VG_URateSet"); 
  Vsetclass(vgrp_id_uleis_rate, "VG_ULEIS_RATE");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_URateSet" )) ==FAIL) {
    print_uleis_rate_error("init_cr_uleis_rate -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_uleis_rate(Vgrp_descrp_URateSet);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_uleis_rate_error("init_cr_uleis_rate -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_URateSet, sizeof(Vgrp_descrp_URateSet))) ==FAIL) {
    print_uleis_rate_error("init_cr_uleis_rate -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_uleis_rate = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_uleis_rate_error("init_cr_uleis_rate -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_uleis_rate, "URateSet");
  VSsetclass(vdata_id_uleis_rate, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_uleis_rate, vdata_id_uleis_rate)) ==FAIL) {
    print_uleis_rate_error("init_cr_uleis_rate -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_uleis_rate, "output_sctime", DFNT_UINT32, (1) )) {
    print_uleis_rate_error("init_cr_uleis_rate -> VSfdefine: Couldn't define output_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_rate, "collect_sctime", DFNT_UINT32, (1) )) {
    print_uleis_rate_error("init_cr_uleis_rate -> VSfdefine: Couldn't define collect_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_rate, "QAC", DFNT_UINT32, (1) )) {
    print_uleis_rate_error("init_cr_uleis_rate -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }

  if (VSsetfields(vdata_id_uleis_rate,"output_sctime, collect_sctime, QAC")){
    print_uleis_rate_error("init_cr_uleis_rate -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 4;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = U_MTRX_RATE_SIZE;
  dim_sizes[2] = U_SPINS;
  dim_sizes[3] = U_SECTRS;
  if((sds_id_uleis_rate1 = SDcreate(sd_id, "URateSet_Matrx", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_uleis_rate_error("init_cr_uleis_rate -> SDcreate: Couldn't create URateSet_Matrx");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_uleis_rate1)) == FAIL)
    print_uleis_rate_error("init_cr_uleis_rate -> SDidtoref: Couldn't get ref for URateSet_Matrx");

  if((Vaddtagref(vgrp_id_uleis_rate, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_uleis_rate_error("init_cr_uleis_rate -> Vaddtagref: Couldn't add SDS URateSet_Matrx to Vgrp");

  rank = 4;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = U_MTRX_PRS_RATE_SIZE;
  dim_sizes[2] = U_SPINPRS;
  dim_sizes[3] = U_SECTRS;
  if((sds_id_uleis_rate2 = SDcreate(sd_id, "URateSet_Matrx_prs", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_uleis_rate_error("init_cr_uleis_rate -> SDcreate: Couldn't create URateSet_Matrx_prs");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w2 = SDidtoref(sds_id_uleis_rate2)) == FAIL)
    print_uleis_rate_error("init_cr_uleis_rate -> SDidtoref: Couldn't get ref for URateSet_Matrx_prs");

  if((Vaddtagref(vgrp_id_uleis_rate, DFTAG_NDG, sds_ref_w2)) == FAIL)
    print_uleis_rate_error("init_cr_uleis_rate -> Vaddtagref: Couldn't add SDS URateSet_Matrx_prs to Vgrp");

  rank = 4;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = U_SNGL_RATE_SIZE;
  dim_sizes[2] = U_SPINPRS;
  dim_sizes[3] = U_SECTRS;
  if((sds_id_uleis_rate3 = SDcreate(sd_id, "URateSet_Single", DFNT_UINT16, rank, dim_sizes)) == FAIL)
    print_uleis_rate_error("init_cr_uleis_rate -> SDcreate: Couldn't create URateSet_Single");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w3 = SDidtoref(sds_id_uleis_rate3)) == FAIL)
    print_uleis_rate_error("init_cr_uleis_rate -> SDidtoref: Couldn't get ref for URateSet_Single");

  if((Vaddtagref(vgrp_id_uleis_rate, DFTAG_NDG, sds_ref_w3)) == FAIL)
    print_uleis_rate_error("init_cr_uleis_rate -> Vaddtagref: Couldn't add SDS URateSet_Single to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_uleis_rate(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_uleis_rate(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_uleis_rate(struct URateSet URateSet_struc, int32 recnum)
{
  int32 start[4], edges[4];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_uleis_rate_error();
void pack_uleis_rate();

  odata = (uint8 *) malloc(sizeof(struct URateSet));
  pack_uleis_rate(odata, &URateSet_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_uleis_rate, recnum)==-1) {
		print_uleis_rate_error("write_uleis_rate -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_uleis_rate, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_uleis_rate_error("write_uleis_rate -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  start[3] = 0;
  edges[0] = 1;

  edges[1] = U_MTRX_RATE_SIZE;
  edges[2] = U_SPINS;
  edges[3] = U_SECTRS;
  if (SDwritedata(sds_id_uleis_rate1,start,NULL,edges, (VOIDP)(URateSet_struc.Matrx)) ==FAIL)
    print_uleis_rate_error("write_uleis_rate -> SDwritedata: Problem writing Matrx data.");

  edges[1] = U_MTRX_PRS_RATE_SIZE;
  edges[2] = U_SPINPRS;
  edges[3] = U_SECTRS;
  if (SDwritedata(sds_id_uleis_rate2,start,NULL,edges, (VOIDP)(URateSet_struc.Matrx_prs)) ==FAIL)
    print_uleis_rate_error("write_uleis_rate -> SDwritedata: Problem writing Matrx_prs data.");

  edges[1] = U_SNGL_RATE_SIZE;
  edges[2] = U_SPINPRS;
  edges[3] = U_SECTRS;
  if (SDwritedata(sds_id_uleis_rate3,start,NULL,edges, (VOIDP)(URateSet_struc.Single)) ==FAIL)
    print_uleis_rate_error("write_uleis_rate -> SDwritedata: Problem writing Single data.");

  memset(&URateSet_struc, 0, sizeof(struct URateSet));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_uleis_rate()
{
  VSdetach(vdata_id_uleis_rate);
  Vdetach(vgrp_id_uleis_rate);
  SDendaccess(sds_id_uleis_rate1);
  SDendaccess(sds_id_uleis_rate2);
  SDendaccess(sds_id_uleis_rate3);
}

/*----     init access function    ----*/

int32 init_acc_uleis_rate(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  static int32 sds_index2;
  static int32 sds_index3;
  int32 vdata_ref;
  int32 num_rec;

  void print_uleis_rate_error();

  if((sds_index1=SDnametoindex(sd_id, "URateSet_Matrx" )) ==FAIL) {
      print_uleis_rate_error("init_acc_uleis_rate -> SDnametoindex: Couldn't find URateSet_Matrx");
      return(-1);
  }
  if((sds_id_uleis_rate1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_uleis_rate_error("init_acc_uleis_rate -> SDselect: Couldn't select sds_index1");
      return(-1);
  }
  if((sds_index2=SDnametoindex(sd_id, "URateSet_Matrx_prs" )) ==FAIL) {
      print_uleis_rate_error("init_acc_uleis_rate -> SDnametoindex: Couldn't find URateSet_Matrx_prs");
      return(-1);
  }
  if((sds_id_uleis_rate2=SDselect(sd_id, sds_index2)) ==FAIL) {
      print_uleis_rate_error("init_acc_uleis_rate -> SDselect: Couldn't select sds_index2");
      return(-1);
  }
  if((sds_index3=SDnametoindex(sd_id, "URateSet_Single" )) ==FAIL) {
      print_uleis_rate_error("init_acc_uleis_rate -> SDnametoindex: Couldn't find URateSet_Single");
      return(-1);
  }
  if((sds_id_uleis_rate3=SDselect(sd_id, sds_index3)) ==FAIL) {
      print_uleis_rate_error("init_acc_uleis_rate -> SDselect: Couldn't select sds_index3");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "URateSet")) <= 0 ) {
    print_uleis_rate_error("init_acc_uleis_rate -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_uleis_rate = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_uleis_rate_error("init_acc_uleis_rate -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_uleis_rate, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_uleis_rate,"output_sctime, collect_sctime, QAC")) {
      print_uleis_rate_error("init_acc_uleis_rate -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_uleis_rate(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_uleis_rate(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_uleis_rate(struct URateSet *URateSet_struc, int32 recnum_rd)
{
int32 start[4], edges[4];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_uleis_rate_error();
void unpack_uleis_rate();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;
  start[3] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct URateSet));
  VSinquire(vdata_id_uleis_rate, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_uleis_rate, recnum_rd)==FAIL) {
          print_uleis_rate_error("read_uleis_rate -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = U_MTRX_RATE_SIZE;
  edges[2] = U_SPINS;
  edges[3] = U_SECTRS;

  if(SDreaddata(sds_id_uleis_rate1,start,NULL,edges, (VOIDP)(URateSet_struc->Matrx )) ==FAIL) {
    print_uleis_rate_error("read_uleis_rate -> SDreaddata: Couldn't read Matrx");
    retval = -1;
  }
  edges[1] = U_MTRX_PRS_RATE_SIZE;
  edges[2] = U_SPINPRS;
  edges[3] = U_SECTRS;

  if(SDreaddata(sds_id_uleis_rate2,start,NULL,edges, (VOIDP)(URateSet_struc->Matrx_prs )) ==FAIL) {
    print_uleis_rate_error("read_uleis_rate -> SDreaddata: Couldn't read Matrx_prs");
    retval = -1;
  }
  edges[1] = U_SNGL_RATE_SIZE;
  edges[2] = U_SPINPRS;
  edges[3] = U_SECTRS;

  if(SDreaddata(sds_id_uleis_rate3,start,NULL,edges, (VOIDP)(URateSet_struc->Single )) ==FAIL) {
    print_uleis_rate_error("read_uleis_rate -> SDreaddata: Couldn't read Single");
    retval = -1;
  }
  if(VSread(vdata_id_uleis_rate, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_uleis_rate_error("read_uleis_rate -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_uleis_rate(odata, URateSet_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_uleis_rate()
{
  VSdetach(vdata_id_uleis_rate);
  SDendaccess(sds_id_uleis_rate1);
  SDendaccess(sds_id_uleis_rate2);
  SDendaccess(sds_id_uleis_rate3);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_uleis_rate(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_uleis_rate_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_URateSet" )) ==FAIL)
    print_uleis_rate_error("rd_Vgrp_uleis_rate -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_uleis_rate_error("rd_Vgrp_uleis_rate -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_uleis_rate_error("rd_Vgrp_uleis_rate -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_uleis_rate_error("rd_Vgrp_uleis_rate -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_URateSet, HDstrlen(Vgrp_descrp_URateSet)) ==FAIL)
    print_uleis_rate_error("rd_Vgrp_uleis_rate -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_URateSet);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_uleis_rate_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_uleis_rate.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_uleis_rate(uint8 *data, struct URateSet *URateSet_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &URateSet_ptr->output_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &URateSet_ptr->collect_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &URateSet_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_uleis_rate(uint8 *data, struct URateSet *URateSet_ptr)
{
int32 ptr=0;

   memcpy(&URateSet_ptr->output_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&URateSet_ptr->collect_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&URateSet_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_uleis_rate() {return(vgrp_id_uleis_rate);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_uleis_rate(char *wr_strval)
{
  strcpy(wr_strval, "The file 'uleis_rate.h' is shown below, it was used to create the data in the Vgroup named 'VG_URateSet'.\n\n");
  strcat(wr_strval,"/* Id: uleis_rate.h,v 1.5 1997/04/10 22:19:24 steves Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define U_SPINS               10 	/* 10 spins, 1-10 */\n");
  strcat(wr_strval,"#define U_SPINPRS              5	/* 5 spin pairs 1-5 */\n");
  strcat(wr_strval,"#define U_SECTRS               8	/* 8 sectors, 0-7 */\n");
  strcat(wr_strval,"#define U_MTRX_RATE_SIZE      34	/* 34 bytes per sector */\n");
  strcat(wr_strval,"#define U_MTRX_PRS_RATE_SIZE  42	/* 42 bytes per sector */\n");
  strcat(wr_strval,"#define U_SNGL_RATE_SIZE      16        /* 16 2-byte items per sector */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct URateSet\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 output_sctime;		/* time for beginning of data output cycle */\n");
  strcat(wr_strval,"  uint32 collect_sctime;	/* time for beginning of data collection */\n");
  strcat(wr_strval,"  uint32 QAC;			/* number of bad frames in this cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* Matrix rates: 34 bytes, 10 spins, 8 sectors */\n");
  strcat(wr_strval,"  uint8 Matrx[U_MTRX_RATE_SIZE][U_SPINS][U_SECTRS];\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* Matrix pair rates: 42 bytes, 5 spin pairs, 8 sectors */\n");
  strcat(wr_strval,"  uint8 Matrx_prs[U_MTRX_PRS_RATE_SIZE][U_SPINPRS][U_SECTRS];\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* Singles rates:  32 bytes, 5 spin pairs, 8 sectors */\n");
  strcat(wr_strval,"  uint16 Single[U_SNGL_RATE_SIZE][U_SPINPRS][U_SECTRS];\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  return(0);
}
