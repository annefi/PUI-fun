#include "swindal.h"

extern "C" {
void mmqbyhand(double eq, double pav, int tch, int ech, 
	       double *mm, double *mq);
}

int main(int argc, char* argv[]){
  string thisprog = "mmq";

  //initSwindal();

  //AnalysisData ad;
  double mm,mq;

  double pav; 
  //pav = ad.PapsVolt;
  pav = 22.8;

  int nedb;
  double eq;

  // EDBs to process
  int slices[6] = {18, 24, 30, 36, 42, 48};

  cout << thisprog << " -I- dumping mass and m/q:" << endl;
  for (int i = 0; i < 6; i++){
    nedb = slices[i];
    //eq = ad.Eqtab[nedb];
    eq = 22.8;
    for (int ntof = 0; ntof < MAXTOFCH; ntof+=10){
      for (int nesd = 0; nesd < MAXESDCH; nesd+=10){
	//eqte2mmq(eq ,pav , ntof, nesd, mm, mq);
	mmqbyhand(eq, pav, ntof, nesd, &mm, &mq);
	cout << "+ (nedb,ntof,nesd)=(" << nedb << "," 
	     << ntof << "," << nesd << ") "
	     << "(mass,m/q)=(" << mm << "," << mq << ")" << endl;
      }
    }
  }
}
