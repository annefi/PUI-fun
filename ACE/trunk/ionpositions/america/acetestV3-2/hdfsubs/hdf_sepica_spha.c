/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_spha.h,v 1.6 1998/12/07 18:12:39 ad Exp  */

#include "s3_spha.h"
#include "df.h"

int32 vgrp_id_s3_spha;
static int32 vdata_id_s3_spha;

  /* 2152 is the size of s3_spha.h + 1 added line */
char Vgrp_descrp_spha[2152];

/****----  init create function  ----****/

int32 init_cr_s3_spha(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_spha();

  void print_s3_spha_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_spha = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_spha_error("init_cr_s3_spha -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_spha, "VG_spha"); 
  Vsetclass(vgrp_id_s3_spha, "VG_S3_SPHA");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_spha" )) ==FAIL) {
    print_s3_spha_error("init_cr_s3_spha -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_spha(Vgrp_descrp_spha);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_spha_error("init_cr_s3_spha -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_spha, sizeof(Vgrp_descrp_spha))) ==FAIL) {
    print_s3_spha_error("init_cr_s3_spha -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_spha = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_spha_error("init_cr_s3_spha -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_spha, "spha");
  VSsetclass(vdata_id_s3_spha, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_spha, vdata_id_s3_spha)) ==FAIL) {
    print_s3_spha_error("init_cr_s3_spha -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_spha, "sctime_readout", DFNT_UINT32, (1) )) {
    print_s3_spha_error("init_cr_s3_spha -> VSfdefine: Couldn't define sctime_readout");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_spha, "sctime_collection", DFNT_FLOAT64, (1) )) {
    print_s3_spha_error("init_cr_s3_spha -> VSfdefine: Couldn't define sctime_collection");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_spha, "QAC", DFNT_UINT16, (1) )) {
    print_s3_spha_error("init_cr_s3_spha -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_spha, "concat", DFNT_UINT16, (1) )) {
    print_s3_spha_error("init_cr_s3_spha -> VSfdefine: Couldn't define concat");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_spha, "numevts", DFNT_UINT16, (1) )) {
    print_s3_spha_error("init_cr_s3_spha -> VSfdefine: Couldn't define numevts");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_spha, "numevtsedb", DFNT_UINT16, (1) )) {
    print_s3_spha_error("init_cr_s3_spha -> VSfdefine: Couldn't define numevtsedb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_spha, "edb", DFNT_UINT16, (1) )) {
    print_s3_spha_error("init_cr_s3_spha -> VSfdefine: Couldn't define edb");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_spha, "range", DFNT_UINT8, (SEP_PHA_MAX) )) {
    print_s3_spha_error("init_cr_s3_spha -> VSfdefine: Couldn't define range");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_spha, "sector", DFNT_UINT8, (SEP_PHA_MAX) )) {
    print_s3_spha_error("init_cr_s3_spha -> VSfdefine: Couldn't define sector");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_spha, "fan", DFNT_UINT8, (SEP_PHA_MAX) )) {
    print_s3_spha_error("init_cr_s3_spha -> VSfdefine: Couldn't define fan");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_spha, "sys", DFNT_UINT8, (SEP_PHA_MAX) )) {
    print_s3_spha_error("init_cr_s3_spha -> VSfdefine: Couldn't define sys");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_spha, "dZ", DFNT_UINT8, (SEP_PHA_MAX) )) {
    print_s3_spha_error("init_cr_s3_spha -> VSfdefine: Couldn't define dZ");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_spha, "E", DFNT_UINT16, (SEP_PHA_MAX) )) {
    print_s3_spha_error("init_cr_s3_spha -> VSfdefine: Couldn't define E");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_spha, "Eg", DFNT_UINT8, (SEP_PHA_MAX) )) {
    print_s3_spha_error("init_cr_s3_spha -> VSfdefine: Couldn't define Eg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_spha, "dE", DFNT_UINT16, (SEP_PHA_MAX) )) {
    print_s3_spha_error("init_cr_s3_spha -> VSfdefine: Couldn't define dE");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_spha, "dEg", DFNT_UINT8, (SEP_PHA_MAX) )) {
    print_s3_spha_error("init_cr_s3_spha -> VSfdefine: Couldn't define dEg");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_spha, "Y", DFNT_UINT16, (SEP_PHA_MAX) )) {
    print_s3_spha_error("init_cr_s3_spha -> VSfdefine: Couldn't define Y");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_spha,"sctime_readout, sctime_collection, QAC, concat, numevts, numevtsedb, edb, range, sector, fan, sys, dZ, E, Eg, dE, dEg, Y")){
    print_s3_spha_error("init_cr_s3_spha -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_spha(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_spha(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_spha(struct spha spha_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_spha_error();
void pack_s3_spha();

  odata = (uint8 *) malloc(sizeof(struct spha));
  pack_s3_spha(odata, &spha_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_spha, recnum)==-1) {
		print_s3_spha_error("write_s3_spha -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_spha, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_spha_error("write_s3_spha -> VSwrite: Couldn't write data.");

  memset(&spha_struc, 0, sizeof(struct spha));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_spha()
{
  VSdetach(vdata_id_s3_spha);
  Vdetach(vgrp_id_s3_spha);
}

/*----     init access function    ----*/

int32 init_acc_s3_spha(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_spha_error();


  if ((vdata_ref = VSfind(hdf_fp, "spha")) <= 0 ) {
    print_s3_spha_error("init_acc_s3_spha -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_spha = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_spha_error("init_acc_s3_spha -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_spha, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_spha,"sctime_readout, sctime_collection, QAC, concat, numevts, numevtsedb, edb, range, sector, fan, sys, dZ, E, Eg, dE, dEg, Y")) {
      print_s3_spha_error("init_acc_s3_spha -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_spha(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_spha(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_spha(struct spha *spha_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_spha_error();
void unpack_s3_spha();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct spha));
  VSinquire(vdata_id_s3_spha, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_spha, recnum_rd)==FAIL) {
          print_s3_spha_error("read_s3_spha -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_spha, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_spha_error("read_s3_spha -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_spha(odata, spha_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_spha()
{
  VSdetach(vdata_id_s3_spha);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_spha(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_spha_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_spha" )) ==FAIL)
    print_s3_spha_error("rd_Vgrp_s3_spha -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_spha_error("rd_Vgrp_s3_spha -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_spha_error("rd_Vgrp_s3_spha -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_spha_error("rd_Vgrp_s3_spha -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_spha, HDstrlen(Vgrp_descrp_spha)) ==FAIL)
    print_s3_spha_error("rd_Vgrp_s3_spha -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_spha);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_spha_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_sepica_spha.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_spha(uint8 *data, struct spha *spha_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &spha_ptr->sctime_readout, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &spha_ptr->sctime_collection, ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(data+ptr, &spha_ptr->QAC, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &spha_ptr->concat, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &spha_ptr->numevts, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &spha_ptr->numevtsedb, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &spha_ptr->edb, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &spha_ptr->range[0], ((1)*(SEP_PHA_MAX)) );
   ptr+= ((1)*(SEP_PHA_MAX));
   memcpy(data+ptr, &spha_ptr->sector[0], ((1)*(SEP_PHA_MAX)) );
   ptr+= ((1)*(SEP_PHA_MAX));
   memcpy(data+ptr, &spha_ptr->fan[0], ((1)*(SEP_PHA_MAX)) );
   ptr+= ((1)*(SEP_PHA_MAX));
   memcpy(data+ptr, &spha_ptr->sys[0], ((1)*(SEP_PHA_MAX)) );
   ptr+= ((1)*(SEP_PHA_MAX));
   memcpy(data+ptr, &spha_ptr->dZ[0], ((1)*(SEP_PHA_MAX)) );
   ptr+= ((1)*(SEP_PHA_MAX));
   memcpy(data+ptr, &spha_ptr->E[0], ((2)*(SEP_PHA_MAX)) );
   ptr+= ((2)*(SEP_PHA_MAX));
   memcpy(data+ptr, &spha_ptr->Eg[0], ((1)*(SEP_PHA_MAX)) );
   ptr+= ((1)*(SEP_PHA_MAX));
   memcpy(data+ptr, &spha_ptr->dE[0], ((2)*(SEP_PHA_MAX)) );
   ptr+= ((2)*(SEP_PHA_MAX));
   memcpy(data+ptr, &spha_ptr->dEg[0], ((1)*(SEP_PHA_MAX)) );
   ptr+= ((1)*(SEP_PHA_MAX));
   memcpy(data+ptr, &spha_ptr->Y[0], ((2)*(SEP_PHA_MAX)) );
   ptr+= ((2)*(SEP_PHA_MAX));
}

/*----   unpack function    ----*/

void unpack_s3_spha(uint8 *data, struct spha *spha_ptr)
{
int32 ptr=0;

   memcpy(&spha_ptr->sctime_readout, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&spha_ptr->sctime_collection, data+ptr,  ((8)*(1)) );
   ptr+= ((8)*(1));
   memcpy(&spha_ptr->QAC, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&spha_ptr->concat, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&spha_ptr->numevts, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&spha_ptr->numevtsedb, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&spha_ptr->edb, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&spha_ptr->range[0], data+ptr,  ((1)*(SEP_PHA_MAX)) );
   ptr+= ((1)*(SEP_PHA_MAX));
   memcpy(&spha_ptr->sector[0], data+ptr,  ((1)*(SEP_PHA_MAX)) );
   ptr+= ((1)*(SEP_PHA_MAX));
   memcpy(&spha_ptr->fan[0], data+ptr,  ((1)*(SEP_PHA_MAX)) );
   ptr+= ((1)*(SEP_PHA_MAX));
   memcpy(&spha_ptr->sys[0], data+ptr,  ((1)*(SEP_PHA_MAX)) );
   ptr+= ((1)*(SEP_PHA_MAX));
   memcpy(&spha_ptr->dZ[0], data+ptr,  ((1)*(SEP_PHA_MAX)) );
   ptr+= ((1)*(SEP_PHA_MAX));
   memcpy(&spha_ptr->E[0], data+ptr,  ((2)*(SEP_PHA_MAX)) );
   ptr+= ((2)*(SEP_PHA_MAX));
   memcpy(&spha_ptr->Eg[0], data+ptr,  ((1)*(SEP_PHA_MAX)) );
   ptr+= ((1)*(SEP_PHA_MAX));
   memcpy(&spha_ptr->dE[0], data+ptr,  ((2)*(SEP_PHA_MAX)) );
   ptr+= ((2)*(SEP_PHA_MAX));
   memcpy(&spha_ptr->dEg[0], data+ptr,  ((1)*(SEP_PHA_MAX)) );
   ptr+= ((1)*(SEP_PHA_MAX));
   memcpy(&spha_ptr->Y[0], data+ptr,  ((2)*(SEP_PHA_MAX)) );
   ptr+= ((2)*(SEP_PHA_MAX));
}
int32 get_vgrp_id_s3_spha() {return(vgrp_id_s3_spha);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_spha(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_spha.h' is shown below, it was used to create the data in the Vgroup named 'VG_spha'.\n\n");
  strcat(wr_strval,"/* Id: s3_spha.h,v 1.6 1998/12/07 18:12:39 ad Exp $	     */\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define SEP_PHA_MAX 30     /* the maximum number of pha events that fit */\n");
  strcat(wr_strval,"                           /* into this data structure - an arbitrary number */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define SEP_PHA_CYCPERSR 60 /* number of pha collection cycles per Science Rec */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* sctime_readout: spacecraft clock of first minor frame of the EDB */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"/* sctime_collection: pha data are collected over 1 spin and output */\n");
  strcat(wr_strval,"/* during the next spin. There are 60 pha collection cycles per SR. */\n");
  strcat(wr_strval,"/* sctime_collection contains the time of the start of the */\n");
  strcat(wr_strval,"/* collection cycle (spin), in spacecraft clock time units */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct spha{\n");
  strcat(wr_strval,"	uint32 sctime_readout;	   /* 32 bit spacecraft time  */\n");
  strcat(wr_strval,"	float64 sctime_collection; /* spacecraft time, sub-second resolution */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint16 QAC;	/* number of frames missing in this EDB */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint16  concat; /* Sequence number for this structure will be */\n");
  strcat(wr_strval,"		        /* greater than 1 for cases where the number of */\n");
  strcat(wr_strval,"		        /* events in the EDB exceeds SEP_PHA_MAX. In these */\n");
  strcat(wr_strval,"		        /* cases, concat will count down from N to 1, where N */\n");
  strcat(wr_strval,"			/* is the total number of spha structures for the */\n");
  strcat(wr_strval,"			/* current EDB. */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint16 numevts; /* Number of pha events in this data structure. */\n");
  strcat(wr_strval,"                        /* Should be SEP_PHA_MAX when concat > 1. */\n");
  strcat(wr_strval,"			/* When concat == 1, numevts <= SEP_PHA_MAX */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint16 numevtsedb; /* Number of pha events in the whole EDB */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"	uint16 edb; /* sequence number of EDB in Science Record (0-59) */\n");
  strcat(wr_strval,"	\n");
  strcat(wr_strval,"	uint8  range[SEP_PHA_MAX]; /* range*/\n");
  strcat(wr_strval,"	uint8  sector[SEP_PHA_MAX];/* sector*/\n");
  strcat(wr_strval,"	uint8  fan[SEP_PHA_MAX];   /* fan */\n");
  strcat(wr_strval,"	uint8  sys[SEP_PHA_MAX];   /* sys*/\n");
  strcat(wr_strval,"	uint8  dZ[SEP_PHA_MAX];    /*  delta Z */\n");
  strcat(wr_strval,"	uint16 E[SEP_PHA_MAX];     /* Energy*/\n");
  strcat(wr_strval,"	uint8  Eg[SEP_PHA_MAX];    /* Energy gain bit */\n");
  strcat(wr_strval,"	uint16 dE[SEP_PHA_MAX];    /* delta Energy */\n");
  strcat(wr_strval,"	uint8  dEg[SEP_PHA_MAX];   /* delta Energy gain bit*/\n");
  strcat(wr_strval,"	uint16 Y[SEP_PHA_MAX];     /* Y value */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
