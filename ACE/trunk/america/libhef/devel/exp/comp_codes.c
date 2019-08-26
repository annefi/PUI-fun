/*
  File: 

  Description:
    

  Author(s): Jim Raines (jmr)

  Method:
    
  Major Modification History:
    ddMmmYYYY   jmr   initial coding

*/
// Print table of libhef compression codes
// Jim Raines, 20May2003

#include <stdio.h>
#include <libhef.h>

int main(int argc, char *argv[]){

  int i;
  long a;
  long c;

  int diverged = 0;

  printf("UMD Compression Codes\n");
  printf("%3s\t%8s\t%8s\n","raw", "code_A","code_C");
  for( i=0; i < 256; i++){
    a = decmpa(i);
    c = decmpc(i);
    if (a != c && diverged == 0) {
      printf("----------codes diverge----------\n");
      diverged = 1;
    }
    printf("%03d\t%8d\t%8d\n", i, a, c);

  }

}
