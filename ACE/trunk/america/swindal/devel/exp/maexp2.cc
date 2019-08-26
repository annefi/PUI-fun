#include <iostream>

#include "tnt/tnt.h"
#include "tnt/cmat.h"
#include <stl.h>
#include <stdlib.h>

#include <fstream>

int main(){
  const int MAXTOFCH = 5;
  const int MAXESDCH = 5;
  const int MAXEDB   = 3;
  const int FIRSTEDB = 0;
  

  TNT::Matrix<float> A(MAXTOFCH,MAXESDCH, 0.0);
  vector<TNT::Matrix<float> > MA; 
  vector<TNT::Matrix<float> > MA2;
  vector<TNT::Matrix<float> > DMA;

  /* --- fill vector with (tofch,esdch) matrices --- */
  for (int i = 0; i < MAXEDB; i++){
    MA.push_back(A);
    MA2.push_back(A);
    DMA.push_back(A);
  }

  /* --- increment measurement array --- */
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    for (int ntof = 0; ntof < MAXTOFCH; ntof++){
      for (int nesd = 0; nesd < MAXESDCH; nesd++){
	MA[nedb][ntof][nesd] += 1.0 + rand();
      }
    }
  }

  // dump matrices

  ofstream fout;
  fout.open("maexp2.dat");
  fout.precision(10);
  cout << "writing MA ..." << endl;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    fout << MA[nedb];
  }
  fout.close();

  ifstream fin;
  fin.open("maexp2.dat");
  cout << "reading MA ..." << endl;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    fin >> MA2[nedb];
  }

  // compare
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    DMA[nedb] = MA2[nedb] - MA[nedb];
  }

  if (MA == MA2){
    cout << "MA == MA2" << endl;
  }
  else{
    cout << "MA != MA2" << endl;
  }


  cout << "dumping MA:" << endl;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    cout << MA[nedb];
  }

  cout << "dumping MA2:" << endl;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    cout << MA2[nedb];
  }

  cout << "dumping DMA:" << endl;
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    cout << DMA[nedb];
  }
  
}
