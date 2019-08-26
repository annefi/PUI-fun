#include "sort.h"

using namespace std;

vint sort(vdouble &param)
{
  vdouble paramtmp(param.size()/7);
  vint liste(param.size()/7);
  for (int i=0;i<param.size()/7;i++){
    paramtmp[i]=param[i*7];
  }
  for (int i=0;i<param.size()/7;i++){
    liste[i]=maxpos(paramtmp);
    paramtmp[liste[i]]=-1.;
  }
  return liste;
}


int maxpos(vdouble &vec)
{
  int maxp=0;
  for (int i=1;i<vec.size();i++){
    if (vec[i]>vec[maxp]){
      maxp=i;
    }
  }
  return maxp;
}
