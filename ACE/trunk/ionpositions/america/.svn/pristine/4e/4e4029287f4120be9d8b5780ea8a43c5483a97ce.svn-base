#include "swindal.h"

int main(int argc, const char* argv[]){

  MeasurementArray MA;

  for (int filter = 0; filter < 8; filter++){
    cout << "filter=" << filter  << " range(s)=";

    for (int range = 0; range < 3; range++){
      MA.setFilter(filter); 

      if (MA.passRange(range))
	cout << " " << range;
    }
    cout << endl;
  }
}
