#include "function.h"

int main() {
  double eye[] = {0, 0, -1};
  double center[] = {0, 0, 0};
  double up[] = {0, 1, 0};
  double width[] = {10, -10};   // right, left
  double height[] = {10, -10};  // top, bottom
  double length[] = {1, 10}; // front, back

  viewNormalization(eye, center, up, 10, -10, 10, -10, 1, 10);
  JLLoadIdentity();
  
  JLTranslate(1,0,0);
  //JLScale(0.1, 0.1, 0.1);
  JLBegin(triangle);
    JLVertex(-1,0,0);
    JLVertex(1,0,0);
    JLVertex(0,1,0);
  JLEnd();
  
  return 0;
}
