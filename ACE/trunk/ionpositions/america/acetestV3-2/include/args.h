/* $Id: args.h,v 1.5 1998/05/12 05:56:51 ad Exp $ */
#include "hdfi.h"

struct proc_flags {

    uint32 start;           /* Processing Start time (SCclock) */
    uint32 stop;            /* Processing Stop time (SCclock) */

    uint32 fstart;          /* SCclock value of begining of current file */
    uint32 fstop;            /* SCclock value of end of current file */

    uint32 QACoff;	  /* offset to QAC list in data file */

    uint32 firstframe;    /* Frame that data processing starts */
    uint32 finalframe;    /* Frame that data processing stops */

    uint8 qlp;		    /* Quick look flag */
    uint8 lop;		    /* Level 1 flag */
    uint8 brw;		    /* browse flag */
    uint8 dbm;		    /* Data base maintainence flag (output coverage)*/
    uint8 osf;		    /* Output status file */
    uint8 isf;		    /* Input status file */
    uint8 flush_crisis;     /* flag to flush cris and sis buffers at end of */
                            /* input file */
    uint8 scramblechk;      /* flag to read list of scrambled frames and avoid */
                            /* processing them */
} ;
