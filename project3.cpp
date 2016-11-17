#include "shapes.h"
//#include <pnm.h>

int main() {
  double eye[] = {-2, 2, 10};
  double center[] = {0, 0, 0};
  double up[] = {0, 1, 0};
  double width[] = {300, -300};   // right, left
  double height[] = {300, -300};  // top, bottom
  double length[] = {1, 10}; // front, back

  viewNormalization(eye, center, up, 10, -10, 10, -10, 1, 10);
  JLLoadIdentity();
  
  
  drawboxWithEave();

  printFinal();
  
  return 0;
}
