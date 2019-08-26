/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: uleis_br_out.h,v 1.2 1997/09/22 16:35:21 steves Exp  */

#include "uleis_br_out.h"
#include "df.h"

int32 vgrp_id_uleis_br_out;
static int32 vdata_id_uleis_br_out;

  /* 572 is the size of uleis_br_out.h + 1 added line */
char Vgrp_descrp_Uleis_br_out[572];

/****----  init create function  ----****/

int32 init_cr_uleis_br_out(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_uleis_br_out();

  void print_uleis_br_out_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_uleis_br_out = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_uleis_br_out_error("init_cr_uleis_br_out -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_uleis_br_out, "VG_Uleis_br_out"); 
  Vsetclass(vgrp_id_uleis_br_out, "VG_ULEIS_BR_OUT");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_Uleis_br_out" )) ==FAIL) {
    print_uleis_br_out_error("init_cr_uleis_br_out -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_uleis_br_out(Vgrp_descrp_Uleis_br_out);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_uleis_br_out_error("init_cr_uleis_br_out -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_Uleis_br_out, sizeof(Vgrp_descrp_Uleis_br_out))) ==FAIL) {
    print_uleis_br_out_error("init_cr_uleis_br_out -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_uleis_br_out = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_uleis_br_out_error("init_cr_uleis_br_out -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_uleis_br_out, "Uleis_br_out");
  VSsetclass(vdata_id_uleis_br_out, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_uleis_br_out, vdata_id_uleis_br_out)) ==FAIL) {
    print_uleis_br_out_error("init_cr_uleis_br_out -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_uleis_br_out, "bin_start", DFNT_FLOAT64, (1) )) {
    print_uleis_br_out_error("init_cr_uleis_br_out -> VSfdefine: Couldn't define bin_start");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_br_out, "bin_end", DFNT_FLOAT64, (1) )) {
    print_uleis_br_out_error("init_cr_uleis_br_out -> VSfdefine: Couldn't define bin_end");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_br_out, "ULEIS_livetime", DFNT_FLOAT32, (1) )) {
    print_uleis_br_out_error("init_cr_uleis_br_out -> VSfdefine: Couldn't define ULEIS_livetime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_br_out, "rate_assign", DFNT_UINT16, (9) )) {
    print_uleis_br_out_error("init_cr_uleis_br_out -> VSfdefine: Couldn't define rate_assign");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_br_out, "brws_rates", DFNT_FLOAT32, (9) )) {
    print_uleis_br_out_error("init_cr_uleis_br_out -> VSfdefine: Couldn't define brws_rates");
    retval = -1;
  }

  if (VSsetfields(vdata_id_uleis_br_out,"bin_start, bin_end, ULEIS_livetime, rate_assign, brws_rates")){
    print_uleis_br_out_error("init_cr_uleis_br_out -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_uleis_br_out(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_uleis_br_out(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_uleis_br_out(struct Uleis_br_out Uleis_br_out_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_uleis_br_out_error();
void pack_uleis_br_out();

  odata = (uint8 *) malloc(sizeof(struct Uleis_br_out));
  pack_uleis_br_out(odata, &Uleis_br_out_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_uleis_br_out, recnum)==-1) {
		print_uleis_br_out_error("write_uleis_br_out -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_uleis_br_out, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_uleis_br_out_error("write_uleis_br_out -> VSwrite: Couldn't write data.");

  memset(&Uleis_br_out_struc, 0, sizeof(struct Uleis_br_out));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_uleis_br_out()
{
  VSdetach(vdata_id_uleis_br_out);
  Vdetach(vgrp_id_uleis_br_out);
}

/*----     init access function    ----*/

int32 init_acc_uleis_br_out(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_uleis_br_out_error();


  if ((vdata_ref = VSfind(hdf_fp, "Uleis_br_out")) <= 0 ) {
    print_uleis_br_out_error("init_acc_uleis_br_out -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_uleis_br_out = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_uleis_br_out_error("init_acc_uleis_br_out -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_uleis_br_out, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_uleis_br_out,"bin_start, bin_end, ULEIS_livetime, rate_assign, brws_rates")) {
      print_uleis_br_out_error("init_acc_uleis_br_out -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_uleis_br_out(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_uleis_br_out(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_uleis_br_out(struct Uleis_br_out *Uleis_br_out_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_uleis_br_out_error();
void unpack_uleis_br_out();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct Uleis_br_out));
  VSinquire(vdata_id_uleis_br_out, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_uleis_br_out, recnum_rd)==FAIL) {
          print_uleis_br_out_error("read_uleis_br_out -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_uleis_br_out, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_uleis_br_out_error("read_uleis_br_out -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_uleis_br_out(odata, Uleis_br_out_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_uleis_br_out()
{
  VSdetach(vdata_id_uleis_br_out);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_uleis_br_out(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_uleis_br_out_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_Uleis_br_out" )) ==FAIL)
    print_uleis_br_out_error("rd_Vgrp_uleis_br_out -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_uleis_br_out_error("rd_Vgrp_uleis_br_out -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_uleis_br_out_error("rd_Vgrp_uleis_br_out -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_uleis_br_out_error("rd_Vgrp_uleis_br_out -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_Uleis_br_out, HDstrlen(Vgrp_descrp_Uleis_br_out)) ==FAIL)
    print_uleis_br_out_error("rd_Vgrp_uleis_br_out -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_Uleis_br_out);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_uleis_br_out_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_uleis_br_out.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_uleis_br_out(uint8 *data, struct Uleis_br_out *Uleis_br_out_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &Uleis_br_out_ptr->bin_start, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &Uleis_br_out_ptr->bin_end, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &Uleis_br_out_ptr->ULEIS_livetime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &Uleis_br_out_ptr->rate_assign[0], ((2)*(9)) );
   ptr+= ((2)*(9));
   memcpy(data+ptr, &Uleis_br_out_ptr->brws_rates[0], ((4)*(9)) );
   ptr+= ((4)*(9));
}

/*----   unpack function    ----*/

void unpack_uleis_br_out(uint8 *data, struct Uleis_br_out *Uleis_br_out_ptr)
{
int32 ptr=0;

   memcpy(&Uleis_br_out_ptr->bin_start, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&Uleis_br_out_ptr->bin_end, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&Uleis_br_out_ptr->ULEIS_livetime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&Uleis_br_out_ptr->rate_assign[0], data+ptr,  ((2)*(9)) );
   ptr+= ((2)*(9));
   memcpy(&Uleis_br_out_ptr->brws_rates[0], data+ptr,  ((4)*(9)) );
   ptr+= ((4)*(9));
}
int32 get_vgrp_id_uleis_br_out() {return(vgrp_id_uleis_br_out);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_uleis_br_out(char *wr_strval)
{
  strcpy(wr_strval, "The file 'uleis_br_out.h' is shown below, it was used to create the data in the Vgroup named 'VG_Uleis_br_out'.\n\n");
  strcat(wr_strval,"/* Id: uleis_br_out.h,v 1.2 1997/09/22 16:35:21 steves Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct Uleis_br_out\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  float64 bin_start;  /* beginning of bin. # of sec since Jan 1 1996 UTC */\n");
  strcat(wr_strval,"  float64 bin_end;    /* end of bin. # of sec since Jan 1 1996 UTC */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  float32 ULEIS_livetime;   /* livetime for this measurement. */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint16 rate_assign[9];\n");
  strcat(wr_strval,"  float32 brws_rates[9];\n");
  strcat(wr_strval,"};\n");
  return(0);
}
