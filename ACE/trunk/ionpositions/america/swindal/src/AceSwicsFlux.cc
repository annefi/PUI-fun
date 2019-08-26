/*
  File: AceSwixFlux.h

  Description:
    Header file for ACE/SWICS flux class, a class which reads in output from 
    the ACE/SWICS Level II processor (axlv2) and serves it up.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: AceSwicsFlux.cc,v 1.2 2004/07/28 13:28:35 jraines Exp $

  Major Modification History:
    05May2004   jmr   initial coding

*/
#include "swindal.h"
#include <sstream>
#include <iomanip>

AceSwicsFlux::AceSwicsFlux(string file){
  // make routine and build info available to code and 
  // from binary file via 'strings' program
  string thisprog = "AceSwicsFlux";
  string build_info = __DATE__;
  build_info = build_info + " ";
  build_info = build_info + __TIME__;
  string rcs_id = "$Id: AceSwicsFlux.cc,v 1.2 2004/07/28 13:28:35 jraines Exp $";

  // read in rate data
  std::ifstream fin(file.c_str());
  if (! fin.good()) {
    cout << thisprog << " -E- error opening " << file << endl;
    return;
  }

  string line;
  vector<string> headers;
  while(! fin.eof()){
    getline(fin,line);

    if (line.substr(0,1) == "#"){
      headers.push_back(line);
    }
    else {
      std::istringstream ssline(line);
      RateRecord tmprec;
      ssline >> tmprec;
      Data.push_back(tmprec);
    }
  }

}

AceSwicsFlux::RateRecord::RateRecord(){
  doyfr = -1.0;
  edb = -1;
  eoq = -1.0;
  ion = "";
  rate = -1.0;
  counts = -1.0;
}

std::istream& operator>>( std::istream &input, AceSwicsFlux::RateRecord& rr){
  input.setf(std::ios::skipws);
  input >> rr.doyfr >> rr.edb >> rr.eoq >> std::setw(8) >> rr.ion 
	>> rr.rate >> rr.counts;
  return input;
}

std::ostream& operator<<( std::ostream &output, 
			  const AceSwicsFlux::RateRecord& rr){
  output << rr.doyfr << "\t" << rr.edb << "\t" << rr.eoq << "\t" 
	 << rr.ion << "\t" << rr.rate << "\t" << rr.counts;
  return output;
}

void AceSwicsFlux::dump(string file) const {
  std::ofstream fout;
  fout.open(file.c_str());

  
  fout << "# ACE/SWICS Level II Fluxes" << endl;

  for (unsigned int nrec = 0; nrec < Data.size(); nrec++){
    fout << Data[nrec] << endl;
  }
  
  fout.close();
  return;
}

void AceSwicsFlux::dumpIons(string file) const {
  std::ofstream fout;
  fout.open(file.c_str());

  
  fout << "# ACE/SWICS Level II Flux Ions" << endl;

  for (unsigned int nrec = 0; nrec < Data.size(); nrec++){
    fout << Data[nrec].ion << " ";
    if (Data[nrec].edb == 59) fout << endl;
  }

  fout.close();
  return;
}

unsigned int AceSwicsFlux::getNumRateRecords(void) const {
  return(Data.size());
}

AceSwicsFlux::RateRecord AceSwicsFlux::getRateRecord(int i) const {
  if (i < Data.size()){
    return(Data[i]);
  }
  else {
    RateRecord tmp;
    return(tmp);
  }
}

