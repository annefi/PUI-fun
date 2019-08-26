/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: mag_avgvec.h,v 1.2 1998/09/18 21:16:21 ad Exp  */

#include "mag_avgvec.h"
#include "df.h"

int32 vgrp_id_mag_avgvec;
static int32 vdata_id_mag_avgvec;

  /* 867 is the size of mag_avgvec.h + 1 added line */
char Vgrp_descrp_MagAvgVec[867];

/****----  init create function  ----****/

int32 init_cr_mag_avgvec(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_mag_avgvec();

  void print_mag_avgvec_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_mag_avgvec = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_mag_avgvec_error("init_cr_mag_avgvec -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_mag_avgvec, "VG_MagAvgVec"); 
  Vsetclass(vgrp_id_mag_avgvec, "VG_MAG_AVGVEC");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_MagAvgVec" )) ==FAIL) {
    print_mag_avgvec_error("init_cr_mag_avgvec -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_mag_avgvec(Vgrp_descrp_MagAvgVec);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_mag_avgvec_error("init_cr_mag_avgvec -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_MagAvgVec, sizeof(Vgrp_descrp_MagAvgVec))) ==FAIL) {
    print_mag_avgvec_error("init_cr_mag_avgvec -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_mag_avgvec = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_mag_avgvec_error("init_cr_mag_avgvec -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_mag_avgvec, "MagAvgVec");
  VSsetclass(vdata_id_mag_avgvec, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_mag_avgvec, vdata_id_mag_avgvec)) ==FAIL) {
    print_mag_avgvec_error("init_cr_mag_avgvec -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_mag_avgvec, "sctime_readout", DFNT_UINT32, (1) )) {
    print_mag_avgvec_error("init_cr_mag_avgvec -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_avgvec, "sctime_collection", DFNT_UINT32, (1) )) {
    print_mag_avgvec_error("init_cr_mag_avgvec -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_avgvec, "QAC", DFNT_UINT32, (1) )) {
    print_mag_avgvec_error("init_cr_mag_avgvec -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_avgvec, "b_inertial", DFNT_FLOAT64, (MAGAVGDIM) )) {
    print_mag_avgvec_error("init_cr_mag_avgvec -> VSfdefine: Couldn't define b_inertial");
    retval = -1;
  }
  if (VSfdefine(vdata_id_mag_avgvec, "b_sigma", DFNT_FLOAT64, (1) )) {
    print_mag_avgvec_error("init_cr_mag_avgvec -> VSfdefine: Couldn't define b_sigma");
    retval = -1;
  }

  if (VSsetfields(vdata_id_mag_avgvec,"sctime_readout, sctime_collection, QAC, b_inertial, b_sigma")){
    print_mag_avgvec_error("init_cr_mag_avgvec -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_mag_avgvec(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_mag_avgvec(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_mag_avgvec(struct MagAvgVec MagAvgVec_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_mag_avgvec_error();
void pack_mag_avgvec();

  odata = (uint8 *) malloc(sizeof(struct MagAvgVec));
  pack_mag_avgvec(odata, &MagAvgVec_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_mag_avgvec, recnum)==-1) {
		print_mag_avgvec_error("write_mag_avgvec -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_mag_avgvec, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_mag_avgvec_error("write_mag_avgvec -> VSwrite: Couldn't write data.");

  memset(&MagAvgVec_struc, 0, sizeof(struct MagAvgVec));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_mag_avgvec()
{
  VSdetach(vdata_id_mag_avgvec);
  Vdetach(vgrp_id_mag_avgvec);
}

/*----     init access function    ----*/

int32 init_acc_mag_avgvec(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_mag_avgvec_error();


  if ((vdata_ref = VSfind(hdf_fp, "MagAvgVec")) <= 0 ) {
    print_mag_avgvec_error("init_acc_mag_avgvec -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_mag_avgvec = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_mag_avgvec_error("init_acc_mag_avgvec -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_mag_avgvec, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_mag_avgvec,"sctime_readout, sctime_collection, QAC, b_inertial, b_sigma")) {
      print_mag_avgvec_error("init_acc_mag_avgvec -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_mag_avgvec(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_mag_avgvec(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_mag_avgvec(struct MagAvgVec *MagAvgVec_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_mag_avgvec_error();
void unpack_mag_avgvec();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct MagAvgVec));
  VSinquire(vdata_id_mag_avgvec, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_mag_avgvec, recnum_rd)==FAIL) {
          print_mag_avgvec_error("read_mag_avgvec -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_mag_avgvec, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_mag_avgvec_error("read_mag_avgvec -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_mag_avgvec(odata, MagAvgVec_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_mag_avgvec()
{
  VSdetach(vdata_id_mag_avgvec);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_mag_avgvec(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_mag_avgvec_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_MagAvgVec" )) ==FAIL)
    print_mag_avgvec_error("rd_Vgrp_mag_avgvec -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_mag_avgvec_error("rd_Vgrp_mag_avgvec -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_mag_avgvec_error("rd_Vgrp_mag_avgvec -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_mag_avgvec_error("rd_Vgrp_mag_avgvec -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_MagAvgVec, HDstrlen(Vgrp_descrp_MagAvgVec)) ==FAIL)
    print_mag_avgvec_error("rd_Vgrp_mag_avgvec -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_MagAvgVec);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_mag_avgvec_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_mag_avgvec.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_mag_avgvec(uint8 *data, struct MagAvgVec *MagAvgVec_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &MagAvgVec_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &MagAvgVec_ptr->sctime_collection, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &MagAvgVec_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &MagAvgVec_ptr->b_inertial[0], ((8)*(MAGAVGDIM)) );
   ptr+= ((8)*(MAGAVGDIM));
   memcpy(data+ptr, &MagAvgVec_ptr->b_sigma, ((8)*(1)) );
   ptr+= ((8)*(1));
}

/*----   unpack function    ----*/

void unpack_mag_avgvec(uint8 *data, struct MagAvgVec *MagAvgVec_ptr)
{
int32 ptr=0;

   memcpy(&MagAvgVec_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&MagAvgVec_ptr->sctime_collection, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&MagAvgVec_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&MagAvgVec_ptr->b_inertial[0], data+ptr,  ((8)*(MAGAVGDIM)) );
   ptr+= ((8)*(MAGAVGDIM));
   memcpy(&MagAvgVec_ptr->b_sigma, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
}
int32 get_vgrp_id_mag_avgvec() {return(vgrp_id_mag_avgvec);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_mag_avgvec(char *wr_strval)
{
  strcpy(wr_strval, "The file 'mag_avgvec.h' is shown below, it was used to create the data in the Vgroup named 'VG_MagAvgVec'.\n\n");
  strcat(wr_strval,"/* Id: mag_avgvec.h,v 1.2 1998/09/18 21:16:21 ad Exp $ */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define MAGAVGDIM 3\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct MagAvgVec\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 sctime_readout;          /* 32 bit spacecraft readout time.    */\n");
  strcat(wr_strval,"			          /* scclock for first minor frame */\n");
  strcat(wr_strval,"  uint32 sctime_collection;       /* 32 bit spacecraft collection time    */\n");
  strcat(wr_strval,"                                  /* beginning of MAG data collection cycle */\n");
  strcat(wr_strval,"  uint32 QAC;                     /* number of missing minor frames in this 16-sec cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  float64 b_inertial[MAGAVGDIM];  /* 16 second average mag vector in despun s/c */\n");
  strcat(wr_strval,"			          /* inertial coordinates */\n");
  strcat(wr_strval,"  float64 b_sigma;		  /* dBrms over 16 seconds */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
