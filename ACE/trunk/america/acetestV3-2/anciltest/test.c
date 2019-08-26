#include <stdio.h>

// Compile: gcc test.c -I/usr/local/hdf/include -L/usr/local/hdf/lib -lmfhdf -ldf -ljpeg -lz -lm

int main(argc, argv)
int argc;
char *argv[];
{
  //char filenm[] = "ace_att_gse_23May2003.txt";
  char filenm[] = "ACE_QL1_2000-198T16-50-45Z_V3-0.HDF";
  int hdf_fp;

  if((hdf_fp=Hopen(filenm, 1, 0)) == -1) {
    fprintf(stderr, "COULDN'T OPEN FILE\n");
    exit(1);
  }
  else {
    printf("FILE OPENED SUCCESSFULLY: %d\n", hdf_fp);
  }
  close(hdf_fp);
}
