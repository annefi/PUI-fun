/* ---------------------------------------------------------------------------
   decoded.h --- define "expanded" SWICS/ACE and SWIMS/ACE data structure
   (c) 1998/1999 Simon Hefti (hefti@umich.edu)
   $Id: decoded.h,v 1.2 2003/11/09 12:50:32 jraines Exp $
   ------------------------------------------------------------------------ */

/* ---------------------------------------------------------------------------
   conventions
   -----------
   X --> SWICS
   M --> SWIMS
   ...........
   N --> number of
   L --> Location (Position in array)
   ...........
   a --> array
   l --> long
   i --> int
   s --> short
   b --> byte

   TBC   --> to be checked
   Y2K   --> year 2000 bug (year encoded with two digits)
   FIXME --> expect a problem here
   -------------------------------------------------------------------------*/



#include "datatypes.h"

#ifndef DECODEDH
#define DECODEDH

#define DSTRUCTVER 31                   /* structure VERSION */

#define NBINEDB 2436                    /* bytes in EDB */
#define NBINDDB  203                    /* bytes in dummy EDB */
#define NSEC       8                    /* number of sectors */
#define NEDB      60

/* --- SWICS --- */                     /* number of ... */
#define NXEQ      60                    /* .. SWICS E/q steps */
#define NXBR       4                    /* .. basic rates */
#define NXPH     800                    /* .. PHA words (maximal) */
#define NXMR       8                    /* .. matrix rates */

#define NXBRBOX    8                    /*  8 boxes are possible for 
					**    basic rates */
#define NXMRBOX   20                    /* 20 for the matrix rates */

#define NEDBFRST   7                    /* first few bytes of EDB */

/* --- SWIMS --- */                     /* number of ... */
#define NMPH       400                  /* .. PHA words (maximal) */
#define NMEQ        60                  /* .. E/q steps */
#define NMBR         4                  /* .. basic rates (TBC) */
#define NMTOFHIST 1024                  /* length of ToF histogram */
#define NMSTATUS     5                  /* status bytes. No idea */
#define NMTOFPEREDB 35                  /* ToF bytes per EDB (2100/60) */

/* ---------------------------------------------------------------------------
** find (L)ocations in array: sensor rates
** ------------------------------------------------------------------------ */
#define LXFSR 5
#define LXDCR 4
#define LXTCR 3
#define LXSSR 2
#define LXPR  1
#define LXAR  0

#define NXSR  6

/* ---------------------------------------------------------------------------
** find (L)ocations in array: SWIMS sensor rates
** ------------------------------------------------------------------------ */
#define LMFSR   7 /* start rate */
#define LMFSRA  6 /* Stop Rate */
#define LMFSRB  5 /* Stop Rate */
#define LMFSRAB 4 /* Stop Rate */
#define LMRSR   3 /* start rate */
#define LMDCR   2 /* double coincidence */
#define LMMFSR  1 /* multiple start, one stop */
#define LMMDCR  0 /* multiple stops, one start */

#define NMSR  8

/* ---------------------------------------------------------------------------
** find (L)ocations in array: Telemetry allocation
** ------------------------------------------------------------------------ */
#define LDTLM      0
#define LDHK       1
#define LSHK       2
#define LMHK       3
#define LCHK       4
#define LSSTATUS   5
#define LSMATRIX   6
#define LSSECTOR   7
#define LSBASIC    8
#define LSMONITOR  9
#define LMSTATUS  10
#define LMTOF     11
#define LMBASIC   12
#define LMMONITOR 13
#define LCSTATUS  14
#define LCELEMENT 15
#define LCBASIC   16
#define LCMONITOR 17
#define LDSPARE   18
#define LSPHA     19
#define LMPHA     20
#define LCPHA     21
#define LSDIAG    22

#define NLOC      23 /* locations */

#define LTLMPOS    0 /* position (aspos[NXEQ][NLOC][ LTLMPOS ]) */
#define LTLMLEN    1 /* length */

/* ---------------------------------------------------------------------------
** find (L)ocations in array: S3DPU HK block
** Details from 'ACE S3DPU Command and Data Document'.
** ------------------------------------------------------------------------ */
#define LSSDVERSION        0
#define LSSDFLAGS          1
#define LSSDSPINART        1
#define LSSDSPINABSENT     1
#define LSSDSUNABSENT      1
#define LSSDMEMSCRUB       1
#define LSSDAUTOTLM        1
#define LSSDMPBIDENT       1
#define LSSDLUCNT          2
#define LSSDIDLECTR        3
#define LSSDJOB            4
#define LSSDSMODENEXT      5
#define LSSDSMODE          5
#define LSSDMMODENEXT      6
#define LSSDMMODE          6
#define LSSDCMODENEXT      7
#define LSSDCMODE          7
#define LSSDSPINCTR        8
#define LSSDRECORDCTR     11
#define LSSDMPOWER        14 
#define LSSDCPOWER        14
#define LSSDSPOWER        14
#define LSSDSUNSECTOR     14
#define LSSDSECTOR7LEN    15
#define LSSDSECTOR0LEN    17
#define LSSDSPINCLOCKS    19
#define LSSDTTMUX         21
#define LSSDTTSTATUS      23
#define LSSDLUSTROBE      24
#define LSSDLUMASK        26
#define LSSDOSCSTATE      28
#define LSSDLUSTATE       28
#define LSSDCLASSMUX3     30
#define LSSDCLASSMUX2     30
#define LSSDCLASSMUX1     30
#define LSSDCLASSMUX0     30
#define LSSDCMDOK         31
#define LSSDCMDERR        32
#define LSSDCMDHIST1      33
#define LSSDCMDHIST1ID    33
#define LSSDCMDHIST1TYPE  34
#define LSSDCMDHIST1LEN   34
#define LSSDCMDHIST2      35
#define LSSDCMDHIST2ID    35
#define LSSDCMDHIST2TYPE  36
#define LSSDCMDHIST2LEN   36
#define LSSDCMDHIST3      37
#define LSSDCMDHIST3ID    37
#define LSSDCMDHIST3TYPE  38
#define LSSDCMDHIST3LEN   38
#define LSSDPARITYERR     39
#define LSSDSCMDERR       40
#define LSSDMCMDERR       41
#define LSSDCCMDERR       42
#define LSSDEEFILL        43
#define LSSDMEM0A         44
#define LSSDMEM0B         44
#define LSSDMEM1A         45
#define LSSDMEM1B         45
#define LSSDMEM2A         46
#define LSSDMEM2B         46
#define LSSDMEM3A         47
#define LSSDMEM3B         47

#define NDHK      48 /* number of S3DPU HK block items */

/* ---------------------------------------------------------------------------
** find (M)asks for each item: S3DPU HK block
** usage:  cyc.abs3dpuhk[ie][LSSDLUSTATE] & MSSDLUSTATE
** ------------------------------------------------------------------------ */
#define MSSDVERSION           0xff
#define MSSDFLAGS             0x80
#define MSSDSPINART           0x80
#define MSSDSPINABSENT        0x40
#define MSSDSUNABSENT         0x20
#define MSSDMEMSCRUB          0x04
#define MSSDAUTOTLM           0x02
#define MSSDMPBIDENT          0x01
#define MSSDLUCNT             0xff
#define MSSDIDLECTR           0xff
#define MSSDJOB               0xff
#define MSSDSMODENEXT         0xf0
#define MSSDSMODE             0x0f
#define MSSDMMODENEXT         0xf0
#define MSSDMMODE             0x0f
#define MSSDCMODENEXT         0xf0
#define MSSDCMODE             0x0f
#define MSSDSPINCTR       0xffffff
#define MSSDRECORDCTR     0xffffff
#define MSSDMPOWER            0x80 
#define MSSDCPOWER            0x40
#define MSSDSPOWER            0x20
#define MSSDSUNSECTOR         0x1f
#define MSSDSECTOR7LEN      0xffff
#define MSSDSECTOR0LEN      0xffff
#define MSSDSPINCLOCKS      0xffff
#define MSSDTTMUX           0xffff
#define MSSDTTSTATUS          0xff
#define MSSDLUSTROBE        0x01ff
#define MSSDLUMASK          0x01ff
#define MSSDOSCSTATE          0x02
#define MSSDLUSTATE         0x01ff
#define MSSDCLASSMUX3         0xc0
#define MSSDCLASSMUX2         0x30
#define MSSDCLASSMUX1         0x0c
#define MSSDCLASSMUX0         0x03
#define MSSDCMDOK             0xff
#define MSSDCMDERR            0xff
#define MSSDCMDHIST1        0xffff
#define MSSDCMDHIST1ID        0xff
#define MSSDCMDHIST1TYPE      0xe0
#define MSSDCMDHIST1LEN       0x1f
#define MSSDCMDHIST2        0xffff
#define MSSDCMDHIST2ID        0xff
#define MSSDCMDHIST2TYPE      0xe0
#define MSSDCMDHIST2LEN       0x1f
#define MSSDCMDHIST3        0xffff
#define MSSDCMDHIST3ID        0xff
#define MSSDCMDHIST3TYPE      0xe0
#define MSSDCMDHIST3LEN       0x1f
#define MSSDPARITYERR         0xff
#define MSSDSCMDERR           0xff
#define MSSDMCMDERR           0xff
#define MSSDCCMDERR           0xff
#define MSSDEEFILL            0xff
#define MSSDMEM0A             0xf0
#define MSSDMEM0B             0x0f
#define MSSDMEM1A             0xf0
#define MSSDMEM1B             0x0f
#define MSSDMEM2A             0xf0
#define MSSDMEM2B             0x0f
#define MSSDMEM3A             0xf0
#define MSSDMEM3B             0x0f

/* ---------------------------------------------------------------------------
** find (L)ocations in array: SEPICA HK block
** Details from 'ACE S3DPU Command and Data Document'.
** The SHK block is commutated in 22 byte units over 5 EDBs.  See
** ------------------------------------------------------------------------ */
#define LSSSFAN1MODE    6  /* 0 ->science 1->engineering */
#define LSSSFAN2MODE    8  /* 0 ->science 1->engineering */
#define LSSSFAN3MODE   10  /* 0 ->science 1->engineering */

#define NSHK           22
/* ---------------------------------------------------------------------------
** find (M)asks for each item: S3DPU HK block
** usage:  cyc.abs3shk[ie][LSSDLUSTATE] & MSSDLUSTATE
** Many items are not identified here
** ------------------------------------------------------------------------ */
#define MSSSFAN1MODE   0x20
#define MSSSFAN2MODE   0x20
#define MSSSFAN3MODE   0x20

/* ---------------------------------------------------------------------------
** find (L)ocations in array: Corner Table
** ------------------------------------------------------------------------ */
#define LXQN       0 /* minimal m/q */
#define LXQX       1 /* maximal m/q */
#define LXMN       2 /* minimal m */
#define LXMX       3 /* maximal m */
#define LXBOX      4 /* which range is defined by this box */

#define NCORN      5

/* ---------------------------------------------------------------------------
** find (L)ocations in array: SWICS housekeeping
** ------------------------------------------------------------------------ */
#define LXGV28      0 /* ground-referenced primary 28 V */
#define LXGV20      1 /* */
#define LXGV10      2 /* */
#define LXGV5P      3 /* */
#define LXGV5M      4 /* */
#define LXSPR1      5 /* unused */
#define LXGTE1      6 /* temperature */
#define LXGTE2      7 /* */
#define LXGPI1      8 /* ground ref. +28V current primary */
#define LXGPI2      9 /* ground ref. +28V current secondary */
#define LXGI5P     10 /* */
#define LXGI20     11 /* */
#define LXGPAV     12 /* post-acceleration */
#define LXSPR2     13 /* unused */
#define LXGEOQ     14 /* E/q of entrance system */
#define LXSPR3     15 /* unused */
/* PAPS-referenced */
#define LXPAC7     16 /* */
#define LXPTE1     17 /* temperature */
#define LXPTE2     18 /* */
#define LXPV5P     19 /* */
#define LXPI5P     20 /* */
#define LXPV5M     21 /* */
#define LXPI5M     22 /* */
#define LXPMCP     23 /* MCP voltage */
#define LXPGAI     24 /* E/q GAIN */

#define NXHK       25  /* number of SWICS HK entries */


/* ---------------------------------------------------------------------------
** find (L)ocations in array: SWICS command
** ------------------------------------------------------------------------ */
#define LXTRIG      0 /* Trigger mode */
#define LXMCPL      1 /* MCP level */
#define LXTCAL      2 /* T Cal, USS threshold */
#define LXECA1      3 /* E cal */
#define LXECA2      4 /* E cal */
#define LXETAC      5 /* TAC slope */
#define LXSSDE      6 /* SSD enables */
#define LXDPPS      7 /* DPPS Level */
#define LXPAPS      8 /* PAPS Level */
#define LXHVEN      9 /* HV enables */

#define NXCMD      10  /* ............... "command" bytes */

/* ---------------------------------------------------------------------------
** find (L)ocations in array: SWIMS command
** ------------------------------------------------------------------------ */

#define LMAHYP     12 /* Hyperbola Level (A for commAnd, not control) */
#define LMAMCO     13 /* Stop  MCP Level (actually may be Start MCP) */
#define LMAMCA     14 /* Start MCP Level */

#define NMCMD      20  /* ............... "command" bytes */

/* ---------------------------------------------------------------------------
** find (L)ocations in array: SWICS control
** ------------------------------------------------------------------------ */
#define LXLDPP      0 /* DPPS Limit */
#define LXDDPP      1 /* DPPS Delta */
#define LXLMCP      2 /* MCP  Limit */
#define LXDMCP      3 /* MCP  Delta */
#define LXLPAV      4 /* PAPS Limit */
#define LXDPAV      5 /* PAPS Delta */

#define NXCTRL     16  /* ............... "control" bytes */

  /* Note: 2 items in the CTRL block are currently not identified.
  ** There are 2 x 8 bytes there, one block for the commanded control
  ** bytes and one block for the active control bytes.
  ** Add 8 to those indices to access the block with the currently
  ** active bytes */

/* find (L)ocations in array: SWIMS control */

#define NMCTRL     32  /* ............... "control" bytes */

/* ---------------------------------------------------------------------------
** find (L)ocations in array: SWIMS housekeeping
** ------------------------------------------------------------------------ */
#define LMGV28      0 /* ground-referenced primary 28 V */
#define LMGV09      1 /* */
#define LMGV5P      2 /* */
#define LMGV5M      3 /* */
#define LMGV12      4 /* */
#define LMGTE1      5 /* temperature */
#define LMGTE2      6 /* temperature */
#define LMSPR1      7 /* unused */
#define LMGPI1      8 /* ground ref. +28V current primary */
#define LMGPI2      9 /* ground ref. +28V current secondary */
#define LMGI5P     10 /* */
#define LMSPR2     11 /* unused */
#define LMSPR3     12 /* unused */
#define LMSPR4     13 /* unused */
#define LMGEOQ     14 /* E/q of entrance system */
#define LMGV_F     16 /* Vf (E/q is 16 bits)*/
/* Vf-referenced */
#define LMVV28     18 /* (Vf is 16 bits) */
#define LMVV09     19 /* */
#define LMVV06     20 /* */
#define LMVV5P     21 /* */
#define LMVV5M     22 /* */
#define LMVV12     23 /* */
#define LMVTE1     24 /* temperature */
#define LMVTE2     25 /* "           */
#define LMVI28     26 /* */
#define LMVPI6     27 /* */
#define LMVPI5     28 /* */
#define LMVMI5     29 /* */
#define LMVMCA     30 /* start MCP */
#define LMSPR5     31 /* unused */
#define LMVMCO     32 /* stop MCP */
#define LMVHPS     33 /* Hyperbola */
#define LMVSTA     34 /* status */

#define NMHK       35  /* number of SWIMS HK entries */

/* ---------------------------------------------------------------------------
** DPU/Classification Parameters/CNQ
** ------------------------------------------------------------------------ */

#define LCNQTMIN  0
#define LCNQTMAX  1
#define LCNQCMIN  2                     /* Classification */
#define LCNQCMAX  3
#define LCNQTOFF  4                     /* offset */
#define LCNQTDAC  5
#define LCNQPOF1  6                     /* PAPS conversion 1 */
#define LCNQPOF2  7                     /* slope */
#define LCNQPSL1  8
#define LCNQPSL2  9
#define LCNQEOQ0 10                     /* E/q */
#define LCNQEOQ1 11
#define LCNQCLA0 12                     /* Classification const */
#define LCNQCLA1 13
#define LCNQCLA2 14

#define NCNQ     15

/* ---------------------------------------------------------------------------
** DPU/Classification Parameters/CNM
** ------------------------------------------------------------------------ */

#define LCNMTMIN  0
#define LCNMTMAX  1
#define LCNMEMIN  2
#define LCNMEMAX  3
#define LCNMCMIN  4                     /* Classification */
#define LCNMCMAX  5
#define LCNMTOFF  6                     /* offset */
#define LCNMEOFF  7 
#define LCNMTDAC  8
#define LCNMEDAC  9
#define LCNMCLA0 10                     /* Classification const */
#define LCNMCLA1 11
#define LCNMCLA2 12
#define LCNMCLA3 13
#define LCNMCLA4 14
#define LCNMCLA5 15

#define NCNM     16

/* ---------------------------------------------------------------------------
** Cycle
** ------------------------------------------------------------------------ */
typedef struct SBCYC {
  /* decoding HK */
  short    sver;                        /* data structure version */
  short    sdecomp_problem;             /* flag is if decompression caused
					   problems */
  /* information on EDB */
  BYTE     abQAC[NEDB];                 /* QAC from L1 file */
  long     alNr[NEDB];                  /* long EDB number */
  double   adtime[NEDB];                /* so-called s/c readout time */
  double   adepoch[NEDB];               /* so-called epoch */
  BYTE     abedbfrst[NEDB][NEDBFRST];   /* first few bytes of EDB */
  BYTE     abgood[NEDB];                /* my QAC (use EDB only if 0) */
  /* TOC */
  short    aspos[NXEQ][NLOC][2];        /* EDB,item,pos and length */ 

  /* S3DPU HK block */
  BYTE     abs3dpuhk[NEDB][NDHK];

  /* SEPICA HK block */
  BYTE     abshk[NEDB][NSHK];

  /* SWICS rates */
  long     alxsr[NXEQ][NXSR][NSEC + 1]; /* sensor rate */
                                        /* EDB,rate,sector and sum */ 
  long     alxmr[NXEQ][NXMR][NSEC + 1]; /* matrix rate */ 
  long     alxbr[NXEQ][NXBR][NSEC + 1]; /* basic rate */ 
  /* SWIMS rates */
  long     almsr[NMEQ][NMSR][NSEC + 1]; /* sensor rate */
  long     almbr[NMEQ][NMBR][NSEC + 1]; /* basic rate */
  // long     *almbr;
  /* */
  long     lrecNr;                      /* record number */
  double   adcnm[NCNM];                 /* SWICS classification */
  double   adcnq[NCNQ];
  BYTE     abxbrtab[NXBRBOX][NCORN];    /* corner table of basic rates */
  BYTE     abxmrtab[NXMRBOX][NCORN];    /* ... matrix rates */
  BYTE     abxeqtab[NXEQ];              /* SWICS E/q values of cycle */
  short    asmeqtab[NMEQ];              /* SWIMS E/q values of cycle */
  /* SWICS PHA words */
  BYTE     abxsec[NXEQ][NXPH];          /* sector */
  BYTE     abxdid[NXEQ][NXPH];          /* ID as found in telemetry */
  BYTE     abxesd[NXEQ][NXPH];          /* E_SSD */
  short    asxtof[NXEQ][NXPH];          /* TOF */
  BYTE     abxrng[NXEQ][NXPH];          /* range as calculated off-line */
  short    asxNof[NXEQ];                /* number of PHAs in each EDB */
  short    asxnr[NXEQ][NXBR][NSEC + 1]; /* PHA per range and sector */
  float    afxmas[NXEQ][NXPH];          /* classsified */
  float    afxmoq[NXEQ][NXPH];          /* classsified */
  float    afxwgt[NXEQ][NXBR];          /* weights */
  /* SWICS HK */
  float    afxhk[NXEQ][NXHK];
  BYTE     abxcmd[NXCMD];
  BYTE     abxctrl[NXCTRL];
  float    fxpav;                       /* DPU-value of PA voltage [kV] */
  float    afxeoqdpu[NXEQ];             /* E/q from eqtab (DPU values) */
  float    afxeoqaux[NXEQ];             /* AUX: E/q from eqtab (DPU values) */
  /* SWIMS PHA words */
  BYTE     abmsec[NMEQ][NMPH];          /* sector */
  BYTE     abmdid[NMEQ][NMPH];          /* DPU-calculated range */
  short    asmsta[NMEQ][NMPH];          /* Start Amplitude */
  short    asmak1[NMEQ][NMPH];          /* Stop Amplitude K1 */
  short    asmak2[NMEQ][NMPH];          /* Stop Amplitude K2 */
  short    asmtof[NMEQ][NMPH];          /* TOF */
  short    asmNof[NMEQ];                /* number of PHAs in each EDB */
  short    asmnr[NMEQ][NMBR][NSEC + 1]; /* PHA per range and sector */
  float    afmwgt[NMEQ][NMBR];          /* weights */
  /* histograms */
  long     almtof1[NMTOFHIST];          /* time-of-fligh histogram of SWIMS */
  long     almtof2[NMTOFHIST];
  /* SWIMS HK */
  BYTE     abmstatus[NMSTATUS];         /* status bytes */
  float    afmhk[NMEQ][NMHK];
  short    asmcmd[NMCMD];
  BYTE     abmctrl[NMCTRL];
  float    afmeoqdpu[NMEQ];             /* E/q from eqtab (DPU values) */
} SBCYC;

#endif

/* ---------------------------------------------------------------------------

   history
   ---------------------------------------------------------------------------
   struct version|changes
      date       |
   11 15-Jul-98  |added m and m/q to SWICS PHA arrays
   ---------------------------------------------------------------------------

   -------------------------------------------------------------------------*/
