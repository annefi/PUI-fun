#include <iostream>

#include "tnt/tnt.h"
#include "tnt/cmat.h"
#include <stl.h>
#include <stdlib.h>

int main(){
  const int MAXTOFCH = 5;
  const int MAXESDCH = 5;
  const int MAXEDB   = 3;
  const int FIRSTEDB = 0;
  

  TNT::Matrix<float> A(MAXTOFCH,MAXESDCH, 0.0);
  vector<TNT::Matrix<float> > MA;  // the measurement array itself

  /* --- fill vector with (tofch,esdch) matrices --- */
  for (int i = 0; i < MAXEDB; i++){
    MA.push_back(A);
  }

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    cout << "Dumping matrix " << nedb << "(before value):" << endl;
    A = MA[nedb];
    cout << A;
  }

//   /* --- initialize measurement array --- */
//   for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
//     for (int ntof = 0; ntof < MAXTOFCH; ntof++){
//       for (int nesd = 0; nesd < MAXESDCH; nesd++){
// 	MA[nedb][ntof][nesd] = 0.0;
//       }
//     }
//   }

  /* --- increment measurement array --- */
  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    for (int ntof = 0; ntof < MAXTOFCH; ntof++){
      for (int nesd = 0; nesd < MAXESDCH; nesd++){
	MA[nedb][ntof][nesd] += 1.0 + rand();
      }
    }
  }

  // dump matrices
  cout.precision(3);

  TNT::Index1D k(2,4);
  TNT::Index1D l(3,5);

  for (int nedb = FIRSTEDB; nedb < MAXEDB; nedb++){
    cout << "Dumping matrix " << nedb << ":" << endl;
    A = MA[nedb];
    if (nedb == FIRSTEDB){
      cout << A(k,l);
    
    }

    cout << A;
    
  }
}
