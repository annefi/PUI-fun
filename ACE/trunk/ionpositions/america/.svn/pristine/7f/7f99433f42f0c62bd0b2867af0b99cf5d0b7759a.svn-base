/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: swepam_dhskpe.h,v 1.1 1997/06/20 17:58:55 jeff Exp  */

#include "swepam_dhskpe.h"
#include "df.h"

int32 vgrp_id_swepam_dhskpe;
static int32 vdata_id_swepam_dhskpe;

  /* 1373 is the size of swepam_dhskpe.h + 1 added line */
char Vgrp_descrp_DHSKPE[1373];

/****----  init create function  ----****/

int32 init_cr_swepam_dhskpe(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_swepam_dhskpe();

  void print_swepam_dhskpe_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_swepam_dhskpe = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_swepam_dhskpe, "VG_DHSKPE"); 
  Vsetclass(vgrp_id_swepam_dhskpe, "VG_SWEPAM_DHSKPE");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_DHSKPE" )) ==FAIL) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_swepam_dhskpe(Vgrp_descrp_DHSKPE);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_DHSKPE, sizeof(Vgrp_descrp_DHSKPE))) ==FAIL) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_swepam_dhskpe = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_swepam_dhskpe, "DHSKPE");
  VSsetclass(vdata_id_swepam_dhskpe, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_swepam_dhskpe, vdata_id_swepam_dhskpe)) ==FAIL) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_swepam_dhskpe, "output_sctime", DFNT_UINT32, (1) )) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSfdefine: Couldn't define output_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpe, "collect_sctime", DFNT_UINT32, (1) )) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSfdefine: Couldn't define collect_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpe, "QAC", DFNT_UINT8, (1) )) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpe, "SCid", DFNT_UINT8, (8) )) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSfdefine: Couldn't define SCid");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpe, "FmtFC", DFNT_UINT8, (8) )) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSfdefine: Couldn't define FmtFC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpe, "FmtID", DFNT_UINT8, (8) )) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSfdefine: Couldn't define FmtID");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpe, "EF", DFNT_UINT8, (8) )) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSfdefine: Couldn't define EF");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpe, "CS", DFNT_UINT16, (8) )) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSfdefine: Couldn't define CS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpe, "DB", DFNT_UINT8, (8) )) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSfdefine: Couldn't define DB");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpe, "HVMON1", DFNT_UINT8, (8) )) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSfdefine: Couldn't define HVMON1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpe, "HVMON2", DFNT_UINT8, (8) )) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSfdefine: Couldn't define HVMON2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpe, "PSMON", DFNT_UINT8, (8) )) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSfdefine: Couldn't define PSMON");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpe, "TMon", DFNT_UINT8, (8) )) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSfdefine: Couldn't define TMon");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpe, "IMon", DFNT_UINT8, (8) )) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSfdefine: Couldn't define IMon");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpe, "IFTMon", DFNT_UINT8, (8) )) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSfdefine: Couldn't define IFTMon");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpe, "MainBusV", DFNT_UINT8, (8) )) {
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSfdefine: Couldn't define MainBusV");
    retval = -1;
  }

  if (VSsetfields(vdata_id_swepam_dhskpe,"output_sctime, collect_sctime, QAC, SCid, FmtFC, FmtID, EF, CS, DB, HVMON1, HVMON2, PSMON, TMon, IMon, IFTMon, MainBusV")){
    print_swepam_dhskpe_error("init_cr_swepam_dhskpe -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_swepam_dhskpe(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_swepam_dhskpe(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_swepam_dhskpe(struct DHSKPE DHSKPE_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_swepam_dhskpe_error();
void pack_swepam_dhskpe();

  odata = (uint8 *) malloc(sizeof(struct DHSKPE));
  pack_swepam_dhskpe(odata, &DHSKPE_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_swepam_dhskpe, recnum)==-1) {
		print_swepam_dhskpe_error("write_swepam_dhskpe -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_swepam_dhskpe, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_swepam_dhskpe_error("write_swepam_dhskpe -> VSwrite: Couldn't write data.");

  memset(&DHSKPE_struc, 0, sizeof(struct DHSKPE));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_swepam_dhskpe()
{
  VSdetach(vdata_id_swepam_dhskpe);
  Vdetach(vgrp_id_swepam_dhskpe);
}

/*----     init access function    ----*/

int32 init_acc_swepam_dhskpe(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_swepam_dhskpe_error();


  if ((vdata_ref = VSfind(hdf_fp, "DHSKPE")) <= 0 ) {
    print_swepam_dhskpe_error("init_acc_swepam_dhskpe -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_swepam_dhskpe = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_swepam_dhskpe_error("init_acc_swepam_dhskpe -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_swepam_dhskpe, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_swepam_dhskpe,"output_sctime, collect_sctime, QAC, SCid, FmtFC, FmtID, EF, CS, DB, HVMON1, HVMON2, PSMON, TMon, IMon, IFTMon, MainBusV")) {
      print_swepam_dhskpe_error("init_acc_swepam_dhskpe -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_swepam_dhskpe(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_swepam_dhskpe(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_swepam_dhskpe(struct DHSKPE *DHSKPE_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_swepam_dhskpe_error();
void unpack_swepam_dhskpe();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct DHSKPE));
  VSinquire(vdata_id_swepam_dhskpe, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_swepam_dhskpe, recnum_rd)==FAIL) {
          print_swepam_dhskpe_error("read_swepam_dhskpe -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_swepam_dhskpe, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_swepam_dhskpe_error("read_swepam_dhskpe -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_swepam_dhskpe(odata, DHSKPE_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_swepam_dhskpe()
{
  VSdetach(vdata_id_swepam_dhskpe);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_swepam_dhskpe(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_swepam_dhskpe_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_DHSKPE" )) ==FAIL)
    print_swepam_dhskpe_error("rd_Vgrp_swepam_dhskpe -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_swepam_dhskpe_error("rd_Vgrp_swepam_dhskpe -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_swepam_dhskpe_error("rd_Vgrp_swepam_dhskpe -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_swepam_dhskpe_error("rd_Vgrp_swepam_dhskpe -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_DHSKPE, HDstrlen(Vgrp_descrp_DHSKPE)) ==FAIL)
    print_swepam_dhskpe_error("rd_Vgrp_swepam_dhskpe -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_DHSKPE);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_swepam_dhskpe_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swepam_dhskpe.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_swepam_dhskpe(uint8 *data, struct DHSKPE *DHSKPE_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &DHSKPE_ptr->output_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &DHSKPE_ptr->collect_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &DHSKPE_ptr->QAC, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DHSKPE_ptr->SCid[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPE_ptr->FmtFC[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPE_ptr->FmtID[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPE_ptr->EF[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPE_ptr->CS[0], ((2)*(8)) );
   ptr+= ((2)*(8));
   memcpy(data+ptr, &DHSKPE_ptr->DB[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPE_ptr->HVMON1[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPE_ptr->HVMON2[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPE_ptr->PSMON[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPE_ptr->TMon[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPE_ptr->IMon[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPE_ptr->IFTMon[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPE_ptr->MainBusV[0], ((1)*(8)) );
   ptr+= ((1)*(8));
}

/*----   unpack function    ----*/

void unpack_swepam_dhskpe(uint8 *data, struct DHSKPE *DHSKPE_ptr)
{
int32 ptr=0;

   memcpy(&DHSKPE_ptr->output_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&DHSKPE_ptr->collect_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&DHSKPE_ptr->QAC, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DHSKPE_ptr->SCid[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPE_ptr->FmtFC[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPE_ptr->FmtID[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPE_ptr->EF[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPE_ptr->CS[0], data+ptr,  ((2)*(8)) );
   ptr+= ((2)*(8));
   memcpy(&DHSKPE_ptr->DB[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPE_ptr->HVMON1[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPE_ptr->HVMON2[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPE_ptr->PSMON[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPE_ptr->TMon[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPE_ptr->IMon[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPE_ptr->IFTMon[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPE_ptr->MainBusV[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
}
int32 get_vgrp_id_swepam_dhskpe() {return(vgrp_id_swepam_dhskpe);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_swepam_dhskpe(char *wr_strval)
{
  strcpy(wr_strval, "The file 'swepam_dhskpe.h' is shown below, it was used to create the data in the Vgroup named 'VG_DHSKPE'.\n\n");
  strcat(wr_strval,"/* Id: swepam_dhskpe.h,v 1.1 1997/06/20 17:58:55 jeff Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct DHSKPE               /* Swepam-E Housekeeping  */\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 output_sctime;   /* time for beginning of data output cycle */\n");
  strcat(wr_strval,"  uint32 collect_sctime;  /* time for beginning of data collection */\n");
  strcat(wr_strval,"  uint8  QAC;             /* number of bad frames in this cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* Major Frame Header */\n");
  strcat(wr_strval,"  uint8  SCid[8];         /* SubCom ID */\n");
  strcat(wr_strval,"  uint8  FmtFC[8];        /* Frame Format Count */\n");
  strcat(wr_strval,"  uint8  FmtID[8];        /* Format ID */\n");
  strcat(wr_strval,"  uint8  EF[8];           /* Event Flag */\n");
  strcat(wr_strval,"  uint16 CS[8];           /* subcom Configuration Status */\n");
  strcat(wr_strval,"  uint8  DB[8];           /* DataBase paramter */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* subcom analog monitors - one complete cycle per 8 major frames in SCA Normal mode */\n");
  strcat(wr_strval,"  uint8  HVMON1[8];   /* Subcom ananlog high voltage power monitor */\n");
  strcat(wr_strval,"  uint8  HVMON2[8];   /* Subcom ananlog high voltage power monitor */\n");
  strcat(wr_strval,"  uint8  PSMON[8];    /* Subcom ananlog low voltage power monitor */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint8  TMon[8];     /* Internal temp monitor */\n");
  strcat(wr_strval,"  uint8  IMon[8];     /* 28v return Curr Mon */\n");
  strcat(wr_strval,"  uint8  IFTMon[8];   /* Interface temp monitor */\n");
  strcat(wr_strval,"  uint8  MainBusV[8]; /* Main Bus voltage monitor */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
