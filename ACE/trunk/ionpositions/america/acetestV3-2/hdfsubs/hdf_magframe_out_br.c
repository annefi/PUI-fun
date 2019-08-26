/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: magframe_out_br.h,v 1.7 1998/04/16 18:32:30 ad Exp  */

#include "magframe_out_br.h"
#include "df.h"

int32 vgrp_id_mag_br;
static int32 vdata_id_mag_br;

  /* 923 is the size of magframe_out_br.h + 1 added line */
char Vgrp_descrp_MagFrm_out_br[923];

/****----  init create function  ----****/

int32 init_cr_mag_br(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_mag_br();

  void print_mag_br_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_mag_br = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_mag_br_error("init_cr_mag_br -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_mag_br, "VG_MagFrm_out_br"); 
  Vsetclass(vgrp_id_mag_br, "VG_MAGFRAME_OUT_BR");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_MagFrm_out_br" )) ==FAIL) {
    print_mag_br_error("init_cr_mag_br -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_mag_br(Vgrp_descrp_MagFrm_out_br);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_mag_br_error("init_cr_mag_br -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_MagFrm_out_br, sizeof(Vgrp_descrp_MagFrm_out_br))) ==FAIL) {
    print_mag_br_error("init_cr_mag_br -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_mag_br = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_mag_br_error("init_cr_mag_br -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_mag_br, "MagFrm_out_br");
  VSsetclass(vdata_id_mag_br, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_mag_br, vdata_id_mag_br)) ==FAIL) {
    print_mag_br_error("init_cr_mag_br -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_mag_br, "bin_start", DFNT_FLOAT64, (1) )) {
    print_mag_br_error("init_cr_mag_br -> VSfdefine: Couldn't define bin_start");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_br, "bin_end", DFNT_FLOAT64, (1) )) {
    print_mag_br_error("init_cr_mag_br -> VSfdefine: Couldn't define bin_end");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_br, "b_out", DFNT_FLOAT64, (3) )) {
    print_mag_br_error("init_cr_mag_br -> VSfdefine: Couldn't define b_out");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_br, "b_mag_av", DFNT_FLOAT64, (1) )) {
    print_mag_br_error("init_cr_mag_br -> VSfdefine: Couldn't define b_mag_av");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_br, "b_sigma", DFNT_FLOAT64, (1) )) {
    print_mag_br_error("init_cr_mag_br -> VSfdefine: Couldn't define b_sigma");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_br, "iflag_out", DFNT_UINT32, (1) )) {
    print_mag_br_error("init_cr_mag_br -> VSfdefine: Couldn't define iflag_out");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_br, "weight", DFNT_UINT8, (1) )) {
    print_mag_br_error("init_cr_mag_br -> VSfdefine: Couldn't define weight");
    retval = -1;
  }

  if (VSsetfields(vdata_id_mag_br,"bin_start, bin_end, b_out, b_mag_av, b_sigma, iflag_out, weight")){
    print_mag_br_error("init_cr_mag_br -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_mag_br(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_mag_br(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_mag_br(struct MagFrm_out_br MagFrm_out_br_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_mag_br_error();
void pack_mag_br();

  odata = (uint8 *) malloc(sizeof(struct MagFrm_out_br));
  pack_mag_br(odata, &MagFrm_out_br_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_mag_br, recnum)==-1) {
		print_mag_br_error("write_mag_br -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_mag_br, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_mag_br_error("write_mag_br -> VSwrite: Couldn't write data.");

  memset(&MagFrm_out_br_struc, 0, sizeof(struct MagFrm_out_br));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_mag_br()
{
  VSdetach(vdata_id_mag_br);
  Vdetach(vgrp_id_mag_br);
}

/*----     init access function    ----*/

int32 init_acc_mag_br(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_mag_br_error();


  if ((vdata_ref = VSfind(hdf_fp, "MagFrm_out_br")) <= 0 ) {
    print_mag_br_error("init_acc_mag_br -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_mag_br = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_mag_br_error("init_acc_mag_br -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_mag_br, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_mag_br,"bin_start, bin_end, b_out, b_mag_av, b_sigma, iflag_out, weight")) {
      print_mag_br_error("init_acc_mag_br -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_mag_br(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_mag_br(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_mag_br(struct MagFrm_out_br *MagFrm_out_br_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_mag_br_error();
void unpack_mag_br();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct MagFrm_out_br));
  VSinquire(vdata_id_mag_br, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_mag_br, recnum_rd)==FAIL) {
          print_mag_br_error("read_mag_br -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_mag_br, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_mag_br_error("read_mag_br -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_mag_br(odata, MagFrm_out_br_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_mag_br()
{
  VSdetach(vdata_id_mag_br);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_mag_br(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_mag_br_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_MagFrm_out_br" )) ==FAIL)
    print_mag_br_error("rd_Vgrp_mag_br -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_mag_br_error("rd_Vgrp_mag_br -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_mag_br_error("rd_Vgrp_mag_br -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_mag_br_error("rd_Vgrp_mag_br -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_MagFrm_out_br, HDstrlen(Vgrp_descrp_MagFrm_out_br)) ==FAIL)
    print_mag_br_error("rd_Vgrp_mag_br -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_MagFrm_out_br);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_mag_br_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_magframe_out_br.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_mag_br(uint8 *data, struct MagFrm_out_br *MagFrm_out_br_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &MagFrm_out_br_ptr->bin_start, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &MagFrm_out_br_ptr->bin_end, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &MagFrm_out_br_ptr->b_out[0], ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(data+ptr, &MagFrm_out_br_ptr->b_mag_av, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &MagFrm_out_br_ptr->b_sigma, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &MagFrm_out_br_ptr->iflag_out, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &MagFrm_out_br_ptr->weight, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_mag_br(uint8 *data, struct MagFrm_out_br *MagFrm_out_br_ptr)
{
int32 ptr=0;

   memcpy(&MagFrm_out_br_ptr->bin_start, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&MagFrm_out_br_ptr->bin_end, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&MagFrm_out_br_ptr->b_out[0], data+ptr,  ((8)*(3)) );
   ptr+= ((8)*(3));
   memcpy(&MagFrm_out_br_ptr->b_mag_av, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&MagFrm_out_br_ptr->b_sigma, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&MagFrm_out_br_ptr->iflag_out, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&MagFrm_out_br_ptr->weight, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_mag_br() {return(vgrp_id_mag_br);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_mag_br(char *wr_strval)
{
  strcpy(wr_strval, "The file 'magframe_out_br.h' is shown below, it was used to create the data in the Vgroup named 'VG_MagFrm_out_br'.\n\n");
  strcat(wr_strval,"/* Id: magframe_out_br.h,v 1.7 1998/04/16 18:32:30 ad Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct MagFrm_out_br\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  float64 bin_start;  /* beginning of bin. # of sec since Jan 1 1996 UTC */\n");
  strcat(wr_strval,"  float64 bin_end;    /* end of bin. # of sec since Jan 1 1996 UTC */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  float64 b_out[3];\n");
  strcat(wr_strval,"  float64 b_mag_av;\n");
  strcat(wr_strval,"  float64 b_sigma;\n");
  strcat(wr_strval,"  uint32 iflag_out;\n");
  strcat(wr_strval,"  uint8  weight;\n");
  strcat(wr_strval,"};\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/*The identity of the variables is as follows: */\n");
  strcat(wr_strval,"/*b_out[3]	are the 3 (R,T,N) components of the output 16-second */\n");
  strcat(wr_strval,"/*		average of the IMF. */\n");
  strcat(wr_strval,"/*b_mag_av      the value of <|B|> computed over 16 seconds */\n");
  strcat(wr_strval,"/*b_sigma       dBrms over 16 seconds */\n");
  strcat(wr_strval,"/* weight       number of individual measurements in the average */\n");
  strcat(wr_strval,"/*iflag_out	obsolete. Now set to be same as weight */\n");
  return(0);
}
