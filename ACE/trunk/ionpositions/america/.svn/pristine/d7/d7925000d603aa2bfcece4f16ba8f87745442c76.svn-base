/*
  File: initSwindal.cc

  Description:
    Initialize global variables and other misc. items for swindal.
    I need to find a better way to do this.

  Author: Jim Raines, 24May2001

  Method:
    
  Major Modification History:
    

*/
#include "swindal.h"

int    gDbgLvl;
string gCurLv1File;
float  gAccumTime;
string gVersion;
string gBuildInfo;

int initSwindal(void){
  static bool fBeenDone = false;   // true => this routine has been run

  if (! fBeenDone) {

    gDbgLvl = 0;

    gCurLv1File = "";

    gAccumTime = 0.0;

    fBeenDone = true;

    /* gVersion -- this is set at compile time with CFLAG/CPPFLAG:
         -DSWINDAL_VERSION='"1.0.0"' 
       (the quotes ensure that is comes in as a string rather than number)
    */
    gVersion = SWINDAL_VERSION;

    /* __DATE__ and __TIME__ are replaced by the compiler with the
       current values.  There must be a way to avoid tmpstr, but I
       cannot find it.
    */
    char tmpstr[20];
    sprintf(tmpstr,"%s %s",__DATE__,__TIME__);
    gBuildInfo =  tmpstr;
  }


  // print banner
  printf("swindal -- Solar Wind Data Analysis Library\n");
  printf("           Version %s built %s %s\n",gVersion.c_str(),
	 __DATE__,__TIME__);
  printf("           Version %s built %s \n",gVersion.c_str(),
	 gBuildInfo.c_str());

  return(0);
}
  
