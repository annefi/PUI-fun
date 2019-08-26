/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: epam_br.h,v 1.6 1998/07/24 17:01:41 ad Exp  */

#include "epam_br.h"
#include "df.h"

int32 vgrp_id_epam_br;
static int32 vdata_id_epam_br;

  /* 1049 is the size of epam_br.h + 1 added line */
char Vgrp_descrp_Epam_br[1049];

/****----  init create function  ----****/

int32 init_cr_epam_br(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_epam_br();

  void print_epam_br_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_epam_br = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_epam_br_error("init_cr_epam_br -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_epam_br, "VG_Epam_br"); 
  Vsetclass(vgrp_id_epam_br, "VG_EPAM_BR");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_Epam_br" )) ==FAIL) {
    print_epam_br_error("init_cr_epam_br -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_epam_br(Vgrp_descrp_Epam_br);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_epam_br_error("init_cr_epam_br -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_Epam_br, sizeof(Vgrp_descrp_Epam_br))) ==FAIL) {
    print_epam_br_error("init_cr_epam_br -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_epam_br = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_epam_br_error("init_cr_epam_br -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_epam_br, "Epam_br");
  VSsetclass(vdata_id_epam_br, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_epam_br, vdata_id_epam_br)) ==FAIL) {
    print_epam_br_error("init_cr_epam_br -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_epam_br, "bin_start", DFNT_FLOAT64, (1) )) {
    print_epam_br_error("init_cr_epam_br -> VSfdefine: Couldn't define bin_start");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_br, "bin_end", DFNT_FLOAT64, (1) )) {
    print_epam_br_error("init_cr_epam_br -> VSfdefine: Couldn't define bin_end");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_br, "P1", DFNT_FLOAT32, (1) )) {
    print_epam_br_error("init_cr_epam_br -> VSfdefine: Couldn't define P1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_br, "P3", DFNT_FLOAT32, (1) )) {
    print_epam_br_error("init_cr_epam_br -> VSfdefine: Couldn't define P3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_br, "P5", DFNT_FLOAT32, (1) )) {
    print_epam_br_error("init_cr_epam_br -> VSfdefine: Couldn't define P5");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_br, "P7", DFNT_FLOAT32, (1) )) {
    print_epam_br_error("init_cr_epam_br -> VSfdefine: Couldn't define P7");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_br, "DE1", DFNT_FLOAT32, (1) )) {
    print_epam_br_error("init_cr_epam_br -> VSfdefine: Couldn't define DE1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_br, "DE4", DFNT_FLOAT32, (1) )) {
    print_epam_br_error("init_cr_epam_br -> VSfdefine: Couldn't define DE4");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_br, "W1", DFNT_FLOAT32, (1) )) {
    print_epam_br_error("init_cr_epam_br -> VSfdefine: Couldn't define W1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_br, "fp6p", DFNT_FLOAT32, (1) )) {
    print_epam_br_error("init_cr_epam_br -> VSfdefine: Couldn't define fp6p");
    retval = -1;
  }
  if (VSfdefine(vdata_id_epam_br, "EPAM_livetime", DFNT_FLOAT32, (1) )) {
    print_epam_br_error("init_cr_epam_br -> VSfdefine: Couldn't define EPAM_livetime");
    retval = -1;
  }

  if (VSsetfields(vdata_id_epam_br,"bin_start, bin_end, P1, P3, P5, P7, DE1, DE4, W1, fp6p, EPAM_livetime")){
    print_epam_br_error("init_cr_epam_br -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_epam_br(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_epam_br(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_epam_br(struct Epam_br Epam_br_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_epam_br_error();
void pack_epam_br();

  odata = (uint8 *) malloc(sizeof(struct Epam_br));
  pack_epam_br(odata, &Epam_br_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_epam_br, recnum)==-1) {
		print_epam_br_error("write_epam_br -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_epam_br, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_epam_br_error("write_epam_br -> VSwrite: Couldn't write data.");

  memset(&Epam_br_struc, 0, sizeof(struct Epam_br));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_epam_br()
{
  VSdetach(vdata_id_epam_br);
  Vdetach(vgrp_id_epam_br);
}

/*----     init access function    ----*/

int32 init_acc_epam_br(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_epam_br_error();


  if ((vdata_ref = VSfind(hdf_fp, "Epam_br")) <= 0 ) {
    print_epam_br_error("init_acc_epam_br -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_epam_br = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_epam_br_error("init_acc_epam_br -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_epam_br, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_epam_br,"bin_start, bin_end, P1, P3, P5, P7, DE1, DE4, W1, fp6p, EPAM_livetime")) {
      print_epam_br_error("init_acc_epam_br -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_epam_br(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_epam_br(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_epam_br(struct Epam_br *Epam_br_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_epam_br_error();
void unpack_epam_br();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct Epam_br));
  VSinquire(vdata_id_epam_br, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_epam_br, recnum_rd)==FAIL) {
          print_epam_br_error("read_epam_br -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_epam_br, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_epam_br_error("read_epam_br -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_epam_br(odata, Epam_br_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_epam_br()
{
  VSdetach(vdata_id_epam_br);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_epam_br(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_epam_br_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_Epam_br" )) ==FAIL)
    print_epam_br_error("rd_Vgrp_epam_br -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_epam_br_error("rd_Vgrp_epam_br -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_epam_br_error("rd_Vgrp_epam_br -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_epam_br_error("rd_Vgrp_epam_br -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_Epam_br, HDstrlen(Vgrp_descrp_Epam_br)) ==FAIL)
    print_epam_br_error("rd_Vgrp_epam_br -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_Epam_br);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_epam_br_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_epam_br.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_epam_br(uint8 *data, struct Epam_br *Epam_br_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &Epam_br_ptr->bin_start, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &Epam_br_ptr->bin_end, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &Epam_br_ptr->P1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &Epam_br_ptr->P3, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &Epam_br_ptr->P5, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &Epam_br_ptr->P7, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &Epam_br_ptr->DE1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &Epam_br_ptr->DE4, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &Epam_br_ptr->W1, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &Epam_br_ptr->fp6p, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &Epam_br_ptr->EPAM_livetime, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_epam_br(uint8 *data, struct Epam_br *Epam_br_ptr)
{
int32 ptr=0;

   memcpy(&Epam_br_ptr->bin_start, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&Epam_br_ptr->bin_end, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&Epam_br_ptr->P1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&Epam_br_ptr->P3, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&Epam_br_ptr->P5, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&Epam_br_ptr->P7, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&Epam_br_ptr->DE1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&Epam_br_ptr->DE4, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&Epam_br_ptr->W1, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&Epam_br_ptr->fp6p, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&Epam_br_ptr->EPAM_livetime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_epam_br() {return(vgrp_id_epam_br);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_epam_br(char *wr_strval)
{
  strcpy(wr_strval, "The file 'epam_br.h' is shown below, it was used to create the data in the Vgroup named 'VG_Epam_br'.\n\n");
  strcat(wr_strval,"/* Id: epam_br.h,v 1.6 1998/07/24 17:01:41 ad Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct Epam_br\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  float64 bin_start;            /* beginning of bin. ACE epoch */\n");
  strcat(wr_strval,"  float64 bin_end;            /* end of bin. ACE epoch */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  float32 P1;              /* Flux of .047 - .065 Mev ions EPAM */\n");
  strcat(wr_strval,"  float32 P3;              /* Flux of .112 - .187 Mev ions EPAM */\n");
  strcat(wr_strval,"  float32 P5;              /* Flux of .310 - .580 Mev ions EPAM */\n");
  strcat(wr_strval,"  float32 P7;              /* Flux of 1.06 - 1.91 MeV ions EPAM */\n");
  strcat(wr_strval,"  float32 DE1;             /* Flux of .038 - .053 Mev electrons EPAM */\n");
  strcat(wr_strval,"  float32 DE4;             /* Flux of .175 - .315 Mev electrons EPAM */\n");
  strcat(wr_strval,"  float32 W1;              /* Flux of .480 - .966 Mev protons EPAM */\n");
  strcat(wr_strval,"  float32 fp6p;            /* Flux of .761 - 1.22 Mev protons EPAM */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  float32 EPAM_livetime;   /* livetime (seconds) for these measurements. */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
