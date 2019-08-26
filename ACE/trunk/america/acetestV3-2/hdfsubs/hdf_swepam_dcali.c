/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: swepam_dcali.h,v 1.1 1997/06/20 17:56:55 jeff Exp  */

#include "swepam_dcali.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_swepam_dcali;
static int32 vdata_id_swepam_dcali;

static int32 sds_id_swepam_dcali1;

  /* 1519 is the size of swepam_dcali.h + 1 added line */
char Vgrp_descrp_DCALI[1519];

/****----  init create function  ----****/

int32 init_cr_swepam_dcali(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[5];
  int32 rank;

  int32 wr_Vgrp_desc_swepam_dcali();

  void print_swepam_dcali_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_swepam_dcali = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_swepam_dcali_error("init_cr_swepam_dcali -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_swepam_dcali, "VG_DCALI"); 
  Vsetclass(vgrp_id_swepam_dcali, "VG_SWEPAM_DCALI");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_DCALI" )) ==FAIL) {
    print_swepam_dcali_error("init_cr_swepam_dcali -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_swepam_dcali(Vgrp_descrp_DCALI);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_swepam_dcali_error("init_cr_swepam_dcali -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_DCALI, sizeof(Vgrp_descrp_DCALI))) ==FAIL) {
    print_swepam_dcali_error("init_cr_swepam_dcali -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_swepam_dcali = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_swepam_dcali_error("init_cr_swepam_dcali -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_swepam_dcali, "DCALI");
  VSsetclass(vdata_id_swepam_dcali, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_swepam_dcali, vdata_id_swepam_dcali)) ==FAIL) {
    print_swepam_dcali_error("init_cr_swepam_dcali -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_swepam_dcali, "output_sctime", DFNT_UINT32, (1) )) {
    print_swepam_dcali_error("init_cr_swepam_dcali -> VSfdefine: Couldn't define output_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dcali, "collect_sctime", DFNT_UINT32, (1) )) {
    print_swepam_dcali_error("init_cr_swepam_dcali -> VSfdefine: Couldn't define collect_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dcali, "QAC", DFNT_UINT8, (1) )) {
    print_swepam_dcali_error("init_cr_swepam_dcali -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dcali, "PhiLim", DFNT_UINT8, (1) )) {
    print_swepam_dcali_error("init_cr_swepam_dcali -> VSfdefine: Couldn't define PhiLim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dcali, "DQAlarm", DFNT_UINT8, (1) )) {
    print_swepam_dcali_error("init_cr_swepam_dcali -> VSfdefine: Couldn't define DQAlarm");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dcali, "CEMLev", DFNT_UINT8, (1) )) {
    print_swepam_dcali_error("init_cr_swepam_dcali -> VSfdefine: Couldn't define CEMLev");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dcali, "Lmx", DFNT_UINT8, (1) )) {
    print_swepam_dcali_error("init_cr_swepam_dcali -> VSfdefine: Couldn't define Lmx");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dcali, "RLmxs", DFNT_UINT8, (5) )) {
    print_swepam_dcali_error("init_cr_swepam_dcali -> VSfdefine: Couldn't define RLmxs");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dcali, "DCLmxs", DFNT_UINT8, (5) )) {
    print_swepam_dcali_error("init_cr_swepam_dcali -> VSfdefine: Couldn't define DCLmxs");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dcali, "PhiLmxs", DFNT_UINT8, (5) )) {
    print_swepam_dcali_error("init_cr_swepam_dcali -> VSfdefine: Couldn't define PhiLmxs");
    retval = -1;
  }

  if (VSsetfields(vdata_id_swepam_dcali,"output_sctime, collect_sctime, QAC, PhiLim, DQAlarm, CEMLev, Lmx, RLmxs, DCLmxs, PhiLmxs")){
    print_swepam_dcali_error("init_cr_swepam_dcali -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 5;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = SWEPAM_DCALI_specseg;
  dim_sizes[2] = SWEPAM_DCALI_phi;
  dim_sizes[3] = SWEPAM_DCALI_discrim;
  dim_sizes[4] = SWEPAM_DCALI_theta;
  if((sds_id_swepam_dcali1 = SDcreate(sd_id, "DCALI_COUNT", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_swepam_dcali_error("init_cr_swepam_dcali -> SDcreate: Couldn't create DCALI_COUNT");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_swepam_dcali1)) == FAIL)
    print_swepam_dcali_error("init_cr_swepam_dcali -> SDidtoref: Couldn't get ref for DCALI_COUNT");

  if((Vaddtagref(vgrp_id_swepam_dcali, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_swepam_dcali_error("init_cr_swepam_dcali -> Vaddtagref: Couldn't add SDS DCALI_COUNT to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_swepam_dcali(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_swepam_dcali(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_swepam_dcali(struct DCALI DCALI_struc, int32 recnum)
{
  int32 start[5], edges[5];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_swepam_dcali_error();
void pack_swepam_dcali();

  odata = (uint8 *) malloc(sizeof(struct DCALI));
  pack_swepam_dcali(odata, &DCALI_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_swepam_dcali, recnum)==-1) {
		print_swepam_dcali_error("write_swepam_dcali -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_swepam_dcali, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_swepam_dcali_error("write_swepam_dcali -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  start[3] = 0;
  start[4] = 0;
  edges[0] = 1;

  edges[1] = SWEPAM_DCALI_specseg;
  edges[2] = SWEPAM_DCALI_phi;
  edges[3] = SWEPAM_DCALI_discrim;
  edges[4] = SWEPAM_DCALI_theta;
  if (SDwritedata(sds_id_swepam_dcali1,start,NULL,edges, (VOIDP)(DCALI_struc.COUNT)) ==FAIL)
    print_swepam_dcali_error("write_swepam_dcali -> SDwritedata: Problem writing COUNT data.");

  memset(&DCALI_struc, 0, sizeof(struct DCALI));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_swepam_dcali()
{
  VSdetach(vdata_id_swepam_dcali);
  Vdetach(vgrp_id_swepam_dcali);
  SDendaccess(sds_id_swepam_dcali1);
}

/*----     init access function    ----*/

int32 init_acc_swepam_dcali(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_swepam_dcali_error();

  if((sds_index1=SDnametoindex(sd_id, "DCALI_COUNT" )) ==FAIL) {
      print_swepam_dcali_error("init_acc_swepam_dcali -> SDnametoindex: Couldn't find DCALI_COUNT");
      return(-1);
  }
  if((sds_id_swepam_dcali1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_swepam_dcali_error("init_acc_swepam_dcali -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "DCALI")) <= 0 ) {
    print_swepam_dcali_error("init_acc_swepam_dcali -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_swepam_dcali = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_swepam_dcali_error("init_acc_swepam_dcali -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_swepam_dcali, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_swepam_dcali,"output_sctime, collect_sctime, QAC, PhiLim, DQAlarm, CEMLev, Lmx, RLmxs, DCLmxs, PhiLmxs")) {
      print_swepam_dcali_error("init_acc_swepam_dcali -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_swepam_dcali(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_swepam_dcali(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_swepam_dcali(struct DCALI *DCALI_struc, int32 recnum_rd)
{
int32 start[5], edges[5];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_swepam_dcali_error();
void unpack_swepam_dcali();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;
  start[3] = 0;
  start[4] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct DCALI));
  VSinquire(vdata_id_swepam_dcali, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_swepam_dcali, recnum_rd)==FAIL) {
          print_swepam_dcali_error("read_swepam_dcali -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = SWEPAM_DCALI_specseg;
  edges[2] = SWEPAM_DCALI_phi;
  edges[3] = SWEPAM_DCALI_discrim;
  edges[4] = SWEPAM_DCALI_theta;

  if(SDreaddata(sds_id_swepam_dcali1,start,NULL,edges, (VOIDP)(DCALI_struc->COUNT )) ==FAIL) {
    print_swepam_dcali_error("read_swepam_dcali -> SDreaddata: Couldn't read COUNT");
    retval = -1;
  }
  if(VSread(vdata_id_swepam_dcali, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_swepam_dcali_error("read_swepam_dcali -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_swepam_dcali(odata, DCALI_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_swepam_dcali()
{
  VSdetach(vdata_id_swepam_dcali);
  SDendaccess(sds_id_swepam_dcali1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_swepam_dcali(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_swepam_dcali_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_DCALI" )) ==FAIL)
    print_swepam_dcali_error("rd_Vgrp_swepam_dcali -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_swepam_dcali_error("rd_Vgrp_swepam_dcali -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_swepam_dcali_error("rd_Vgrp_swepam_dcali -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_swepam_dcali_error("rd_Vgrp_swepam_dcali -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_DCALI, HDstrlen(Vgrp_descrp_DCALI)) ==FAIL)
    print_swepam_dcali_error("rd_Vgrp_swepam_dcali -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_DCALI);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_swepam_dcali_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swepam_dcali.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_swepam_dcali(uint8 *data, struct DCALI *DCALI_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &DCALI_ptr->output_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &DCALI_ptr->collect_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &DCALI_ptr->QAC, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DCALI_ptr->PhiLim, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DCALI_ptr->DQAlarm, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DCALI_ptr->CEMLev, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DCALI_ptr->Lmx, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DCALI_ptr->RLmxs[0], ((1)*(5)) );
   ptr+= ((1)*(5));
   memcpy(data+ptr, &DCALI_ptr->DCLmxs[0], ((1)*(5)) );
   ptr+= ((1)*(5));
   memcpy(data+ptr, &DCALI_ptr->PhiLmxs[0], ((1)*(5)) );
   ptr+= ((1)*(5));
}

/*----   unpack function    ----*/

void unpack_swepam_dcali(uint8 *data, struct DCALI *DCALI_ptr)
{
int32 ptr=0;

   memcpy(&DCALI_ptr->output_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&DCALI_ptr->collect_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&DCALI_ptr->QAC, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DCALI_ptr->PhiLim, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DCALI_ptr->DQAlarm, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DCALI_ptr->CEMLev, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DCALI_ptr->Lmx, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DCALI_ptr->RLmxs[0], data+ptr,  ((1)*(5)) );
   ptr+= ((1)*(5));
   memcpy(&DCALI_ptr->DCLmxs[0], data+ptr,  ((1)*(5)) );
   ptr+= ((1)*(5));
   memcpy(&DCALI_ptr->PhiLmxs[0], data+ptr,  ((1)*(5)) );
   ptr+= ((1)*(5));
}
int32 get_vgrp_id_swepam_dcali() {return(vgrp_id_swepam_dcali);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_swepam_dcali(char *wr_strval)
{
  strcpy(wr_strval, "The file 'swepam_dcali.h' is shown below, it was used to create the data in the Vgroup named 'VG_DCALI'.\n\n");
  strcat(wr_strval,"/* Id: swepam_dcali.h,v 1.1 1997/06/20 17:56:55 jeff Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define SWEPAM_DCALI_specseg 5 /* spectral segment index. approx=spins */\n");
  strcat(wr_strval,"#define SWEPAM_DCALI_phi    27 /* \"Spin\" sector index */\n");
  strcat(wr_strval,"#define SWEPAM_DCALI_discrim 2 /* Discrim thrshld index in spin sector */\n");
  strcat(wr_strval,"#define SWEPAM_DCALI_theta  16 /* Polar angle index.  0=CEM1,..,15=CEM16 */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct DCALI               /* CALI Data Mode */\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 output_sctime;   /* time for beginning of data output cycle */\n");
  strcat(wr_strval,"  uint32 collect_sctime;  /* time for beginning of data collection */\n");
  strcat(wr_strval,"  uint8  QAC;             /* number of bad frames in this cycle */\n");
  strcat(wr_strval,"  \n");
  strcat(wr_strval,"  /* Data set header */\n");
  strcat(wr_strval,"  uint8 PhiLim;       /* Decompressed phi limit (55-61) */\n");
  strcat(wr_strval,"  uint8 DQAlarm;      /* Data Quality alarm.  0/1=OK/data suspect */\n");
  strcat(wr_strval,"  uint8 CEMLev;       /* CEM bias level */\n");
  strcat(wr_strval,"  uint8 Lmx;          /* ESA lvl with max count rate in previous */\n");
  strcat(wr_strval,"		        /* SWI or SSTI mode.0-199.255=invalid*/\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* spectral segment headers, NOT USED BY DCALI, all should be 0 */\n");
  strcat(wr_strval,"  uint8 RLmxs[5];      /* Rel ESA lvl with max rate in Spec seg s */\n");
  strcat(wr_strval,"  uint8 DCLmxs[5];     /* Data Channel of Lmxs */\n");
  strcat(wr_strval,"  uint8 PhiLmxs[5];    /* Phi of Lmxs */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* Count array.  Compressed count \"pixels\" */\n");
  strcat(wr_strval,"  uint8 COUNT[SWEPAM_DCALI_specseg][SWEPAM_DCALI_phi][SWEPAM_DCALI_discrim][SWEPAM_DCALI_theta]; \n");
  strcat(wr_strval,"};\n");
  return(0);
}
