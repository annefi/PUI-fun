#include <stdio.h>
#include <string.h>
#include "hdfi.h"

void main(argc, argv)
int argc;
char *argv[];
{

  int32 init_ACEancillary();
  void dump_ascii_aosr();

  if (argc!=2) {
      printf("Usage: aos_data_rd hdf_file\n");
      exit(1);
  }

  init_ACEancillary(argv[1]);

  dump_ascii_aosr();

  exit(0);
}
    
