/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: swics_br.h,v 1.2 1999/09/01 21:22:19 ad Exp  */

#include "swics_br.h"
#include "mfhdf.h"
#include "df.h"

int32 vgrp_id_swics_br;
static int32 vdata_id_swics_br;

static int32 sds_id_swics_br1;

  /* 764 is the size of swics_br.h + 1 added line */
char Vgrp_descrp_Swics_br[764];

/****----  init create function  ----****/

int32 init_cr_swics_br(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;

  int32 sds_ref_w1;
  int32 dim_sizes[3];
  int32 rank;

  int32 wr_Vgrp_desc_swics_br();

  void print_swics_br_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_swics_br = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_swics_br_error("init_cr_swics_br -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_swics_br, "VG_Swics_br"); 
  Vsetclass(vgrp_id_swics_br, "VG_SWICS_BR");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_Swics_br" )) ==FAIL) {
    print_swics_br_error("init_cr_swics_br -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_swics_br(Vgrp_descrp_Swics_br);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_swics_br_error("init_cr_swics_br -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_Swics_br, sizeof(Vgrp_descrp_Swics_br))) ==FAIL) {
    print_swics_br_error("init_cr_swics_br -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_swics_br = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_swics_br_error("init_cr_swics_br -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_swics_br, "Swics_br");
  VSsetclass(vdata_id_swics_br, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_swics_br, vdata_id_swics_br)) ==FAIL) {
    print_swics_br_error("init_cr_swics_br -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_swics_br, "bin_start", DFNT_FLOAT64, (1) )) {
    print_swics_br_error("init_cr_swics_br -> VSfdefine: Couldn't define bin_start");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swics_br, "bin_end", DFNT_FLOAT64, (1) )) {
    print_swics_br_error("init_cr_swics_br -> VSfdefine: Couldn't define bin_end");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swics_br, "dpps", DFNT_INT32, (60) )) {
    print_swics_br_error("init_cr_swics_br -> VSfdefine: Couldn't define dpps");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swics_br, "grpaps", DFNT_INT32, (60) )) {
    print_swics_br_error("init_cr_swics_br -> VSfdefine: Couldn't define grpaps");
    retval = -1;
  }
  if (VSfdefine(vdata_id_swics_br, "edb", DFNT_INT32, (60) )) {
    print_swics_br_error("init_cr_swics_br -> VSfdefine: Couldn't define edb");
    retval = -1;
  }

  if (VSsetfields(vdata_id_swics_br,"bin_start, bin_end, dpps, grpaps, edb")){
    print_swics_br_error("init_cr_swics_br -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

 /*  Create SDS's and add to the Vgroup  */
  rank = 3;
  dim_sizes[0] = SD_UNLIMITED;
  dim_sizes[1] = 5;
  dim_sizes[2] = 60;
  if((sds_id_swics_br1 = SDcreate(sd_id, "Swics_br_rate", DFNT_INT32, rank, dim_sizes)) == FAIL)
    print_swics_br_error("init_cr_swics_br -> SDcreate: Couldn't create Swics_br_rate");

  /*  Add SDS to Vgroup  */
  if((sds_ref_w1 = SDidtoref(sds_id_swics_br1)) == FAIL)
    print_swics_br_error("init_cr_swics_br -> SDidtoref: Couldn't get ref for Swics_br_rate");

  if((Vaddtagref(vgrp_id_swics_br, DFTAG_NDG, sds_ref_w1)) == FAIL)
    print_swics_br_error("init_cr_swics_br -> Vaddtagref: Couldn't add SDS Swics_br_rate to Vgrp");

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_swics_br(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_swics_br(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_swics_br(struct Swics_br Swics_br_struc, int32 recnum)
{
  int32 start[3], edges[3];
  int32 retval = 0;
  uint8 *odata;
  static int32 recnum_wr=0;

void print_swics_br_error();
void pack_swics_br();

  odata = (uint8 *) malloc(sizeof(struct Swics_br));
  pack_swics_br(odata, &Swics_br_struc);

  if(recnum!=-1) {
	recnum_wr=recnum;
	if(VSseek(vdata_id_swics_br, recnum)==-1) {
		print_swics_br_error("write_swics_br -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_swics_br, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_swics_br_error("write_swics_br -> VSwrite: Couldn't write data.");

  start[0] = recnum_wr++;
  start[1] = 0;
  start[2] = 0;
  edges[0] = 1;

  edges[1] = 5;
  edges[2] = 60;
  if (SDwritedata(sds_id_swics_br1,start,NULL,edges, (VOIDP)(Swics_br_struc.rate)) ==FAIL)
    print_swics_br_error("write_swics_br -> SDwritedata: Problem writing rate data.");

  memset(&Swics_br_struc, 0, sizeof(struct Swics_br));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_swics_br()
{
  VSdetach(vdata_id_swics_br);
  Vdetach(vgrp_id_swics_br);
  SDendaccess(sds_id_swics_br1);
}

/*----     init access function    ----*/

int32 init_acc_swics_br(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  static int32 sds_index1;
  int32 vdata_ref;
  int32 num_rec;

  void print_swics_br_error();

  if((sds_index1=SDnametoindex(sd_id, "Swics_br_rate" )) ==FAIL) {
      print_swics_br_error("init_acc_swics_br -> SDnametoindex: Couldn't find Swics_br_rate");
      return(-1);
  }
  if((sds_id_swics_br1=SDselect(sd_id, sds_index1)) ==FAIL) {
      print_swics_br_error("init_acc_swics_br -> SDselect: Couldn't select sds_index1");
      return(-1);
  }

  if ((vdata_ref = VSfind(hdf_fp, "Swics_br")) <= 0 ) {
    print_swics_br_error("init_acc_swics_br -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_swics_br = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_swics_br_error("init_acc_swics_br -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_swics_br, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_swics_br,"bin_start, bin_end, dpps, grpaps, edb")) {
      print_swics_br_error("init_acc_swics_br -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_swics_br(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_swics_br(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_swics_br(struct Swics_br *Swics_br_struc, int32 recnum_rd)
{
int32 start[3], edges[3];
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_swics_br_error();
void unpack_swics_br();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  start[0] = recnum_rd;
  start[1] = 0;
  start[2] = 0;

  edges[0] = 1;

  odata = (uint8 *) malloc(sizeof(struct Swics_br));
  VSinquire(vdata_id_swics_br, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_swics_br, recnum_rd)==FAIL) {
          print_swics_br_error("read_swics_br -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  edges[1] = 5;
  edges[2] = 60;

  if(SDreaddata(sds_id_swics_br1,start,NULL,edges, (VOIDP)(Swics_br_struc->rate )) ==FAIL) {
    print_swics_br_error("read_swics_br -> SDreaddata: Couldn't read rate");
    retval = -1;
  }
  if(VSread(vdata_id_swics_br, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_swics_br_error("read_swics_br -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_swics_br(odata, Swics_br_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_swics_br()
{
  VSdetach(vdata_id_swics_br);
  SDendaccess(sds_id_swics_br1);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_swics_br(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_swics_br_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_Swics_br" )) ==FAIL)
    print_swics_br_error("rd_Vgrp_swics_br -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_swics_br_error("rd_Vgrp_swics_br -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_swics_br_error("rd_Vgrp_swics_br -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_swics_br_error("rd_Vgrp_swics_br -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_Swics_br, HDstrlen(Vgrp_descrp_Swics_br)) ==FAIL)
    print_swics_br_error("rd_Vgrp_swics_br -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_Swics_br);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_swics_br_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_swics_br.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_swics_br(uint8 *data, struct Swics_br *Swics_br_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &Swics_br_ptr->bin_start, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &Swics_br_ptr->bin_end, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &Swics_br_ptr->dpps[0], ((4)*(60)) );
   ptr+= ((4)*(60));
   memcpy(data+ptr, &Swics_br_ptr->grpaps[0], ((4)*(60)) );
   ptr+= ((4)*(60));
   memcpy(data+ptr, &Swics_br_ptr->edb[0], ((4)*(60)) );
   ptr+= ((4)*(60));
}

/*----   unpack function    ----*/

void unpack_swics_br(uint8 *data, struct Swics_br *Swics_br_ptr)
{
int32 ptr=0;

   memcpy(&Swics_br_ptr->bin_start, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&Swics_br_ptr->bin_end, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&Swics_br_ptr->dpps[0], data+ptr,  ((4)*(60)) );
   ptr+= ((4)*(60));
   memcpy(&Swics_br_ptr->grpaps[0], data+ptr,  ((4)*(60)) );
   ptr+= ((4)*(60));
   memcpy(&Swics_br_ptr->edb[0], data+ptr,  ((4)*(60)) );
   ptr+= ((4)*(60));
}
int32 get_vgrp_id_swics_br() {return(vgrp_id_swics_br);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_swics_br(char *wr_strval)
{
  strcpy(wr_strval, "The file 'swics_br.h' is shown below, it was used to create the data in the Vgroup named 'VG_Swics_br'.\n\n");
  strcat(wr_strval,"/* Id: swics_br.h,v 1.2 1999/09/01 21:22:19 ad Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct Swics_br\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  float64 bin_start;            /* beginning of bin. ACE epoch */\n");
  strcat(wr_strval,"  float64 bin_end;              /* end of bin. ACE epoch */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  int32 dpps[60];               /* DPPS voltage */\n");
  strcat(wr_strval,"  int32 grpaps[60];             /* Post-Accel. Power Supply voltage (unconverted - mult by 0.15) */\n");
  strcat(wr_strval,"  int32 edb[60];                /* = (EDB,-1) if (good/bad) EDB */\n");
  strcat(wr_strval,"  int32 rate[5][60];            /* unsectored, decompressed rates */\n");
  strcat(wr_strval,"				/* 0=H+(AuxH), 1=He++, 2=O6, 3=O7, 4=Fe(8-11) */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
