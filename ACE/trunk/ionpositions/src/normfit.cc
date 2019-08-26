#include "normfit.h"

using namespace std;

vdouble normfit(vdouble &param,mdouble &et_mat,double (*funcs)(int, int , vdouble &, vdouble &, int, int,vint &, double))
{
  int dbglvl=0;
  int XDIM = 512;
  int YDIM = 128;
  mdouble norm_et_mat(YDIM,XDIM);
  mdouble erg_et_mat(YDIM,XDIM);
  vdouble paramion(7);
  vdouble daiondummy(7);
  vdouble dadummy(param.size());
  int numberions=(param.size()/7);
  vint parause(param.size(),0);
  vint parauseion(7,0);  
  double norm=0.;
  double sum=0.;
  string thisprogram="normfit : ";
  vdouble ergparam(param.size(),0.);
  int allzero=1;
  for (int i=0;i<(param.size()/7);i++){
    if (param[i*7]>0.){
      allzero=0;
    }
  }
  if (allzero){
    return param;
  }


  for (int ion=0;ion<numberions;ion++){
    sum=0.;
    for (int i=0;i<7;i++){
      paramion[i]=param[i+(ion*7)];
    }
    for (int y=0;y<YDIM;y++){
      for (int x=0;x<XDIM;x++){
	norm=funcs(x,y,param,dadummy,int(param.size()),int(param.size())/7,parause,3.);
	if (norm>0.){
	  norm_et_mat[y][x]=funcs(x,y,paramion,daiondummy,7,1,parauseion,3.)/norm;
	}
	else{
	  norm_et_mat[y][x]=0.;
	}				
      }
    }
    for (int y=0;y<YDIM;y++){
      for (int x=0;x<XDIM;x++){
	erg_et_mat[y][x]=et_mat[y][x]*norm_et_mat[y][x];
	sum+=erg_et_mat[y][x];
      }
    }
    for (int i=1;i<7;i++){
      ergparam[(ion*7)+i]=param[(ion*7)+i];
    }
    ergparam[(ion*7)]=sum;
    if (dbglvl>=1){
      cout << thisprogram << "param[" << ion*7 << "] = " << ergparam[ion*7] << endl;
    }
  }
  return ergparam;
}
