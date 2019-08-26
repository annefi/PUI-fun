/*
  Filename: loadPha.cc

  Description:  
  Loads vector of Pha objects by reading data from Level 1 files. 

  Created by : Jim Raines, 1May2001

  Major Modification History
    Adapted from al2c.c.  J. Raines, 1May2001

*/

#include "swindal.h"
extern "C" {
#include "libhef.h"
}

int dumpPha(Pha *pha, int npha, int ncycle);

int loadPha(vector<Pha> *pha, int AnalysisInterval){
  /* parameters */
  const int iPrintInterval=10;  // printing interval for per cycle stdout info.

  /* local software housekeeping variables */
  const char thisprog[]="loadPha";  // name of this program
  int i,j,k;             // short range loop counters
  int status = 0;        // exit status of routine

  int result;            // return value from libhef function
  int a3rcresult=0;      // return value from a3readcycle

  char infile[150];      // input data filename
  FILE *pInfile;         // input file stream

  int nedb;              // counter for looping over EDBs
  int npha;              // counter for looping over PHAs
  int irange;            // counter for counter for looping over ranges

  static bool fNewFile = true;  // true => open new file

  int DbgLvl= gDbgLvl;   // init local debugging level to global one

  bool fKeep;            // T => store PHA in big vector; F => discard

  /* data variables */
  Pha lpha;              // local pha object, put into vector at end
  list<Pha> cycpha;      // PHA words from current cycle
  list<Pha>::iterator cycpha_it;

  /* -- stats variables -- */
  // for proton speed
  double eq[MAXEDB];    // set of eq values used for weights
  int nphaedb[MAXEDB];   // number of pha words per EDB
  static long int nphatot = 0;      // total number of PHA words read thus far
  double hspeed;          // H+ speed for current cycle

  // for weights
  int br[MAXEDB][3];     // basic rates for this cycle
  int npharng[MAXEDB][4]; // npha with a range of second index
  double weight[MAXEDB]; // factor to scale nphaedb to actual if all
                         // PHAs had been transmitted

  // misc. counters
  int ncycle=0;          // number of cycles read
  int ncyclemax;         // number of cycles to analyze
  long nlines=0;         // number of lines written to outfile
  long nto=0;            // number of PHAs thrown out
  float topercent;       // thrown-out % for PHAs

  /* ---------
     open file
     ---------
  */

  if (fNewFile){
    strcpy(infile,gCurLv1File.c_str());
    printf("%s -D- %szzzz\n",thisprog,infile);

    result = a3opencyclefile(infile);
    if (result != 0) {
      printf("%s -F- error (%d) opening %s\n",thisprog,result,infile);
      return(1);
    }

    fNewFile = false;
  }

  /* ---------------- */
  /* Loop over cycles */
  /* ---------------- */

  ncyclemax = AnalysisInterval;
  if (DbgLvl > 0){
    printf("%s -I- reading %d cycles maximum\n",thisprog, ncyclemax);
  }

  while (a3rcresult == 0 && ncycle <= ncyclemax){
  //while (a3rcresult == 0 && ncycle < 1){
    a3rcresult = 1;

    /* re-init. some counters */
    for (nedb = FIRSTEDB; nedb < MAXEDB; nedb++)
      for (i = 0; i < 4; i++)
	npharng[nedb][i] = 0;

    /* Get ACE cycle and expand */
    /* ------------------------ */
    a3rcresult = a3readcycle();
    if (result > 0){
	printf("%s -E- a3readcycle returned %d\n",thisprog, result);
    }
    else{
      result = a3expand();
      if (result > 0)
	printf("%s -E- a3readcycle returned %d\n",thisprog, result);
    }
 
    /* set level of output messages from libhef */
    result = perr_setlevel(1);

    /* cycle time */
    if (! (ncycle % iPrintInterval))
      printf("%s -I- Cycle[%03d] time is %s\n",thisprog,ncycle,a3zrecid());

    /* scet -- spacecraft event time
       This is reported in seconds since 1Jan1950 to work with Nathan's 
       code.  The offset of seconds since 1Jan1970 to 1Jan1950 is:

       offset = 86400 sec/day * ( 20 year * 365 day/year + 5 days (leap))
    */
    lpha.scet = a3gtime() + (double)(86400*(20*365 + 5));

    /* Get everything else */
    /* ------------------- */
    for (nedb=FIRSTEDB; nedb < MAXEDB; nedb++){
      
      /* get number of pha words */

      nphaedb[nedb] = a3xnpha(nedb);
      cout << thisprog << " -D- nphaedb[" <<nedb << "]=" << nphaedb[nedb] <<endl;

      // this should not be needed now that we have 
      /* info in EDB 0 must be discarded -- this EDB does not contain
	 proper info. from libhef. */
//       if (nedb == 0){
// 	/*printf("%s -I- zeroing nphaedb[%02d]=%d\n",thisprog,nedb,
// 	  nphaedb);*/
// 	nphaedb[nedb] = 0;
//       }

      /* store edb number */
      lpha.nedb = nedb;

      /* get eq */
      /* The -1 comes from the fact that PHA words are put into the TM
	 one EDB after they are actually read.  This re-aligns them
	 with the E/q at which they were measured.
	 See libhef docs for details. */
      lpha.eq = a3gxeqdpu_i(nedb - 1);

      /* get items for each PHA */
      for (npha = 0; npha < nphaedb[nedb]; npha++){
	
	/* assign tof
	   tch is converted to ns by 0.1955 ns/ch (from Simon Hefti) */
	lpha.tofch = a3gxtof_i(nedb,npha);
	lpha.tof = lpha.tofch * 0.1955;
	
	/* assign energy */
	/* ech (digital energy) conv. to keV by 2.395 keV/ch (from S. Hefti)*/
	lpha.esdch = a3gxesd_i(nedb,npha);
	lpha.esd = lpha.esdch * 2.395;
	
	/*assign sector */
        lpha.sector = a3gxsec_i(nedb,npha);

	/* assign detector*/
	lpha.detector = a3gxdid_i(nedb,npha); // right func.?

	/* assign range and count number in each range */
	lpha.range = a3gxrng_i(nedb,npha);
	
	// keep track of number of pha in each range for weighting (later)
	if (lpha.range >= 0 && lpha.range <= 3){
	  npharng[nedb][lpha.range]++;
	}
	else{
	  printf("%s -W- range out of limits",thisprog);
	}

	/* assign br0-2 */
	for( i = 0; i < 4; i++){
	  lpha.br[i] = a3gxbr(nedb, i, 8);
	  br[nedb][i] = lpha.br[i];  // store in local array for weighting
	}

	/* assign TCR */
	lpha.tcr = a3gxtcr_i(nedb,8);
	
	/* assign mass */
	lpha.mmch = a3gxmas_i(nedb,npha);
	if (lpha.mmch == 0){    // handle special channels, see libhef docs
	  /* signify mass zero events as zero */
	  lpha.mm = 0.0;
	}
	else if (lpha.mmch >= 123){
	  // just pass on the channel; beware in further processing
	  lpha.mm = lpha.mmch * 10.0;
	}
	else {
	  // not a special channel, convert normally
	  lpha.mm = a3cxmas(lpha.mmch);
	  if (lpha.mm == -1.0){ 
	    printf("%s -W- a3cxmas returned error (-1.0) ", thisprog);
	    printf("for non-special channel.  Discarding pha.\n");
	    printf("+ lpha.mmch = %d lpha.mm = %f\n",lpha.mmch,lpha.mm);
	    fKeep = false;
	  }
	}
	
	/* assign m/q */
	lpha.mqch = a3gxmoq_i(nedb,npha) ;
        /* handle special channels, see libhef docs */
	if (lpha.mqch == 0){
	  /* just pass on the channel; beware in further
	     processing */
	  lpha.mq = 0.0;
	}
	else if (lpha.mqch < 1){ // should never occur
	  printf("%s -W- 0 < mqch < 1 not handled correctly\n",thisprog);
	  lpha.mq = lpha.mqch / 10.0;
	}	      
	else if (lpha.mqch > 124){
	  /* just pass on the channel; beware in further
	     processing */
	  lpha.mq = lpha.mqch * 10.0;
	}
	else {
	  /* not a special channel, convert normally */
	  lpha.mq = a3cxmoq(lpha.mqch);
	  if (lpha.mq == -1.0){
	    printf("%s -W- a3cxmoq returned error (-1.0) ", thisprog);
	    printf("for non-special channel.  Discarding pha.\n");
	    printf("+ lpha.mmch = %d lpha.mm = %f\n",lpha.mqch,lpha.mq);
	    fKeep = false;
	  }
	}

	/* Add to this cycles PHA list if this is a good one */
	if (fKeep) {
	  cycpha.push_back(lpha);
	}
	else {
	  nto++;  // one more pha thrown out

	  if (DbgLvl > 1) {
	    cout << "thisprog -I- discarded current PHA\n";
	  }
	}
			   

      } /* loop over phas */
    } /* loop over edbs */


    /* calculate H+ speed for this cycle */
    hspeed = swspeed(eq,nphaedb,1.0,0.8); // moq = 1.0, cutoff = 0.8

    if (! (ncycle % iPrintInterval))
      printf("%s -I- SW speed = %10.2f\n",thisprog,hspeed);

    /* --- calculate PHA weighting for each EDB --- */
    if (DbgLvl > 1) {
      printf("%s -D- nphaedb = \n", thisprog);
    }

     for (nedb = FIRSTEDB; nedb < MAXEDB; nedb ++){
      /* print number of PHA words by EDB */
      if (DbgLvl > 1) printf("%d ", nphaedb[nedb]);
      nphatot += nphaedb[nedb];
      
      for(irange = 0; irange < 4; irange++){
	if( npharng[nedb][irange] > 0 && br[nedb][irange] > 0){
	  weight[nedb] = (float)br[nedb][irange] /
	    (float)npharng[nedb][irange];
	}
	else
	  weight[nedb] = 0.0;
      
      }

    }
    if (DbgLvl > 1) printf("\n");

    if (DbgLvl > 0) {
      if (nphatot > 0) {
	topercent = (float)nto * 100.0 / (float)nphatot ;
      }
      else {
	topercent = 0;
      }

      printf("%s -I- read %d PHAs so far, %d thrown out (%03.1f%%)\n",
	     thisprog,nphatot, nto, topercent);
    }

    // Store weights in phas from this cycle and add them to big vector
    cycpha_it = cycpha.begin();
    while (cycpha_it != cycpha.end()){

      if (cycpha.front().nedb < MAXEDB){
	cycpha.front().weight = weight[cycpha.front().nedb];
      }
      else {
	printf("%s -W- nedb=%d (out of range)\n",thisprog,cycpha.front().nedb);
      }

      if ( hspeed > 0 &&  hspeed < 10000 ){
	cycpha.front().hspeed = hspeed;
      }
      else {
	//printf("%s -W- hspeed = %6.2f (out of range)\n",thisprog,hspeed);
      }
      
      // add 
      pha->push_back(cycpha.front());

      // pop this element off
      cycpha.pop_front();

      // set iterator to new beginning of vector (pop changed it)
      cycpha_it = cycpha.begin();
    
    }
  
    ncycle++;

  } /* loop over cycles */  

  if (a3rcresult != 0){
    a3closecyclefile();

    cout << thisprog << " -I- end of file reached (" << result << ")\n";

    status = 2;
    fNewFile = true;
  }

  return status;
}

/* print PHA info to stdout */
int dumpPha(Pha *pha, int npha, int ncycle){

  /* scet, nedb, npha, eq */
  printf("%010.0f %02d %03d %6.2f",pha->scet, pha->nedb,npha,pha->eq);

  /* tof, esd, sector */
  printf(" %10.2f %10.2f %02d",pha->tof,pha->esd,pha->sector);

  /* range, br0-2, wt */
  printf(" %01d %05d %05d %05d %10.2f",pha->range,
	  pha->br[0],pha->br[1],pha->br[2], pha->weight);
  
  /* vw, mm, mq, ncycle, asp */
  printf(" %10.2f %10.2f %10.2f %03d %6.2f\n",pha->hspeed,pha->mm,pha->mq,
	 ncycle,pha->asp);

  return(0);
}  
