/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: swepam_dstea.h,v 1.1 1997/06/20 18:05:42 jeff Exp  */

#include "swepam_dstea.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_swepam_dstea;
static int32 vdata_id_swepam_dstea;

static int32 sds_id_swepam_dstea1;

  /* 1430 is the size of swepam_dstea.h + 1 added line */
char Vgrp_descrp_DSTEA[1430];

/****----  init create function  ----****/

int32 init_cr_swepam_dstea(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[5];
  int32 rank;

  int32 wr_Vgrp_desc_swepam_dstea();

  void print_swepam_dstea_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_swepam_dstea = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_swepam_dstea_error("init_cr_swepam_dstea -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_swepam_dstea, "VG_DSTEA"); 
  Vsetclass(vgrp_id_swepam_dstea, "VG_SWEPAM_DSTEA");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_DSTEA" )) ==FAIL) {
    print_swepam_dstea_error("init_cr_swepam_dstea -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_swepam_dstea(Vgrp_descrp_DSTEA);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_swepam_dstea_error("init_cr_swepam_dstea -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_DSTEA, sizeof(Vgrp_descrp_DSTEA))) ==FAIL) {
    print_swepam_dstea_error("init_cr_swepam_dstea -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_swepam_dstea = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_swepam_dstea_error("init_cr_swepam_dstea -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_swepam_dstea, "DSTEA");
  VSsetclass(vdata_id_swepam_dstea, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_swepam_dstea, vdata_id_swepam_dstea)) ==FAIL) {
    print_swepam_dstea_error("init_cr_swepam_dstea -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_swepam_dstea, "output_sctime", DFNT_UINT32, (1) )) {
    print_swepam_dstea_error("init_cr_swepam_dstea -> VSfdefine: Couldn't define output_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dstea, "collect_sctime", DFNT_UINT32, (1) )) {
    print_swepam_dstea_error("init_cr_swepam_dstea -> VSfdefine: Couldn't define collect_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dstea, "QAC", DFNT_UINT8, (1) )) {
    print_swepam_dstea_error("init_cr_swepam_dstea -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dstea, "PhiLim", DFNT_UINT8, (1) )) {
    print_swepam_dstea_error("init_cr_swepam_dstea -> VSfdefine: Couldn't define PhiLim");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dstea, "DQAlarm", DFNT_UINT8, (1) )) {
    print_swepam_dstea_error("init_cr_swepam_dstea -> VSfdefine: Couldn't define DQAlarm");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dstea, "CEMLev", DFNT_UINT8, (1) )) {
    print_swepam_dstea_error("init_cr_swepam_dstea -> VSfdefine: Couldn't define CEMLev");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dstea, "Lmx", DFNT_UINT8, (1) )) {
    print_swepam_dstea_error("init_cr_swepam_dstea -> VSfdefine: Couldn't define Lmx");
    retval = -1;
  }

  if (VSsetfields(vdata_id_swepam_dstea,"output_sctime, collect_sctime, QAC, PhiLim, DQAlarm, CEMLev, Lmx")){
    print_swepam_dstea_error("init_cr_swepam_dstea -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 5;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = SWEPAM_DSTEA_specseg;
  dim_sizes[2] = SWEPAM_DSTEA_phi;
  dim_sizes[3] = SWEPAM_DSTEA_energy;
  dim_sizes[4] = SWEPAM_DSTEA_otheta;
  if((sds_id_swepam_dstea1 = SDcreate(sd_id, "DSTEA_COUNT", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_swepam_dstea_error("init_cr_swepam_dstea -> SDcreate: Couldn't create DSTEA_COUNT");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_swepam_dstea1)) == FAIL)
    print_swepam_dstea_error("init_cr_swepam_dstea -> SDidtoref: Couldn't get ref for DSTEA_COUNT");

  if((Vaddtagref(vgrp_id_swepam_dstea, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_swepam_dstea_error("init_cr_swepam_dstea -> Vaddtagref: Couldn't add SDS DSTEA_COUNT to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_swepam_dstea(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_swepam_dstea(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_swepam_dstea(struct DSTEA DSTEA_struc, int32 recnum)
{
  int32 start[5], edges[5];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_swepam_dstea_error();
void pack_swepam_dstea();

  odata = (uint8 *) malloc(sizeof(struct DSTEA));
  pack_swepam_dstea(odata, &DSTEA_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_swepam_dstea, recnum)==-1) {
		print_swepam_dstea_error("write_swepam_dstea -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_swepam_dstea, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_swepam_dstea_error("write_swepam_dstea -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  start[3] = 0;
  start[4] = 0;
  edges[0] = 1;

  edges[1] = SWEPAM_DSTEA_specseg;
  edges[2] = SWEPAM_DSTEA_phi;
  edges[3] = SWEPAM_DSTEA_energy;
  edges[4] = SWEPAM_DSTEA_otheta;
  if (SDwritedata(sds_id_swepam_dstea1,start,NULL,edges, (VOIDP)(DSTEA_struc.COUNT)) ==FAIL)
    print_swepam_dstea_error("write_swepam_dstea -> SDwritedata: Problem writing COUNT data.");

  memset(&DSTEA_struc, 0, sizeof(struct DSTEA));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_swepam_dstea()
{
  VSdetach(vdata_id_swepam_dstea);
  Vdetach(vgrp_id_swepam_dstea);
  SDendaccess(sds_id_swepam_dstea1);
}

/*----     init access function    ----*/

int32 init_acc_swepam_dstea(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_swepam_dstea_error();

  if((sds_index1=SDnametoindex(sd_id, "DSTEA_COUNT" )) ==FAIL) {
      print_swepam_dstea_error("init_acc_swepam_dstea -> SDnametoindex: Couldn't find DSTEA_COUNT");
      return(-1);
  }
  if((sds_id_swepam_dstea1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_swepam_dstea_error("init_acc_swepam_dstea -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "DSTEA")) <= 0 ) {
    print_swepam_dstea_error("init_acc_swepam_dstea -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_swepam_dstea = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_swepam_dstea_error("init_acc_swepam_dstea -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_swepam_dstea, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_swepam_dstea,"output_sctime, collect_sctime, QAC, PhiLim, DQAlarm, CEMLev, Lmx")) {
      print_swepam_dstea_error("init_acc_swepam_dstea -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_swepam_dstea(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_swepam_dstea(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_swepam_dstea(struct DSTEA *DSTEA_struc, int32 recnum_rd)
{
int32 start[5], edges[5];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_swepam_dstea_error();
void unpack_swepam_dstea();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;
  start[3] = 0;
  start[4] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct DSTEA));
  VSinquire(vdata_id_swepam_dstea, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_swepam_dstea, recnum_rd)==FAIL) {
          print_swepam_dstea_error("read_swepam_dstea -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = SWEPAM_DSTEA_specseg;
  edges[2] = SWEPAM_DSTEA_phi;
  edges[3] = SWEPAM_DSTEA_energy;
  edges[4] = SWEPAM_DSTEA_otheta;

  if(SDreaddata(sds_id_swepam_dstea1,start,NULL,edges, (VOIDP)(DSTEA_struc->COUNT )) ==FAIL) {
    print_swepam_dstea_error("read_swepam_dstea -> SDreaddata: Couldn't read COUNT");
    retval = -1;
  }
  if(VSread(vdata_id_swepam_dstea, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_swepam_dstea_error("read_swepam_dstea -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_swepam_dstea(odata, DSTEA_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_swepam_dstea()
{
  VSdetach(vdata_id_swepam_dstea);
  SDendaccess(sds_id_swepam_dstea1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_swepam_dstea(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_swepam_dstea_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_DSTEA" )) ==FAIL)
    print_swepam_dstea_error("rd_Vgrp_swepam_dstea -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_swepam_dstea_error("rd_Vgrp_swepam_dstea -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_swepam_dstea_error("rd_Vgrp_swepam_dstea -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_swepam_dstea_error("rd_Vgrp_swepam_dstea -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_DSTEA, HDstrlen(Vgrp_descrp_DSTEA)) ==FAIL)
    print_swepam_dstea_error("rd_Vgrp_swepam_dstea -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_DSTEA);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_swepam_dstea_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swepam_dstea.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_swepam_dstea(uint8 *data, struct DSTEA *DSTEA_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &DSTEA_ptr->output_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &DSTEA_ptr->collect_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &DSTEA_ptr->QAC, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DSTEA_ptr->PhiLim, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DSTEA_ptr->DQAlarm, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DSTEA_ptr->CEMLev, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DSTEA_ptr->Lmx, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_swepam_dstea(uint8 *data, struct DSTEA *DSTEA_ptr)
{
int32 ptr=0;

   memcpy(&DSTEA_ptr->output_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&DSTEA_ptr->collect_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&DSTEA_ptr->QAC, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DSTEA_ptr->PhiLim, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DSTEA_ptr->DQAlarm, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DSTEA_ptr->CEMLev, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DSTEA_ptr->Lmx, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_swepam_dstea() {return(vgrp_id_swepam_dstea);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_swepam_dstea(char *wr_strval)
{
  strcpy(wr_strval, "The file 'swepam_dstea.h' is shown below, it was used to create the data in the Vgroup named 'VG_DSTEA'.\n\n");
  strcat(wr_strval,"/* Id: swepam_dstea.h,v 1.1 1997/06/20 18:05:42 jeff Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define SWEPAM_DSTEA_specseg  5  /* spectral segment index, approx = spins */\n");
  strcat(wr_strval,"#define SWEPAM_DSTEA_phi     60  /* \"Spin\" sector index */\n");
  strcat(wr_strval,"#define SWEPAM_DSTEA_energy   2  /* Energy sample index withn a spin sector */\n");
  strcat(wr_strval,"#define SWEPAM_DSTEA_otheta   7  /* Polar angle indx.oddphi.0=CEM1,..,6=CEM7*/\n");
  strcat(wr_strval,"#define SWEPAM_DSTEA_etheta   5  /* Polar angle indx.evenphi.0=CEM1,..,6=CEM7*/\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct DSTEA   /* swepam-e data set from Supra thermal angle scan mode */\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 output_sctime;   /* time for beginning of data output cycle */\n");
  strcat(wr_strval,"  uint32 collect_sctime;  /* time for beginning of data collection */\n");
  strcat(wr_strval,"  uint8  QAC;             /* number of bad frames in this cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* Data set header- Philim and Lmx not used in DSTEA mode */\n");
  strcat(wr_strval,"  uint8 PhiLim;   /* Decompressed phil limit. (55-61) */\n");
  strcat(wr_strval,"  uint8 DQAlarm;  /* Data Quality alarm. 0/1 = OK/suspect data */\n");
  strcat(wr_strval,"  uint8 CEMLev;   /* CEM bias level. 0-15 */\n");
  strcat(wr_strval,"  uint8 Lmx;      /* set to 255=invalid*/\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* count array - compressed count \"pixels\" */\n");
  strcat(wr_strval,"  /* even phi values have 0 fill in elements 0&6 (CEM1&CEM7) */\n");
  strcat(wr_strval,"  uint8 COUNT[SWEPAM_DSTEA_specseg][SWEPAM_DSTEA_phi][SWEPAM_DSTEA_energy][SWEPAM_DSTEA_otheta];\n");
  strcat(wr_strval,"};\n");
  return(0);
}
