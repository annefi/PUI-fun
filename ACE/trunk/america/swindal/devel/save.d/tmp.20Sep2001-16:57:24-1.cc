/* filter is a bit-field, where the first 3 bits tell whether to
   include PHAs from those respective ranges.
   
   bit        range        decimal
    0           0             1
    1           1             2
    2           2             4

   For example, to include PHAs from the following ranges, set filter
   to the indicated value:
   
   range(s)       filter
   0                1
   1                2      
   0,1              3
   2                4
   0,2              5
   1,2              6
   0,1,2            7

*/
const int RANGE0 = 0;
const int RANGE1 = 1;
const int RANGE2 = 2;

int test_range[3]; 

int filter = 2;  

bool fKeep = false;

for (int i = 0; i < 3; i++){
  if (filter & ) test_range[i] = 1;
}

if (test_range[pha_it->range]) fKeep = true;



