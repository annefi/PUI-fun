/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: swepam_bri.h,v 1.1 1997/08/15 00:51:02 jeff Exp  */

#include "swepam_bri.h"
#include "df.h"

int32 vgrp_id_swepam_br;
static int32 vdata_id_swepam_br;

  /* 889 is the size of swepam_bri.h + 1 added line */
char Vgrp_descrp_SwepamI_br[889];

/****----  init create function  ----****/

int32 init_cr_swepam_br(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_swepam_br();

  void print_swepam_br_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_swepam_br = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_swepam_br_error("init_cr_swepam_br -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_swepam_br, "VG_SwepamI_br"); 
  Vsetclass(vgrp_id_swepam_br, "VG_SWEPAM_BRI");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_SwepamI_br" )) ==FAIL) {
    print_swepam_br_error("init_cr_swepam_br -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_swepam_br(Vgrp_descrp_SwepamI_br);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_swepam_br_error("init_cr_swepam_br -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_SwepamI_br, sizeof(Vgrp_descrp_SwepamI_br))) ==FAIL) {
    print_swepam_br_error("init_cr_swepam_br -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_swepam_br = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_swepam_br_error("init_cr_swepam_br -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_swepam_br, "SwepamI_br");
  VSsetclass(vdata_id_swepam_br, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_swepam_br, vdata_id_swepam_br)) ==FAIL) {
    print_swepam_br_error("init_cr_swepam_br -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_swepam_br, "bin_start", DFNT_FLOAT64, (1) )) {
    print_swepam_br_error("init_cr_swepam_br -> VSfdefine: Couldn't define bin_start");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_br, "bin_end", DFNT_FLOAT64, (1) )) {
    print_swepam_br_error("init_cr_swepam_br -> VSfdefine: Couldn't define bin_end");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_br, "flag3d", DFNT_INT32, (1) )) {
    print_swepam_br_error("init_cr_swepam_br -> VSfdefine: Couldn't define flag3d");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_br, "np", DFNT_FLOAT32, (1) )) {
    print_swepam_br_error("init_cr_swepam_br -> VSfdefine: Couldn't define np");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_br, "he_ratio", DFNT_FLOAT32, (1) )) {
    print_swepam_br_error("init_cr_swepam_br -> VSfdefine: Couldn't define he_ratio");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_br, "speed", DFNT_FLOAT32, (1) )) {
    print_swepam_br_error("init_cr_swepam_br -> VSfdefine: Couldn't define speed");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swepam_br, "Trr", DFNT_FLOAT32, (1) )) {
    print_swepam_br_error("init_cr_swepam_br -> VSfdefine: Couldn't define Trr");
    retval = -1;
  }

  if (VSsetfields(vdata_id_swepam_br,"bin_start, bin_end, flag3d, np, he_ratio, speed, Trr")){
    print_swepam_br_error("init_cr_swepam_br -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_swepam_br(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_swepam_br(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_swepam_br(struct SwepamI_br SwepamI_br_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_swepam_br_error();
void pack_swepam_br();

  odata = (uint8 *) malloc(sizeof(struct SwepamI_br));
  pack_swepam_br(odata, &SwepamI_br_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_swepam_br, recnum)==-1) {
		print_swepam_br_error("write_swepam_br -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_swepam_br, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_swepam_br_error("write_swepam_br -> VSwrite: Couldn't write data.");

  memset(&SwepamI_br_struc, 0, sizeof(struct SwepamI_br));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_swepam_br()
{
  VSdetach(vdata_id_swepam_br);
  Vdetach(vgrp_id_swepam_br);
}

/*----     init access function    ----*/

int32 init_acc_swepam_br(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_swepam_br_error();


  if ((vdata_ref = VSfind(hdf_fp, "SwepamI_br")) <= 0 ) {
    print_swepam_br_error("init_acc_swepam_br -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_swepam_br = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_swepam_br_error("init_acc_swepam_br -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_swepam_br, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_swepam_br,"bin_start, bin_end, flag3d, np, he_ratio, speed, Trr")) {
      print_swepam_br_error("init_acc_swepam_br -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_swepam_br(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_swepam_br(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_swepam_br(struct SwepamI_br *SwepamI_br_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_swepam_br_error();
void unpack_swepam_br();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct SwepamI_br));
  VSinquire(vdata_id_swepam_br, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_swepam_br, recnum_rd)==FAIL) {
          print_swepam_br_error("read_swepam_br -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_swepam_br, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_swepam_br_error("read_swepam_br -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_swepam_br(odata, SwepamI_br_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_swepam_br()
{
  VSdetach(vdata_id_swepam_br);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_swepam_br(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_swepam_br_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_SwepamI_br" )) ==FAIL)
    print_swepam_br_error("rd_Vgrp_swepam_br -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_swepam_br_error("rd_Vgrp_swepam_br -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_swepam_br_error("rd_Vgrp_swepam_br -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_swepam_br_error("rd_Vgrp_swepam_br -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_SwepamI_br, HDstrlen(Vgrp_descrp_SwepamI_br)) ==FAIL)
    print_swepam_br_error("rd_Vgrp_swepam_br -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_SwepamI_br);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_swepam_br_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swepam_br.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_swepam_br(uint8 *data, struct SwepamI_br *SwepamI_br_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &SwepamI_br_ptr->bin_start, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &SwepamI_br_ptr->bin_end, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &SwepamI_br_ptr->flag3d, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &SwepamI_br_ptr->np, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &SwepamI_br_ptr->he_ratio, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &SwepamI_br_ptr->speed, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &SwepamI_br_ptr->Trr, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_swepam_br(uint8 *data, struct SwepamI_br *SwepamI_br_ptr)
{
int32 ptr=0;

   memcpy(&SwepamI_br_ptr->bin_start, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&SwepamI_br_ptr->bin_end, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&SwepamI_br_ptr->flag3d, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&SwepamI_br_ptr->np, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&SwepamI_br_ptr->he_ratio, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&SwepamI_br_ptr->speed, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&SwepamI_br_ptr->Trr, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_swepam_br() {return(vgrp_id_swepam_br);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_swepam_br(char *wr_strval)
{
  strcpy(wr_strval, "The file 'swepam_bri.h' is shown below, it was used to create the data in the Vgroup named 'VG_SwepamI_br'.\n\n");
  strcat(wr_strval,"/* Id: swepam_bri.h,v 1.1 1997/08/15 00:51:02 jeff Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct SwepamI_br\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  float64 bin_start;      /* beginning of bin. ACE epoch */\n");
  strcat(wr_strval,"  float64 bin_end;        /* end of bin. ACE epoch */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    int32 flag3d;          /* =0 data OK. */\n");
  strcat(wr_strval,"			    /* & 0x01 - proton density < 0 */\n");
  strcat(wr_strval,"			    /* & 0x02 - alpha density < 0 */\n");
  strcat(wr_strval,"			    /* & 0x04 - proton T < 0 */\n");
  strcat(wr_strval,"			    /* & 0x08 - speed < 0 */\n");
  strcat(wr_strval,"			    /* & 0x10 - lmx=255, not SWI mode */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    float32 np;            /* proton number density, cm^-3 */\n");
  strcat(wr_strval,"    float32 he_ratio;      /* nHe++/np */\n");
  strcat(wr_strval,"    float32 speed;         /* SW (bulk) speed */\n");
  strcat(wr_strval,"    float32 Trr;           /* (1,1) component of temp tensor along radial dir*/\n");
  strcat(wr_strval,"};\n");
  return(0);
}
