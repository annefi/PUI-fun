/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: sepica_rwbr.h,v 1.3 1998/02/18 21:55:37 asc Exp  */

#include "sepica_rwbr.h"
#include "df.h"

int32 vgrp_id_sepica_rwbr;
static int32 vdata_id_sepica_rwbr;

  /* 1192 is the size of sepica_rwbr.h + 1 added line */
char Vgrp_descrp_Sepica_rwbr[1192];

/****----  init create function  ----****/

int32 init_cr_sepica_rwbr(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_sepica_rwbr();

  void print_sepica_rwbr_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_sepica_rwbr = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_sepica_rwbr, "VG_Sepica_rwbr"); 
  Vsetclass(vgrp_id_sepica_rwbr, "VG_SEPICA_RWBR");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_Sepica_rwbr" )) ==FAIL) {
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_sepica_rwbr(Vgrp_descrp_Sepica_rwbr);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_Sepica_rwbr, sizeof(Vgrp_descrp_Sepica_rwbr))) ==FAIL) {
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_sepica_rwbr = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_sepica_rwbr, "Sepica_rwbr");
  VSsetclass(vdata_id_sepica_rwbr, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_sepica_rwbr, vdata_id_sepica_rwbr)) ==FAIL) {
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_sepica_rwbr, "bin_start", DFNT_FLOAT64, (1) )) {
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> VSfdefine: Couldn't define bin_start");
    retval = -1;
  }
  if (VSfdefine(vdata_id_sepica_rwbr, "bin_end", DFNT_FLOAT64, (1) )) {
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> VSfdefine: Couldn't define bin_end");
    retval = -1;
  }
  if (VSfdefine(vdata_id_sepica_rwbr, "H_lo", DFNT_FLOAT32, (1) )) {
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> VSfdefine: Couldn't define H_lo");
    retval = -1;
  }
  if (VSfdefine(vdata_id_sepica_rwbr, "H_hi", DFNT_FLOAT32, (1) )) {
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> VSfdefine: Couldn't define H_hi");
    retval = -1;
  }
  if (VSfdefine(vdata_id_sepica_rwbr, "He_lo", DFNT_FLOAT32, (1) )) {
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> VSfdefine: Couldn't define He_lo");
    retval = -1;
  }
  if (VSfdefine(vdata_id_sepica_rwbr, "He_hi", DFNT_FLOAT32, (1) )) {
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> VSfdefine: Couldn't define He_hi");
    retval = -1;
  }
  if (VSfdefine(vdata_id_sepica_rwbr, "C", DFNT_FLOAT32, (1) )) {
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> VSfdefine: Couldn't define C");
    retval = -1;
  }
  if (VSfdefine(vdata_id_sepica_rwbr, "O", DFNT_FLOAT32, (1) )) {
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> VSfdefine: Couldn't define O");
    retval = -1;
  }
  if (VSfdefine(vdata_id_sepica_rwbr, "Mg_Si", DFNT_FLOAT32, (1) )) {
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> VSfdefine: Couldn't define Mg_Si");
    retval = -1;
  }
  if (VSfdefine(vdata_id_sepica_rwbr, "Fe", DFNT_FLOAT32, (1) )) {
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> VSfdefine: Couldn't define Fe");
    retval = -1;
  }
  if (VSfdefine(vdata_id_sepica_rwbr, "livetime", DFNT_FLOAT32, (1) )) {
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> VSfdefine: Couldn't define livetime");
    retval = -1;
  }

  if (VSsetfields(vdata_id_sepica_rwbr,"bin_start, bin_end, H_lo, H_hi, He_lo, He_hi, C, O, Mg_Si, Fe, livetime")){
    print_sepica_rwbr_error("init_cr_sepica_rwbr -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_sepica_rwbr(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_sepica_rwbr(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_sepica_rwbr(struct Sepica_rwbr Sepica_rwbr_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_sepica_rwbr_error();
void pack_sepica_rwbr();

  odata = (uint8 *) malloc(sizeof(struct Sepica_rwbr));
  pack_sepica_rwbr(odata, &Sepica_rwbr_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_sepica_rwbr, recnum)==-1) {
		print_sepica_rwbr_error("write_sepica_rwbr -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_sepica_rwbr, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_sepica_rwbr_error("write_sepica_rwbr -> VSwrite: Couldn't write data.");

  memset(&Sepica_rwbr_struc, 0, sizeof(struct Sepica_rwbr));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_sepica_rwbr()
{
  VSdetach(vdata_id_sepica_rwbr);
  Vdetach(vgrp_id_sepica_rwbr);
}

/*----     init access function    ----*/

int32 init_acc_sepica_rwbr(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_sepica_rwbr_error();


  if ((vdata_ref = VSfind(hdf_fp, "Sepica_rwbr")) <= 0 ) {
    print_sepica_rwbr_error("init_acc_sepica_rwbr -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_sepica_rwbr = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_sepica_rwbr_error("init_acc_sepica_rwbr -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_sepica_rwbr, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_sepica_rwbr,"bin_start, bin_end, H_lo, H_hi, He_lo, He_hi, C, O, Mg_Si, Fe, livetime")) {
      print_sepica_rwbr_error("init_acc_sepica_rwbr -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_sepica_rwbr(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_sepica_rwbr(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_sepica_rwbr(struct Sepica_rwbr *Sepica_rwbr_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_sepica_rwbr_error();
void unpack_sepica_rwbr();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct Sepica_rwbr));
  VSinquire(vdata_id_sepica_rwbr, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_sepica_rwbr, recnum_rd)==FAIL) {
          print_sepica_rwbr_error("read_sepica_rwbr -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_sepica_rwbr, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_sepica_rwbr_error("read_sepica_rwbr -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_sepica_rwbr(odata, Sepica_rwbr_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_sepica_rwbr()
{
  VSdetach(vdata_id_sepica_rwbr);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_sepica_rwbr(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_sepica_rwbr_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_Sepica_rwbr" )) ==FAIL)
    print_sepica_rwbr_error("rd_Vgrp_sepica_rwbr -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_sepica_rwbr_error("rd_Vgrp_sepica_rwbr -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_sepica_rwbr_error("rd_Vgrp_sepica_rwbr -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_sepica_rwbr_error("rd_Vgrp_sepica_rwbr -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_Sepica_rwbr, HDstrlen(Vgrp_descrp_Sepica_rwbr)) ==FAIL)
    print_sepica_rwbr_error("rd_Vgrp_sepica_rwbr -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_Sepica_rwbr);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_sepica_rwbr_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_sepica_rwbr.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_sepica_rwbr(uint8 *data, struct Sepica_rwbr *Sepica_rwbr_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &Sepica_rwbr_ptr->bin_start, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &Sepica_rwbr_ptr->bin_end, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &Sepica_rwbr_ptr->H_lo, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &Sepica_rwbr_ptr->H_hi, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &Sepica_rwbr_ptr->He_lo, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &Sepica_rwbr_ptr->He_hi, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &Sepica_rwbr_ptr->C, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &Sepica_rwbr_ptr->O, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &Sepica_rwbr_ptr->Mg_Si, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &Sepica_rwbr_ptr->Fe, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &Sepica_rwbr_ptr->livetime, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_sepica_rwbr(uint8 *data, struct Sepica_rwbr *Sepica_rwbr_ptr)
{
int32 ptr=0;

   memcpy(&Sepica_rwbr_ptr->bin_start, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&Sepica_rwbr_ptr->bin_end, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&Sepica_rwbr_ptr->H_lo, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&Sepica_rwbr_ptr->H_hi, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&Sepica_rwbr_ptr->He_lo, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&Sepica_rwbr_ptr->He_hi, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&Sepica_rwbr_ptr->C, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&Sepica_rwbr_ptr->O, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&Sepica_rwbr_ptr->Mg_Si, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&Sepica_rwbr_ptr->Fe, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&Sepica_rwbr_ptr->livetime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_sepica_rwbr() {return(vgrp_id_sepica_rwbr);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_sepica_rwbr(char *wr_strval)
{
  strcpy(wr_strval, "The file 'sepica_rwbr.h' is shown below, it was used to create the data in the Vgroup named 'VG_Sepica_rwbr'.\n\n");
  strcat(wr_strval,"/* Id: sepica_rwbr.h,v 1.3 1998/02/18 21:55:37 asc Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define SEP_GEOMFAC .18   /* cm2 - sr */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct Sepica_rwbr\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  float64 bin_start;  /* beginning of bin. # of sec since Jan 1 1996 UTC */\n");
  strcat(wr_strval,"  float64 bin_end;  /* end of bin. # of sec since Jan 1 1996 UTC */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    /* rate for indicated channel, negative values indicate */\n");
  strcat(wr_strval,"    /* missing data */\n");
  strcat(wr_strval,"    float32 H_lo;             /* low Energy (0.1-0.8 Mev/n) H channel */\n");
  strcat(wr_strval,"    float32 H_hi;             /* high Energy (0.8-9.0 Mev/n) H channel */\n");
  strcat(wr_strval,"    float32 He_lo;            /* low Energy (0.025-0.75 MeV/n) He channel */\n");
  strcat(wr_strval,"    float32 He_hi;            /* high Energy (0.75-14 MeV/n) He channel */\n");
  strcat(wr_strval,"    float32 C;                /* (1.5-25 MeV/n) C channel */\n");
  strcat(wr_strval,"    float32 O;                /* (1.12-18.8 MeV/n) O channel */\n");
  strcat(wr_strval,"    float32 Mg_Si;            /* (0.7-11.5 MeV/n) Mg,Si channel */\n");
  strcat(wr_strval,"    float32 Fe;               /* (0.35-5.75 MeV/n) Fe channel */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    float32 livetime;       /* livetime for this cycle */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
