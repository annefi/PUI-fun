/*
  File: axlv2.h

  Description:
    Header file for ACE/SWICS Level II data processor.  Does not include 
    SWINDAL header info.

  Author(s): Jim Raines (jmr)

  Method:

  Revision controlled by CVS:
  $Id: axlv2.h,v 1.9 2005/03/24 21:34:24 jraines Exp $

  Major Modification History:
    26Jan2004   jmr   initial coding

*/

int outputBR(FILE *BRF, float doyfr, BoxRates BR, const AnalysisData& ad);
int outputSR(FILE *SRF, float doyfr, SpillRates SR, const AnalysisData& ad);
int outputPR(FILE *PRF, float doyfr, ProbRates PR, const AnalysisData& ad);
int outputLV2(FILE *LV2F, float doyfr, DistFunc DF, AnalysisData ad);
int correctFeFM(string file, AnalysisData& ad);
int correctFM_phys(AnalysisData& ad, const vector<string>& elements, 
		   double pav);
extern "C" {
  double *xfmexp_phys(double eoq, double pav, double mas, double crg);
}

// convert floating point day of year to string of form 001.08 for doyfr=1.08
string doyfr2doy_fr_str(float doyfr);
string cycletimetodate(double cycletime);

int setPrGaussCutoff(float PRGaussCutoff, int FirstHSFe, 
		     float PRGaussCutoffHSFe, AnalysisData& ad);

int setErrorLevels(AnalysisData& ad);

#include "AxPhysicsFM.h"
//#include "../../swindal/include/set_asp_int.h"
//#include "../../swindal/include/get_asp_int.h"

void showVersions(void);

int loadIons(AnalysisData& ad);
