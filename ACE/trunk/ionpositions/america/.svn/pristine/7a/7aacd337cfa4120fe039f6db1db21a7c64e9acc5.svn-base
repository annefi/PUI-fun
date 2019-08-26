// Try out UlyssesSwicsEffic object
// JR, 01Dec2003
// works! 24Jun2004

#include "swindal.h"
#include "swindal_nr.h"
#include <iomanip>

void passString(string ion);

int main(){
  cout << "uswx_eff -I- Is this thing on?" << endl;

  UlyssesSwicsEffic eff;

  string dir = "/shrg1/ulysses/calib/effic";
  eff.setEfficDirectory(dir);
  cout << "Eff. dir. = " << eff.getEfficDirectory() << endl;

  AnalysisData ad;
  ad.init();

  // open output file for eff. data
  string outfile = "uswx_eff.dat";
  ofstream fout;
  fout.open(outfile.c_str());
  if (! fout.good()) cout << "Error opening " << outfile << endl;
  fout << "# AXLV2 efficiency data for eff. validation only" << endl;
  fout << "# ion\tetot\teff" << endl;
  fout.setf(ios::showpoint);
  fout.setf(ios::fixed);

  float eq, eq_step, etot, ion_eff;
  string ion;
  const int NumESteps = 50;
  for (int s = 0; s < ad.Ions.size(); s++){
    for (int ieq = 0; ieq < NumESteps; ieq++){
      eq_step = 86.0 / static_cast<float>(NumESteps);
      eq = eq_step*static_cast<float>( ieq );
      etot = eq + ad.Ions[s].charge*25.8;
      
      ion = ad.Ions[s].name;
      ion_eff = eff.getEffic(ion , etot);

      cout << "s=" << s << " ion=" << ad.Ions[s].name
	   << " eff=" << ion_eff << endl;
      
      fout << ion << "\t" 
	   << setprecision(2) << etot << "\t" 
	   << setprecision(4) << ion_eff << endl;
    }
  }

}
