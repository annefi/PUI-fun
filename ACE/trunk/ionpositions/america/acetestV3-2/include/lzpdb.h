/* $Id: lzpdb.h,v 1.4 1998/03/10 19:31:38 hemple Exp $ */
#define LZPDB_MAX_ENTRIES 10000
#define MAX_LZP_FILES 20

#define LZPDB_HOME "/home/mussel9/asc/LZPDB_file"
#define LZP_ENTRY_SIZE 100

struct lzp_entry {
    char  dbpath[LZP_ENTRY_SIZE];
    char  dbfilename[LZP_ENTRY_SIZE];
    char  dbclockstart[LZP_ENTRY_SIZE];
    char  dbclockstop[LZP_ENTRY_SIZE];
    char  dbDAToffset[LZP_ENTRY_SIZE];
    char  dbQACoffset[LZP_ENTRY_SIZE];
    char  dbflags[LZP_ENTRY_SIZE];
};
