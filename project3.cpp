#include "number.h"
#include "letter.h"
//#include <pnm.h>

int main() {
  double eye[] = {0, 2, 11};
  double center[] = {0, 0, 0};
  double up[] = {0, 1, 0};

  viewNormalization(eye, center, up, 10, -10, 10, -10, 1, 10);
  JLLoadIdentity();
  
  
  //drawboxWithEave();
 
  JLPushMatrix();
    JLTranslate(0, 4, -3);
    JLScale(0.25,0.25,0.25);
    drawNumber(5);
  JLPopMatrix();
  

  JLPushMatrix();
    JLTranslate(-1, 0, -2);
    JLScale(0.25,0.25,0.25);
    drawboxWithEave();
  JLPopMatrix();

  JLPushMatrix();
    JLTranslate(-3, 0, -4);
    JLScale(0.25,0.25,0.25);
    drawboxWithEave();
  JLPopMatrix();

  JLPushMatrix();
    //JLTranslate(1, 0, -2);
    JLScale(0.25,0.25,0.25);
    drawboxWithEave();
  JLPopMatrix();

  JLPushMatrix();
    JLTranslate(1, 0, -2);
    JLScale(0.25,0.25,0.25);
    drawboxWithEave();
  JLPopMatrix();

  JLPushMatrix();
    JLTranslate(3, 0, -4);
    JLScale(0.25,0.25,0.25);
    drawboxWithEave();
  JLPopMatrix();

  printFinal();
  
  return 0;
}
