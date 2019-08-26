/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: BrowseSis.h,v 1.3 1997/09/11 00:07:52 jeff Exp  */

#include "BrowseSis.h"
#include "df.h"

int32 vgrp_id_BrowseSis;
static int32 vdata_id_BrowseSis;

  /* 1395 is the size of BrowseSis.h + 1 added line */
char Vgrp_descrp_BrowseSis[1395];

/****----  init create function  ----****/

int32 init_cr_BrowseSis(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_BrowseSis();

  void print_BrowseSis_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_BrowseSis = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_BrowseSis_error("init_cr_BrowseSis -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_BrowseSis, "VG_BrowseSis"); 
  Vsetclass(vgrp_id_BrowseSis, "VG_BROWSESIS");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_BrowseSis" )) ==FAIL) {
    print_BrowseSis_error("init_cr_BrowseSis -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_BrowseSis(Vgrp_descrp_BrowseSis);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_BrowseSis_error("init_cr_BrowseSis -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_BrowseSis, sizeof(Vgrp_descrp_BrowseSis))) ==FAIL) {
    print_BrowseSis_error("init_cr_BrowseSis -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_BrowseSis = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_BrowseSis, "BrowseSis");
  VSsetclass(vdata_id_BrowseSis, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_BrowseSis, vdata_id_BrowseSis)) ==FAIL) {
    print_BrowseSis_error("init_cr_BrowseSis -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_BrowseSis, "bin_start", DFNT_FLOAT64, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define bin_start");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "bin_end", DFNT_FLOAT64, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define bin_end");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "FluxProton_6_5", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define FluxProton_6_5");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "FluxProton_7_5", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define FluxProton_7_5");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "FluxHelium_3_7", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define FluxHelium_3_7");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "FluxHelium_4_8", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define FluxHelium_4_8");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "FluxHelium_7_4", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define FluxHelium_7_4");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "FluxHelium_14", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define FluxHelium_14");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "FluxCno_7", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define FluxCno_7");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "FluxCno_9_7", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define FluxCno_9_7");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "FluxCno_15", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define FluxCno_15");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "FluxCno_28", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define FluxCno_28");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "FluxHiZ_9_4", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define FluxHiZ_9_4");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "FluxHiZ_13_6", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define FluxHiZ_13_6");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "FluxHiZ_21_4", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define FluxHiZ_21_4");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "FluxHiZ_41", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define FluxHiZ_41");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "FluxPen", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define FluxPen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "FluxHeliumSubset", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define FluxHeliumSubset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "FluxCnoSubset", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define FluxCnoSubset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "WgtFactProton_6_5", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define WgtFactProton_6_5");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "WgtFactProton_7_5", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define WgtFactProton_7_5");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "WgtFactHelium_3_7", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define WgtFactHelium_3_7");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "WgtFactHelium_4_8", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define WgtFactHelium_4_8");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "WgtFactHelium_7_4", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define WgtFactHelium_7_4");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "WgtFactHelium_14", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define WgtFactHelium_14");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "WgtFactCno_7", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define WgtFactCno_7");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "WgtFactCno_9_7", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define WgtFactCno_9_7");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "WgtFactCno_15", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define WgtFactCno_15");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "WgtFactCno_28", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define WgtFactCno_28");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "WgtFactHiZ_9_4", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define WgtFactHiZ_9_4");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "WgtFactHiZ_13_6", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define WgtFactHiZ_13_6");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "WgtFactHiZ_21_4", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define WgtFactHiZ_21_4");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "WgtFactHiZ_41", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define WgtFactHiZ_41");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "WgtFactPen", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define WgtFactPen");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "WgtFactHeliumSubset", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define WgtFactHeliumSubset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_BrowseSis, "WgtFactCnoSubset", DFNT_FLOAT32, (1) )) {
    print_BrowseSis_error("init_cr_BrowseSis -> VSfdefine: Couldn't define WgtFactCnoSubset");
    retval = -1;
  }

  if (VSsetfields(vdata_id_BrowseSis,"bin_start, bin_end, FluxProton_6_5, FluxProton_7_5, FluxHelium_3_7, FluxHelium_4_8, FluxHelium_7_4, FluxHelium_14, FluxCno_7, FluxCno_9_7, FluxCno_15, FluxCno_28, FluxHiZ_9_4, FluxHiZ_13_6, FluxHiZ_21_4, FluxHiZ_41, FluxPen, FluxHeliumSubset, FluxCnoSubset, WgtFactProton_6_5, WgtFactProton_7_5, WgtFactHelium_3_7, WgtFactHelium_4_8, WgtFactHelium_7_4, WgtFactHelium_14, WgtFactCno_7, WgtFactCno_9_7, WgtFactCno_15, WgtFactCno_28, WgtFactHiZ_9_4, WgtFactHiZ_13_6, WgtFactHiZ_21_4, WgtFactHiZ_41, WgtFactPen, WgtFactHeliumSubset, WgtFactCnoSubset")){
    print_BrowseSis_error("init_cr_BrowseSis -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_BrowseSis(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_BrowseSis(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_BrowseSis(struct BrowseSis BrowseSis_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_BrowseSis_error();
void pack_BrowseSis();

  odata = (uint8 *) malloc(sizeof(struct BrowseSis));
  pack_BrowseSis(odata, &BrowseSis_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_BrowseSis, recnum)==-1) {
		print_BrowseSis_error("write_BrowseSis -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_BrowseSis, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_BrowseSis_error("write_BrowseSis -> VSwrite: Couldn't write data.");

  memset(&BrowseSis_struc, 0, sizeof(struct BrowseSis));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_BrowseSis()
{
  VSdetach(vdata_id_BrowseSis);
  Vdetach(vgrp_id_BrowseSis);
}

/*----     init access function    ----*/

int32 init_acc_BrowseSis(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_BrowseSis_error();


  if ((vdata_ref = VSfind(hdf_fp, "BrowseSis")) <= 0 ) {
    print_BrowseSis_error("init_acc_BrowseSis -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_BrowseSis = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_BrowseSis_error("init_acc_BrowseSis -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_BrowseSis, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_BrowseSis,"bin_start, bin_end, FluxProton_6_5, FluxProton_7_5, FluxHelium_3_7, FluxHelium_4_8, FluxHelium_7_4, FluxHelium_14, FluxCno_7, FluxCno_9_7, FluxCno_15, FluxCno_28, FluxHiZ_9_4, FluxHiZ_13_6, FluxHiZ_21_4, FluxHiZ_41, FluxPen, FluxHeliumSubset, FluxCnoSubset, WgtFactProton_6_5, WgtFactProton_7_5, WgtFactHelium_3_7, WgtFactHelium_4_8, WgtFactHelium_7_4, WgtFactHelium_14, WgtFactCno_7, WgtFactCno_9_7, WgtFactCno_15, WgtFactCno_28, WgtFactHiZ_9_4, WgtFactHiZ_13_6, WgtFactHiZ_21_4, WgtFactHiZ_41, WgtFactPen, WgtFactHeliumSubset, WgtFactCnoSubset")) {
      print_BrowseSis_error("init_acc_BrowseSis -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_BrowseSis(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_BrowseSis(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_BrowseSis(struct BrowseSis *BrowseSis_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_BrowseSis_error();
void unpack_BrowseSis();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct BrowseSis));
  VSinquire(vdata_id_BrowseSis, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_BrowseSis, recnum_rd)==FAIL) {
          print_BrowseSis_error("read_BrowseSis -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_BrowseSis, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_BrowseSis_error("read_BrowseSis -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_BrowseSis(odata, BrowseSis_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_BrowseSis()
{
  VSdetach(vdata_id_BrowseSis);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_BrowseSis(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_BrowseSis_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_BrowseSis" )) ==FAIL)
    print_BrowseSis_error("rd_Vgrp_BrowseSis -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_BrowseSis_error("rd_Vgrp_BrowseSis -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_BrowseSis_error("rd_Vgrp_BrowseSis -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_BrowseSis_error("rd_Vgrp_BrowseSis -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_BrowseSis, HDstrlen(Vgrp_descrp_BrowseSis)) ==FAIL)
    print_BrowseSis_error("rd_Vgrp_BrowseSis -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_BrowseSis);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_BrowseSis_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_BrowseSis.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_BrowseSis(uint8 *data, struct BrowseSis *BrowseSis_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &BrowseSis_ptr->bin_start, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->bin_end, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->FluxProton_6_5, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->FluxProton_7_5, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->FluxHelium_3_7, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->FluxHelium_4_8, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->FluxHelium_7_4, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->FluxHelium_14, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->FluxCno_7, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->FluxCno_9_7, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->FluxCno_15, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->FluxCno_28, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->FluxHiZ_9_4, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->FluxHiZ_13_6, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->FluxHiZ_21_4, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->FluxHiZ_41, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->FluxPen, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->FluxHeliumSubset, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->FluxCnoSubset, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->WgtFactProton_6_5, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->WgtFactProton_7_5, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->WgtFactHelium_3_7, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->WgtFactHelium_4_8, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->WgtFactHelium_7_4, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->WgtFactHelium_14, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->WgtFactCno_7, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->WgtFactCno_9_7, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->WgtFactCno_15, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->WgtFactCno_28, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->WgtFactHiZ_9_4, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->WgtFactHiZ_13_6, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->WgtFactHiZ_21_4, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->WgtFactHiZ_41, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->WgtFactPen, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->WgtFactHeliumSubset, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &BrowseSis_ptr->WgtFactCnoSubset, ((4)*(1)) );
   ptr+= ((4)*(1));
}

/*----   unpack function    ----*/

void unpack_BrowseSis(uint8 *data, struct BrowseSis *BrowseSis_ptr)
{
int32 ptr=0;

   memcpy(&BrowseSis_ptr->bin_start, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&BrowseSis_ptr->bin_end, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&BrowseSis_ptr->FluxProton_6_5, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->FluxProton_7_5, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->FluxHelium_3_7, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->FluxHelium_4_8, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->FluxHelium_7_4, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->FluxHelium_14, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->FluxCno_7, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->FluxCno_9_7, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->FluxCno_15, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->FluxCno_28, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->FluxHiZ_9_4, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->FluxHiZ_13_6, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->FluxHiZ_21_4, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->FluxHiZ_41, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->FluxPen, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->FluxHeliumSubset, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->FluxCnoSubset, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->WgtFactProton_6_5, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->WgtFactProton_7_5, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->WgtFactHelium_3_7, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->WgtFactHelium_4_8, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->WgtFactHelium_7_4, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->WgtFactHelium_14, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->WgtFactCno_7, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->WgtFactCno_9_7, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->WgtFactCno_15, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->WgtFactCno_28, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->WgtFactHiZ_9_4, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->WgtFactHiZ_13_6, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->WgtFactHiZ_21_4, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->WgtFactHiZ_41, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->WgtFactPen, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->WgtFactHeliumSubset, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&BrowseSis_ptr->WgtFactCnoSubset, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
}
int32 get_vgrp_id_BrowseSis() {return(vgrp_id_BrowseSis);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_BrowseSis(char *wr_strval)
{
  strcpy(wr_strval, "The file 'BrowseSis.h' is shown below, it was used to create the data in the Vgroup named 'VG_BrowseSis'.\n\n");
  strcat(wr_strval,"/* Id: BrowseSis.h,v 1.3 1997/09/11 00:07:52 jeff Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* $Source: /home/mussel9/asc/aceprog/include/RCS/BrowseSis.h,v $ */\n");
  strcat(wr_strval,"/* $Author: jeff $ */\n");
  strcat(wr_strval,"/* $Date: 1997/09/11 00:07:52 $ */\n");
  strcat(wr_strval,"/* $Revision: 1.3 $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct BrowseSis {\n");
  strcat(wr_strval,"   float64 bin_start;\n");
  strcat(wr_strval,"   float64 bin_end;\n");
  strcat(wr_strval,"   float32 FluxProton_6_5;\n");
  strcat(wr_strval,"   float32 FluxProton_7_5;\n");
  strcat(wr_strval,"   float32 FluxHelium_3_7;\n");
  strcat(wr_strval,"   float32 FluxHelium_4_8;\n");
  strcat(wr_strval,"   float32 FluxHelium_7_4;\n");
  strcat(wr_strval,"   float32 FluxHelium_14;\n");
  strcat(wr_strval,"   float32 FluxCno_7;\n");
  strcat(wr_strval,"   float32 FluxCno_9_7;\n");
  strcat(wr_strval,"   float32 FluxCno_15;\n");
  strcat(wr_strval,"   float32 FluxCno_28;\n");
  strcat(wr_strval,"   float32 FluxHiZ_9_4;\n");
  strcat(wr_strval,"   float32 FluxHiZ_13_6;\n");
  strcat(wr_strval,"   float32 FluxHiZ_21_4;\n");
  strcat(wr_strval,"   float32 FluxHiZ_41;\n");
  strcat(wr_strval,"   float32 FluxPen;\n");
  strcat(wr_strval,"   float32 FluxHeliumSubset;\n");
  strcat(wr_strval,"   float32 FluxCnoSubset;\n");
  strcat(wr_strval,"   float32 WgtFactProton_6_5;\n");
  strcat(wr_strval,"   float32 WgtFactProton_7_5;\n");
  strcat(wr_strval,"   float32 WgtFactHelium_3_7;\n");
  strcat(wr_strval,"   float32 WgtFactHelium_4_8;\n");
  strcat(wr_strval,"   float32 WgtFactHelium_7_4;\n");
  strcat(wr_strval,"   float32 WgtFactHelium_14;\n");
  strcat(wr_strval,"   float32 WgtFactCno_7;\n");
  strcat(wr_strval,"   float32 WgtFactCno_9_7;\n");
  strcat(wr_strval,"   float32 WgtFactCno_15;\n");
  strcat(wr_strval,"   float32 WgtFactCno_28;\n");
  strcat(wr_strval,"   float32 WgtFactHiZ_9_4;\n");
  strcat(wr_strval,"   float32 WgtFactHiZ_13_6;\n");
  strcat(wr_strval,"   float32 WgtFactHiZ_21_4;\n");
  strcat(wr_strval,"   float32 WgtFactHiZ_41;\n");
  strcat(wr_strval,"   float32 WgtFactPen;\n");
  strcat(wr_strval,"   float32 WgtFactHeliumSubset;\n");
  strcat(wr_strval,"   float32 WgtFactCnoSubset;\n");
  strcat(wr_strval,"};\n");
  return(0);
}
