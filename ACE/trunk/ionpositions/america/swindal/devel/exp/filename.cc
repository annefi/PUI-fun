#include "swindal.h"
#include <fstream>
#include <cstring>

extern "C" {
#include "libhef.h"
}

string gCurLv1File;
long int incrementYdoy(long int);

int main(){ 
  int result;

  char thisprog[] = "filename";
  char acelv1file[150];

  /* -- run start/stop days -- */
  long int StartYdoy = 2000158;
  long int StopYdoy  = 2000162;

  char LV1DIR[] = "/home/acedata/LV1";

  
  for (long int CurYdoy = StartYdoy; CurYdoy <= StopYdoy; 
       CurYdoy = incrementYdoy(CurYdoy)) {

    sprintf(acelv1file, "%s/%4d/%d.nc",LV1DIR, CurYdoy/1000, CurYdoy);

    gCurLv1File = (string) acelv1file;
    cout << thisprog << " -I- " << gCurLv1File << endl;

    result = a3opencyclefile(acelv1file);

    a3readcycle();
    a3expand();
    printf("%s -I- Cycle time is %s\n",thisprog,a3zrecid());
    result = a3closecyclefile();
  }
}

long int incrementYdoy(long int CurYdoy){
  int year = CurYdoy/1000;
  int day  = CurYdoy - year*1000;

  if ( day == (365 + is_leap(year) ) ){
    CurYdoy = (year + 1)*1000 + 1; 
  }
  else{
    CurYdoy++;
  }
  
  return CurYdoy;
}

