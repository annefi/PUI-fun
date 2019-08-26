/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1CrisSummary.h,v 1.3 1997/09/11 00:37:38 jeff Exp  */

#include "L1CrisSummary.h"
#include "df.h"

int32 vgrp_id_L1CrisSummary;
static int32 vdata_id_L1CrisSummary;

  /* 2525 is the size of L1CrisSummary.h + 1 added line */
char Vgrp_descrp_L1CrisSummary[2525];

/****----  init create function  ----****/

int32 init_cr_L1CrisSummary(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_L1CrisSummary();

  void print_L1CrisSummary_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1CrisSummary = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1CrisSummary, "VG_L1CrisSummary"); 
  Vsetclass(vgrp_id_L1CrisSummary, "VG_L1CRISSUMMARY");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1CrisSummary" )) ==FAIL) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1CrisSummary(Vgrp_descrp_L1CrisSummary);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1CrisSummary, sizeof(Vgrp_descrp_L1CrisSummary))) ==FAIL) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1CrisSummary = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1CrisSummary, "L1CrisSummary");
  VSsetclass(vdata_id_L1CrisSummary, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1CrisSummary, vdata_id_L1CrisSummary)) ==FAIL) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1CrisSummary, "ClockMinorFrame", DFNT_UINT32, (1) )) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> VSfdefine: Couldn't define ClockMinorFrame");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSummary, "Second1996", DFNT_UINT32, (1) )) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> VSfdefine: Couldn't define Second1996");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSummary, "microsecond", DFNT_UINT32, (1) )) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> VSfdefine: Couldn't define microsecond");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSummary, "FormatId", DFNT_UINT8, (1) )) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> VSfdefine: Couldn't define FormatId");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSummary, "MajorFrameCount", DFNT_UINT8, (1) )) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> VSfdefine: Couldn't define MajorFrameCount");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSummary, "MinorFrameCount", DFNT_UINT8, (1) )) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> VSfdefine: Couldn't define MinorFrameCount");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSummary, "quality", DFNT_UINT8, (1) )) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> VSfdefine: Couldn't define quality");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSummary, "MainBusVoltage", DFNT_UINT8, (1) )) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> VSfdefine: Couldn't define MainBusVoltage");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSummary, "CrisCurrent", DFNT_UINT8, (1) )) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> VSfdefine: Couldn't define CrisCurrent");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSummary, "CrisInternalTemperature1", DFNT_UINT8, (1) )) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> VSfdefine: Couldn't define CrisInternalTemperature1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSummary, "CrisInternalTemperature2", DFNT_UINT8, (1) )) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> VSfdefine: Couldn't define CrisInternalTemperature2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSummary, "CrisInterfaceTemperature", DFNT_UINT8, (1) )) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> VSfdefine: Couldn't define CrisInterfaceTemperature");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisSummary, "CrisHskp", DFNT_UINT8, (NUM_CRIS_HSKP_BYTES) )) {
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> VSfdefine: Couldn't define CrisHskp");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1CrisSummary,"ClockMinorFrame, Second1996, microsecond, FormatId, MajorFrameCount, MinorFrameCount, quality, MainBusVoltage, CrisCurrent, CrisInternalTemperature1, CrisInternalTemperature2, CrisInterfaceTemperature, CrisHskp")){
    print_L1CrisSummary_error("init_cr_L1CrisSummary -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1CrisSummary(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1CrisSummary(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1CrisSummary(struct L1CrisSummary L1CrisSummary_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_L1CrisSummary_error();
void pack_L1CrisSummary();

  odata = (uint8 *) malloc(sizeof(struct L1CrisSummary));
  pack_L1CrisSummary(odata, &L1CrisSummary_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_L1CrisSummary, recnum)==-1) {
		print_L1CrisSummary_error("write_L1CrisSummary -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1CrisSummary, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1CrisSummary_error("write_L1CrisSummary -> VSwrite: Couldn't write data.");

  memset(&L1CrisSummary_struc, 0, sizeof(struct L1CrisSummary));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1CrisSummary()
{
  VSdetach(vdata_id_L1CrisSummary);
  Vdetach(vgrp_id_L1CrisSummary);
}

/*----     init access function    ----*/

int32 init_acc_L1CrisSummary(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_L1CrisSummary_error();


  if ((vdata_ref = VSfind(hdf_fp, "L1CrisSummary")) <= 0 ) {
    print_L1CrisSummary_error("init_acc_L1CrisSummary -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1CrisSummary = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1CrisSummary_error("init_acc_L1CrisSummary -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1CrisSummary, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1CrisSummary,"ClockMinorFrame, Second1996, microsecond, FormatId, MajorFrameCount, MinorFrameCount, quality, MainBusVoltage, CrisCurrent, CrisInternalTemperature1, CrisInternalTemperature2, CrisInterfaceTemperature, CrisHskp")) {
      print_L1CrisSummary_error("init_acc_L1CrisSummary -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1CrisSummary(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1CrisSummary(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1CrisSummary(struct L1CrisSummary *L1CrisSummary_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1CrisSummary_error();
void unpack_L1CrisSummary();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct L1CrisSummary));
  VSinquire(vdata_id_L1CrisSummary, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1CrisSummary, recnum_rd)==FAIL) {
          print_L1CrisSummary_error("read_L1CrisSummary -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_L1CrisSummary, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1CrisSummary_error("read_L1CrisSummary -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1CrisSummary(odata, L1CrisSummary_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1CrisSummary()
{
  VSdetach(vdata_id_L1CrisSummary);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1CrisSummary(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1CrisSummary_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1CrisSummary" )) ==FAIL)
    print_L1CrisSummary_error("rd_Vgrp_L1CrisSummary -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1CrisSummary_error("rd_Vgrp_L1CrisSummary -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1CrisSummary_error("rd_Vgrp_L1CrisSummary -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1CrisSummary_error("rd_Vgrp_L1CrisSummary -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1CrisSummary, HDstrlen(Vgrp_descrp_L1CrisSummary)) ==FAIL)
    print_L1CrisSummary_error("rd_Vgrp_L1CrisSummary -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1CrisSummary);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1CrisSummary_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1CrisSummary.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1CrisSummary(uint8 *data, struct L1CrisSummary *L1CrisSummary_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1CrisSummary_ptr->ClockMinorFrame, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisSummary_ptr->Second1996, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisSummary_ptr->microsecond, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisSummary_ptr->FormatId, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSummary_ptr->MajorFrameCount, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSummary_ptr->MinorFrameCount, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSummary_ptr->quality, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSummary_ptr->MainBusVoltage, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSummary_ptr->CrisCurrent, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSummary_ptr->CrisInternalTemperature1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSummary_ptr->CrisInternalTemperature2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSummary_ptr->CrisInterfaceTemperature, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &L1CrisSummary_ptr->CrisHskp[0], ((1)*(NUM_CRIS_HSKP_BYTES)) );
   ptr+= ((1)*(NUM_CRIS_HSKP_BYTES));
}

/*----   unpack function    ----*/

void unpack_L1CrisSummary(uint8 *data, struct L1CrisSummary *L1CrisSummary_ptr)
{
int32 ptr=0;

   memcpy(&L1CrisSummary_ptr->ClockMinorFrame, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisSummary_ptr->Second1996, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisSummary_ptr->microsecond, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisSummary_ptr->FormatId, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSummary_ptr->MajorFrameCount, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSummary_ptr->MinorFrameCount, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSummary_ptr->quality, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSummary_ptr->MainBusVoltage, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSummary_ptr->CrisCurrent, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSummary_ptr->CrisInternalTemperature1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSummary_ptr->CrisInternalTemperature2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSummary_ptr->CrisInterfaceTemperature, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&L1CrisSummary_ptr->CrisHskp[0], data+ptr,  ((1)*(NUM_CRIS_HSKP_BYTES)) );
   ptr+= ((1)*(NUM_CRIS_HSKP_BYTES));
}
int32 get_vgrp_id_L1CrisSummary() {return(vgrp_id_L1CrisSummary);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1CrisSummary(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1CrisSummary.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1CrisSummary'.\n\n");
  strcat(wr_strval,"/* Id: L1CrisSummary.h,v 1.3 1997/09/11 00:37:38 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisSummary.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 00:37:38 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.3 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"CrisConstants.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1CrisSummary\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32  ClockMinorFrame;\n");
  strcat(wr_strval,"   uint32  Second1996;\n");
  strcat(wr_strval,"   uint32  microsecond;\n");
  strcat(wr_strval,"    uint8  FormatId;\n");
  strcat(wr_strval,"    uint8  MajorFrameCount;\n");
  strcat(wr_strval,"    uint8  MinorFrameCount;\n");
  strcat(wr_strval,"    uint8  quality;\n");
  strcat(wr_strval,"    uint8  MainBusVoltage;\n");
  strcat(wr_strval,"    uint8  CrisCurrent;\n");
  strcat(wr_strval,"    uint8  CrisInternalTemperature1;\n");
  strcat(wr_strval,"    uint8  CrisInternalTemperature2;\n");
  strcat(wr_strval,"    uint8  CrisInterfaceTemperature;\n");
  strcat(wr_strval,"    uint8  CrisHskp[NUM_CRIS_HSKP_BYTES];\n");
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
  strcat(wr_strval,"/*    CrisCurrent = CRIS I/F & survial heater current (255=no data)  */\n");
  strcat(wr_strval,"/*    CrisInternalTemperature1 = CRIS internal temperature 1         */\n");
  strcat(wr_strval,"/*                              (255=no data)                        */\n");
  strcat(wr_strval,"/*    CrisInternalTemperature2 = CRIS internal temperature 2         */\n");
  strcat(wr_strval,"/*                              (255=no data)                        */\n");
  strcat(wr_strval,"/*    CrisInterfaceTemperature = CRIS interface temperature          */\n");
  strcat(wr_strval,"/*                              (255=no data)                        */\n");
  strcat(wr_strval,"/*    CrisHskp = Housekeeping/rate bytes from CRIS telemetry         */\n");
  return(0);
}
