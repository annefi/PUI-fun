/*
  File: initSwindal.cc

  Description:
    Initialize global variables and other misc. items for swindal.

  Author: Jim Raines, 24May2001

  Method:
    
  Major Modification History:
    

*/
#include "swindal.h"

int    gDbgLvl;
long   gStartDoy;
long   gStopDoy;
string gCurLv1File;

int initSwindal(void){
  static bool fBeenDone = false;   // true => this routine has been run

  if (! fBeenDone) {

    gDbgLvl = 0;

    gStartDoy = 2000158;
    gStopDoy  = 2000158;

    gCurLv1File = "";

    fBeenDone = true;
  }

  return(0);
}
  
