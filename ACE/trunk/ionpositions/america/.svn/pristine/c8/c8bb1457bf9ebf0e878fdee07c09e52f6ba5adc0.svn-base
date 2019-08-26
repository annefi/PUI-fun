/*
  File: ace_ancil_test.c

  Description:
    Test of libace_ancil, a library of functions for ancillary data extraction

  Author(s): Jim Raines (jmr)

  Method:
    
  Major Modification History:
    24Sep2003   jmr   adapted from ace_ancil_test.pl

*/

#include <stdio.h>
#include <string.h>

main(int argc, char *argv[]){
  char thisprog[] = "";

  int result;
  result = 
    libancil::a3goa_read("/shrg1/ace/sw/src/acetest/anciltest/ACE_ANCIL.HDF");
  printf("result of call to a3goa_read(): %d\n", result);

libancil::print_aosr(libancil::a3goa(1054252800));

 printf("Attitude:\n   X: %f\n   Y: %f\n   Z: %f\n",
	      a3goa_att_GSE_x(1054252800),
	      a3goa_att_GSE_y(1054252800),
	      a3goa_att_GSE_z(1054252800));
 return (0);
}
