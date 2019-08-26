/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: swepam_dnswe.h,v 1.1 1997/06/20 18:01:44 jeff Exp  */

#include "swepam_dnswe.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_swepam_dnswe;
static int32 vdata_id_swepam_dnswe;

static int32 sds_id_swepam_dnswe1;

  /* 1473 is the size of swepam_dnswe.h + 1 added line */
char Vgrp_descrp_DNSWE[1473];

/****----  init create function  ----****/

int32 init_cr_swepam_dnswe(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[5];
  int32 rank;

  int32 wr_Vgrp_desc_swepam_dnswe();

  void print_swepam_dnswe_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_swepam_dnswe = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_swepam_dnswe_error("init_cr_swepam_dnswe -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_swepam_dnswe, "VG_DNSWE"); 
  Vsetclass(vgrp_id_swepam_dnswe, "VG_SWEPAM_DNSWE");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_DNSWE" )) ==FAIL) {
    print_swepam_dnswe_error("init_cr_swepam_dnswe -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_swepam_dnswe(Vgrp_descrp_DNSWE);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_swepam_dnswe_error("init_cr_swepam_dnswe -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_DNSWE, sizeof(Vgrp_descrp_DNSWE))) ==FAIL) {
    print_swepam_dnswe_error("init_cr_swepam_dnswe -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_swepam_dnswe = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_swepam_dnswe_error("init_cr_swepam_dnswe -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_swepam_dnswe, "DNSWE");
  VSsetclass(vdata_id_swepam_dnswe, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_swepam_dnswe, vdata_id_swepam_dnswe)) ==FAIL) {
    print_swepam_dnswe_error("init_cr_swepam_dnswe -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_swepam_dnswe, "output_sctime", DFNT_UINT32, (1) )) {
    print_swepam_dnswe_error("init_cr_swepam_dnswe -> VSfdefine: Couldn't define output_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dnswe, "collect_sctime", DFNT_UINT32, (1) )) {
    print_swepam_dnswe_error("init_cr_swepam_dnswe -> VSfdefine: Couldn't define collect_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dnswe, "QAC", DFNT_UINT8, (1) )) {
    print_swepam_dnswe_error("init_cr_swepam_dnswe -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dnswe, "PhiLim", DFNT_UINT8, (1) )) {
    print_swepam_dnswe_error("init_cr_swepam_dnswe -> VSfdefine: Couldn't define PhiLim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dnswe, "DQAlarm", DFNT_UINT8, (1) )) {
    print_swepam_dnswe_error("init_cr_swepam_dnswe -> VSfdefine: Couldn't define DQAlarm");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dnswe, "CEMLev", DFNT_UINT8, (1) )) {
    print_swepam_dnswe_error("init_cr_swepam_dnswe -> VSfdefine: Couldn't define CEMLev");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dnswe, "Lmx", DFNT_UINT8, (1) )) {
    print_swepam_dnswe_error("init_cr_swepam_dnswe -> VSfdefine: Couldn't define Lmx");
    retval = -1;
  }

  if (VSsetfields(vdata_id_swepam_dnswe,"output_sctime, collect_sctime, QAC, PhiLim, DQAlarm, CEMLev, Lmx")){
    print_swepam_dnswe_error("init_cr_swepam_dnswe -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 5;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = SWEPAM_DNSWE_specseg;
  dim_sizes[2] = SWEPAM_DNSWE_phi;
  dim_sizes[3] = SWEPAM_DNSWE_energy;
  dim_sizes[4] = SWEPAM_DNSWE_otheta;
  if((sds_id_swepam_dnswe1 = SDcreate(sd_id, "DNSWE_COUNT", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_swepam_dnswe_error("init_cr_swepam_dnswe -> SDcreate: Couldn't create DNSWE_COUNT");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_swepam_dnswe1)) == FAIL)
    print_swepam_dnswe_error("init_cr_swepam_dnswe -> SDidtoref: Couldn't get ref for DNSWE_COUNT");

  if((Vaddtagref(vgrp_id_swepam_dnswe, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_swepam_dnswe_error("init_cr_swepam_dnswe -> Vaddtagref: Couldn't add SDS DNSWE_COUNT to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_swepam_dnswe(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_swepam_dnswe(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_swepam_dnswe(struct DNSWE DNSWE_struc, int32 recnum)
{
  int32 start[5], edges[5];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_swepam_dnswe_error();
void pack_swepam_dnswe();

  odata = (uint8 *) malloc(sizeof(struct DNSWE));
  pack_swepam_dnswe(odata, &DNSWE_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_swepam_dnswe, recnum)==-1) {
		print_swepam_dnswe_error("write_swepam_dnswe -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_swepam_dnswe, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_swepam_dnswe_error("write_swepam_dnswe -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  start[3] = 0;
  start[4] = 0;
  edges[0] = 1;

  edges[1] = SWEPAM_DNSWE_specseg;
  edges[2] = SWEPAM_DNSWE_phi;
  edges[3] = SWEPAM_DNSWE_energy;
  edges[4] = SWEPAM_DNSWE_otheta;
  if (SDwritedata(sds_id_swepam_dnswe1,start,NULL,edges, (VOIDP)(DNSWE_struc.COUNT)) ==FAIL)
    print_swepam_dnswe_error("write_swepam_dnswe -> SDwritedata: Problem writing COUNT data.");

  memset(&DNSWE_struc, 0, sizeof(struct DNSWE));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_swepam_dnswe()
{
  VSdetach(vdata_id_swepam_dnswe);
  Vdetach(vgrp_id_swepam_dnswe);
  SDendaccess(sds_id_swepam_dnswe1);
}

/*----     init access function    ----*/

int32 init_acc_swepam_dnswe(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_swepam_dnswe_error();

  if((sds_index1=SDnametoindex(sd_id, "DNSWE_COUNT" )) ==FAIL) {
      print_swepam_dnswe_error("init_acc_swepam_dnswe -> SDnametoindex: Couldn't find DNSWE_COUNT");
      return(-1);
  }
  if((sds_id_swepam_dnswe1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_swepam_dnswe_error("init_acc_swepam_dnswe -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "DNSWE")) <= 0 ) {
    print_swepam_dnswe_error("init_acc_swepam_dnswe -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_swepam_dnswe = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_swepam_dnswe_error("init_acc_swepam_dnswe -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_swepam_dnswe, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_swepam_dnswe,"output_sctime, collect_sctime, QAC, PhiLim, DQAlarm, CEMLev, Lmx")) {
      print_swepam_dnswe_error("init_acc_swepam_dnswe -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_swepam_dnswe(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_swepam_dnswe(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_swepam_dnswe(struct DNSWE *DNSWE_struc, int32 recnum_rd)
{
int32 start[5], edges[5];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_swepam_dnswe_error();
void unpack_swepam_dnswe();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;
  start[3] = 0;
  start[4] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct DNSWE));
  VSinquire(vdata_id_swepam_dnswe, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_swepam_dnswe, recnum_rd)==FAIL) {
          print_swepam_dnswe_error("read_swepam_dnswe -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = SWEPAM_DNSWE_specseg;
  edges[2] = SWEPAM_DNSWE_phi;
  edges[3] = SWEPAM_DNSWE_energy;
  edges[4] = SWEPAM_DNSWE_otheta;

  if(SDreaddata(sds_id_swepam_dnswe1,start,NULL,edges, (VOIDP)(DNSWE_struc->COUNT )) ==FAIL) {
    print_swepam_dnswe_error("read_swepam_dnswe -> SDreaddata: Couldn't read COUNT");
    retval = -1;
  }
  if(VSread(vdata_id_swepam_dnswe, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_swepam_dnswe_error("read_swepam_dnswe -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_swepam_dnswe(odata, DNSWE_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_swepam_dnswe()
{
  VSdetach(vdata_id_swepam_dnswe);
  SDendaccess(sds_id_swepam_dnswe1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_swepam_dnswe(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_swepam_dnswe_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_DNSWE" )) ==FAIL)
    print_swepam_dnswe_error("rd_Vgrp_swepam_dnswe -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_swepam_dnswe_error("rd_Vgrp_swepam_dnswe -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_swepam_dnswe_error("rd_Vgrp_swepam_dnswe -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_swepam_dnswe_error("rd_Vgrp_swepam_dnswe -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_DNSWE, HDstrlen(Vgrp_descrp_DNSWE)) ==FAIL)
    print_swepam_dnswe_error("rd_Vgrp_swepam_dnswe -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_DNSWE);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_swepam_dnswe_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swepam_dnswe.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_swepam_dnswe(uint8 *data, struct DNSWE *DNSWE_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &DNSWE_ptr->output_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &DNSWE_ptr->collect_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &DNSWE_ptr->QAC, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DNSWE_ptr->PhiLim, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DNSWE_ptr->DQAlarm, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DNSWE_ptr->CEMLev, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DNSWE_ptr->Lmx, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_swepam_dnswe(uint8 *data, struct DNSWE *DNSWE_ptr)
{
int32 ptr=0;

   memcpy(&DNSWE_ptr->output_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&DNSWE_ptr->collect_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&DNSWE_ptr->QAC, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DNSWE_ptr->PhiLim, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DNSWE_ptr->DQAlarm, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DNSWE_ptr->CEMLev, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DNSWE_ptr->Lmx, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_swepam_dnswe() {return(vgrp_id_swepam_dnswe);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_swepam_dnswe(char *wr_strval)
{
  strcpy(wr_strval, "The file 'swepam_dnswe.h' is shown below, it was used to create the data in the Vgroup named 'VG_DNSWE'.\n\n");
  strcat(wr_strval,"/* Id: swepam_dnswe.h,v 1.1 1997/06/20 18:01:44 jeff Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define SWEPAM_DNSWE_specseg  5 /*spectral seg index, approx = spins */\n");
  strcat(wr_strval,"#define SWEPAM_DNSWE_phi     30 /*\"Spin\" sector index */\n");
  strcat(wr_strval,"#define SWEPAM_DNSWE_energy   4 /*Energy sample index within a spin sector*/\n");
  strcat(wr_strval,"#define SWEPAM_DNSWE_otheta   7 /*Polar angle index.odd phi.0=CEM1, .. 6=CEM7*/\n");
  strcat(wr_strval,"#define SWEPAM_DNSWE_etheta   5 /*Polar angle index.evenphi.0=CEM1, .. 6=CEM7*/\n");
  strcat(wr_strval,"                                /* CEM1, CEM6 are zero filled in even mode */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct DNSWE\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 output_sctime;   /* time for beginning of data output cycle */\n");
  strcat(wr_strval,"  uint32 collect_sctime;  /* time for beginning of data collection */\n");
  strcat(wr_strval,"  uint8  QAC;              /* number of bad frames in this cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* Data set header - PhiLim & Lmx not used in DNSWE (or DPHE) mode*/\n");
  strcat(wr_strval,"  uint8 PhiLim;   /* Decompressed Philimit (55-61)*/\n");
  strcat(wr_strval,"  uint8 DQAlarm;  /* Data Quality alarm. 0/1 = OK/Suspect data */\n");
  strcat(wr_strval,"  uint8 CEMLev;   /* CEM bias level. 0-15 */\n");
  strcat(wr_strval,"  uint8 Lmx;      /* ESA lvl with max count rate.0-199.255=invalid*/\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* Count array - Compressed count \"pixels\" */\n");
  strcat(wr_strval,"  /* use otheta for theta index, zero fill missing even values */\n");
  strcat(wr_strval,"  uint8 COUNT[SWEPAM_DNSWE_specseg][SWEPAM_DNSWE_phi][SWEPAM_DNSWE_energy][SWEPAM_DNSWE_otheta]; \n");
  strcat(wr_strval,"};\n");
  return(0);
}
