/* point2vec.cc -- Experiment on just how to point to an element of a
   vector.
   J. Raines, 2May2001
 */

#include "../swindal.h"

class coord {
public:
  int x;
  int y;

  coord::coord(void);
  coord::coord(int i_x, int i_y);
};

coord::coord(void){
  x = 0;
  y = 0;
}

coord::coord(int i_x, int i_y){
  x = i_x;
  y = i_y;
}


int sub1(vector<int> *v, vector<coord> *c);


int main() {
  
  vector<int> v;
  vector<coord> c;

  int i;
  for (i = 0; i < 5; i++){
    v.push_back(i*i);
    c.push_back(coord(i,2*i));
  }

  sub1(&v, &c);

}

int sub1(vector<int> *v, vector<coord> *c){
  int i;
  coord lc;
  coord *plc;
  int *px;

  for (i = 0; i < 5; i++){
    lc = (*c)[i];
    plc = &((*c)[i]);
    px = &((*c)[i].x);

    printf("*v[%d]=%d\n",i,(*v)[i]);

    cout << "lc[i].x=" << lc.x;
    cout << " lc[i].y=" << lc.y;
    cout << "\n";

    cout << "(*c)[i].x=" << (*c)[i].x;
    cout << " lc[i].y=" << lc.y;
    cout << "\n";
    
    cout << "*px=" << *px;
    cout << " plc->x=" << plc->x;
    cout << "\n";
  }

  return (0);
}
