#include "copy_header.h"

bool copy_header(ifstream &datastream,ofstream &ergstream){
  string thisprogram="copy_header : ";
  string tmp="";
  int dbglvl=0;

  //  Reading header
  while (tmp!="*****"){
    getline(datastream,tmp);
    ergstream << tmp;
    ergstream << std::endl;
  }
  if (dbglvl>=1){
    cout << thisprogram << "finished copying header!" << std::endl;
  }
  return true;
}
