/*
  File: loadIons.cc

  Description:
    Load ions for analysis in ACE/SWICS Level II package.

  Author(s): Jim Raines (jmr)

  Method:
    Calls AnalysisData class function to do actual loading.  Name,
    mass and charge are specified here. 

  Revision controlled by CVS:
  $Id: loadIons.cc,v 1.5 2005/03/31 18:24:57 jraines Exp $

  Major Modification History:
    10Mar2005   jmr   Adapted from amlv2::loadIons

*/
#include "swindal.h"
#include "axlv2.h"

int loadIons(AnalysisData& ad){

  // Hydrogen
  ad.loadIon("H+","H",1.0,1.0);
  
  // Helium
  ad.loadIon("3He1+","He",3.0,1.0);
  ad.loadIon("3He2+","He",3.0,2.0);
  ad.loadIon("He1+","He",4.0,1.0);
  ad.loadIon("He2+","He",4.0,2.0);

  // Carbon
  ad.loadIon("C1+","C",12.0,1.0);
  ad.loadIon("C2+","C",12.0,2.0);
  ad.loadIon("C3+","C",12.0,3.0);
  // 4+ has been min. before Jan. 2005
  ad.loadIon("C4+","C",12.0,4.0);
  ad.loadIon("C5+","C",12.0,5.0);
  ad.loadIon("C6+","C",12.0,6.0);

  // Nitrogen
  ad.loadIon("N1+","N",14.0,1.0);
  ad.loadIon("N2+","N",14.0,2.0);
  ad.loadIon("N3+","N",14.0,3.0);
  // 4+ has been min. before Jan. 2005
  ad.loadIon("N4+","N",14.0,4.0); 
  ad.loadIon("N5+","N",14.0,5.0);
  ad.loadIon("N6+","N",14.0,6.0);
  ad.loadIon("N7+","N",14.0,7.0);

  // Oxygen
  ad.loadIon("O1+","O",16.0,1.0);
  ad.loadIon("O2+","O",16.0,2.0);
  ad.loadIon("O3+","O",16.0,3.0);
  ad.loadIon("O4+","O",16.0,4.0);
  // 5+ has been min. before Jan. 2005
  ad.loadIon("O5+","O",16.0,5.0);
  ad.loadIon("O6+","O",16.0,6.0);
  ad.loadIon("O7+","O",16.0,7.0);
  ad.loadIon("O8+","O",16.0,8.0);

  // Neon
  ad.loadIon("20Ne6+","Ne",20.0,6.0);
  ad.loadIon("20Ne7+","Ne",20.0,7.0);
  ad.loadIon("20Ne8+","Ne",20.0,8.0);
  ad.loadIon("20Ne9+","Ne",20.0,9.0);

  // Magnesium
  ad.loadIon("Mg6+","Mg",24.0,6.0);
  ad.loadIon("Mg7+","Mg",24.0,7.0);
  ad.loadIon("Mg8+","Mg",24.0,8.0);
  ad.loadIon("Mg9+","Mg",24.0,9.0);
  ad.loadIon("Mg10+","Mg",24.0,10.0);
  ad.loadIon("Mg11+","Mg",24.0,11.0);
  ad.loadIon("Mg12+","Mg",24.0,12.0);

  // Silicon
  ad.loadIon("Si6+","Si",28.0,6.0);
  ad.loadIon("Si7+","Si",28.0,7.0);
  ad.loadIon("Si8+","Si",28.0,8.0);
  ad.loadIon("Si9+","Si",28.0,9.0);
  ad.loadIon("Si10+","Si",28.0,10.0);
  ad.loadIon("Si11+","Si",28.0,11.0);
  ad.loadIon("Si12+","Si",28.0,12.0);

  // Sulfur
  ad.loadIon("S6+","S",32.0,6.0);
  ad.loadIon("S7+","S",32.0,7.0);
  ad.loadIon("S8+","S",32.0,8.0);
  ad.loadIon("S9+","S",32.0,9.0);
  ad.loadIon("S10+","S",32.0,10.0);
  ad.loadIon("S11+","S",32.0,11.0);
  ad.loadIon("S12+","S",32.0,12.0);
  ad.loadIon("S13+","S",32.0,13.0);
  ad.loadIon("S14+","S",32.0,14.0);

  // Iron
  ad.loadIon("Fe1+","Fe",56.0,1.0);
  ad.loadIon("Fe2+","Fe",56.0,2.0);
  ad.loadIon("Fe3+","Fe",56.0,3.0);
  ad.loadIon("Fe4+","Fe",56.0,4.0);
  ad.loadIon("Fe5+","Fe",56.0,5.0);
  // 6+ has been min. before Jan. 2005
  ad.loadIon("Fe6+","Fe",56.0,6.0);
  ad.loadIon("Fe7+","Fe",56.0,7.0);
  ad.loadIon("Fe8+","Fe",56.0,8.0);
  ad.loadIon("Fe9+","Fe",56.0,9.0);
  ad.loadIon("Fe10+","Fe",56.0,10.0);
  ad.loadIon("Fe11+","Fe",56.0,11.0);
  ad.loadIon("Fe12+","Fe",56.0,12.0);
  ad.loadIon("Fe13+","Fe",56.0,13.0);
  ad.loadIon("Fe14+","Fe",56.0,14.0);
  ad.loadIon("Fe15+","Fe",56.0,15.0);
  ad.loadIon("Fe16+","Fe",56.0,16.0);
  ad.loadIon("Fe17+","Fe",56.0,17.0);
  ad.loadIon("Fe18+","Fe",56.0,18.0);
  ad.loadIon("Fe19+","Fe",56.0,19.0);
  ad.loadIon("Fe20+","Fe",56.0,20.0);
  ad.loadIon("Fe21+","Fe",56.0,21.0);
  ad.loadIon("Fe22+","Fe",56.0,22.0);
  ad.loadIon("Fe23+","Fe",56.0,23.0);
  ad.loadIon("Fe24+","Fe",56.0,24.0);

 return(0);
}
