/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: uleis_evnt.h,v 1.8 1997/06/11 17:09:21 jeff Exp  */

#include "uleis_evnt.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_uleis_evnt;
static int32 vdata_id_uleis_evnt;

static int32 sds_id_uleis_evnt1;

  /* 905 is the size of uleis_evnt.h + 1 added line */
char Vgrp_descrp_UEvntSet[905];

/****----  init create function  ----****/

int32 init_cr_uleis_evnt(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[5];
  int32 rank;

  int32 wr_Vgrp_desc_uleis_evnt();

  void print_uleis_evnt_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_uleis_evnt = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_uleis_evnt_error("init_cr_uleis_evnt -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_uleis_evnt, "VG_UEvntSet"); 
  Vsetclass(vgrp_id_uleis_evnt, "VG_ULEIS_EVNT");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_UEvntSet" )) ==FAIL) {
    print_uleis_evnt_error("init_cr_uleis_evnt -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_uleis_evnt(Vgrp_descrp_UEvntSet);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_uleis_evnt_error("init_cr_uleis_evnt -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_UEvntSet, sizeof(Vgrp_descrp_UEvntSet))) ==FAIL) {
    print_uleis_evnt_error("init_cr_uleis_evnt -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_uleis_evnt = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_uleis_evnt_error("init_cr_uleis_evnt -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_uleis_evnt, "UEvntSet");
  VSsetclass(vdata_id_uleis_evnt, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_uleis_evnt, vdata_id_uleis_evnt)) ==FAIL) {
    print_uleis_evnt_error("init_cr_uleis_evnt -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_uleis_evnt, "output_sctime", DFNT_UINT32, (1) )) {
    print_uleis_evnt_error("init_cr_uleis_evnt -> VSfdefine: Couldn't define output_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_evnt, "collect_sctime", DFNT_UINT32, (1) )) {
    print_uleis_evnt_error("init_cr_uleis_evnt -> VSfdefine: Couldn't define collect_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_evnt, "QAC", DFNT_UINT32, (1) )) {
    print_uleis_evnt_error("init_cr_uleis_evnt -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }

  if (VSsetfields(vdata_id_uleis_evnt,"output_sctime, collect_sctime, QAC")){
    print_uleis_evnt_error("init_cr_uleis_evnt -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 5;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = U_SPINS;
  dim_sizes[2] = U_SECTRS;
  dim_sizes[3] = U_EVTSECTR;
  dim_sizes[4] = U_EVNT_NUM;
  if((sds_id_uleis_evnt1 = SDcreate(sd_id, "UEvntSet_event", DFNT_UINT16, rank, dim_sizes)) == FAIL)
    print_uleis_evnt_error("init_cr_uleis_evnt -> SDcreate: Couldn't create UEvntSet_event");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_uleis_evnt1)) == FAIL)
    print_uleis_evnt_error("init_cr_uleis_evnt -> SDidtoref: Couldn't get ref for UEvntSet_event");

  if((Vaddtagref(vgrp_id_uleis_evnt, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_uleis_evnt_error("init_cr_uleis_evnt -> Vaddtagref: Couldn't add SDS UEvntSet_event to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_uleis_evnt(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_uleis_evnt(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_uleis_evnt(struct UEvntSet UEvntSet_struc, int32 recnum)
{
  int32 start[5], edges[5];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_uleis_evnt_error();
void pack_uleis_evnt();

  odata = (uint8 *) malloc(sizeof(struct UEvntSet));
  pack_uleis_evnt(odata, &UEvntSet_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_uleis_evnt, recnum)==-1) {
		print_uleis_evnt_error("write_uleis_evnt -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_uleis_evnt, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_uleis_evnt_error("write_uleis_evnt -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  start[3] = 0;
  start[4] = 0;
  edges[0] = 1;

  edges[1] = U_SPINS;
  edges[2] = U_SECTRS;
  edges[3] = U_EVTSECTR;
  edges[4] = U_EVNT_NUM;
  if (SDwritedata(sds_id_uleis_evnt1,start,NULL,edges, (VOIDP)(UEvntSet_struc.event)) ==FAIL)
    print_uleis_evnt_error("write_uleis_evnt -> SDwritedata: Problem writing event data.");

  memset(&UEvntSet_struc, 0, sizeof(struct UEvntSet));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_uleis_evnt()
{
  VSdetach(vdata_id_uleis_evnt);
  Vdetach(vgrp_id_uleis_evnt);
  SDendaccess(sds_id_uleis_evnt1);
}

/*----     init access function    ----*/

int32 init_acc_uleis_evnt(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_uleis_evnt_error();

  if((sds_index1=SDnametoindex(sd_id, "UEvntSet_event" )) ==FAIL) {
      print_uleis_evnt_error("init_acc_uleis_evnt -> SDnametoindex: Couldn't find UEvntSet_event");
      return(-1);
  }
  if((sds_id_uleis_evnt1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_uleis_evnt_error("init_acc_uleis_evnt -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "UEvntSet")) <= 0 ) {
    print_uleis_evnt_error("init_acc_uleis_evnt -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_uleis_evnt = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_uleis_evnt_error("init_acc_uleis_evnt -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_uleis_evnt, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_uleis_evnt,"output_sctime, collect_sctime, QAC")) {
      print_uleis_evnt_error("init_acc_uleis_evnt -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_uleis_evnt(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_uleis_evnt(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_uleis_evnt(struct UEvntSet *UEvntSet_struc, int32 recnum_rd)
{
int32 start[5], edges[5];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_uleis_evnt_error();
void unpack_uleis_evnt();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;
  start[3] = 0;
  start[4] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct UEvntSet));
  VSinquire(vdata_id_uleis_evnt, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_uleis_evnt, recnum_rd)==FAIL) {
          print_uleis_evnt_error("read_uleis_evnt -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = U_SPINS;
  edges[2] = U_SECTRS;
  edges[3] = U_EVTSECTR;
  edges[4] = U_EVNT_NUM;

  if(SDreaddata(sds_id_uleis_evnt1,start,NULL,edges, (VOIDP)(UEvntSet_struc->event )) ==FAIL) {
    print_uleis_evnt_error("read_uleis_evnt -> SDreaddata: Couldn't read event");
    retval = -1;
  }
  if(VSread(vdata_id_uleis_evnt, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_uleis_evnt_error("read_uleis_evnt -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_uleis_evnt(odata, UEvntSet_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_uleis_evnt()
{
  VSdetach(vdata_id_uleis_evnt);
  SDendaccess(sds_id_uleis_evnt1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_uleis_evnt(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_uleis_evnt_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_UEvntSet" )) ==FAIL)
    print_uleis_evnt_error("rd_Vgrp_uleis_evnt -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_uleis_evnt_error("rd_Vgrp_uleis_evnt -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_uleis_evnt_error("rd_Vgrp_uleis_evnt -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_uleis_evnt_error("rd_Vgrp_uleis_evnt -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_UEvntSet, HDstrlen(Vgrp_descrp_UEvntSet)) ==FAIL)
    print_uleis_evnt_error("rd_Vgrp_uleis_evnt -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_UEvntSet);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_uleis_evnt_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_uleis_evnt.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_uleis_evnt(uint8 *data, struct UEvntSet *UEvntSet_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &UEvntSet_ptr->output_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &UEvntSet_ptr->collect_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &UEvntSet_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_uleis_evnt(uint8 *data, struct UEvntSet *UEvntSet_ptr)
{
int32 ptr=0;

   memcpy(&UEvntSet_ptr->output_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&UEvntSet_ptr->collect_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&UEvntSet_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_uleis_evnt() {return(vgrp_id_uleis_evnt);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_uleis_evnt(char *wr_strval)
{
  strcpy(wr_strval, "The file 'uleis_evnt.h' is shown below, it was used to create the data in the Vgroup named 'VG_UEvntSet'.\n\n");
  strcat(wr_strval,"/* Id: uleis_evnt.h,v 1.8 1997/06/11 17:09:21 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define U_BYT_EVNT_SIZE    21		/* 21 bytes per event */\n");
  strcat(wr_strval,"#define U_EVNT_NUM         14		/* number of 12 bit events */\n");
  strcat(wr_strval,"#define U_EVTSECTR          6 		/* 6 events per sector */\n");
  strcat(wr_strval,"#define U_SECTRS            8		/* 8 sectors, 0-7 */\n");
  strcat(wr_strval,"#define U_SPINS            10 		/* 10 spins, 1-10 */\n");
  strcat(wr_strval," \n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct UEvntSet\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 output_sctime;		/* time for beginning of data output cycle */\n");
  strcat(wr_strval,"  uint32 collect_sctime;	/* time for beginning of data collection */\n");
  strcat(wr_strval,"  uint32 QAC;			/* number of bad frames in this cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"   /* Events: 10 spins, 8 sectors, 6 events, event num (14) */\n");
  strcat(wr_strval,"  uint16 event[U_SPINS][U_SECTRS][U_EVTSECTR][U_EVNT_NUM];\n");
  strcat(wr_strval,"};\n");
  return(0);
}
