/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: BrowseCris.h,v 1.3 1997/09/11 00:07:52 jeff Exp  */

#include "BrowseCris.h"
#include "df.h"

int32 vgrp_id_BrowseCris;
static int32 vdata_id_BrowseCris;

  /* 1158 is the size of BrowseCris.h + 1 added line */
char Vgrp_descrp_BrowseCris[1158];

/****----  init create function  ----****/

int32 init_cr_BrowseCris(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_BrowseCris();

  void print_BrowseCris_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_BrowseCris = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_BrowseCris_error("init_cr_BrowseCris -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_BrowseCris, "VG_BrowseCris"); 
  Vsetclass(vgrp_id_BrowseCris, "VG_BROWSECRIS");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_BrowseCris" )) ==FAIL) {
    print_BrowseCris_error("init_cr_BrowseCris -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_BrowseCris(Vgrp_descrp_BrowseCris);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_BrowseCris_error("init_cr_BrowseCris -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_BrowseCris, sizeof(Vgrp_descrp_BrowseCris))) ==FAIL) {
    print_BrowseCris_error("init_cr_BrowseCris -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_BrowseCris = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_BrowseCris, "BrowseCris");
  VSsetclass(vdata_id_BrowseCris, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_BrowseCris, vdata_id_BrowseCris)) ==FAIL) {
    print_BrowseCris_error("init_cr_BrowseCris -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_BrowseCris, "bin_start", DFNT_FLOAT64, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define bin_start");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "bin_end", DFNT_FLOAT64, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define bin_end");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "FluxHelium_31", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define FluxHelium_31");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "FluxHelium_41", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define FluxHelium_41");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "FluxHelium_70", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define FluxHelium_70");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "FluxCno_63", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define FluxCno_63");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "FluxCno_84", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define FluxCno_84");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "FluxCno_144", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define FluxCno_144");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "FluxCnoSum", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define FluxCnoSum");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "FluxHiZ_92", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define FluxHiZ_92");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "FluxHiZ_124", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define FluxHiZ_124");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "FluxHiZ_220", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define FluxHiZ_220");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "FluxHiZSum", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define FluxHiZSum");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "FluxPen", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define FluxPen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "FluxPenSubset", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define FluxPenSubset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "WgtFactHelium_31", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define WgtFactHelium_31");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "WgtFactHelium_41", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define WgtFactHelium_41");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "WgtFactHelium_70", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define WgtFactHelium_70");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "WgtFactCno_63", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define WgtFactCno_63");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "WgtFactCno_84", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define WgtFactCno_84");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "WgtFactCno_144", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define WgtFactCno_144");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "WgtFactCnoSum", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define WgtFactCnoSum");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "WgtFactHiZ_92", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define WgtFactHiZ_92");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "WgtFactHiZ_124", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define WgtFactHiZ_124");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "WgtFactHiZ_220", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define WgtFactHiZ_220");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "WgtFactHiZSum", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define WgtFactHiZSum");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "WgtFactPen", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define WgtFactPen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseCris, "WgtFactPenSubset", DFNT_FLOAT32, (1) )) {
    print_BrowseCris_error("init_cr_BrowseCris -> VSfdefine: Couldn't define WgtFactPenSubset");
    retval = -1;
  }

  if (VSsetfields(vdata_id_BrowseCris,"bin_start, bin_end, FluxHelium_31, FluxHelium_41, FluxHelium_70, FluxCno_63, FluxCno_84, FluxCno_144, FluxCnoSum, FluxHiZ_92, FluxHiZ_124, FluxHiZ_220, FluxHiZSum, FluxPen, FluxPenSubset, WgtFactHelium_31, WgtFactHelium_41, WgtFactHelium_70, WgtFactCno_63, WgtFactCno_84, WgtFactCno_144, WgtFactCnoSum, WgtFactHiZ_92, WgtFactHiZ_124, WgtFactHiZ_220, WgtFactHiZSum, WgtFactPen, WgtFactPenSubset")){
    print_BrowseCris_error("init_cr_BrowseCris -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_BrowseCris(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_BrowseCris(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_BrowseCris(struct BrowseCris BrowseCris_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_BrowseCris_error();
void pack_BrowseCris();

  odata = (uint8 *) malloc(sizeof(struct BrowseCris));
  pack_BrowseCris(odata, &BrowseCris_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_BrowseCris, recnum)==-1) {
		print_BrowseCris_error("write_BrowseCris -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_BrowseCris, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_BrowseCris_error("write_BrowseCris -> VSwrite: Couldn't write data.");

  memset(&BrowseCris_struc, 0, sizeof(struct BrowseCris));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_BrowseCris()
{
  VSdetach(vdata_id_BrowseCris);
  Vdetach(vgrp_id_BrowseCris);
}

/*----     init access function    ----*/

int32 init_acc_BrowseCris(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_BrowseCris_error();


  if ((vdata_ref = VSfind(hdf_fp, "BrowseCris")) <= 0 ) {
    print_BrowseCris_error("init_acc_BrowseCris -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_BrowseCris = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_BrowseCris_error("init_acc_BrowseCris -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_BrowseCris, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_BrowseCris,"bin_start, bin_end, FluxHelium_31, FluxHelium_41, FluxHelium_70, FluxCno_63, FluxCno_84, FluxCno_144, FluxCnoSum, FluxHiZ_92, FluxHiZ_124, FluxHiZ_220, FluxHiZSum, FluxPen, FluxPenSubset, WgtFactHelium_31, WgtFactHelium_41, WgtFactHelium_70, WgtFactCno_63, WgtFactCno_84, WgtFactCno_144, WgtFactCnoSum, WgtFactHiZ_92, WgtFactHiZ_124, WgtFactHiZ_220, WgtFactHiZSum, WgtFactPen, WgtFactPenSubset")) {
      print_BrowseCris_error("init_acc_BrowseCris -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_BrowseCris(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_BrowseCris(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_BrowseCris(struct BrowseCris *BrowseCris_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_BrowseCris_error();
void unpack_BrowseCris();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct BrowseCris));
  VSinquire(vdata_id_BrowseCris, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_BrowseCris, recnum_rd)==FAIL) {
          print_BrowseCris_error("read_BrowseCris -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_BrowseCris, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_BrowseCris_error("read_BrowseCris -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_BrowseCris(odata, BrowseCris_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_BrowseCris()
{
  VSdetach(vdata_id_BrowseCris);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_BrowseCris(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_BrowseCris_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_BrowseCris" )) ==FAIL)
    print_BrowseCris_error("rd_Vgrp_BrowseCris -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_BrowseCris_error("rd_Vgrp_BrowseCris -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_BrowseCris_error("rd_Vgrp_BrowseCris -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_BrowseCris_error("rd_Vgrp_BrowseCris -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_BrowseCris, HDstrlen(Vgrp_descrp_BrowseCris)) ==FAIL)
    print_BrowseCris_error("rd_Vgrp_BrowseCris -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_BrowseCris);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_BrowseCris_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_BrowseCris.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_BrowseCris(uint8 *data, struct BrowseCris *BrowseCris_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &BrowseCris_ptr->bin_start, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->bin_end, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->FluxHelium_31, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->FluxHelium_41, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->FluxHelium_70, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->FluxCno_63, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->FluxCno_84, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->FluxCno_144, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->FluxCnoSum, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->FluxHiZ_92, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->FluxHiZ_124, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->FluxHiZ_220, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->FluxHiZSum, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->FluxPen, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->FluxPenSubset, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->WgtFactHelium_31, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->WgtFactHelium_41, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->WgtFactHelium_70, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->WgtFactCno_63, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->WgtFactCno_84, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->WgtFactCno_144, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->WgtFactCnoSum, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->WgtFactHiZ_92, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->WgtFactHiZ_124, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->WgtFactHiZ_220, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->WgtFactHiZSum, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->WgtFactPen, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseCris_ptr->WgtFactPenSubset, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_BrowseCris(uint8 *data, struct BrowseCris *BrowseCris_ptr)
{
int32 ptr=0;

   memcpy(&BrowseCris_ptr->bin_start, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&BrowseCris_ptr->bin_end, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&BrowseCris_ptr->FluxHelium_31, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->FluxHelium_41, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->FluxHelium_70, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->FluxCno_63, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->FluxCno_84, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->FluxCno_144, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->FluxCnoSum, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->FluxHiZ_92, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->FluxHiZ_124, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->FluxHiZ_220, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->FluxHiZSum, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->FluxPen, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->FluxPenSubset, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->WgtFactHelium_31, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->WgtFactHelium_41, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->WgtFactHelium_70, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->WgtFactCno_63, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->WgtFactCno_84, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->WgtFactCno_144, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->WgtFactCnoSum, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->WgtFactHiZ_92, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->WgtFactHiZ_124, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->WgtFactHiZ_220, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->WgtFactHiZSum, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->WgtFactPen, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseCris_ptr->WgtFactPenSubset, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_BrowseCris() {return(vgrp_id_BrowseCris);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_BrowseCris(char *wr_strval)
{
  strcpy(wr_strval, "The file 'BrowseCris.h' is shown below, it was used to create the data in the Vgroup named 'VG_BrowseCris'.\n\n");
  strcat(wr_strval,"/* Id: BrowseCris.h,v 1.3 1997/09/11 00:07:52 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/BrowseCris.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 00:07:52 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.3 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct BrowseCris {\n");
  strcat(wr_strval,"   float64 bin_start;\n");
  strcat(wr_strval,"   float64 bin_end;\n");
  strcat(wr_strval,"   float32 FluxHelium_31;\n");
  strcat(wr_strval,"   float32 FluxHelium_41;\n");
  strcat(wr_strval,"   float32 FluxHelium_70;\n");
  strcat(wr_strval,"   float32 FluxCno_63;\n");
  strcat(wr_strval,"   float32 FluxCno_84;\n");
  strcat(wr_strval,"   float32 FluxCno_144;\n");
  strcat(wr_strval,"   float32 FluxCnoSum;\n");
  strcat(wr_strval,"   float32 FluxHiZ_92;\n");
  strcat(wr_strval,"   float32 FluxHiZ_124;\n");
  strcat(wr_strval,"   float32 FluxHiZ_220;\n");
  strcat(wr_strval,"   float32 FluxHiZSum;\n");
  strcat(wr_strval,"   float32 FluxPen;\n");
  strcat(wr_strval,"   float32 FluxPenSubset;\n");
  strcat(wr_strval,"   float32 WgtFactHelium_31;\n");
  strcat(wr_strval,"   float32 WgtFactHelium_41;\n");
  strcat(wr_strval,"   float32 WgtFactHelium_70;\n");
  strcat(wr_strval,"   float32 WgtFactCno_63;\n");
  strcat(wr_strval,"   float32 WgtFactCno_84;\n");
  strcat(wr_strval,"   float32 WgtFactCno_144;\n");
  strcat(wr_strval,"   float32 WgtFactCnoSum;\n");
  strcat(wr_strval,"   float32 WgtFactHiZ_92;\n");
  strcat(wr_strval,"   float32 WgtFactHiZ_124;\n");
  strcat(wr_strval,"   float32 WgtFactHiZ_220;\n");
  strcat(wr_strval,"   float32 WgtFactHiZSum;\n");
  strcat(wr_strval,"   float32 WgtFactPen;\n");
  strcat(wr_strval,"   float32 WgtFactPenSubset;\n");
  strcat(wr_strval,"};\n");
  return(0);
}
