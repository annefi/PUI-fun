/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: ccr.h,v 1.4 1998/10/20 22:30:09 asc Exp  */

#include "ccr.h"
#include "df.h"

int32 vgrp_id_ccr;
static int32 vdata_id_ccr;

  /* 1217 is the size of ccr.h + 1 added line */
char Vgrp_descrp_ccr_entry[1217];

/****----  init create function  ----****/

int32 init_cr_ccr(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_ccr();

  void print_ccr_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_ccr = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_ccr_error("init_cr_ccr -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_ccr, "VG_ccr_entry"); 
  Vsetclass(vgrp_id_ccr, "VG_CCR");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_ccr_entry" )) ==FAIL) {
    print_ccr_error("init_cr_ccr -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_ccr(Vgrp_descrp_ccr_entry);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_ccr_error("init_cr_ccr -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_ccr_entry, sizeof(Vgrp_descrp_ccr_entry))) ==FAIL) {
    print_ccr_error("init_cr_ccr -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_ccr = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_ccr_error("init_cr_ccr -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_ccr, "ccr_entry");
  VSsetclass(vdata_id_ccr, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_ccr, vdata_id_ccr)) ==FAIL) {
    print_ccr_error("init_cr_ccr -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_ccr, "start", DFNT_UINT32, (1) )) {
    print_ccr_error("init_cr_ccr -> VSfdefine: Couldn't define start");
    retval = -1;
  }
  if (VSfdefine(vdata_id_ccr, "end", DFNT_UINT32, (1) )) {
    print_ccr_error("init_cr_ccr -> VSfdefine: Couldn't define end");
    retval = -1;
  }
  if (VSfdefine(vdata_id_ccr, "slope", DFNT_FLOAT64, (1) )) {
    print_ccr_error("init_cr_ccr -> VSfdefine: Couldn't define slope");
    retval = -1;
  }
  if (VSfdefine(vdata_id_ccr, "offset", DFNT_FLOAT64, (1) )) {
    print_ccr_error("init_cr_ccr -> VSfdefine: Couldn't define offset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_ccr, "cdh", DFNT_UINT8, (1) )) {
    print_ccr_error("init_cr_ccr -> VSfdefine: Couldn't define cdh");
    retval = -1;
  }
  if (VSfdefine(vdata_id_ccr, "year", DFNT_UINT16, (1) )) {
    print_ccr_error("init_cr_ccr -> VSfdefine: Couldn't define year");
    retval = -1;
  }
  if (VSfdefine(vdata_id_ccr, "doy", DFNT_UINT16, (1) )) {
    print_ccr_error("init_cr_ccr -> VSfdefine: Couldn't define doy");
    retval = -1;
  }

  if (VSsetfields(vdata_id_ccr,"start, end, slope, offset, cdh, year, doy")){
    print_ccr_error("init_cr_ccr -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_ccr(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_ccr(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_ccr(struct ccr_entry ccr_entry_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_ccr_error();
void pack_ccr();

  odata = (uint8 *) malloc(sizeof(struct ccr_entry));
  pack_ccr(odata, &ccr_entry_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_ccr, recnum)==-1) {
		print_ccr_error("write_ccr -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_ccr, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_ccr_error("write_ccr -> VSwrite: Couldn't write data.");

  memset(&ccr_entry_struc, 0, sizeof(struct ccr_entry));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_ccr()
{
  VSdetach(vdata_id_ccr);
  Vdetach(vgrp_id_ccr);
}

/*----     init access function    ----*/

int32 init_acc_ccr(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_ccr_error();


  if ((vdata_ref = VSfind(hdf_fp, "ccr_entry")) <= 0 ) {
    print_ccr_error("init_acc_ccr -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_ccr = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_ccr_error("init_acc_ccr -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_ccr, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_ccr,"start, end, slope, offset, cdh, year, doy")) {
      print_ccr_error("init_acc_ccr -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_ccr(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_ccr(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_ccr(struct ccr_entry *ccr_entry_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_ccr_error();
void unpack_ccr();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct ccr_entry));
  VSinquire(vdata_id_ccr, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_ccr, recnum_rd)==FAIL) {
          print_ccr_error("read_ccr -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_ccr, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_ccr_error("read_ccr -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_ccr(odata, ccr_entry_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_ccr()
{
  VSdetach(vdata_id_ccr);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_ccr(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_ccr_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_ccr_entry" )) ==FAIL)
    print_ccr_error("rd_Vgrp_ccr -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_ccr_error("rd_Vgrp_ccr -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_ccr_error("rd_Vgrp_ccr -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_ccr_error("rd_Vgrp_ccr -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_ccr_entry, HDstrlen(Vgrp_descrp_ccr_entry)) ==FAIL)
    print_ccr_error("rd_Vgrp_ccr -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_ccr_entry);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_ccr_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_ccr.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_ccr(uint8 *data, struct ccr_entry *ccr_entry_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &ccr_entry_ptr->start, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ccr_entry_ptr->end, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &ccr_entry_ptr->slope, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &ccr_entry_ptr->offset, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &ccr_entry_ptr->cdh, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &ccr_entry_ptr->year, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &ccr_entry_ptr->doy, ((2)*(1)) );
   ptr+= ((2)*(1));
}

/*----   unpack function    ----*/

void unpack_ccr(uint8 *data, struct ccr_entry *ccr_entry_ptr)
{
int32 ptr=0;

   memcpy(&ccr_entry_ptr->start, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ccr_entry_ptr->end, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&ccr_entry_ptr->slope, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&ccr_entry_ptr->offset, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&ccr_entry_ptr->cdh, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&ccr_entry_ptr->year, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&ccr_entry_ptr->doy, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
}
int32 get_vgrp_id_ccr() {return(vgrp_id_ccr);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_ccr(char *wr_strval)
{
  strcpy(wr_strval, "The file 'ccr.h' is shown below, it was used to create the data in the Vgroup named 'VG_ccr_entry'.\n\n");
  strcat(wr_strval,"/* Id: ccr.h,v 1.4 1998/10/20 22:30:09 asc Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* The values here are used to convert the S/C clock values into seconds */\n");
  strcat(wr_strval,"/* since the S/C EPOCH, which was a short time after ACE launch */\n");
  strcat(wr_strval,"/* S/C_EPOCH_TIME = SC_clock * SLOPE + OFFSET */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* The offset between S/C_EPOCH and ACE_EPOCH is 52069704.604 seconds */\n");
  strcat(wr_strval,"/* ACE_EPOCH is seconds since Jan 1, 1996 */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* the start and end variables indicate the range of validity of the */\n");
  strcat(wr_strval,"/* slope and offset data. Generally, the ACE Flight Dynamics team will */\n");
  strcat(wr_strval,"/* generate a new set of parameters for each 24-hour period */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct ccr_entry {\n");
  strcat(wr_strval,"    uint32   start;    /* Start of range in S/C clock ticks */\n");
  strcat(wr_strval,"    uint32   end;      /* End of range in S/C clock ticks */\n");
  strcat(wr_strval,"    float64  slope;    /* slope for linear fit */\n");
  strcat(wr_strval,"    float64  offset;   /* offset for linear fit */\n");
  strcat(wr_strval,"    uint8    cdh;      /* =1: C&DH A, =2: C&DH B, error otherwise */\n");
  strcat(wr_strval,"    uint16   year;     /* 4 digit year for product */\n");
  strcat(wr_strval,"    uint16   doy;      /* Day of Year for product */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
