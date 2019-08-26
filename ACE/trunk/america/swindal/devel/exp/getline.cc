
  string infile = "/home/jraines/ulysses/rvs-duty-cycle/DUTYCYCL.DAT";

  // read in file
  ifstream fin;
  fin.open(infile.c_str());
  if (! fin.good()) cout << "Error opening " << infile << endl;

vector<string> lines;
string line;
int count = 0;
while (getline(fin, line)){
  //while (! fin.eof()){  // also works
  //while ( fin >> line){ // also works
  cout << "line " << ++count << ": " << line << endl;
  lines.push_back(line);
}

