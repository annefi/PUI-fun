/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: swepam_dhskpi.h,v 1.1 1997/06/20 17:59:19 jeff Exp  */

#include "swepam_dhskpi.h"
#include "df.h"

int32 vgrp_id_swepam_dhskpi;
static int32 vdata_id_swepam_dhskpi;

  /* 1432 is the size of swepam_dhskpi.h + 1 added line */
char Vgrp_descrp_DHSKPI[1432];

/****----  init create function  ----****/

int32 init_cr_swepam_dhskpi(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_swepam_dhskpi();

  void print_swepam_dhskpi_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_swepam_dhskpi = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_swepam_dhskpi, "VG_DHSKPI"); 
  Vsetclass(vgrp_id_swepam_dhskpi, "VG_SWEPAM_DHSKPI");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_DHSKPI" )) ==FAIL) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_swepam_dhskpi(Vgrp_descrp_DHSKPI);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_DHSKPI, sizeof(Vgrp_descrp_DHSKPI))) ==FAIL) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_swepam_dhskpi = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_swepam_dhskpi, "DHSKPI");
  VSsetclass(vdata_id_swepam_dhskpi, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_swepam_dhskpi, vdata_id_swepam_dhskpi)) ==FAIL) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_swepam_dhskpi, "output_sctime", DFNT_UINT32, (1) )) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSfdefine: Couldn't define output_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpi, "collect_sctime", DFNT_UINT32, (1) )) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSfdefine: Couldn't define collect_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpi, "QAC", DFNT_UINT8, (1) )) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpi, "SCid", DFNT_UINT8, (8) )) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSfdefine: Couldn't define SCid");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpi, "FmtFC", DFNT_UINT8, (8) )) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSfdefine: Couldn't define FmtFC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpi, "FmtID", DFNT_UINT8, (8) )) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSfdefine: Couldn't define FmtID");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpi, "EF", DFNT_UINT8, (8) )) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSfdefine: Couldn't define EF");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpi, "CS", DFNT_UINT16, (8) )) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSfdefine: Couldn't define CS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpi, "DB", DFNT_UINT8, (8) )) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSfdefine: Couldn't define DB");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpi, "HVMON1", DFNT_UINT8, (8) )) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSfdefine: Couldn't define HVMON1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpi, "HVMON2", DFNT_UINT8, (8) )) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSfdefine: Couldn't define HVMON2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpi, "PSMON", DFNT_UINT8, (8) )) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSfdefine: Couldn't define PSMON");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpi, "TMon", DFNT_UINT8, (8) )) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSfdefine: Couldn't define TMon");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpi, "IMon", DFNT_UINT8, (8) )) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSfdefine: Couldn't define IMon");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpi, "IFTMon", DFNT_UINT8, (8) )) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSfdefine: Couldn't define IFTMon");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_dhskpi, "MainBusV", DFNT_UINT8, (8) )) {
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSfdefine: Couldn't define MainBusV");
    retval = -1;
  }

  if (VSsetfields(vdata_id_swepam_dhskpi,"output_sctime, collect_sctime, QAC, SCid, FmtFC, FmtID, EF, CS, DB, HVMON1, HVMON2, PSMON, TMon, IMon, IFTMon, MainBusV")){
    print_swepam_dhskpi_error("init_cr_swepam_dhskpi -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_swepam_dhskpi(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_swepam_dhskpi(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_swepam_dhskpi(struct DHSKPI DHSKPI_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_swepam_dhskpi_error();
void pack_swepam_dhskpi();

  odata = (uint8 *) malloc(sizeof(struct DHSKPI));
  pack_swepam_dhskpi(odata, &DHSKPI_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_swepam_dhskpi, recnum)==-1) {
		print_swepam_dhskpi_error("write_swepam_dhskpi -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_swepam_dhskpi, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_swepam_dhskpi_error("write_swepam_dhskpi -> VSwrite: Couldn't write data.");

  memset(&DHSKPI_struc, 0, sizeof(struct DHSKPI));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_swepam_dhskpi()
{
  VSdetach(vdata_id_swepam_dhskpi);
  Vdetach(vgrp_id_swepam_dhskpi);
}

/*----     init access function    ----*/

int32 init_acc_swepam_dhskpi(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_swepam_dhskpi_error();


  if ((vdata_ref = VSfind(hdf_fp, "DHSKPI")) <= 0 ) {
    print_swepam_dhskpi_error("init_acc_swepam_dhskpi -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_swepam_dhskpi = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_swepam_dhskpi_error("init_acc_swepam_dhskpi -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_swepam_dhskpi, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_swepam_dhskpi,"output_sctime, collect_sctime, QAC, SCid, FmtFC, FmtID, EF, CS, DB, HVMON1, HVMON2, PSMON, TMon, IMon, IFTMon, MainBusV")) {
      print_swepam_dhskpi_error("init_acc_swepam_dhskpi -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_swepam_dhskpi(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_swepam_dhskpi(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_swepam_dhskpi(struct DHSKPI *DHSKPI_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_swepam_dhskpi_error();
void unpack_swepam_dhskpi();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct DHSKPI));
  VSinquire(vdata_id_swepam_dhskpi, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_swepam_dhskpi, recnum_rd)==FAIL) {
          print_swepam_dhskpi_error("read_swepam_dhskpi -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_swepam_dhskpi, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_swepam_dhskpi_error("read_swepam_dhskpi -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_swepam_dhskpi(odata, DHSKPI_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_swepam_dhskpi()
{
  VSdetach(vdata_id_swepam_dhskpi);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_swepam_dhskpi(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_swepam_dhskpi_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_DHSKPI" )) ==FAIL)
    print_swepam_dhskpi_error("rd_Vgrp_swepam_dhskpi -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_swepam_dhskpi_error("rd_Vgrp_swepam_dhskpi -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_swepam_dhskpi_error("rd_Vgrp_swepam_dhskpi -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_swepam_dhskpi_error("rd_Vgrp_swepam_dhskpi -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_DHSKPI, HDstrlen(Vgrp_descrp_DHSKPI)) ==FAIL)
    print_swepam_dhskpi_error("rd_Vgrp_swepam_dhskpi -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_DHSKPI);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_swepam_dhskpi_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swepam_dhskpi.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_swepam_dhskpi(uint8 *data, struct DHSKPI *DHSKPI_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &DHSKPI_ptr->output_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &DHSKPI_ptr->collect_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &DHSKPI_ptr->QAC, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &DHSKPI_ptr->SCid[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPI_ptr->FmtFC[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPI_ptr->FmtID[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPI_ptr->EF[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPI_ptr->CS[0], ((2)*(8)) );
   ptr+= ((2)*(8));
   memcpy(data+ptr, &DHSKPI_ptr->DB[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPI_ptr->HVMON1[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPI_ptr->HVMON2[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPI_ptr->PSMON[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPI_ptr->TMon[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPI_ptr->IMon[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPI_ptr->IFTMon[0], ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(data+ptr, &DHSKPI_ptr->MainBusV[0], ((1)*(8)) );
   ptr+= ((1)*(8));
}

/*----   unpack function    ----*/

void unpack_swepam_dhskpi(uint8 *data, struct DHSKPI *DHSKPI_ptr)
{
int32 ptr=0;

   memcpy(&DHSKPI_ptr->output_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&DHSKPI_ptr->collect_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&DHSKPI_ptr->QAC, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&DHSKPI_ptr->SCid[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPI_ptr->FmtFC[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPI_ptr->FmtID[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPI_ptr->EF[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPI_ptr->CS[0], data+ptr,  ((2)*(8)) );
   ptr+= ((2)*(8));
   memcpy(&DHSKPI_ptr->DB[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPI_ptr->HVMON1[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPI_ptr->HVMON2[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPI_ptr->PSMON[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPI_ptr->TMon[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPI_ptr->IMon[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPI_ptr->IFTMon[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
   memcpy(&DHSKPI_ptr->MainBusV[0], data+ptr,  ((1)*(8)) );
   ptr+= ((1)*(8));
}
int32 get_vgrp_id_swepam_dhskpi() {return(vgrp_id_swepam_dhskpi);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_swepam_dhskpi(char *wr_strval)
{
  strcpy(wr_strval, "The file 'swepam_dhskpi.h' is shown below, it was used to create the data in the Vgroup named 'VG_DHSKPI'.\n\n");
  strcat(wr_strval,"/* Id: swepam_dhskpi.h,v 1.1 1997/06/20 17:59:19 jeff Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct DHSKPI               /* Swepam-I Housekeeping   */\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 output_sctime;   /* time for beginning of data output cycle */\n");
  strcat(wr_strval,"  uint32 collect_sctime;  /* time for beginning of data collection */\n");
  strcat(wr_strval,"  uint8  QAC;              /* number of bad frames in this cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* Major Frame Header */\n");
  strcat(wr_strval,"  uint8  SCid[8];         /* SubCom ID */\n");
  strcat(wr_strval,"  uint8  FmtFC[8];        /* Frame Format Count */\n");
  strcat(wr_strval,"  uint8  FmtID[8];        /* Format ID */\n");
  strcat(wr_strval,"  uint8  EF[8];           /* Event Flag */\n");
  strcat(wr_strval,"  uint16 CS[8];           /* subcom Configuration Status */\n");
  strcat(wr_strval,"  uint8  DB[8];           /* DataBase paramter */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* Subcom analog monitors - one complete cycle per 8 major frames in SCA normal mode. */\n");
  strcat(wr_strval,"  uint8  HVMON1[8]; /* subcom analog high power supply monitor */\n");
  strcat(wr_strval,"  uint8  HVMON2[8]; /* subcom analog high power supply monitor */\n");
  strcat(wr_strval,"  uint8  PSMON[8];  /* subcom analog low power supply monitor */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  /* analog and telltale monitors - one sample per major frame */\n");
  strcat(wr_strval,"  uint8  TMon[8];     /* Internal temp monitor */\n");
  strcat(wr_strval,"  uint8  IMon[8];     /* 28v return Curr Mon */\n");
  strcat(wr_strval,"  uint8  IFTMon[8];   /* Interface temp monitor */\n");
  strcat(wr_strval,"  uint8  MainBusV[8];   /* Main bux voltage monitor */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
