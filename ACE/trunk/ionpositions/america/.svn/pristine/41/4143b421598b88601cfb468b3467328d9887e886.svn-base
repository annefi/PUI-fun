// File: a3dif.i
// (c) 1998/1999 Simon Hefti (hefti@umich.edu)
// $Id: a3dif.i,v 1.6 2004/05/20 14:58:18 jraines Exp $

%subsection "binary data: reading and expanding"

%text %{
  Typical use of these routines (perl code):
  // open file
  $res = libhef::a3opencyclefile($fn);
  if( $res ) { exit(1); }

  // loop
  $rres = 0;
  while($rres == 0) {
    // read
    $rres = libhef::a3readcycle();
    // stop on error
    if( $rres != 0 ) {last};
    // decode data
    $res  = libhef::a3expand();

    // (your code to access data here)
  }
  // close
  $res = libhef::a3closecyclefile();
%}

/* open netCDF SWICS/ACE EDB file for reading */
extern int    a3opencyclefile  (char *zfn);

/* close at the end */
extern int    a3closecyclefile (void);

/* read one cycle, keep in memory for further processing */
extern int    a3readcycle      (void);

/* decompress TLM bytes to meaningfull values */
extern int    a3expand         (void);


%subsection "time information"

/* get time of beginning of cycle */
extern double a3gtime(void);

// string describing record number and time
extern char *a3zrecid(void);

%subsection "file and library version information"

// report name of original HDF file (if available)
extern char *a3hdffn(void);

// report version of my netCDF file format
extern char *a3ncfver(void);

%subsection "S3DPU Housekeeping"
/* S3DPU Housekeeping Block Item (raw)
   Returns ith element of S3DPU HK array for edb ie.  There are 48
   elements total.  (C users use constant 'NDHK' to avoid hardcoding.)
   
   C users:
   --------
   Data can be accessed via mnemonics and masks from 'ACE S3DPU
   Command and Data Document'.  See libhef::decoded.h for details.
   For example, the latchup state can be extracted with the following
   code:

   BYTE lustate
   lustate = a3gdpuhk(ie, LSSDLUSTATE) & MSSDLUSTATE;

   NOTE:  This does not work with items having masks larger than 0xff.  
   In that case, assemble the word according to the mask.
*/
extern BYTE   a3gdpuhk(int ie,int i);

%subsection "SWICS: quality checking"

// ensure settings of SWICS/ACE. Checked are:
// [] increasing record counter [] increasing time
// [] no problems encountered when decompressing rates
// [] needed EDBs (22,42,47,53,54) are present in cycle
// [] MCP Level 2               [] PAPS Level 127
// [] HK values for E/q are monotonically decreasing
// [] E/q table from EDBs is compared with known table itab
//    possible itabs are: 0 --> nominal table
//                        1 --> table used in Jan 1998
//    if omitted, itab=0 is used
// [] meaningfull rates: FSR,DCR,TCR,SDR all >= 0.0 and DCR >= TCR
// Note: all testing routines are separatly available in libhef,
//       but I did not write an interface for perl yet.
extern int a3cycx_nominal(int itab=0);




%subsection "SWICS: instrument status and DPU settings"



// get SWICS E/q [kV] of step ie.
// Calculated from CNQ structure and E/q Table as found in DPU Spare
// Block of current cycle.
// The user has to make sure that he combines the correct data and
// E/q values. The routine does not do this (minimal impact philosophy).
// In nominal stepping mode, one will find:
// 99.979 kV for EDB 0 and 0.612 kV for EDB 59.
extern double a3gxeqdpu_i(int ie);

// SWICS digital value of E/q as found in DPU Spare block of this cycle.
// This is the command sent to the instrument in step i. The conversion
// to kV relies on calibration and might depend on temperature and
// aspect angle. For the "default conversion", use
// a3gxeqdpu_i to get the value in kV.
extern int a3gxeqtab_i(int ie);


// get SWICS E/q [kV] for AUX channel of step ie.
// See a3gxeqdpu_i for description.
extern double a3gxeqaux_i(int ie);


// SWICS PAPS according to DPU (not HK) [kV].
// Calculated from CNQ structure and PAPS Level as found in DPU Spare
// Block of current cycle.
extern double a3gxpavdpu(void);

// PAPS Level for SWICS
extern int a3xpavlev(void);

// SWICS ADC State: on (1) or off (0)
extern int a3xadc(void);

// SWICS "Cal Trigger" state on (1) or off (0)
extern int a3xtrigcal(void);

// SWICS Trigger Mode (T AND E, T OR E, E only, T only)
extern int a3xtrigmode(void);

// SWICS DPU settings for m/q classification (CNQ)
extern double *a3gcnq          (void);

// SWICS DPU settings for m   classification (CNM)
extern double *a3gcnm          (void);

// SWICS Basic Rates Definition in [channels] of DPU classification.
// -------------------------------------------------
// icorn   reference
// 0       minimal m/q
// 1       maximal m/q
// 2       minimal m
// 3       maximal m
// 4       range being defined
// -------------------------------------------------
// Notes: 1) several boxes can be used to define one range.
// 2) A maximum of 8 boxes can be defined for the Basic Rates.
// 3) 255 indicates undefined value.
// See also: decoded.h and asummary.pl for definitions and usage.
extern int a3gbrtab(int ibox, int icorn);

// SWICS Matrix Rates Definition in [channels] of DPU classification.
// ------------------------------------------------------------------
// icorn   reference
// 0       minimal m/q 
// 1       maximal m/q 
// 2       minimal m
// 3       maximal m
// 4       matrix rate being defined
// -------------------------------------------------------------------
// Notes: 1) several boxes can be used to define one matrix rate.
// 2) A maximum of 20 boxes can be defined for the Matrix Rates.
// 3) 255 indicates undefined value
// See also: decoded.h and asummary.pl for definitions and usage.
extern int a3gmrtab(int ibox, int icorn);

/* SWICS Housekeeping Block Item (converted)
   Returns ith element of SWICS HK array for edb ie.  There are 25
   elements total.  (C users use constant 'NXHK' to avoid hardcoding.)
   
   C users:
   --------
   Data can be accessed via mnemonics similar to those in 'ACE S3DPU
   Command and Data Document'.  See libhef::decoded.h for details.
   For example, the main current can be retrieved with the following
   code:

   float x_main_current_1;
   x_main_current_1 = a3gxhk(ie, LXGPI1);

   NOTE:  Unlike the raw HK blocks, masks are not needed since these
   items are already extracted/assembled and converted to physical units.

*/
extern float a3gxhk(int ie, int i);

%subsection "SWICS Rates"

// get SWICS FSR of EDB ie and sector isec
// If isec is omitted or 8, FSR summed over sectors will be returned
// see also: a3gx===_i, where === can be fsr,dcr,tcr,sdr
extern double a3gxfsr_i(int ie, int isec=8);
 

// get SWICS DCR[ie] of EDB ie and sector isec
// If isec is omitted or 8, FSR summed over sectors will be returned
// see also: a3gx===_i, where === can be fsr,dcr,tcr,sdr
extern double a3gxdcr_i(int ie, int isec=8);


// get SWICS TCR[ie] of EDB ie and sector isec
// see also: a3gx===_i, where === can be fsr,dcr,tcr,sdr
extern double a3gxtcr_i(int ie, int isec=8);


// get SWICS SSD Rate of EDB ie and sector isec
// see also: a3gx===_i, where === can be fsr,dcr,tcr,sdr
extern double a3gxsdr_i(int ie, int isec=8);


// SWICS "proton rate" (AUX)  of EDB ie and sector isec
// If isec is omitted or 8, sum over sectors is returned
extern double a3gxpr_i(int ie, int isec=8);


// SWICS "alpha rate" (AUX)  of EDB ie and sector isec
// If isec is omitted or 8, sum over sectors is returned
extern double a3gxar_i(int ie, int isec=8);


// SWICS Matrix Rate imr in Step ie and Sector isec
// If isec is omitted, sum over sectors is returned (or use isec=8)
// 0     H+        Note: this is the default definition of the 
// 1     He++            SWICS Matrix Rate boxes. However, the
// 2     He+             hard-wired definition within the DPU
// 3     O7+             is different from this setup. Whenever
// 4     O6+             the DPU resets, the Matrix Rate box
// 5     Fe              definition must be uploaded manually.
// 6     Si
// 7     Err
extern double a3gxmr(int imr, int ie, int isec=8);

// SWICS matrix rate imr of EDB ie in sector isec.
// This is identical to a3gxmr except 
//   1) this returns double
//   2) the edb number (ie) and rate number (imr) are swapped
//      in the calling sequence.
// See a3gxmr for other details. 
long a3gxmr_i(int ie, int imr, int isec=8);

//
// SWICS Basic Rate of Range ibr at EDB ie of secot sec
// if isec is omitted or 8, the sum over all sectors is returned
// (stored in ...[NSEC] in the cycle structure)
extern long a3gxbr(int ie, int ibr, int isec=8);

// SWICS Basic Rate weigth at EDB ie, BR ibr
// Note: Basic Rate Definition is commandable and therefore
// can change in time. Use libhef::a3gbrtab to
// get the currently active table.
// The idea is as follows:
// Range Ions         Def
// 0     He++ and H+  0 < m ca<= 10 
// 1     minor ions   10 ca<= m <= 100
// 2     pick-up ions 
// 3     everything else ("error range")
// See also: a3xnpha, a3gbrtab.
extern double a3xbrwgt(int ie, int ibr);




%subsection "SWICS PHAs", pre

// total number of SWICS PHAs in EDB ie
// Note that ie refers to the EDB number, rather than to the
// E/q voltage (Tech Note 3)
extern int a3xnpha(int ie);

// number of PHAs in range ibr,sector sec, EDB ie
// if isec is omitted or 8, the sum over all sectors is returned
// (stored in ...[NSEC] in the cycle structure)
extern int a3gxnr(int ie, int ibr, int isec=8);

// SWICS PHA[i]: m/q (just one PHA word) in DPU units (channels)
//
// The DPU truncates the number to get the integer value
// (cuts the digits after the point). This number has been
// calculated during the "expand" process using the "DPU simulator"
// (check out asxdpusim.c). I often use it to do histograms
// in m-m/q (colored plots).
// A couple of channels have special meaning (the "DPU
// simulator" does try to imitate the DPU in all aspects):
// MQUNDER    0 Output this code if M/Q is too small
// MQOVER   125 Output this code if M/Q is too big  
// TOFUNDER 126 Output this code if TOF is too small
// TOFOVER  127 Output this code if TOF is too big  
//
// Check result: -1.0 indicates error (see error message)
extern double a3gxmoq_i(int ie, int i);


// SWICS PHA[i]: mass (just one PHA word) in DPU units (channels)
//
// See above (a3gxmoq_i) for detailed description.
// Special channels:
// MUNDER     0 Output this code if M is too small  
// MOVER    123 Output this code if M is too big    
// EUNDER   124 Output this code if E is too small  
// EOVER    125 Output this code if E is too big    
// TOFUNDER 126 Output this code if TOF is too small
// TOFOVER  127 Output this code if TOF is too big  
//
// Check result: -1.0 indicates error (see error message)
// See also: a3xnpha
extern double a3gxmas_i(int ie, int i);

// SWICS PHA[i]: TOF [ch] (just one PHA word)
// In case of error, -1 is returned (check error message)
// See also: a3xnpha
extern int a3gxtof_i(int ie, int i);

// SWICS PHA[i]: E_SSD [ch] (just one PHA word)
// In case of error, -1 is returned (check error message)
// See also: a3xnpha
extern int a3gxesd_i(int ie, int i);

// SWICS PHA[i]: DPU Id [1] (opposed to off-line calculated range)
// In case of error, -1 is returned (check error message)
// See also: a3xnpha
extern int a3gxdid_i(int ie, int i);

// SWICS PHA[i]: Sector [1]
// In case of error, -1 is returned (check error message)
// See also: a3xnpha
extern int a3gxsec_i(int ie, int i);

// SWICS PHA[i]: Off-line calculated range [1]
// In case of error, -1 is returned (check error message)
// See also: a3xnpha
extern int a3gxrng_i(int ie, int i);

// convert SWICS m/q from DPU units to phyiscal units ([1])
// Will not convert reserved channels (-1 is returned).
// In order to reduce messages, use: libhef::perr_setlevel(1).
extern double a3cxmoq(double dmoq_ch);

// convert SWICS m from DPU units to phyiscal units ([amu])
// Will not convert reserved channels (-1 is returned).
// In order to reduce messages, use: libhef::perr_setlevel(1).
extern double a3cxmas(double dmas_ch);


%subsection "SWICS: high-level PHA access", pre


// get N(PHA) falling into ellipse at step ie (m-m/q domain)
// Note that ie refers to the EDB number, rather than to the
// E/q voltage (Tech Note 3)
extern int    a3xellmmq(int ie, double moq0, double smq1, double smq2,
				double mas0, double sma1, double sma2);


// get N(PHA) falling into ruedi's ellipse at step ie (m-m/q domain)
// Uses a3cxmas and a3cxmoq to convert from DPU to physical units,
// and therefore _neglects_ reserved channels (see e.g. a3gxmas_i).
// Typical ellipses:
// O6+ 2.667	1.025	15.0 	1.2
// O7+ 2.286	1.025	15.0 	1.2
// Note that ie refers to the EDB number, rather than to the
// E/q voltage (Tech Note 3)
// The bits in lflag are used as follows:
// bit value meaning
// 1   1     filter out accidental coincidences (vH = 0 if off)
// 2   2     use basic rate weighting
// 3   4     use upper half of ellipse only
// bits can be combined. lflag=(1+2+4) turns on filtering,
// basic weighting, and ellipse selection.
// In case the filter is off, vH is not used and
// can be set to 0.0.
extern double a3xrell(int ie, int ir, double vH, long lflag,
	       double moq0, double bmoq,
	       double mas0, double bmas);


// get N(PHA) falling into ellipse at step ie (E-T domain)
// ir is the Basic Range to consider, vH is the speed of the protons.
// ie is the EDB where the PHA was found in telemetry (Tech Note 3).
// The bits in lflag are used as follows:
// bit value meaning
// 1   1     filter out accidental coincidences (vH = 0 if off)
// 2   2     use basic rate weighting
// bits can be combined. lflag=(1+2) turns on both filtering and
// basic weighting. In case the filter is off, vH is not used and
// can be set to 0.0.
// Note: both PAPS and E/q are determined within the routine (by
//       use of a3 routines). E/q of step ie-1 is used.
// example: a3xelletm(30,1,315.4,0,200.0,3.0,5.0,30.0,7.0,7.0);
extern double a3xelletm(int ie, int ir, double vH, long lflag,
		     double t0, double st1, double st2, 
		     double e0, double se1, double se2);



// histogram of SWICS PHA of one cycle in m-m/q domain (added to existing)
// a3mmq(hst,x,y,0,333.1,300,1.0,20.0,128,1.0,100.0)
// Uses a3cxmas and a3cxmoq to convert from DPU to physical units,
// and therefore _neglects_ reserved channels (see e.g. a3gxmas_i).
// The bits in lflag are used as follows:
// bit value meaning
// 1   1     filter out accidental coincidences (vH = 0 if off)
// 2   2     use basic rate weighting
// bits can be combined. lflag=(1+2) turns on both filtering and
// basic weighting. In case the filter is off, vH is not used and
// can be set to 0.0.
extern int a3mmq(double *adhst, double *adx, double *ady, 
		 long lflag, double vH,
		 int Nx, double dxl, double dxh,
		 int Ny, double dyl, double dyh);


// histogram of SWICS PHA in E-T domain (added to existing)
// histogram is determined by offsets in both TOF and ESSD, and the
// dimensions in both directions. offx=200 and Nx=512 would then map
// TOF channels 200..711 into the histogram. ie is the EDB where
// the PHA has been found (ie >= 2).
// The bits in lflag are used as follows:
// bit value meaning
// 1   1     filter out accidental coincidences (vH = 0 if off)
// 2   2     use basic rate weighting
// bits can be combined. lflag=(1+2) turns on both filtering and
// basic weighting. In case the filter is off, vH is not used and
// can be set to 0.0.
// Note: both PAPS and E/q are determined within the routine (by
//       use of a3 routines). E/q of step ie-1 is used.
extern int a3eth(double *adhst, long lflag, int ie, double vH, 
  int offx, int Nx, int offy, int Ny);


// histogram of SWICS PHA in E/q-T domain (added to existing)
// histogram is determined by offsets in both TOF and E/q (step), and the
// dimensions in both directions. offx=200 and Nx=512 would then map
// TOF channels 200..711 into the histogram.
// The bits in lflag are used as follows:
// bit value meaning
// 1   1     filter out accidental coincidences (vH = 0 if off)
// 2   2     use basic rate weighting
// bits can be combined. lflag=(1+2) turns on both filtering and
// basic weighting. In case the filter is off, vH is not used and
// can be set to 0.0.
extern int a3qth(double *adhst, long lflag, double vH, 
		 int offx, int Nx, int offy, int Ny);


%subsection "SWICS: Speed from Matrix Rates"

%text %{
 Note: strictly speaking, this routine does not belong to a3dif.
 It is here for the moment, until I found a clear organization of
 the data.
%}
// SWICS: kinetic properties for Matrix Rate imr
extern double *a3xmrspd(int imr);

// SWICS: kinetic prop from AUX channel
extern double *a3auxspd(void);

// SWICS: correction for density calculation --- version 1
// speed,thermal speed,mass,charge,first/last E/q step in sum (2..59)
extern double a3xeoqsumv1(double v0, double vth, double mas, double crg,
		   int ifrst, int ilast);


%subsection "SWIMS: quality checking"

// ensure settings of SWIMS/ACE. Checked are:
// [] increasing record counter [] increasing time
// [] needed EDBs (21,41,35,36) are present in cycle
// [] Start MCP Level 155       [] Stop MCP Level 155
// [] Hyperbola Level 177
// [] HK values for E/q are monotonically decreasing
// [] E/q table from DPU Spare is compared with known table
// table valid
// 0     ?
// 1     ?
// 2     ? (used to be active before 3 came in)
// 3     "new" E/q stepping scheme after Hefti and Zurbuchen [1999]
// Note: routines for these checks are also available separately.
// Note: Levels for MCP and Hyperbola, as well as E/q Stepping
//       Table can passed as arguments.
extern int a3cycm_nominal(int alev=155, int olev=155,
  int hlev=177, int itab=0);

/* all data needed for SWIMS are available */
extern int a3ccycm(void);

/* SWIMS Start MCP is at level lev */
extern int a3ccycm_mcalev(int lev);

/* SWIMS Stop MCP is at level lev */
extern int a3ccycm_mcolev(int lev);

/* SWIMS Hyperbola is at level lev */
extern int a3ccycm_hyplev(int lev);

/* SWIMS E/q stepping (from HK) is monotonically decreasing. */
extern int a3ccycm_eqhk(void);

// SWIMS E/q stepping (from table) is as predefined.
extern int a3ccycm_eqtabnom(void);

%subsection "SWIMS: instrument status and DPU settings"

// get SWIMS E/q [kV] of step ie.
// Using calibrated values for U(ie): parabola with (69.8,0.119,0.048)
// The user has to make sure that he combines the correct data and
// E/q values. The routine does not do this (minimal impact philosophy).
// In nominal stepping mode, one will find:
// [TBD] 99.979 kV for EDB 0 and 0.612 kV for EDB 59.
extern double a3gmeqdpu_i(int ie);

// SWIMS Hyperbola Level (from CMD block)
extern int a3mhyplev(void);

/* SWIMS Housekeeping Block Item (converted)
   Returns ith element of SWIMS HK array for edb ie.  There are 35
   elements total.  (C users use constant 'NMHK' to avoid hardcoding.)
   
   C users:
   --------
   Data can be accessed via mnemonics similar to those in 'ACE S3DPU
   Command and Data Document'.  See libhef::decoded.h for details.
   For example, the main current can be retrieved with the following
   code:

   float m_main_current_1;
   m_main_current_1 = a3gmhk(ie, LMGPI1);

   NOTE:  Unlike the raw HK blocks, masks are not needed since these
   items are already extracted/assembled and converted to physical units.

*/
float a3gmhk(int ie, int i);

%subsection "SWIMS Rates"

// SWIMS Basic Rate weigth at EDB ie, BR ibr
// Note: Basic Rate Definition _not known_ / commandable.
extern double a3mbrwgt(int ie, int ibr);


// get SWIMS FSR of EDB ie and sector isec
// If isec is omitted or 8, FSR summed over sectors will be returned
// see also: a3gm===_i, where === can be
// fsr     start rate
// fsra    start rate on anode A
// fsrb    start rate on anode B
// fsrab   start rate on anode A AND B
// rsr     stop rate
// dcr     double coincidence rate
// mfsr    more than one start, but only one stop in a given time
// mdcr    one start, but more than one stop in a given time
extern double a3gmfsr_i(int ie, int isec=8);

// get SWIMS FSRA of EDB ie and sector isec
// If isec is omitted or 8, FSR summed over sectors will be returned
// see also: a3gmfsr_i and links from there
extern double a3gmfsra_i(int ie, int isec=8);

// get SWIMS FSRB of EDB ie and sector isec
// If isec is omitted or 8, FSR summed over sectors will be returned
// see also: a3gmfsr_i and links from there
extern double a3gmfsrb_i(int ie, int isec=8);

// get SWIMS FSRAB of EDB ie and sector isec
// If isec is omitted or 8, FSR summed over sectors will be returned
// see also: a3gmfsr_i and links from there
extern double a3gmfsrab_i(int ie, int isec=8);

// get SWIMS RSR (stop rate) of EDB ie and sector isec
// If isec is omitted or 8, FSR summed over sectors will be returned
// see also: a3gmfsr_i and links from there
extern double a3gmrsr_i(int ie, int isec=8);

// get SWIMS DCR of EDB ie and sector isec
// If isec is omitted or 8, FSR summed over sectors will be returned
// see also: a3gmfsr_i and links from there
extern double a3gmdcr_i(int ie, int isec=8);

// get SWIMS MFSR of EDB ie and sector isec
// If isec is omitted or 8, FSR summed over sectors will be returned
// see also: a3gmfsr_i and links from there
extern double a3gmmfsr_i(int ie, int isec=8);

// get SWIMS MDCR of EDB ie and sector isec
// If isec is omitted or 8, FSR summed over sectors will be returned
// see also: a3gmfsr_i and links from there
extern double a3gmmdcr_i(int ie, int isec=8);

%subsection "SWIMS PHA"

// get SWIMS number of PHA words in EDB ie
extern int a3mnpha(int ie);

// get SWIMS DPU id for PHA word i in EDB ie
// (This is the DPU-calculated range.)
// See also a3gxdid_i
extern int a3gmdid(int ie, int i);

// get SWIMS sector for PHA word i in EDB ie
extern int a3gmsec(int ie, int i);

// get SWIMS start (or is it stop?) amplitute for PHA word i in EDB ie
extern int a3gmstamp(int ie, int i);

// get SWIMS stop k1 for PHA word i in EDB ie
extern int a3gmstopk1(int ie, int i);

// get SWIMS stop k2 for PHA word i in EDB ie
extern int a3gmstopk2(int ie, int i);

// get SWIMS tof for PHA word i in EDB ie
// This is the tof in channels.  Use a3cmtof to convert.
extern int a3gmtof(int ie, int i);

// convert SWIMS tof in channels (itof_ch) to tof in ns
// Works only on normal channels, 0-4095, error otherwise.
// Returns -1.0 on error; see error message.
//
// NOTE:  This has been hardcoded to work for a TOF range of 500ns.  This 
//        range can be commanded to 900ns, after which this routine will give
//        bad conversions.  (Use dtof_ch.)
extern double a3cmtof(int itof_ch);

%subsection "SWIMS PHA from TOF range"


// count PHA of type id in given TOF range at E/q step ie
// id = -1 --> use all ranges
extern int    a3mcntpha        (int ie, int tid, int tlow, int thig);

// SWIMS TOF histogram for iel <= E/q step <= ieh,
// itl <= TOF <= ith and PHA type tid
// tid == -1 means: all types
extern double *a3mtofhist(int iel, int ieh, int itl, int ith, int tid);

%subsection "SWIMS additional data types"

// SWIMS TOF histogram 1 accumulated by the DPU on-board
// 0 < i < 1024
// The histograms 1 and 2 differ by the selection criteria.
// These are commandable --> bedini@umich.edu
extern long a3mtof1_i(int i);

// SWIMS TOF histogram 1 accumulated by the DPU on-board
// 0 < i < 1024
// The histograms 1 and 2 differ by the selection criteria.
// These are commandable --> bedini@umich.edu
extern long a3mtof2_i(int i);

%subsection "SEPICA Housekeeping"
/* SEPICA Housekeeping Block Item (raw)
   Returns ith element of SEPICA HK array for edb ie.  There are 22
   elements total.  (C users use constant 'NDHK' to avoid hardcoding.)
   These are commutated over 5 EDBs to make 110 items total.  The
   commutation counter is NEDB % 5, as described in the 'ACE S3DPU
   Command and Data Document'.
   
   C users:
   --------
   Data can be accessed via mnemonics and masks from 'ACE S3DPU
   Command and Data Document'.  See libhef::decoded.h for details.
   For example, the fan 1 mode can be extracted with the following
   code:

   BYTE fan1mode
   fan1mode = a3gshk(ie, LSSSFAN1MODE) & MSSSFAN1MODE;

   NOTE:  This does not work with items having masks larger than 0xff.  
   In that case, assemble the word according to the mask.
*/
extern BYTE   a3gshk(int ie,int i);


%subsection "Obsolete Routines"

// SWICS E/q table
// As found in DPU Spare block of this cycle. Double used for interface only.
extern float *a3gxeqtab(void);

// get SWICS E/q values (calculated from eqtab; not HK)
extern float *a3gxeqdpu(void);

/* get SWICS FSR (summed over sectors) */
extern  double *a3gxfsr         (void);

/* get SWICS DCR (summed over sectors) */
extern  double *a3gxdcr         (void);

/* get SWICS TCR (summed over sectors) */
extern  double *a3gxtcr         (void);

/* get SWICS SSD rate (summed over sectors) */
extern  double *a3gxsdr         (void);

/* get SWICS AUX proton rate (summed over sectors) */
extern  double *a3gxpr          (void);

/* get SWICS AUX alpha rate (summed over sectors) */
extern  double *a3gxar          (void);

///* get SWICS matrix rate for H+ (summed over sectors) */
//extern double *a3gxmrh_1(void);
//
//
///* get SWICS matrix rate for He++ (summed over sectors) */
//extern double *a3gxmrhe2(void);
//
//
///* get SWICS matrix rate for He+ (summed over sectors) */
//extern double *a3gxmrhe1(void);
//
//
///* get SWICS matrix rate for O7+ (summed over sectors) */
//extern double *a3gxmro_7(void);
//
//
///* get SWICS matrix rate for O6+ (summed over sectors) */
//extern double *a3gxmro_6(void);
//
//
///* get SWICS matrix rate for Fe (summed over sectors) */
//extern double *a3gxmrfes(void);
//
//
///* get SWICS matrix rate for Si (summed over sectors) */
//extern double *a3gxmrsis(void);
//
//
///* get SWICS matrix rate "Err" (summed over sectors) */
//extern double *a3gxmrerr(void);

// get SWIMS E/q table
extern float *a3gmeqtab(void);

// get SWIMS E/q table entry of spin ie
extern int a3gmeqtab_i(int ie);

// get SWIMS entrance system voltage values (calculated from eqtab; not HK)
extern float *a3gmeqdpu(void);

// SWICS PHAs: m/q (array with a3xnpha(ie) entries)
// See also: a3xnpha, a3gxmas, a3gxtof_i, a3gxesd_i,a3gxdid_i,
//           a3gxsec_i, a3gxrng_i
extern float *a3gxmoq(int ie);

// SWICS PHAs: mass (array with a3xnpha(ie) entries)
// See also: a3xnpha
extern float *a3gxmas(int ie);
