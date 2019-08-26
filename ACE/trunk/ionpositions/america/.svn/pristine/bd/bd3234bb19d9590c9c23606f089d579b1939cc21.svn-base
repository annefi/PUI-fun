// Trying out Numerical Recipes bilinear interpolation on ULY/SWICS duty cycle
// data from RVS.
// J. Raines, 23Oct2003
// (was bilinear_interpol.cc)

#include "swindal.h"
#include "swindal_nr.h"

#include <cmath>
#include <iostream.h>

int imin(int a, int b);
int imax(int a, int b);

int main(){
  
  string infile = "/home/jraines/ulysses/rvs-duty-cycle/DUTYCYCL.DAT";

  // read in file
  ifstream fin;
  fin.open(infile.c_str());
  if (! fin.good()) cout << "Error opening " << infile << endl;

  if (0){
    vector<string> lines;
    string line;
    int count = 0;
    while (getline(fin, line)){
      //while (! fin.eof()){
      //while ( fin >> line){
      cout << "line " << ++count << ": " << line << endl;
      lines.push_back(line);
    }

    cout << "dumping lines:" << endl;
    for(int i=0; i < lines.size(); i++){
      cout << lines[i] << endl;
    }
  }
  
  vector<float> values;
  float tmpval;
  int nrow = 1;
  while(! fin.eof()){
    fin >> tmpval;
    values.push_back(tmpval);
  }

  cout << "dumping values:" << endl;
  for(int i=0; i < values.size(); i++){
    cout << values[i] << endl;
  }

  cout << "copying to arrays:" << endl;
  const int ncols = 9;  // number of actual columns in file
  int nrows = values.size()/ncols;
    
  float *x1a;
  x1a = nr::vector(1,nrows+1);
  x1a[0] = -1.0;

  float *x2a;
  x2a = nr::vector(1,ncols);
  x2a[0] = -1.0;
  x2a[1] = 0.0;  // known a priori from note from Ruedi von Steiger
  x2a[2] = 0.1;
  x2a[3] = 0.5;
  x2a[4] = 1.0;
  x2a[5] = 2.0;
  x2a[6] = 3.0;
  x2a[7] = 5.0;
  x2a[8] = 10.0;

  float **ya;
  ya = nr::matrix(1,nrows+1,1,ncols);

  int iv = 0; // index into values vector
  int ix1a = 0;
  for (int row = 1; row <= nrows ; row++){
    for (int col = 1; col <= ncols; col++){
      if (col == 1){
	x1a[++ix1a] = values[iv];// pre-increment so index 1 is first val.
      }
      else{
	ya[row][col-1] = values[iv];
      }
      iv++;
    }
  }

  cout << "dumping NR arrays:" << endl;
  for (int i = 1; i <= ix1a; i++)
    cout << "x1a["  << i << "]=" << x1a[i] << endl;
  cout << endl;

  for (int i = 1; i <= ncols; i++)
    cout << "x2a["  << i << "]=" << x2a[i] << endl;
  cout << endl;

  cout << "dumping ya:" << endl;
  for (int row = 1; row <= nrows ; row++){
    for (int col = 1; col <= ncols-1; col++){
      cout << ya[row][col] << "   ";
    }
    cout << endl;
  }

  float alpha, del_psi;
  float duty, accur;

  while(1){
    cout << "alpha: ";
    cin >> alpha;
    
    cout << "del_psi: ";
    cin >> del_psi;

    cout << "find neighborhood of alpha:" << endl;
    unsigned long i_alpha;
    nr::locate(x1a, nrows, alpha, &i_alpha);
    cout << " x1a[" << i_alpha << "]=" << x1a[i_alpha] 
	 << " <-> x1a[" << i_alpha+1 << "]=" << x1a[i_alpha+1] << endl;
    const int NPOINT_INTERPOL = 4;
    int j;
    j = imin(imax((i_alpha-(NPOINT_INTERPOL-1)/2),1),nrows+1-NPOINT_INTERPOL);

    //j = 3;

    cout << "find neighborhood of del_psi:" << endl;
    unsigned long i_del_psi;
    nr::locate(x2a, ncols, del_psi, &i_del_psi);
    cout << " x2a[" << i_del_psi << "]=" << x2a[i_del_psi] 
	 << " <-> x2a[" << i_del_psi+1 << "]=" << x2a[i_del_psi+1]<< endl; 
    int k;
    k = imin(imax((i_del_psi-(NPOINT_INTERPOL-1)/2),1),ncols+1-NPOINT_INTERPOL);
    //k = 2;

    cout << "j=" << j << " k=" << k << endl;
    cout << "make a smaller ya, yasub=" << endl;
    float **yasub;
    yasub = nr::matrix(1,NPOINT_INTERPOL,1,NPOINT_INTERPOL);
    for (int nrow = 1; nrow <= NPOINT_INTERPOL; nrow++){
      for (int ncol = 1; ncol <= NPOINT_INTERPOL; ncol++){
	yasub[nrow][ncol] = ya[nrow+j-1][ncol+k-1];
	cout << yasub[nrow][ncol] << "   ";
      }
      cout << endl;
    }

    cout << "do actual interpolation:" << endl; 
    duty = -1.0;
    accur = -1.0;
    //    nr::polin2(&x1a[j-1], &x2a[k-1], &ya[j-1], 
    nr::polin2(&x1a[j-1], &x2a[k-1], yasub, 
	       NPOINT_INTERPOL, NPOINT_INTERPOL,
	       alpha, del_psi, &duty, &accur);
    cout << " duty=" << duty << endl;
    cout << " accur=" << accur << endl;
    
  }

  fin.close();
  

  return(0);
}

int imin(int a, int b){
  long lminarg1,lminarg2;
  return(lminarg1=(a),lminarg2=(b),(lminarg1) < (lminarg2) ?\
	 (lminarg1) : (lminarg2));
}

int imax(int a, int b){
  int imaxarg1,imaxarg2;
  return(imaxarg1=(a),imaxarg2=(b),(imaxarg1) > (imaxarg2) ?\
	 (imaxarg1) : (imaxarg2));
}
