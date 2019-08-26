#include "read_header.h"

bool read_header(ifstream &datastream){
  string thisprogram="read_header : ";
  string tmp="";
  int dbglvl=0;

  //  Reading header
  while (tmp!="*****"){
    datastream >> tmp;
  }
  if (dbglvl>=1){
    cout << thisprogram << "finished reading header!" << std::endl;
  }
  return true;
}
