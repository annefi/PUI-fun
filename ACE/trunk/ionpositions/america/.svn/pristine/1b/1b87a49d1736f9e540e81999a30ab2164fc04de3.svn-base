/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1SisSummary.h,v 1.3 1997/09/11 16:50:59 jeff Exp  */

#include "L1SisSummary.h"
#include "df.h"

int32 vgrp_id_L1SisSummary;
static int32 vdata_id_L1SisSummary;

  /* 2617 is the size of L1SisSummary.h + 1 added line */
char Vgrp_descrp_L1SisSummary[2617];

/****----  init create function  ----****/

int32 init_cr_L1SisSummary(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_L1SisSummary();

  void print_L1SisSummary_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1SisSummary = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1SisSummary, "VG_L1SisSummary"); 
  Vsetclass(vgrp_id_L1SisSummary, "VG_L1SISSUMMARY");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1SisSummary" )) ==FAIL) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1SisSummary(Vgrp_descrp_L1SisSummary);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1SisSummary, sizeof(Vgrp_descrp_L1SisSummary))) ==FAIL) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1SisSummary = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1SisSummary, "L1SisSummary");
  VSsetclass(vdata_id_L1SisSummary, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1SisSummary, vdata_id_L1SisSummary)) ==FAIL) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1SisSummary, "ClockMinorFrame", DFNT_UINT32, (1) )) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> VSfdefine: Couldn't define ClockMinorFrame");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisSummary, "Second1996", DFNT_UINT32, (1) )) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> VSfdefine: Couldn't define Second1996");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisSummary, "microsecond", DFNT_UINT32, (1) )) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> VSfdefine: Couldn't define microsecond");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisSummary, "FormatId", DFNT_UINT8, (1) )) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> VSfdefine: Couldn't define FormatId");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisSummary, "MajorFrameCount", DFNT_UINT8, (1) )) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> VSfdefine: Couldn't define MajorFrameCount");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisSummary, "MinorFrameCount", DFNT_UINT8, (1) )) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> VSfdefine: Couldn't define MinorFrameCount");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisSummary, "quality", DFNT_UINT8, (1) )) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> VSfdefine: Couldn't define quality");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisSummary, "MainBusVoltage", DFNT_UINT8, (1) )) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> VSfdefine: Couldn't define MainBusVoltage");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisSummary, "SisCurrent", DFNT_UINT8, (1) )) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> VSfdefine: Couldn't define SisCurrent");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisSummary, "SisInternalTemperature1", DFNT_UINT8, (1) )) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> VSfdefine: Couldn't define SisInternalTemperature1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisSummary, "SisInternalTemperature2", DFNT_UINT8, (1) )) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> VSfdefine: Couldn't define SisInternalTemperature2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisSummary, "SisInterfaceTemperature", DFNT_UINT8, (1) )) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> VSfdefine: Couldn't define SisInterfaceTemperature");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisSummary, "SisCoverTelltale", DFNT_UINT8, (1) )) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> VSfdefine: Couldn't define SisCoverTelltale");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisSummary, "SisHskp", DFNT_UINT8, (NUM_SIS_HSKP_BYTES) )) {
    print_L1SisSummary_error("init_cr_L1SisSummary -> VSfdefine: Couldn't define SisHskp");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1SisSummary,"ClockMinorFrame, Second1996, microsecond, FormatId, MajorFrameCount, MinorFrameCount, quality, MainBusVoltage, SisCurrent, SisInternalTemperature1, SisInternalTemperature2, SisInterfaceTemperature, SisCoverTelltale, SisHskp")){
    print_L1SisSummary_error("init_cr_L1SisSummary -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1SisSummary(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1SisSummary(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1SisSummary(struct L1SisSummary L1SisSummary_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_L1SisSummary_error();
void pack_L1SisSummary();

  odata = (uint8 *) malloc(sizeof(struct L1SisSummary));
  pack_L1SisSummary(odata, &L1SisSummary_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_L1SisSummary, recnum)==-1) {
		print_L1SisSummary_error("write_L1SisSummary -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1SisSummary, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1SisSummary_error("write_L1SisSummary -> VSwrite: Couldn't write data.");

  memset(&L1SisSummary_struc, 0, sizeof(struct L1SisSummary));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1SisSummary()
{
  VSdetach(vdata_id_L1SisSummary);
  Vdetach(vgrp_id_L1SisSummary);
}

/*----     init access function    ----*/

int32 init_acc_L1SisSummary(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_L1SisSummary_error();


  if ((vdata_ref = VSfind(hdf_fp, "L1SisSummary")) <= 0 ) {
    print_L1SisSummary_error("init_acc_L1SisSummary -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1SisSummary = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1SisSummary_error("init_acc_L1SisSummary -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1SisSummary, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1SisSummary,"ClockMinorFrame, Second1996, microsecond, FormatId, MajorFrameCount, MinorFrameCount, quality, MainBusVoltage, SisCurrent, SisInternalTemperature1, SisInternalTemperature2, SisInterfaceTemperature, SisCoverTelltale, SisHskp")) {
      print_L1SisSummary_error("init_acc_L1SisSummary -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1SisSummary(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1SisSummary(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1SisSummary(struct L1SisSummary *L1SisSummary_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1SisSummary_error();
void unpack_L1SisSummary();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct L1SisSummary));
  VSinquire(vdata_id_L1SisSummary, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1SisSummary, recnum_rd)==FAIL) {
          print_L1SisSummary_error("read_L1SisSummary -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_L1SisSummary, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1SisSummary_error("read_L1SisSummary -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1SisSummary(odata, L1SisSummary_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1SisSummary()
{
  VSdetach(vdata_id_L1SisSummary);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1SisSummary(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1SisSummary_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1SisSummary" )) ==FAIL)
    print_L1SisSummary_error("rd_Vgrp_L1SisSummary -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1SisSummary_error("rd_Vgrp_L1SisSummary -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1SisSummary_error("rd_Vgrp_L1SisSummary -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1SisSummary_error("rd_Vgrp_L1SisSummary -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1SisSummary, HDstrlen(Vgrp_descrp_L1SisSummary)) ==FAIL)
    print_L1SisSummary_error("rd_Vgrp_L1SisSummary -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1SisSummary);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1SisSummary_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1SisSummary.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1SisSummary(uint8 *data, struct L1SisSummary *L1SisSummary_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1SisSummary_ptr->ClockMinorFrame, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisSummary_ptr->Second1996, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisSummary_ptr->microsecond, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisSummary_ptr->FormatId, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisSummary_ptr->MajorFrameCount, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisSummary_ptr->MinorFrameCount, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisSummary_ptr->quality, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisSummary_ptr->MainBusVoltage, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisSummary_ptr->SisCurrent, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisSummary_ptr->SisInternalTemperature1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisSummary_ptr->SisInternalTemperature2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisSummary_ptr->SisInterfaceTemperature, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisSummary_ptr->SisCoverTelltale, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1SisSummary_ptr->SisHskp[0], ((1)*(NUM_SIS_HSKP_BYTES)) );
   ptr+= ((1)*(NUM_SIS_HSKP_BYTES));
}

/*----   unpack function    ----*/

void unpack_L1SisSummary(uint8 *data, struct L1SisSummary *L1SisSummary_ptr)
{
int32 ptr=0;

   memcpy(&L1SisSummary_ptr->ClockMinorFrame, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisSummary_ptr->Second1996, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisSummary_ptr->microsecond, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisSummary_ptr->FormatId, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisSummary_ptr->MajorFrameCount, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisSummary_ptr->MinorFrameCount, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisSummary_ptr->quality, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisSummary_ptr->MainBusVoltage, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisSummary_ptr->SisCurrent, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisSummary_ptr->SisInternalTemperature1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisSummary_ptr->SisInternalTemperature2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisSummary_ptr->SisInterfaceTemperature, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisSummary_ptr->SisCoverTelltale, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1SisSummary_ptr->SisHskp[0], data+ptr,  ((1)*(NUM_SIS_HSKP_BYTES)) );
   ptr+= ((1)*(NUM_SIS_HSKP_BYTES));
}
int32 get_vgrp_id_L1SisSummary() {return(vgrp_id_L1SisSummary);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1SisSummary(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1SisSummary.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1SisSummary'.\n\n");
  strcat(wr_strval,"/* Id: L1SisSummary.h,v 1.3 1997/09/11 16:50:59 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisSummary.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 16:50:59 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.3 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"SisConstants.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1SisSummary\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32  ClockMinorFrame;\n");
  strcat(wr_strval,"   uint32  Second1996;\n");
  strcat(wr_strval,"   uint32  microsecond;\n");
  strcat(wr_strval,"    uint8  FormatId;\n");
  strcat(wr_strval,"    uint8  MajorFrameCount;\n");
  strcat(wr_strval,"    uint8  MinorFrameCount;\n");
  strcat(wr_strval,"    uint8  quality;\n");
  strcat(wr_strval,"    uint8  MainBusVoltage;\n");
  strcat(wr_strval,"    uint8  SisCurrent;\n");
  strcat(wr_strval,"    uint8  SisInternalTemperature1;\n");
  strcat(wr_strval,"    uint8  SisInternalTemperature2;\n");
  strcat(wr_strval,"    uint8  SisInterfaceTemperature;\n");
  strcat(wr_strval,"    uint8  SisCoverTelltale;\n");
  strcat(wr_strval,"    uint8  SisHskp[NUM_SIS_HSKP_BYTES];\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* Definition:                                                       */\n");
  strcat(wr_strval,"/*    ClockMinorFrame = S/C clock of the minor frame                 */\n");
  strcat(wr_strval,"/*    FormatId = Format of the minor frame                           */\n");
  strcat(wr_strval,"/*    MajorFrameCount = Major frame count of the minor frame         */\n");
  strcat(wr_strval,"/*    MinorFrameCount = Minor frame count of the minor frame         */\n");
  strcat(wr_strval,"/*    quality = Quality flag associated with the minor frame         */\n");
  strcat(wr_strval,"/*              0x01 = Format ID error                               */\n");
  strcat(wr_strval,"/*              0x02 = Minor/major counter error                     */\n");
  strcat(wr_strval,"/*              0x04 = S/C clock error                               */\n");
  strcat(wr_strval,"/*              0x08 = Sync bit error                                */\n");
  strcat(wr_strval,"/*              0x10 = Command table index error                     */\n");
  strcat(wr_strval,"/*              0x20 = Cycle number error                            */\n");
  strcat(wr_strval,"/*              0x40 = Level 0 quality bit                           */\n");
  strcat(wr_strval,"/*              0x80 = Level 1 quality bit                           */\n");
  strcat(wr_strval,"/*    MainBusVoltage = Main bus voltage value (255=no data)          */\n");
  strcat(wr_strval,"/*    SisCurrent = SIS I/F & survial heater current (255=no data)    */\n");
  strcat(wr_strval,"/*    SisInternalTemperature1 = SIS internal temperature 1           */\n");
  strcat(wr_strval,"/*                              (255=no data)                        */\n");
  strcat(wr_strval,"/*    SisInternalTemperature2 = SIS internal temperature 2           */\n");
  strcat(wr_strval,"/*                              (255=no data)                        */\n");
  strcat(wr_strval,"/*    SisInterfaceTemperature = SIS interface temperature            */\n");
  strcat(wr_strval,"/*                              (255=no data)                        */\n");
  strcat(wr_strval,"/*    SisCoverTelltale = SIS cover telltale (255=no data)            */\n");
  strcat(wr_strval,"/*    SisHskp = Housekeeping/rate bytes from SIS telemetry           */\n");
  return(0);
}
