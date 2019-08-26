#include "swindal.h"

int main(int argc, const char* argv[]){
  string filename;
  char fnstr[100];

  cout << "argc=" << argc << endl;
  for (int i = 0; i < argc; i++){
    cout << "argv[" << i << "]=" << argv[i] << endl;
  }

  switch (argc) { //note: the first is always this program name
  case 1:
    break;
  case 2:
    cout << "arglist contains input filename" << endl;
    filename = *(argv[1]);
    strcpy(fnstr, argv[1]);
    //sprintf(fnstr, "%s",*argv[1]);
    //printf("%s",*argv[1]);
    break;
  case 3:
    break;
  default:
    //error("too many arguments");
    return(1);
    ;
  }
  
  cout << "filename=" << filename << " fnstr=" << fnstr << endl;
  return(0);
}
