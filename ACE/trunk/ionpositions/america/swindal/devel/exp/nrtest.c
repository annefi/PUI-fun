#include <stdio.h>
#include "nr.h"

/* for ran0 */
/* #define IA 16807 */
/* #define IM 2147483647 */
/* #define AM (1.0/IM) */
/* #define IQ 127773 */
/* #define IR 2836 */
/* #define MASK 123459876 */

int main(){
  int i;
  long idum = 7;

  for (i = 0; i < 10; i++){
    printf("random number %d is %f\n",i,ran0(&idum));
  }
}

