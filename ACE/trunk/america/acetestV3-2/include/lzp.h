/* $Id: lzp.h,v 1.4 1998/05/12 05:50:27 ad Exp $ */

#define DataUnitLength 854    /* each ACE packet is 6832 bits long */

#define NUM_DATA_FILES 30       /* Max number of data files to be processed */
#define SIZE_DATA_FILENAME 140   /* Max size of data file names */

#define MAX_NUM_FRM 87040     /* number of minor frames per data file */
                              /* ~ seconds per day */

#define LZPSCRAMBLE_MAX_ENTRIES 365000   /* max number of scrambled minor frames for */
                                         /* ACE mission. 100/day for 10 years */
#define LZPSCRAMBLE_HOME "/home/mussel9/asc/LZPSCRAMBLE_file"


#define QAC_SIZE 14           /* size of a QAC entry */

struct QAC_entry {
    int Pos;		/* Position of errored packet */
    short SeqCnt;	/* Packet Sequence Count */
    char errflag;	/* Error Flag */
    char spare;
    int SCclock;	/* SC clock for errored packet */
    short fill;
};

/*--------------------------------------------------------------*/

#define SCHK_DATA_OFFSET   10
#define SCHK_DATA_SIZE     23
#define INST_DATA_OFFSET   35
#define MAG_DATA_SIZE      38
#define EPAM_DATA_SIZE     21
#define CRIS_DATA_SIZE     58
#define SIS_DATA_SIZE     249
#define SWEPAMI_DATA_SIZE  68
#define SWEPAME_DATA_SIZE  57
#define ULEIS_DATA_SIZE   125
#define S3DPU_DATA_SIZE   203

#define ULEIS_DATA_OFFSET 526
