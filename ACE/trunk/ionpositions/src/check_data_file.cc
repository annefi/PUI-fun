#include "check_data_file.h"

bool check_data_file(ifstream &datastream){
  // checks axlv2_et_mat* file from axlv2 data processor for consitency
  string thisprogram="check_data_file : ";
  string tmp="";

  int dbglvl=0;
  int i=0;
  int tmp1=0;
  int tmp2=0;
  char tmp3;

  // check for header end; header should not be longer than 50 lines or test will fail! Header end is str "*****"

  while ((tmp!="*****") && (i<51)){
    getline(datastream,tmp);
    //cout << i << " , " << tmp << std::endl;
    i++;
  }
  if (i>50){
    datastream.close();
    cout << i << " > 50 : closing file " << std::endl;
    return false;
  }  
  
  // check if 58 steps are present

  for (int j=0;j<58;j++){
    datastream >> tmp1 >> tmp2 >> tmp3;
    //cout << j << "," << tmp1 << "," << tmp2 << std::endl;
    if (!((tmp1==128 || tmp1==256) && (tmp2==512 || tmp2==1024))){
      datastream.close();
      //cout << j << "," << tmp1 << "," << tmp2 << " wrong dimension : closing file"  << std::endl;
      return false;
    }
    for (int k=0;k<tmp1;k++){
      getline(datastream,tmp);
      //cout << k << "," << tmp << std::endl;
    }
  }
  datastream.close();
  cout << "file succesfully tested!" << std::endl;
  return true;

}
  
  
  
