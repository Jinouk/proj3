#include "shapes.h"
//#include <pnm.h>

int main() {
  double eye[] = {-2, 2, 10};
  double center[] = {0, 0, 0};
  double up[] = {0, 1, 0};

  viewNormalization(eye, center, up, 10, -10, 10, -10, 1, 10);
  JLLoadIdentity();
  
  
  drawboxWithEave();

  printFinal();
  
  return 0;
}
