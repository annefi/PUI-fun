/*
  File: UlyssesSwicsEffic.cc

  Description:
    Class provides services for reading in ULYSSES/SWICS efficiencies
    and interpolation to required energy.

  Author(s): Jim Raines (jmr)

  Method:
    See corresponding header (.h) file for further documentation.

  Revision controlled by CVS:
  $Id: UlyssesSwicsEffic.cc,v 1.5 2004/10/19 13:48:26 jraines Exp $

  Major Modification History:
    28Oct2003   jmr   initial coding

*/

#include "swindal.h"
#include "swindal_nr.h"

UlyssesSwicsEffic::UlyssesSwicsEffic(){
  cout << "UlyssesSwicsEffic::setEfficDirectory -I- init."  << endl;

  // initialize data; note that reserve absolutely will not work here
  ElemEffic tmp;
  data.assign(NElement, tmp);
  
  return;
}

void UlyssesSwicsEffic::setEfficDirectory(string dir){
  EfficDir = dir;
  cout << "UlyssesSwicsEffic::setEfficDirectory -I- set to " << dir << endl;
}

string UlyssesSwicsEffic::getEfficDirectory(){
  return(EfficDir);
}

float UlyssesSwicsEffic::getEffic(const string ion, const float input_etot){
  const int NCOLS = 14;      // number of columns in files
  const int N_HEADERS = 11;  // number of header lines before data, 1-11
  const int NPOINT_INTERPOL = 4; // number of points to use for interpolation

  if (gDbgLvl >= 2) 
    cout << "UlyssesSwicsEffic::getEffic -I- entering..." << endl;

  // assign everything based on substring matching an element
  // This is not elegant but it is simple, flexible and avoids the
  // need for a regex. library.
  //
  // order is based on atomic number then re-arranged to avoid
  // mis-assignment, e.g. matching H from ion="He".
  Element elem = He;
  if (ion.find("He") != std::string::npos){
      elem = He;
      data[elem].element_name = "He";
      data[elem].file = "HE_MOD.DAT";
    }
  else if (ion.find("H") != std::string::npos){
    elem = H;
    data[elem].element_name = "H";
    data[elem].file = "H__MOD.DAT";
  }
  else if (ion.find("C") != std::string::npos){
    elem = C;
    data[elem].element_name = "C";
    data[elem].file = "C__MOD.DAT";
  }
  else if (ion.find("Ne") != std::string::npos){
    elem = Ne;
    data[elem].element_name = "Ne";
    data[elem].file = "NE_MOD.DAT";
  }
  else if (ion.find("N") != std::string::npos){
    elem = N;
    data[elem].element_name = "N";
    data[elem].file = "N__MOD.DAT";
  }
  else if (ion.find("O") != std::string::npos){
    elem = O;
    data[elem].element_name = "O";
    data[elem].file = "O__MOD.DAT";
  }
  else if (ion.find("Mg") != std::string::npos){
    elem = Mg;
    data[elem].element_name = "Mg";
    data[elem].file = "MG_MOD.DAT";
  }
  else if (ion.find("S") != std::string::npos){
    elem = S;
    data[elem].element_name = "S";
    data[elem].file = "S__MOD.DAT";
  }
  else if (ion.find("Si") != std::string::npos){
    elem = Si;
    data[elem].element_name = "Si";
    data[elem].file = "SI_MOD.DAT";
  }
  else if (ion.find("Ar") != std::string::npos){
    elem = Ar;
    data[elem].element_name = "Ar";
    data[elem].file = "AR_MOD.DAT";
  }
  else if (ion.find("Fe") != std::string::npos){
    elem = Fe;
    data[elem].element_name = "Fe";
    data[elem].file = "FE_MOD.DAT";
  }
  else if (ion.find("Kr") != std::string::npos){
    elem = Kr;
    data[elem].element_name = "Kr";
    data[elem].file = "KR_MOD.DAT";
  }

  /* ---------------------------------------------------------------------
     read in file containing tabulated efficiency data
     --------------------------------------------------------------------- */
  static int nrows;
  if (! data[elem].loaded){ // load table if needed
    std::ifstream fin;

    string filename = EfficDir + "/" + data[elem].file;
    fin.open(filename.c_str());
    if (! fin.good()) {
      cout << "UlyssesSwicsEffic::getEffic -I- error opening " 
	   << filename << endl;
      exit(1);
    }
     
    // read through header lines (not saved)
    string header;
    for (int i = 0; i < N_HEADERS; i++){
      getline(fin,header);
    }

    vector<float> values;
    float tmpval;
    while(! fin.eof()){
      fin >> tmpval;
      values.push_back(tmpval);
    }

    // setup NR arrays
    data[elem].nrows = nrows = values.size()/NCOLS;
    data[elem].etot = nr::vector(1,nrows); // nrows+1 in duty, here?
    data[elem].prob1 = nr::vector(1,nrows);
    data[elem].prob2 = nr::vector(1,nrows);
    data[elem].prob3 = nr::vector(1,nrows);
    
    int iv = 0;
    float dummy;
    for (int irow = 1; irow <= nrows; irow++){ // nr::vectors start at
					       // 1 for interpolation
      data[elem].etot[irow] = values[iv++];

      dummy = values[iv++];
      dummy = values[iv++];
      dummy = values[iv++];
      dummy = values[iv++];
      dummy = values[iv++];
      
      data[elem].prob1[irow] = values[iv++];

      dummy = values[iv++];

      data[elem].prob2[irow] = values[iv++];

      dummy = values[iv++];
      dummy = values[iv++];

      data[elem].prob3[irow] = values[iv++];

      dummy = values[iv++];
      dummy = values[iv++];
    }

     data[elem].loaded = true;
  }

  /* ----------------------------------------------------------------------
     Find chunk of vector containing input_etot value by locating 
     index so that input_etot is between that index and the next
     2)  calculate the lower bound on a range of indices, roughly
     centered on the locatin (1) containg the intended number of
     points for interpolation
     ---------------------------------------------------------------------- */

  unsigned long ietot;
  nr::locate(data[elem].etot, nrows, input_etot, &ietot);
  /* ----------------------------------------------------------------------
     Calculate the lower bound on a range of indices, roughly
     centered on the location (just found) containg the intended number of
     points for interpolation
     ---------------------------------------------------------------------- */
  int sublb =
    imin(imax((ietot-(NPOINT_INTERPOL-1)/2),1),nrows+1-NPOINT_INTERPOL);

  /* ----------------------------------------------------------------------
     Do actual interpolations
     ---------------------------------------------------------------------- */
  float prob1 = -1.0;
  float accuracy = -1.0;
  nr::polint(&data[elem].etot[sublb-1], &data[elem].prob1[sublb-1],
	    NPOINT_INTERPOL,input_etot, &prob1, &accuracy);

  float prob2 = -1.0;
  nr::polint(&data[elem].etot[sublb-1], &data[elem].prob2[sublb-1],
	    NPOINT_INTERPOL,input_etot, &prob2, &accuracy);

  float prob3 = -1.0;
  nr::polint(&data[elem].etot[sublb-1], &data[elem].prob3[sublb-1],
	    NPOINT_INTERPOL,input_etot, &prob3, &accuracy);

  /* ----------------------------------------------------------------------
     Calculate efficiency
     ---------------------------------------------------------------------- */
  float eff = prob1*prob2*prob3;

  return(eff);
}

int UlyssesSwicsEffic::imin(int a, int b){
  long lminarg1,lminarg2;
  return(lminarg1=(a),lminarg2=(b),(lminarg1) < (lminarg2) ?\
	 (lminarg1) : (lminarg2));
}

int UlyssesSwicsEffic::imax(int a, int b){
  int imaxarg1,imaxarg2;
  return(imaxarg1=(a),imaxarg2=(b),(imaxarg1) > (imaxarg2) ?\
	 (imaxarg1) : (imaxarg2));
}
