/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: uleis_dump.h,v 1.6 1997/05/09 22:04:40 steves Exp  */

#include "uleis_dump.h"
#include "df.h"

int32 vgrp_id_uleis_dump;
static int32 vdata_id_uleis_dump;

  /* 683 is the size of uleis_dump.h + 1 added line */
char Vgrp_descrp_UDumpSet[683];

/****----  init create function  ----****/

int32 init_cr_uleis_dump(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_uleis_dump();

  void print_uleis_dump_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_uleis_dump = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_uleis_dump_error("init_cr_uleis_dump -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_uleis_dump, "VG_UDumpSet"); 
  Vsetclass(vgrp_id_uleis_dump, "VG_ULEIS_DUMP");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_UDumpSet" )) ==FAIL) {
    print_uleis_dump_error("init_cr_uleis_dump -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_uleis_dump(Vgrp_descrp_UDumpSet);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_uleis_dump_error("init_cr_uleis_dump -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_UDumpSet, sizeof(Vgrp_descrp_UDumpSet))) ==FAIL) {
    print_uleis_dump_error("init_cr_uleis_dump -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_uleis_dump = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_uleis_dump_error("init_cr_uleis_dump -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_uleis_dump, "UDumpSet");
  VSsetclass(vdata_id_uleis_dump, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_uleis_dump, vdata_id_uleis_dump)) ==FAIL) {
    print_uleis_dump_error("init_cr_uleis_dump -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_uleis_dump, "output_sctime", DFNT_UINT32, (1) )) {
    print_uleis_dump_error("init_cr_uleis_dump -> VSfdefine: Couldn't define output_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_dump, "collect_sctime", DFNT_UINT32, (1) )) {
    print_uleis_dump_error("init_cr_uleis_dump -> VSfdefine: Couldn't define collect_sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_dump, "QAC", DFNT_UINT32, (1) )) {
    print_uleis_dump_error("init_cr_uleis_dump -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_dump, "dumptime_offset", DFNT_UINT16, (1) )) {
    print_uleis_dump_error("init_cr_uleis_dump -> VSfdefine: Couldn't define dumptime_offset");
    retval = -1;
  }
  if (VSfdefine(vdata_id_uleis_dump, "dump", DFNT_UINT8, (U_DUMP_SIZE) )) {
    print_uleis_dump_error("init_cr_uleis_dump -> VSfdefine: Couldn't define dump");
    retval = -1;
  }

  if (VSsetfields(vdata_id_uleis_dump,"output_sctime, collect_sctime, QAC, dumptime_offset, dump")){
    print_uleis_dump_error("init_cr_uleis_dump -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_uleis_dump(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_uleis_dump(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_uleis_dump(struct UDumpSet UDumpSet_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_uleis_dump_error();
void pack_uleis_dump();

  odata = (uint8 *) malloc(sizeof(struct UDumpSet));
  pack_uleis_dump(odata, &UDumpSet_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_uleis_dump, recnum)==-1) {
		print_uleis_dump_error("write_uleis_dump -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_uleis_dump, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_uleis_dump_error("write_uleis_dump -> VSwrite: Couldn't write data.");

  memset(&UDumpSet_struc, 0, sizeof(struct UDumpSet));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_uleis_dump()
{
  VSdetach(vdata_id_uleis_dump);
  Vdetach(vgrp_id_uleis_dump);
}

/*----     init access function    ----*/

int32 init_acc_uleis_dump(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_uleis_dump_error();


  if ((vdata_ref = VSfind(hdf_fp, "UDumpSet")) <= 0 ) {
    print_uleis_dump_error("init_acc_uleis_dump -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_uleis_dump = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_uleis_dump_error("init_acc_uleis_dump -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_uleis_dump, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_uleis_dump,"output_sctime, collect_sctime, QAC, dumptime_offset, dump")) {
      print_uleis_dump_error("init_acc_uleis_dump -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_uleis_dump(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_uleis_dump(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_uleis_dump(struct UDumpSet *UDumpSet_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_uleis_dump_error();
void unpack_uleis_dump();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct UDumpSet));
  VSinquire(vdata_id_uleis_dump, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_uleis_dump, recnum_rd)==FAIL) {
          print_uleis_dump_error("read_uleis_dump -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_uleis_dump, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_uleis_dump_error("read_uleis_dump -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_uleis_dump(odata, UDumpSet_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_uleis_dump()
{
  VSdetach(vdata_id_uleis_dump);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_uleis_dump(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_uleis_dump_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_UDumpSet" )) ==FAIL)
    print_uleis_dump_error("rd_Vgrp_uleis_dump -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_uleis_dump_error("rd_Vgrp_uleis_dump -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_uleis_dump_error("rd_Vgrp_uleis_dump -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_uleis_dump_error("rd_Vgrp_uleis_dump -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_UDumpSet, HDstrlen(Vgrp_descrp_UDumpSet)) ==FAIL)
    print_uleis_dump_error("rd_Vgrp_uleis_dump -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_UDumpSet);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_uleis_dump_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_uleis_dump.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_uleis_dump(uint8 *data, struct UDumpSet *UDumpSet_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &UDumpSet_ptr->output_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &UDumpSet_ptr->collect_sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &UDumpSet_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &UDumpSet_ptr->dumptime_offset, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &UDumpSet_ptr->dump[0], ((1)*(U_DUMP_SIZE)) );
   ptr+= ((1)*(U_DUMP_SIZE));
}

/*----   unpack function    ----*/

void unpack_uleis_dump(uint8 *data, struct UDumpSet *UDumpSet_ptr)
{
int32 ptr=0;

   memcpy(&UDumpSet_ptr->output_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&UDumpSet_ptr->collect_sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&UDumpSet_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&UDumpSet_ptr->dumptime_offset, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&UDumpSet_ptr->dump[0], data+ptr,  ((1)*(U_DUMP_SIZE)) );
   ptr+= ((1)*(U_DUMP_SIZE));
}
int32 get_vgrp_id_uleis_dump() {return(vgrp_id_uleis_dump);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_uleis_dump(char *wr_strval)
{
  strcpy(wr_strval, "The file 'uleis_dump.h' is shown below, it was used to create the data in the Vgroup named 'VG_UDumpSet'.\n\n");
  strcat(wr_strval,"/* Id: uleis_dump.h,v 1.6 1997/05/09 22:04:40 steves Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#define U_DUMP_SIZE    125	/* Memory dump size in bytes */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct UDumpSet\n");
  strcat(wr_strval,"{\n");
  strcat(wr_strval,"  uint32 output_sctime;		/* time for beginning of data output cycle */\n");
  strcat(wr_strval,"  uint32 collect_sctime;	/* time for beginning of data collection */\n");
  strcat(wr_strval,"  uint32 QAC;			/* number of bad frames in this cycle */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint16 dumptime_offset;	/* offset for output_sctime for dump */\n");
  strcat(wr_strval,"  uint8 dump[U_DUMP_SIZE];      /* dump: 125 bytes */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"};\n");
  return(0);
}
