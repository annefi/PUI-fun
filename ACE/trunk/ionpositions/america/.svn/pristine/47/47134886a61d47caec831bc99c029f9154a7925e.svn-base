/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1SisHighPriorityRate.h,v 1.2 1997/09/11 16:50:59 jeff Exp  */

#include "L1SisHighPriorityRate.h"
#include "df.h"

int32 vgrp_id_L1SisHighPriorityRate;
static int32 vdata_id_L1SisHighPriorityRate;

  /* 2337 is the size of L1SisHighPriorityRate.h + 1 added line */
char Vgrp_descrp_L1SisHighPriorityRate[2337];

/****----  init create function  ----****/

int32 init_cr_L1SisHighPriorityRate(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_L1SisHighPriorityRate();

  void print_L1SisHighPriorityRate_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1SisHighPriorityRate = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1SisHighPriorityRate_error("init_cr_L1SisHighPriorityRate -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1SisHighPriorityRate, "VG_L1SisHighPriorityRate"); 
  Vsetclass(vgrp_id_L1SisHighPriorityRate, "VG_L1SISHIGHPRIORITYRATE");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1SisHighPriorityRate" )) ==FAIL) {
    print_L1SisHighPriorityRate_error("init_cr_L1SisHighPriorityRate -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1SisHighPriorityRate(Vgrp_descrp_L1SisHighPriorityRate);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1SisHighPriorityRate_error("init_cr_L1SisHighPriorityRate -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1SisHighPriorityRate, sizeof(Vgrp_descrp_L1SisHighPriorityRate))) ==FAIL) {
    print_L1SisHighPriorityRate_error("init_cr_L1SisHighPriorityRate -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1SisHighPriorityRate = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1SisHighPriorityRate_error("init_cr_L1SisHighPriorityRate -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1SisHighPriorityRate, "L1SisHighPriorityRate");
  VSsetclass(vdata_id_L1SisHighPriorityRate, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1SisHighPriorityRate, vdata_id_L1SisHighPriorityRate)) ==FAIL) {
    print_L1SisHighPriorityRate_error("init_cr_L1SisHighPriorityRate -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1SisHighPriorityRate, "ClockMinorFrame", DFNT_UINT32, (1) )) {
    print_L1SisHighPriorityRate_error("init_cr_L1SisHighPriorityRate -> VSfdefine: Couldn't define ClockMinorFrame");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHighPriorityRate, "Second1996", DFNT_UINT32, (1) )) {
    print_L1SisHighPriorityRate_error("init_cr_L1SisHighPriorityRate -> VSfdefine: Couldn't define Second1996");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHighPriorityRate, "microsecond", DFNT_UINT32, (1) )) {
    print_L1SisHighPriorityRate_error("init_cr_L1SisHighPriorityRate -> VSfdefine: Couldn't define microsecond");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHighPriorityRate, "hp", DFNT_UINT16, (NUM_SIS_HIGH_PRIORITY_RATES) )) {
    print_L1SisHighPriorityRate_error("init_cr_L1SisHighPriorityRate -> VSfdefine: Couldn't define hp");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1SisHighPriorityRate, "QualityHp", DFNT_UINT8, (NUM_SIS_HIGH_PRIORITY_RATES) )) {
    print_L1SisHighPriorityRate_error("init_cr_L1SisHighPriorityRate -> VSfdefine: Couldn't define QualityHp");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1SisHighPriorityRate,"ClockMinorFrame, Second1996, microsecond, hp, QualityHp")){
    print_L1SisHighPriorityRate_error("init_cr_L1SisHighPriorityRate -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1SisHighPriorityRate(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1SisHighPriorityRate(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1SisHighPriorityRate(struct L1SisHighPriorityRate L1SisHighPriorityRate_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_L1SisHighPriorityRate_error();
void pack_L1SisHighPriorityRate();

  odata = (uint8 *) malloc(sizeof(struct L1SisHighPriorityRate));
  pack_L1SisHighPriorityRate(odata, &L1SisHighPriorityRate_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_L1SisHighPriorityRate, recnum)==-1) {
		print_L1SisHighPriorityRate_error("write_L1SisHighPriorityRate -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1SisHighPriorityRate, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1SisHighPriorityRate_error("write_L1SisHighPriorityRate -> VSwrite: Couldn't write data.");

  memset(&L1SisHighPriorityRate_struc, 0, sizeof(struct L1SisHighPriorityRate));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1SisHighPriorityRate()
{
  VSdetach(vdata_id_L1SisHighPriorityRate);
  Vdetach(vgrp_id_L1SisHighPriorityRate);
}

/*----     init access function    ----*/

int32 init_acc_L1SisHighPriorityRate(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_L1SisHighPriorityRate_error();


  if ((vdata_ref = VSfind(hdf_fp, "L1SisHighPriorityRate")) <= 0 ) {
    print_L1SisHighPriorityRate_error("init_acc_L1SisHighPriorityRate -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1SisHighPriorityRate = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1SisHighPriorityRate_error("init_acc_L1SisHighPriorityRate -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1SisHighPriorityRate, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1SisHighPriorityRate,"ClockMinorFrame, Second1996, microsecond, hp, QualityHp")) {
      print_L1SisHighPriorityRate_error("init_acc_L1SisHighPriorityRate -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1SisHighPriorityRate(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1SisHighPriorityRate(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1SisHighPriorityRate(struct L1SisHighPriorityRate *L1SisHighPriorityRate_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1SisHighPriorityRate_error();
void unpack_L1SisHighPriorityRate();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct L1SisHighPriorityRate));
  VSinquire(vdata_id_L1SisHighPriorityRate, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1SisHighPriorityRate, recnum_rd)==FAIL) {
          print_L1SisHighPriorityRate_error("read_L1SisHighPriorityRate -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_L1SisHighPriorityRate, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1SisHighPriorityRate_error("read_L1SisHighPriorityRate -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1SisHighPriorityRate(odata, L1SisHighPriorityRate_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1SisHighPriorityRate()
{
  VSdetach(vdata_id_L1SisHighPriorityRate);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1SisHighPriorityRate(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1SisHighPriorityRate_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1SisHighPriorityRate" )) ==FAIL)
    print_L1SisHighPriorityRate_error("rd_Vgrp_L1SisHighPriorityRate -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1SisHighPriorityRate_error("rd_Vgrp_L1SisHighPriorityRate -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1SisHighPriorityRate_error("rd_Vgrp_L1SisHighPriorityRate -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1SisHighPriorityRate_error("rd_Vgrp_L1SisHighPriorityRate -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1SisHighPriorityRate, HDstrlen(Vgrp_descrp_L1SisHighPriorityRate)) ==FAIL)
    print_L1SisHighPriorityRate_error("rd_Vgrp_L1SisHighPriorityRate -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1SisHighPriorityRate);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1SisHighPriorityRate_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1SisHighPriorityRate.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1SisHighPriorityRate(uint8 *data, struct L1SisHighPriorityRate *L1SisHighPriorityRate_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1SisHighPriorityRate_ptr->ClockMinorFrame, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisHighPriorityRate_ptr->Second1996, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisHighPriorityRate_ptr->microsecond, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1SisHighPriorityRate_ptr->hp[0], ((2)*(NUM_SIS_HIGH_PRIORITY_RATES)) );
   ptr+= ((2)*(NUM_SIS_HIGH_PRIORITY_RATES));
   memcpy(data+ptr, &L1SisHighPriorityRate_ptr->QualityHp[0], ((1)*(NUM_SIS_HIGH_PRIORITY_RATES)) );
   ptr+= ((1)*(NUM_SIS_HIGH_PRIORITY_RATES));
}

/*----   unpack function    ----*/

void unpack_L1SisHighPriorityRate(uint8 *data, struct L1SisHighPriorityRate *L1SisHighPriorityRate_ptr)
{
int32 ptr=0;

   memcpy(&L1SisHighPriorityRate_ptr->ClockMinorFrame, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisHighPriorityRate_ptr->Second1996, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisHighPriorityRate_ptr->microsecond, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1SisHighPriorityRate_ptr->hp[0], data+ptr,  ((2)*(NUM_SIS_HIGH_PRIORITY_RATES)) );
   ptr+= ((2)*(NUM_SIS_HIGH_PRIORITY_RATES));
   memcpy(&L1SisHighPriorityRate_ptr->QualityHp[0], data+ptr,  ((1)*(NUM_SIS_HIGH_PRIORITY_RATES)) );
   ptr+= ((1)*(NUM_SIS_HIGH_PRIORITY_RATES));
}
int32 get_vgrp_id_L1SisHighPriorityRate() {return(vgrp_id_L1SisHighPriorityRate);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1SisHighPriorityRate(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1SisHighPriorityRate.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1SisHighPriorityRate'.\n\n");
  strcat(wr_strval,"/* Id: L1SisHighPriorityRate.h,v 1.2 1997/09/11 16:50:59 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1SisHighPriorityRate.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 16:50:59 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.2 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"SisConstants.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1SisHighPriorityRate\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32 ClockMinorFrame;\n");
  strcat(wr_strval,"   uint32 Second1996;\n");
  strcat(wr_strval,"   uint32 microsecond;\n");
  strcat(wr_strval,"   uint16 hp[NUM_SIS_HIGH_PRIORITY_RATES];\n");
  strcat(wr_strval,"   uint8  QualityHp[NUM_SIS_HIGH_PRIORITY_RATES];\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* Definition:                                                       */\n");
  strcat(wr_strval,"/*    ClockMinorFrame = Adjusted S/C clock of the minor frame in     */\n");
  strcat(wr_strval,"/*                      which the high priority rate accumulation    */\n");
  strcat(wr_strval,"/*                      began                                        */\n");
  strcat(wr_strval,"/*    hp = high priority rates                                       */\n");
  strcat(wr_strval,"/*    QualityHp = Flags for missing high priority rates              */\n");
  strcat(wr_strval,"/*                                                                   */\n");
  strcat(wr_strval,"/* Note: All rates are compressed.                                   */\n");
  strcat(wr_strval,"/*                                                                   */\n");
  strcat(wr_strval,"/* Note: Quality bits are defined in the table below.  If the field  */\n");
  strcat(wr_strval,"/*       which the quality byte is trying to characterize contains   */\n");
  strcat(wr_strval,"/*       multiple bytes, the quality byte associated with the field  */\n");
  strcat(wr_strval,"/*       is the logical \"or\" of the individual quality bytes.        */\n");
  strcat(wr_strval,"/*                                                                   */\n");
  strcat(wr_strval,"/* Quality bits:                                                     */\n");
  strcat(wr_strval,"/*    0x01 = Format ID error                                         */\n");
  strcat(wr_strval,"/*    0x02 = Minor/major counter error                               */\n");
  strcat(wr_strval,"/*    0x04 = S/C clock error                                         */\n");
  strcat(wr_strval,"/*    0x08 = Sync bit error                                          */\n");
  strcat(wr_strval,"/*    0x10 = Command table index error                               */\n");
  strcat(wr_strval,"/*    0x20 = Cycle number error                                      */\n");
  strcat(wr_strval,"/*    0x40 = Level 0 quality bit                                     */\n");
  strcat(wr_strval,"/*    0x80 = Level 1 quality bit                                     */\n");
  return(0);
}
