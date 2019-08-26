/* $Id: s3_dhk.h,v 1.3 1998/12/07 18:12:39 ad Exp $ */

#include "hdfi.h"

struct sshdhk {
  uint32 sctime;    /* first minor frame of edb, 32 bit spacecraft time */

  uint32 QAC;       /* number of missing minor frames in edb */

    uint8 EDB;      /* EDB number in this SR         */
    uint8 VERSION;      /* Software Version         */
    uint8 FLAGS;        /* Flag Byte               */
		       /* 0x80 Artificial Spin Flag    */
		       /* 0x40 Spin Clock Absent Flag   */
		       /* 0x28 Sun Clock Absent Flag    */
		       /* 0x04 Memory Scrubbing Flag    */
		       /* 0x02 Automatic Telemetry Mode*/
		       /* 0x01 MPB Identifier           */
    uint8 LUCNT;        /* Latch-up Counter         */
    uint8 IDLECTR;      /* Idle Counter             */
    uint8 JOB;          /* Job Status               */
    uint8 SMODENEXT;    /* SEPICA Next Mode         */
    uint8 SMODE;        /* SEPICA Mode              */
    uint8 MMODENEXT;    /* SWIMS Next Mode          */
    uint8 MMODE;        /* SWIMS Mode               */
    uint8 CMODENEXT;    /* SWICS Next Mode          */
    uint8 CMODE;        /* SWICS Mode               */
    uint32 SPINCTR;      /* Spin Counter             */
    uint32 RECORDCTR;    /* Record Counter           */
    uint8 MPOWER;       /* SWIMS Power State        */
    uint8 CPOWER;       /* SWICS Power State        */
    uint8 SPOWER;       /* SEPICA Power State       */
    uint8 SUNSECTOR;    /* Sun Sector               */
    uint16 SECTOR7LEN;   /* Sector 7 Lenght          */
    uint16 SECTOR0LEN;   /* Sector 0 Lenght          */
    uint16 SPINCLOCKS;   /* Number of Spin Clocks    */
    uint16 TTMUX;        /* TT Mux                   */
    uint8 TTSTATUS;     /* TT Status                */
    uint16 LUSTROBE;     /* latch-up Strobe Mask     */
    uint16 LUMASK;       /* latch-up Mask            */
    uint16 LUSTATE;      /* latch-up State           */
    uint8 CLASSMUX;    /* Muliplexer Classifications */
			/* 0xc0 Classification Mux 3     */
			/* 0x30 Classification Mux 2     */
			/* 0x0c Classification Mux 1     */
			/* 0x03 Classification Mux 0     */
    uint8 CMDOK;        /* Command Ok Counter       */
    uint8 CMDERR;       /* Command Error Counter    */
    uint16 CMDHIST1;     /* Command History 1        */
		      /* 0xff00 Command History 1 ID     */
		      /* 0x00e0 Command History 1 Type   */
		      /* 0x001f Command History 1 Lenght */
    uint16 CMDHIST2;     /* Command History 2        */
		      /* 0xff00 Command History 2 ID     */
		      /* 0x00e0 Command History 2 Type   */
		      /* 0x001f Command History 2 Lenght */
    uint16 CMDHIST3;     /* Command History 3        */
		      /* 0xff00 Command History 3 ID     */
		      /* 0x00e0 Command History 3 Type   */
		      /* 0x001f Command History 3 Lenght */
    uint8 PARITYERR;    /* Parity Errors            */
    uint8 SCMDERR;      /* SEPICA Command Errors    */
    uint8 MCMDERR;      /* SWIMS Command Errors     */
    uint8 CCMDERR;      /* SWICS Command Errors     */
    uint8 EEFILL;       /* EEPROM Fill Status       */
    uint8 MEM0;        /* Class 0-A,B Check          */
    uint8 MEM1;        /* Class 1-A,B Check          */
    uint8 MEM2;        /* Class 2-A,B Check          */
    uint8 MEM3;        /* Class 3-A,B Check          */
};
