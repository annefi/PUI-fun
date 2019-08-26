/*
  File: AnalysisData2.cc

  Description:
    Containers and data for analysis of data from for TOF plasma
    instruments.  Does not contain info. specific to any one instrument.

  Author: Jim Raines

  Method:
    
  Revision controlled by CVS:
  $Id: AnalysisData2.cc,v 1.6 2004/11/11 21:47:40 jraines Exp $
  
  Major Modification History:
    23Feb2004   jmr   Adapted from AnalysisData.h

*/
#include "swindal.h"
#include <iomanip>

AnalysisData2::AnalysisData2(InstrumentConstants inst_const){
  ic = inst_const;

  Eqtab.reserve(ic.getNumEdb());
  Eqtab.assign(ic.getNumEdb(), 0.0); // init to 0.0;
  
  // init. to 1.0 since this is safest value
  DutyCycle = 1.0;  

  AccumTime = 0.0;

  CycleTime = -1.0;
  PostAccelVolt = -1.0;

}

double AnalysisData2::getDutyCycle() const{
  cout << "AnalysisData2::getDutyCycle -E- not yet implemented" << endl;
  return(1.0);
}

double AnalysisData2::getEq(int nedb) const{
  return(Eqtab[nedb]);
}

double AnalysisData2::getPav() const{
  return(PostAccelVolt);
}


int AnalysisData2::loadIon(string name, float mass, float charge){
  string element = "jim";
  loadIon(name, element, mass, charge);
  return(0);
}

int AnalysisData2::loadIon(string name, string element, 
			   float mass, float charge){
  Ions.push_back(Ion(name, element, mass, charge));
  // removed pending a way to implement a const map
  //IonsIndex[name] = Ions.size() - 1;
  return(0);
}

int AnalysisData2::getNumIons() const {
  return(Ions.size());
}

Ion AnalysisData2::getIon(int s) const{
  return(Ions[s]);
}

unsigned int AnalysisData2::getIonIndex(string name) const {
  /* Implementation note:  This was originally implemented with 
     map<string,int> IonsIndex, which provided the index for the
     key=name directly.  However, no way could be found to used this
     method inside a 'const' function (required for 'const' passing of
     AnalysisData2 objects), so this more rudimentary implementation
     was developed.
  */

  unsigned int s = 0;
  bool Done = false;
  while (s < Ions.size() && ! Done){
    if (Ions[s].name == name) {
      Done = true;
    }
    else {
      s++;
    }
  }

  return(s);
}

Ion AnalysisData2::getIon(string name) const {
  unsigned int s = getIonIndex(name);
  return(Ions[s]);
}

double AnalysisData2::getCycleTime() const {
  return(CycleTime);
}

float AnalysisData2::getAccumTime() const{
  return(AccumTime);
}

void AnalysisData2::setAccumTime(float time){
  AccumTime = time;
}

// set/get forward model parameters
void AnalysisData2::setFmTof(int s, int nedb, float tof, float stof){
  Ions[s].tof[nedb] = tof;
  Ions[s].stof[nedb] = stof;
}

void AnalysisData2::setFmTof(string ion, int nedb, float tof, float stof){
  int s = getIonIndex(ion);
  setFmTof(s, nedb, tof, stof);
}

double AnalysisData2::getFmTof(int s, int nedb) const {
  return(Ions[s].tof[nedb]);
}

double AnalysisData2::getFmTof(string ion, int nedb) const {
  int s = getIonIndex(ion);
  return(getFmTof(s, nedb));
}

double AnalysisData2::getFmStof(int s, int nedb) const {
  return(Ions[s].stof[nedb]);
}

double AnalysisData2::getFmStof(string ion, int nedb) const {
  int s = getIonIndex(ion);
  return(getFmStof(s, nedb));
}

int AnalysisData2::FMoutput(string file) const {
  std::ofstream fout;
  using std::ios;
  using std::setprecision;

  fout.open(file.c_str());

  fout << "# ACE/SWIMS Level II Forward Model Positions" << endl;
  fout << "# ion\tedb\tE/q\tcenter\thalf_width" << endl;
  fout.setf(ios::showpoint);

  for (unsigned int s = 0; s < Ions.size(); s++){
    for (int nedb = ic.getFirstEdb(); nedb < ic.getNumEdb(); nedb++){
      fout << Ions[s].name << "\t"
	   << nedb << "\t";
      fout.setf(ios::fixed);
      fout << setprecision(2) << Eqtab[nedb] << "\t";
      fout.unsetf(ios::fixed);
      fout << setprecision(4) 
	   << Ions[s].tof[nedb] << "\t"	 
	   << Ions[s].stof[nedb] << endl;
    }
  }
  
  fout.close();
  return(0);
}

