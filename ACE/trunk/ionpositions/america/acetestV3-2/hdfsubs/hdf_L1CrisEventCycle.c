/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: L1CrisEventCycle.h,v 1.3 1997/09/11 00:37:38 jeff Exp  */

#include "L1CrisEventCycle.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_L1CrisEventCycle;
static int32 vdata_id_L1CrisEventCycle;

static int32 sds_id_L1CrisEventCycle1;

  /* 1872 is the size of L1CrisEventCycle.h + 1 added line */
char Vgrp_descrp_L1CrisEventCycle[1872];

/****----  init create function  ----****/

int32 init_cr_L1CrisEventCycle(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[2];
  int32 rank;

  int32 wr_Vgrp_desc_L1CrisEventCycle();

  void print_L1CrisEventCycle_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_L1CrisEventCycle = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_L1CrisEventCycle_error("init_cr_L1CrisEventCycle -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_L1CrisEventCycle, "VG_L1CrisEventCycle"); 
  Vsetclass(vgrp_id_L1CrisEventCycle, "VG_L1CRISEVENTCYCLE");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_L1CrisEventCycle" )) ==FAIL) {
    print_L1CrisEventCycle_error("init_cr_L1CrisEventCycle -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_L1CrisEventCycle(Vgrp_descrp_L1CrisEventCycle);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_L1CrisEventCycle_error("init_cr_L1CrisEventCycle -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_L1CrisEventCycle, sizeof(Vgrp_descrp_L1CrisEventCycle))) ==FAIL) {
    print_L1CrisEventCycle_error("init_cr_L1CrisEventCycle -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_L1CrisEventCycle = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_L1CrisEventCycle_error("init_cr_L1CrisEventCycle -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_L1CrisEventCycle, "L1CrisEventCycle");
  VSsetclass(vdata_id_L1CrisEventCycle, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_L1CrisEventCycle, vdata_id_L1CrisEventCycle)) ==FAIL) {
    print_L1CrisEventCycle_error("init_cr_L1CrisEventCycle -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_L1CrisEventCycle, "ClockCycle", DFNT_UINT32, (1) )) {
    print_L1CrisEventCycle_error("init_cr_L1CrisEventCycle -> VSfdefine: Couldn't define ClockCycle");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisEventCycle, "Second1996", DFNT_UINT32, (1) )) {
    print_L1CrisEventCycle_error("init_cr_L1CrisEventCycle -> VSfdefine: Couldn't define Second1996");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisEventCycle, "microsecond", DFNT_UINT32, (1) )) {
    print_L1CrisEventCycle_error("init_cr_L1CrisEventCycle -> VSfdefine: Couldn't define microsecond");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisEventCycle, "NumberNormalEventBytes", DFNT_UINT16, (MAX_CRIS_EVT_AGE) )) {
    print_L1CrisEventCycle_error("init_cr_L1CrisEventCycle -> VSfdefine: Couldn't define NumberNormalEventBytes");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisEventCycle, "NumberEvents", DFNT_UINT16, (1) )) {
    print_L1CrisEventCycle_error("init_cr_L1CrisEventCycle -> VSfdefine: Couldn't define NumberEvents");
    retval = -1;
  }
  if (VSfdefine(vdata_id_L1CrisEventCycle, "ContinuationFlag", DFNT_UINT8, (1) )) {
    print_L1CrisEventCycle_error("init_cr_L1CrisEventCycle -> VSfdefine: Couldn't define ContinuationFlag");
    retval = -1;
  }

  if (VSsetfields(vdata_id_L1CrisEventCycle,"ClockCycle, Second1996, microsecond, NumberNormalEventBytes, NumberEvents, ContinuationFlag")){
    print_L1CrisEventCycle_error("init_cr_L1CrisEventCycle -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 2;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = SIZE_CRIS_EVENT_BUFFER;
  if((sds_id_L1CrisEventCycle1 = SDcreate(sd_id, "L1CrisEventCycle_EventBuffer", DFNT_UINT8, rank, dim_sizes)) == FAIL)
    print_L1CrisEventCycle_error("init_cr_L1CrisEventCycle -> SDcreate: Couldn't create L1CrisEventCycle_EventBuffer");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_L1CrisEventCycle1)) == FAIL)
    print_L1CrisEventCycle_error("init_cr_L1CrisEventCycle -> SDidtoref: Couldn't get ref for L1CrisEventCycle_EventBuffer");

  if((Vaddtagref(vgrp_id_L1CrisEventCycle, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_L1CrisEventCycle_error("init_cr_L1CrisEventCycle -> Vaddtagref: Couldn't add SDS L1CrisEventCycle_EventBuffer to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_L1CrisEventCycle(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_L1CrisEventCycle(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_L1CrisEventCycle(struct L1CrisEventCycle L1CrisEventCycle_struc, int32 recnum)
{
  int32 start[2], edges[2];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_L1CrisEventCycle_error();
void pack_L1CrisEventCycle();

  odata = (uint8 *) malloc(sizeof(struct L1CrisEventCycle));
  pack_L1CrisEventCycle(odata, &L1CrisEventCycle_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_L1CrisEventCycle, recnum)==-1) {
		print_L1CrisEventCycle_error("write_L1CrisEventCycle -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_L1CrisEventCycle, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_L1CrisEventCycle_error("write_L1CrisEventCycle -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  edges[0] = 1;

  edges[1] = SIZE_CRIS_EVENT_BUFFER;
  if (SDwritedata(sds_id_L1CrisEventCycle1,start,NULL,edges, (VOIDP)(L1CrisEventCycle_struc.EventBuffer)) ==FAIL)
    print_L1CrisEventCycle_error("write_L1CrisEventCycle -> SDwritedata: Problem writing EventBuffer data.");

  memset(&L1CrisEventCycle_struc, 0, sizeof(struct L1CrisEventCycle));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_L1CrisEventCycle()
{
  VSdetach(vdata_id_L1CrisEventCycle);
  Vdetach(vgrp_id_L1CrisEventCycle);
  SDendaccess(sds_id_L1CrisEventCycle1);
}

/*----     init access function    ----*/

int32 init_acc_L1CrisEventCycle(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_L1CrisEventCycle_error();

  if((sds_index1=SDnametoindex(sd_id, "L1CrisEventCycle_EventBuffer" )) ==FAIL) {
      print_L1CrisEventCycle_error("init_acc_L1CrisEventCycle -> SDnametoindex: Couldn't find L1CrisEventCycle_EventBuffer");
      return(-1);
  }
  if((sds_id_L1CrisEventCycle1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_L1CrisEventCycle_error("init_acc_L1CrisEventCycle -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "L1CrisEventCycle")) <= 0 ) {
    print_L1CrisEventCycle_error("init_acc_L1CrisEventCycle -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_L1CrisEventCycle = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_L1CrisEventCycle_error("init_acc_L1CrisEventCycle -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_L1CrisEventCycle, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_L1CrisEventCycle,"ClockCycle, Second1996, microsecond, NumberNormalEventBytes, NumberEvents, ContinuationFlag")) {
      print_L1CrisEventCycle_error("init_acc_L1CrisEventCycle -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_L1CrisEventCycle(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_L1CrisEventCycle(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_L1CrisEventCycle(struct L1CrisEventCycle *L1CrisEventCycle_struc, int32 recnum_rd)
{
int32 start[2], edges[2];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_L1CrisEventCycle_error();
void unpack_L1CrisEventCycle();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct L1CrisEventCycle));
  VSinquire(vdata_id_L1CrisEventCycle, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_L1CrisEventCycle, recnum_rd)==FAIL) {
          print_L1CrisEventCycle_error("read_L1CrisEventCycle -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = SIZE_CRIS_EVENT_BUFFER;

  if(SDreaddata(sds_id_L1CrisEventCycle1,start,NULL,edges, (VOIDP)(L1CrisEventCycle_struc->EventBuffer )) ==FAIL) {
    print_L1CrisEventCycle_error("read_L1CrisEventCycle -> SDreaddata: Couldn't read EventBuffer");
    retval = -1;
  }
  if(VSread(vdata_id_L1CrisEventCycle, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_L1CrisEventCycle_error("read_L1CrisEventCycle -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_L1CrisEventCycle(odata, L1CrisEventCycle_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_L1CrisEventCycle()
{
  VSdetach(vdata_id_L1CrisEventCycle);
  SDendaccess(sds_id_L1CrisEventCycle1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_L1CrisEventCycle(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_L1CrisEventCycle_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_L1CrisEventCycle" )) ==FAIL)
    print_L1CrisEventCycle_error("rd_Vgrp_L1CrisEventCycle -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_L1CrisEventCycle_error("rd_Vgrp_L1CrisEventCycle -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_L1CrisEventCycle_error("rd_Vgrp_L1CrisEventCycle -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_L1CrisEventCycle_error("rd_Vgrp_L1CrisEventCycle -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_L1CrisEventCycle, HDstrlen(Vgrp_descrp_L1CrisEventCycle)) ==FAIL)
    print_L1CrisEventCycle_error("rd_Vgrp_L1CrisEventCycle -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_L1CrisEventCycle);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_L1CrisEventCycle_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_L1CrisEventCycle.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_L1CrisEventCycle(uint8 *data, struct L1CrisEventCycle *L1CrisEventCycle_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &L1CrisEventCycle_ptr->ClockCycle, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisEventCycle_ptr->Second1996, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisEventCycle_ptr->microsecond, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &L1CrisEventCycle_ptr->NumberNormalEventBytes[0], ((2)*(MAX_CRIS_EVT_AGE)) );
   ptr+= ((2)*(MAX_CRIS_EVT_AGE));
   memcpy(data+ptr, &L1CrisEventCycle_ptr->NumberEvents, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &L1CrisEventCycle_ptr->ContinuationFlag, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_L1CrisEventCycle(uint8 *data, struct L1CrisEventCycle *L1CrisEventCycle_ptr)
{
int32 ptr=0;

   memcpy(&L1CrisEventCycle_ptr->ClockCycle, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisEventCycle_ptr->Second1996, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisEventCycle_ptr->microsecond, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&L1CrisEventCycle_ptr->NumberNormalEventBytes[0], data+ptr,  ((2)*(MAX_CRIS_EVT_AGE)) );
   ptr+= ((2)*(MAX_CRIS_EVT_AGE));
   memcpy(&L1CrisEventCycle_ptr->NumberEvents, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&L1CrisEventCycle_ptr->ContinuationFlag, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_L1CrisEventCycle() {return(vgrp_id_L1CrisEventCycle);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_L1CrisEventCycle(char *wr_strval)
{
  strcpy(wr_strval, "The file 'L1CrisEventCycle.h' is shown below, it was used to create the data in the Vgroup named 'VG_L1CrisEventCycle'.\n\n");
  strcat(wr_strval,"/* Id: L1CrisEventCycle.h,v 1.3 1997/09/11 00:37:38 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/L1CrisEventCycle.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 00:37:38 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.3 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"#include \"CrisConstants.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct L1CrisEventCycle\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"   uint32 ClockCycle;\n");
  strcat(wr_strval,"   uint32 Second1996;\n");
  strcat(wr_strval,"   uint32 microsecond;\n");
  strcat(wr_strval,"   uint16 NumberNormalEventBytes[MAX_CRIS_EVT_AGE];\n");
  strcat(wr_strval,"   uint16 NumberEvents;\n");
  strcat(wr_strval,"   uint8  EventBuffer[SIZE_CRIS_EVENT_BUFFER];\n");
  strcat(wr_strval,"   uint8  ContinuationFlag;\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* Definition:                                                       */\n");
  strcat(wr_strval,"/*    ClockCycle = S/C clock of the first minor frame of the cycle   */\n");
  strcat(wr_strval,"/*                 in which CRIS processed the event                 */\n");
  strcat(wr_strval,"/*    NumberNormalEventBytes = Number of bytes used for normal event */\n");
  strcat(wr_strval,"/*                             processing from each of the cycles    */\n");
  strcat(wr_strval,"/*                             that can contribute events to this    */\n");
  strcat(wr_strval,"/*                             structure.                            */\n");
  strcat(wr_strval,"/*    NumberEvents = Number of events stored in the event buffer     */\n");
  strcat(wr_strval,"/*    EventBuffer = Event buffer                                     */\n");
  strcat(wr_strval,"/*    ContinuationFlag = Flag indicating events from this cycle are  */\n");
  strcat(wr_strval,"/*                       continued in the next structure             */\n");
  strcat(wr_strval,"/*                                                                   */\n");
  strcat(wr_strval,"/* Note: Each event in the event buffer is preceded by two bytes.    */\n");
  strcat(wr_strval,"/*       The first is the relative age of the event in cycles.  The  */\n");
  strcat(wr_strval,"/*       second is the minor frame in which the first byte of the    */\n");
  strcat(wr_strval,"/*       event was transmitted.                                      */\n");
  return(0);
}
