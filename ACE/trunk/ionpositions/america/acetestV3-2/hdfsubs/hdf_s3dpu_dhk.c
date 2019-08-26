/* The RCS version of hdfgen.pl used to create this file is: */
/* $Id: hdfgen.pl,v 1.49 1999/11/04 17:17:13 asc Exp  */

/* The include file used to create this file is: */
/* $Id: s3_dhk.h,v 1.3 1998/12/07 18:12:39 ad Exp  */

#include "s3_dhk.h"
#include "df.h"

int32 vgrp_id_s3_dhk;
static int32 vdata_id_s3_dhk;

  /* 3545 is the size of s3_dhk.h + 1 added line */
char Vgrp_descrp_sshdhk[3545];

/****----  init create function  ----****/

int32 init_cr_s3_dhk(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{
  int32 retval=0;
  int32 vgrp_ref_w;
  int32 ann_id_w;
  int32 wr_Vgrp_desc_s3_dhk();

  void print_s3_dhk_error();

  /*         Setup a Vgroup         */
  if ((vgrp_id_s3_dhk = Vattach(hdf_fp, -1, "w"))==FAIL) {
    print_s3_dhk_error("init_cr_s3_dhk -> Vattach: Couldn't create Vgroup");
    retval = -1;
  }
  Vsetname(vgrp_id_s3_dhk, "VG_sshdhk"); 
  Vsetclass(vgrp_id_s3_dhk, "VG_S3_DHK");


  /*      Get the Vgroup reference     */
  if ((vgrp_ref_w = Vfind(hdf_fp, "VG_sshdhk" )) ==FAIL) {
    print_s3_dhk_error("init_cr_s3_dhk -> Vfind: Couldn't get Vgrp reference");
    retval = -1;
  }
  /*      Add a description to the Vgroup      */
  wr_Vgrp_desc_s3_dhk(Vgrp_descrp_sshdhk);

  if ((ann_id_w = ANcreate(an_id, DFTAG_VG, vgrp_ref_w, AN_DATA_DESC)) ==FAIL) {
    print_s3_dhk_error("init_cr_s3_dhk -> ANcreate: Can't create Vgrp description");
    retval = -1;
  }
  if ((ANwriteann(ann_id_w, Vgrp_descrp_sshdhk, sizeof(Vgrp_descrp_sshdhk))) ==FAIL) {
    print_s3_dhk_error("init_cr_s3_dhk -> ANwriteann: Can't write Vgrp description");
    retval = -1;
  }
  ANendaccess(ann_id_w);

  /*        Setup a Vdata        */
  if ((vdata_id_s3_dhk = VSattach(hdf_fp, -1, "w")) ==FAIL) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSattach: Couldn't attach to Vdata");
    retval = -1;
  }
  VSsetname(vdata_id_s3_dhk, "sshdhk");
  VSsetclass(vdata_id_s3_dhk, classname);

  /*       Insert the Vdata into the Vgroup       */
  if ((Vinsert(vgrp_id_s3_dhk, vdata_id_s3_dhk)) ==FAIL) {
    print_s3_dhk_error("init_cr_s3_dhk -> Vinsert: Couldn't insert Vdata into Vgroup");
    retval = -1;
  }

  /*    Define the fields in the Vdata    */
  if (VSfdefine(vdata_id_s3_dhk, "sctime", DFNT_UINT32, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define sctime");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "QAC", DFNT_UINT32, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define QAC");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "EDB", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define EDB");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "VERSION", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define VERSION");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "FLAGS", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define FLAGS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "LUCNT", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define LUCNT");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "IDLECTR", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define IDLECTR");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "JOB", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define JOB");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "SMODENEXT", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define SMODENEXT");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "SMODE", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define SMODE");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "MMODENEXT", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define MMODENEXT");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "MMODE", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define MMODE");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "CMODENEXT", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define CMODENEXT");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "CMODE", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define CMODE");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "SPINCTR", DFNT_UINT32, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define SPINCTR");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "RECORDCTR", DFNT_UINT32, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define RECORDCTR");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "MPOWER", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define MPOWER");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "CPOWER", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define CPOWER");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "SPOWER", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define SPOWER");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "SUNSECTOR", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define SUNSECTOR");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "SECTOR7LEN", DFNT_UINT16, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define SECTOR7LEN");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "SECTOR0LEN", DFNT_UINT16, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define SECTOR0LEN");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "SPINCLOCKS", DFNT_UINT16, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define SPINCLOCKS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "TTMUX", DFNT_UINT16, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define TTMUX");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "TTSTATUS", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define TTSTATUS");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "LUSTROBE", DFNT_UINT16, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define LUSTROBE");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "LUMASK", DFNT_UINT16, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define LUMASK");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "LUSTATE", DFNT_UINT16, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define LUSTATE");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "CLASSMUX", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define CLASSMUX");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "CMDOK", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define CMDOK");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "CMDERR", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define CMDERR");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "CMDHIST1", DFNT_UINT16, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define CMDHIST1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "CMDHIST2", DFNT_UINT16, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define CMDHIST2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "CMDHIST3", DFNT_UINT16, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define CMDHIST3");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "PARITYERR", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define PARITYERR");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "SCMDERR", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define SCMDERR");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "MCMDERR", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define MCMDERR");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "CCMDERR", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define CCMDERR");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "EEFILL", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define EEFILL");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "MEM0", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define MEM0");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "MEM1", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define MEM1");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "MEM2", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define MEM2");
    retval = -1;
  }
  if (VSfdefine(vdata_id_s3_dhk, "MEM3", DFNT_UINT8, (1) )) {
    print_s3_dhk_error("init_cr_s3_dhk -> VSfdefine: Couldn't define MEM3");
    retval = -1;
  }

  if (VSsetfields(vdata_id_s3_dhk,"sctime, QAC, EDB, VERSION, FLAGS, LUCNT, IDLECTR, JOB, SMODENEXT, SMODE, MMODENEXT, MMODE, CMODENEXT, CMODE, SPINCTR, RECORDCTR, MPOWER, CPOWER, SPOWER, SUNSECTOR, SECTOR7LEN, SECTOR0LEN, SPINCLOCKS, TTMUX, TTSTATUS, LUSTROBE, LUMASK, LUSTATE, CLASSMUX, CMDOK, CMDERR, CMDHIST1, CMDHIST2, CMDHIST3, PARITYERR, SCMDERR, MCMDERR, CCMDERR, EEFILL, MEM0, MEM1, MEM2, MEM3")){
    print_s3_dhk_error("init_cr_s3_dhk -> VSsetfields: Couldn't set fields");
    retval = -1;
  }

  return(retval);
}

/* Included for backwards compatibility */

int32 init_wr_s3_dhk(int32 hdf_fp, int32 sd_id, int32 an_id, char *classname)
{ return( init_cr_s3_dhk(hdf_fp, sd_id, an_id, classname) ); }

/******---- write function ----******/

int32 write_s3_dhk(struct sshdhk sshdhk_struc, int32 recnum)
{
  int32 retval = 0;
  uint8 *odata;

void print_s3_dhk_error();
void pack_s3_dhk();

  odata = (uint8 *) malloc(sizeof(struct sshdhk));
  pack_s3_dhk(odata, &sshdhk_struc);

  if(recnum!=-1) {
	if(VSseek(vdata_id_s3_dhk, recnum)==-1) {
		print_s3_dhk_error("write_s3_dhk -> VSseek: error.");
		retval = -1;
	}
  }
  if(VSwrite(vdata_id_s3_dhk, (uint8 *)odata, 1, FULL_INTERLACE) == -1)
    print_s3_dhk_error("write_s3_dhk -> VSwrite: Couldn't write data.");

  memset(&sshdhk_struc, 0, sizeof(struct sshdhk));
  free(odata);
  return(retval);
}

/*----   close write function    ----*/

void close_wr_s3_dhk()
{
  VSdetach(vdata_id_s3_dhk);
  Vdetach(vgrp_id_s3_dhk);
}

/*----     init access function    ----*/

int32 init_acc_s3_dhk(int32 hdf_fp, int32 sd_id, char *access_mode)
{
  int32 vdata_ref;
  int32 num_rec;

  void print_s3_dhk_error();


  if ((vdata_ref = VSfind(hdf_fp, "sshdhk")) <= 0 ) {
    print_s3_dhk_error("init_acc_s3_dhk -> VSfind: Found no vdata of specified type.");
    return(0);
  }
  if ((vdata_id_s3_dhk = VSattach(hdf_fp, vdata_ref, access_mode)) ==FAIL) {
    print_s3_dhk_error("init_acc_s3_dhk -> VSattach: Couldn't attach to hdf file.");
    return(-1);
  }

  VSinquire(vdata_id_s3_dhk, &num_rec, NULL, NULL, NULL, NULL);
  if (num_rec == 0) { return(0); }


  if (VSsetfields(vdata_id_s3_dhk,"sctime, QAC, EDB, VERSION, FLAGS, LUCNT, IDLECTR, JOB, SMODENEXT, SMODE, MMODENEXT, MMODE, CMODENEXT, CMODE, SPINCTR, RECORDCTR, MPOWER, CPOWER, SPOWER, SUNSECTOR, SECTOR7LEN, SECTOR0LEN, SPINCLOCKS, TTMUX, TTSTATUS, LUSTROBE, LUMASK, LUSTATE, CLASSMUX, CMDOK, CMDERR, CMDHIST1, CMDHIST2, CMDHIST3, PARITYERR, SCMDERR, MCMDERR, CCMDERR, EEFILL, MEM0, MEM1, MEM2, MEM3")) {
      print_s3_dhk_error("init_acc_s3_dhk -> VSsetfields: Unable to set fields.");
      return(-1);
  }
  return(num_rec);
}

/* Included for backwards compatability */

int32 init_rd_s3_dhk(int32 hdf_fp, int32 sd_id, char *access_mode)
{ return ( init_acc_s3_dhk(hdf_fp, sd_id, access_mode) ); }

/******---- read function ----******/

int32 read_s3_dhk(struct sshdhk *sshdhk_struc, int32 recnum_rd)
{
int32 maxrec;
static int32 last_recnum = -1;
int32 retval = 0;
uint8 *odata;

void print_s3_dhk_error();
void unpack_s3_dhk();

  if(recnum_rd==-1) recnum_rd=last_recnum+1;

  odata = (uint8 *) malloc(sizeof(struct sshdhk));
  VSinquire(vdata_id_s3_dhk, &maxrec, NULL, NULL, NULL, NULL);
  if (recnum_rd >= maxrec) return(-1);
  if (recnum_rd != last_recnum+1)
      if (VSseek(vdata_id_s3_dhk, recnum_rd)==FAIL) {
          print_s3_dhk_error("read_s3_dhk -> VSseek unsuccessful");
          retval = -1;
    }
  last_recnum = recnum_rd;

  if(VSread(vdata_id_s3_dhk, (uint8 *)odata, 1, FULL_INTERLACE) ==FAIL) {
    print_s3_dhk_error("read_s3_dhk -> VSread: Couldn't read data.");
    retval = -1;
  }
  unpack_s3_dhk(odata, sshdhk_struc);
  free(odata);
  return(retval);
}

/*----   close read function    ----*/

void close_rd_s3_dhk()
{
  VSdetach(vdata_id_s3_dhk);
}

/*----  Read V group description, function    ----*/
void rd_Vgrp_desc_s3_dhk(int32 hdf_fp, int32 an_id)
{
  int32 ann_id_r;
  int32 num_ann;
  int32 *ann_list;
  int32 vgrp_ref_r;

void print_s3_dhk_error();

  /*      Get the Vgroup reference     */
  if ((vgrp_ref_r = Vfind(hdf_fp, "VG_sshdhk" )) ==FAIL)
    print_s3_dhk_error("rd_Vgrp_s3_dhk -> Vfind: Couldn't get Vgrp reference.");

  if ((num_ann = ANnumann(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r)) ==FAIL)
    print_s3_dhk_error("rd_Vgrp_s3_dhk -> ANnumann: Couldn't get number of annotations.");

    ann_list = HDmalloc(num_ann * sizeof(int32));
  if ((num_ann = ANannlist(an_id, AN_DATA_DESC, DFTAG_VG, vgrp_ref_r, ann_list)) ==FAIL)
    print_s3_dhk_error("rd_Vgrp_s3_dhk -> ANannlist: Couldn't");

  if ((ann_id_r = ANselect(an_id, (num_ann-1), AN_DATA_DESC)) ==FAIL)
    print_s3_dhk_error("rd_Vgrp_s3_dhk -> ANselect: Couldn't");

  if (ANreadann(ann_id_r, Vgrp_descrp_sshdhk, HDstrlen(Vgrp_descrp_sshdhk)) ==FAIL)
    print_s3_dhk_error("rd_Vgrp_s3_dhk -> ANreadann: Couldn't");

  printf("AN: %s\n", Vgrp_descrp_sshdhk);
  ANendaccess(ann_id_r);
  ANend(an_id);
}

/*----   error function    ----*/

void print_s3_dhk_error(int8 *mess)
{
  fprintf(stderr,"\nERROR in  hdf_s3dpu_dhk.c -> %s\n", mess);
  HEprint(stderr, 0);
}

/*----   pack function    ----*/

void pack_s3_dhk(uint8 *data, struct sshdhk *sshdhk_ptr)
{
int32 ptr=0;

   memcpy(data+ptr, &sshdhk_ptr->sctime, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sshdhk_ptr->QAC, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sshdhk_ptr->EDB, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->VERSION, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->FLAGS, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->LUCNT, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->IDLECTR, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->JOB, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->SMODENEXT, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->SMODE, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->MMODENEXT, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->MMODE, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->CMODENEXT, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->CMODE, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->SPINCTR, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sshdhk_ptr->RECORDCTR, ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(data+ptr, &sshdhk_ptr->MPOWER, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->CPOWER, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->SPOWER, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->SUNSECTOR, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->SECTOR7LEN, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshdhk_ptr->SECTOR0LEN, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshdhk_ptr->SPINCLOCKS, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshdhk_ptr->TTMUX, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshdhk_ptr->TTSTATUS, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->LUSTROBE, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshdhk_ptr->LUMASK, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshdhk_ptr->LUSTATE, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshdhk_ptr->CLASSMUX, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->CMDOK, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->CMDERR, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->CMDHIST1, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshdhk_ptr->CMDHIST2, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshdhk_ptr->CMDHIST3, ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(data+ptr, &sshdhk_ptr->PARITYERR, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->SCMDERR, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->MCMDERR, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->CCMDERR, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->EEFILL, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->MEM0, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->MEM1, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->MEM2, ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(data+ptr, &sshdhk_ptr->MEM3, ((1)*(1)) );
   ptr+= ((1)*(1));
}

/*----   unpack function    ----*/

void unpack_s3_dhk(uint8 *data, struct sshdhk *sshdhk_ptr)
{
int32 ptr=0;

   memcpy(&sshdhk_ptr->sctime, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sshdhk_ptr->QAC, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sshdhk_ptr->EDB, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->VERSION, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->FLAGS, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->LUCNT, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->IDLECTR, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->JOB, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->SMODENEXT, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->SMODE, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->MMODENEXT, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->MMODE, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->CMODENEXT, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->CMODE, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->SPINCTR, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sshdhk_ptr->RECORDCTR, data+ptr,  ((4)*(1)) );
   ptr+= ((4)*(1));
   memcpy(&sshdhk_ptr->MPOWER, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->CPOWER, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->SPOWER, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->SUNSECTOR, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->SECTOR7LEN, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshdhk_ptr->SECTOR0LEN, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshdhk_ptr->SPINCLOCKS, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshdhk_ptr->TTMUX, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshdhk_ptr->TTSTATUS, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->LUSTROBE, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshdhk_ptr->LUMASK, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshdhk_ptr->LUSTATE, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshdhk_ptr->CLASSMUX, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->CMDOK, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->CMDERR, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->CMDHIST1, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshdhk_ptr->CMDHIST2, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshdhk_ptr->CMDHIST3, data+ptr,  ((2)*(1)) );
   ptr+= ((2)*(1));
   memcpy(&sshdhk_ptr->PARITYERR, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->SCMDERR, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->MCMDERR, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->CCMDERR, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->EEFILL, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->MEM0, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->MEM1, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->MEM2, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
   memcpy(&sshdhk_ptr->MEM3, data+ptr,  ((1)*(1)) );
   ptr+= ((1)*(1));
}
int32 get_vgrp_id_s3_dhk() {return(vgrp_id_s3_dhk);}

/*----   V group description function    ----*/

int32 wr_Vgrp_desc_s3_dhk(char *wr_strval)
{
  strcpy(wr_strval, "The file 's3_dhk.h' is shown below, it was used to create the data in the Vgroup named 'VG_sshdhk'.\n\n");
  strcat(wr_strval,"/* Id: s3_dhk.h,v 1.3 1998/12/07 18:12:39 ad Exp $ */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"#include \"hdfi.h\"\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"struct sshdhk {\n");
  strcat(wr_strval,"  uint32 sctime;    /* first minor frame of edb, 32 bit spacecraft time */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"  uint32 QAC;       /* number of missing minor frames in edb */\n");
  strcat(wr_strval,"\n");
  strcat(wr_strval,"    uint8 EDB;      /* EDB number in this SR         */\n");
  strcat(wr_strval,"    uint8 VERSION;      /* Software Version         */\n");
  strcat(wr_strval,"    uint8 FLAGS;        /* Flag Byte               */\n");
  strcat(wr_strval,"		       /* 0x80 Artificial Spin Flag    */\n");
  strcat(wr_strval,"		       /* 0x40 Spin Clock Absent Flag   */\n");
  strcat(wr_strval,"		       /* 0x28 Sun Clock Absent Flag    */\n");
  strcat(wr_strval,"		       /* 0x04 Memory Scrubbing Flag    */\n");
  strcat(wr_strval,"		       /* 0x02 Automatic Telemetry Mode*/\n");
  strcat(wr_strval,"		       /* 0x01 MPB Identifier           */\n");
  strcat(wr_strval,"    uint8 LUCNT;        /* Latch-up Counter         */\n");
  strcat(wr_strval,"    uint8 IDLECTR;      /* Idle Counter             */\n");
  strcat(wr_strval,"    uint8 JOB;          /* Job Status               */\n");
  strcat(wr_strval,"    uint8 SMODENEXT;    /* SEPICA Next Mode         */\n");
  strcat(wr_strval,"    uint8 SMODE;        /* SEPICA Mode              */\n");
  strcat(wr_strval,"    uint8 MMODENEXT;    /* SWIMS Next Mode          */\n");
  strcat(wr_strval,"    uint8 MMODE;        /* SWIMS Mode               */\n");
  strcat(wr_strval,"    uint8 CMODENEXT;    /* SWICS Next Mode          */\n");
  strcat(wr_strval,"    uint8 CMODE;        /* SWICS Mode               */\n");
  strcat(wr_strval,"    uint32 SPINCTR;      /* Spin Counter             */\n");
  strcat(wr_strval,"    uint32 RECORDCTR;    /* Record Counter           */\n");
  strcat(wr_strval,"    uint8 MPOWER;       /* SWIMS Power State        */\n");
  strcat(wr_strval,"    uint8 CPOWER;       /* SWICS Power State        */\n");
  strcat(wr_strval,"    uint8 SPOWER;       /* SEPICA Power State       */\n");
  strcat(wr_strval,"    uint8 SUNSECTOR;    /* Sun Sector               */\n");
  strcat(wr_strval,"    uint16 SECTOR7LEN;   /* Sector 7 Lenght          */\n");
  strcat(wr_strval,"    uint16 SECTOR0LEN;   /* Sector 0 Lenght          */\n");
  strcat(wr_strval,"    uint16 SPINCLOCKS;   /* Number of Spin Clocks    */\n");
  strcat(wr_strval,"    uint16 TTMUX;        /* TT Mux                   */\n");
  strcat(wr_strval,"    uint8 TTSTATUS;     /* TT Status                */\n");
  strcat(wr_strval,"    uint16 LUSTROBE;     /* latch-up Strobe Mask     */\n");
  strcat(wr_strval,"    uint16 LUMASK;       /* latch-up Mask            */\n");
  strcat(wr_strval,"    uint16 LUSTATE;      /* latch-up State           */\n");
  strcat(wr_strval,"    uint8 CLASSMUX;    /* Muliplexer Classifications */\n");
  strcat(wr_strval,"			/* 0xc0 Classification Mux 3     */\n");
  strcat(wr_strval,"			/* 0x30 Classification Mux 2     */\n");
  strcat(wr_strval,"			/* 0x0c Classification Mux 1     */\n");
  strcat(wr_strval,"			/* 0x03 Classification Mux 0     */\n");
  strcat(wr_strval,"    uint8 CMDOK;        /* Command Ok Counter       */\n");
  strcat(wr_strval,"    uint8 CMDERR;       /* Command Error Counter    */\n");
  strcat(wr_strval,"    uint16 CMDHIST1;     /* Command History 1        */\n");
  strcat(wr_strval,"		      /* 0xff00 Command History 1 ID     */\n");
  strcat(wr_strval,"		      /* 0x00e0 Command History 1 Type   */\n");
  strcat(wr_strval,"		      /* 0x001f Command History 1 Lenght */\n");
  strcat(wr_strval,"    uint16 CMDHIST2;     /* Command History 2        */\n");
  strcat(wr_strval,"		      /* 0xff00 Command History 2 ID     */\n");
  strcat(wr_strval,"		      /* 0x00e0 Command History 2 Type   */\n");
  strcat(wr_strval,"		      /* 0x001f Command History 2 Lenght */\n");
  strcat(wr_strval,"    uint16 CMDHIST3;     /* Command History 3        */\n");
  strcat(wr_strval,"		      /* 0xff00 Command History 3 ID     */\n");
  strcat(wr_strval,"		      /* 0x00e0 Command History 3 Type   */\n");
  strcat(wr_strval,"		      /* 0x001f Command History 3 Lenght */\n");
  strcat(wr_strval,"    uint8 PARITYERR;    /* Parity Errors            */\n");
  strcat(wr_strval,"    uint8 SCMDERR;      /* SEPICA Command Errors    */\n");
  strcat(wr_strval,"    uint8 MCMDERR;      /* SWIMS Command Errors     */\n");
  strcat(wr_strval,"    uint8 CCMDERR;      /* SWICS Command Errors     */\n");
  strcat(wr_strval,"    uint8 EEFILL;       /* EEPROM Fill Status       */\n");
  strcat(wr_strval,"    uint8 MEM0;        /* Class 0-A,B Check          */\n");
  strcat(wr_strval,"    uint8 MEM1;        /* Class 1-A,B Check          */\n");
  strcat(wr_strval,"    uint8 MEM2;        /* Class 2-A,B Check          */\n");
  strcat(wr_strval,"    uint8 MEM3;        /* Class 3-A,B Check          */\n");
  strcat(wr_strval,"};\n");
  return(0);
}
