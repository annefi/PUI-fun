#include "exp.h"

class Coord {
public:
  int x;
  int y;

  Coord(void);
  Coord(const int i_x, const int i_y);

private:
};

/* coord functions */
Coord::Coord(void){
  x = 0;
  y = 0;
}

Coord::Coord(const int i_x, const int i_y){
  x = i_x;
  y = i_y;

}


/* main */
int main(){
  Coord a(2,5);

  map<string,Coord> p;

  p["One"] = Coord(1,6);
}
