#include <cstdio>
#include <vector>

int main(){

  std::vector<float> v;

  v.push_back(435.02);
  v.push_back(1950.2);
  v.push_back(765.67);
  v.push_back(300.00);
  v.push_back(2500.00);

  for (int i=0; i < v.size(); i++){
    printf("9.3g:%9.3g 8.2f:%8.2f\n",v[i],v[i]);
  }

  return(0);
}
