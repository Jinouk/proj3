#include "function.h"

int main() {
  double eye[] = {0, 0, 1};
  double center[] = {0, 0, 0};
  double up[] = {0, 1, 0};
  double width[] = {300, -300};   // right, left
  double height[] = {300, -300};  // top, bottom
  double length[] = {1, 10}; // front, back

  viewNormalization(eye, center, up, 10, -10, 10, -10, 1, 10);
  JLLoadIdentity();
  
  //JLTranslate(0,0,0);
  //JLScale(2,2,2);
  //JLRotate(30, 0, 1,0 );
  //JLScale(0.1, 0.1, 0.1);
  JLBegin(quad);
    JLVertex(-1,-1,0);
    JLVertex(1,-1,0);
    JLVertex(1,1,0);
    JLVertex(-1,1,0);
  JLEnd();
  
  JLPushMatrix();
  
  
  JLTranslate(-10,9,0);
  JLScale(1,2,0);
  JLBegin(triangle);
    JLVertex(-1, 0, 0);
    JLVertex(1, 0, 0);
    JLVertex(0, 1, 0);
  JLEnd();
  /*
  JLPopMatrix();
  JLTranslate(-1,0,0);
  
  JLBegin(triangle);
    JLVertex(-1, 0, 0);
    JLVertex(1, 0, 0);
    JLVertex(0, 1, 0);
  JLEnd();*/
  
  return 0;
}
