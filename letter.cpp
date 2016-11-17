#include "letter.h"

void drawA() {
  JLPushMatrix();
    JLTranslate(0.5, 0, 0);
    JLRotate(15, 0, 0, 1);
    
    JLScale(0.25, 2, 0.5);
    drawbox();
  JLPopMatrix();

  JLPushMatrix();
    JLTranslate(-0.5, 0, 0);
    JLRotate(-15, 0, 0, 1);
    
    JLScale(0.25, 2, 0.5);
    
    drawbox();
  JLPopMatrix();

  JLPushMatrix();
    JLTranslate(0, 0, 0);
    JLScale(0.7, 0.25, 0.25);
    drawbox();
  JLPopMatrix();
}
void drawB(){
  JLPushMatrix();
    JLTranslate(-0.6, 0, 0);
    JLScale(0.25, 2 ,0.5);
    drawbox();
  JLPopMatrix();

  JLPushMatrix();
    JLTranslate(0, 0.9, 0);
    drawRingPart(0.7, 0.6, 0.5, 1, 240, 120);
  JLPopMatrix();

  JLPushMatrix();
    JLTranslate(0, -0.8, 0);
    drawRingPart(0.8, 0.7, 0.5, 1, 240, 120);
  JLPopMatrix();
}
void drawC(){
  JLPushMatrix();
    drawRingPart(1, 1.5, 0.5, 1, 60, 300);
  JLPopMatrix();
}
void drawD(){
  JLPushMatrix();
    JLTranslate(-0.5, 0, 0);
    JLScale(0.25, 1.75, 0.5);
    drawbox();
  JLPopMatrix();

  JLPushMatrix();
    drawRingPart(1, 1.25, 0.5, 1, 250, 120);
  JLPopMatrix();
}
void drawE(){
  JLPushMatrix();
    JLScale(0.25, 1.75, 0.5);
    JLTranslate(-3, 0, 0);
    drawbox();
  JLPopMatrix();

  JLPushMatrix();
    JLScale(0.75, 0.25, 0.5);
    JLTranslate(0, 6, 0);
    drawbox();
  JLPopMatrix();

  JLPushMatrix();
    JLScale(0.75, 0.25, 0.5);
    //JLTranslate(, 0, 0);
    drawbox();
  JLPopMatrix();

  JLPushMatrix();
    JLScale(0.75, 0.25, 0.5);
    JLTranslate(0, -6, 0);
    drawbox();
  JLPopMatrix();
}
void drawF(){
  JLPushMatrix();
    JLScale(0.25, 1.75, 0.5);
    JLTranslate(-3, 0, 0);
    drawbox();
  JLPopMatrix();

  JLPushMatrix();
    JLScale(0.75, 0.25, 0.5);
    JLTranslate(0, 6, 0);
    drawbox();
  JLPopMatrix();

  JLPushMatrix();
    JLScale(0.75, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
}
void drawG(){
  JLPushMatrix();
    drawRingPart(0.75, 1.4, 0.5, 1, 60, 0);
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(0.5, 0, 0);
    JLScale(0.75, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
}
void drawH(){
  JLPushMatrix();
    JLScale(0.25, 1.75, 0.5);
    JLTranslate(-3, 0, 0);
    drawbox();
  JLPopMatrix();

  JLPushMatrix();
    JLScale(0.25, 1.75, 0.5);
    JLTranslate(3, 0, 0);
    drawbox();
  JLPopMatrix();

  JLPushMatrix();
    JLScale(0.75, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
}
void drawI(){
  JLPushMatrix();
    JLScale(0.25, 1.75, 0.5);
    drawbox();
  JLPopMatrix();

  JLPushMatrix();
    JLScale(0.7, 0.25, 0.5);
    JLTranslate(0, 6, 0);
    drawbox();
  JLPopMatrix();

  JLPushMatrix();
    JLScale(0.7, 0.25, 0.5);
    JLTranslate(0, -6, 0);
    drawbox();
  JLPopMatrix();
}
void drawJ(){
  JLPushMatrix();
    JLTranslate(0, 1.5, 0);
    JLScale(1, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(0.5, 0.25, 0);
    JLScale(0.25, 1.25, 0.5);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(-0.25, -0.75, 0);
    drawRingPart(0.5, 0.75, 0.5, 1, 180, 0);
  JLPopMatrix();

}
void drawK(){
  JLPushMatrix();
    JLTranslate(-0.5,0,0);
    JLScale(0.25, 1.75, 0.5);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(0.5,0.5,0);
    JLRotate(50, 0, 0, 1);
    JLScale(1.5, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(0.75,-0.75,0);
    JLRotate(-45, 0, 0, 1);
    JLScale(1.25, 0.25, 0.5);    
    drawbox();
  JLPopMatrix();
}
void drawL(){
  JLPushMatrix();
    JLScale(0.25, 1.75, 0.5);
    JLTranslate(-3,0,0);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLScale(1, 0.25, 0.5);
    JLTranslate(0, -6, 0);
    drawbox();
  JLPopMatrix();
}
void drawM(){
  JLPushMatrix();
    JLScale(0.25, 1.75, 0.5);
    JLTranslate(-5.5, 0, 0);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLRotate(-45, 0, 0, 1);
    JLScale(1, 0.25, 0.5);
    JLTranslate(-1, 0.8, 0);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLRotate(45, 0, 0, 1);
    JLScale(1, 0.25, 0.5);
    JLTranslate(1, 0.8, 0);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLScale(0.25, 1.75, 0.5);
    JLTranslate(5.5, 0, 0);
    drawbox();
  JLPopMatrix();
}
void drawN(){
  JLPushMatrix();
    JLScale(0.25, 1.75, 0.5);
    JLTranslate(-3.5, 0, 0);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLRotate(-60, 0, 0, 1);
    JLScale(1.75, 0.25, 0.5);
    //JLTranslate(-1, , 0);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLScale(0.25, 1.75, 0.5);
    JLTranslate(3.5, 0, 0);
    drawbox();
  JLPopMatrix();
}
void drawO(){
  JLPushMatrix();
    drawRingPart(1, 1.3, 0.5, 1, 0, 360);
  JLPopMatrix();
}
void drawP(){
  JLPushMatrix();
    JLTranslate(-0.5, 0, 0);
    JLScale(0.25, 1.75, 0.5);
    drawbox();
  JLPopMatrix();

  JLPushMatrix();
    JLTranslate(0, 0.75, 0);
    drawRingPart(0.5, 0.5, 0.5, 1, 220, 120);
  JLPopMatrix();
}
void drawQ(){
  JLPushMatrix();
    drawRingPart(1, 1.3, 0.5, 1, 0, 360);
  JLPopMatrix();
  
  JLPushMatrix();
    JLRotate(-45, 0, 0, 1);
    JLScale(0.9, 0.25, 0.5);
    JLTranslate(1.2, -1, 0);
    drawbox();
  JLPopMatrix();
}
void drawR(){
  JLPushMatrix();
    JLTranslate(-0.5, 0, 0);
    JLScale(0.25, 1.75, 0.5);
    drawbox();
  JLPopMatrix();

  JLPushMatrix();
    JLTranslate(0, 0.75, 0);
    drawRingPart(0.5, 0.5, 0.5, 1, 240, 120);
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(0, -1.75, 0);
    drawRingPart(0.7, 1.5, 0.5, 1, 0, 120);
  JLPopMatrix();
}
void drawS(){
  JLPushMatrix();
    JLTranslate(0.1, 0.75, 0);
    drawRingPart(0.5, 0.5, 0.5, 1, 10, 270);
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(0, -0.75, 0);
    drawRingPart(0.5, 0.5, 0.5, 1, 200, 90);
  JLPopMatrix();
}
void drawT(){
  JLPushMatrix();
    JLTranslate(0, 1.5, 0);
    JLScale(1.25, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLScale(0.25, 1.75, 0.5);
    drawbox();
  JLPopMatrix();
}
void drawU(){
  JLPushMatrix();
    JLTranslate(1, 0.4, 0);
    JLScale(0.25, 1.4, 0.5);
    
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(-1, 0.4, 0);
    JLScale(0.25, 1.4, 0.5);    
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(0, -1, 0);
    drawRingPart(0.75, 0.5, 0.5, 1, 180, 0);
  JLPopMatrix();
}
void drawV(){
  JLPushMatrix();
    JLTranslate(0.65, 0, 0);
    JLRotate(65, 0, 0, 1);
    JLScale(1.8, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(-0.65, 0, 0);
    JLRotate(-70, 0, 0, 1);
    JLScale(1.8, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
}
void drawW(){
  JLPushMatrix();
    JLTranslate(1.0, 0, 0);
    JLRotate(70, 0, 0, 1);
    JLScale(1.75, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(0.25, -0.5, 0);
    JLRotate(-75, 0, 0, 1);
    JLScale(1, 0.25, 0.5);
    
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(-0.25, -0.5, 0);
    JLRotate(75, 0, 0, 1);
    JLScale(1, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(-1.0, 0, 0);
    JLRotate(-75, 0, 0, 1);
    JLScale(1.75, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
}
void drawX(){
  JLPushMatrix();
    JLRotate(60, 0, 0, 1);
    JLScale(1.75, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLRotate(-60, 0, 0, 1);
    JLScale(1.75, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
}
void drawY(){
  JLPushMatrix();
    JLTranslate(0.45, 0.75, 0);
    JLRotate(60, 0, 0, 1);
    JLScale(1, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(-0.45, 0.75, 0);
    JLRotate(-60, 0, 0, 1);
    JLScale(1, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(0, -0.75, 0);
    JLScale(0.25, 1, 0.5);
    drawbox();
  JLPopMatrix();
}
void drawZ(){
  JLPushMatrix();
    JLTranslate(0, 1.5, 0);
    JLScale(1, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLRotate(-25, 0, 0, 1);
    JLScale(0.25, 1.75, 0.5);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(0, -1.5, 0);
    JLScale(1, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
}

void drawLetter(char letter) {
  switch (letter){
    case 'A':
      drawA();
      break;
    case 'B':
      drawB();
      break; 
    case 'C':
      drawC();
      break; 
    case 'D':
      drawD();
      break; 
    case 'E':
      drawE();
      break; 
    case 'F':
      drawF();
      break; 
    case 'G':
      drawG();
      break; 
    case 'H':
      drawH();
      break; 
    case 'I':
      drawI();
      break; 
    case 'J':
      drawJ();
      break; 
    case 'K':
      drawK();
      break; 
    case 'L':
      drawL();
      break; 
    case 'M':
      drawM();
      break; 
    case 'N':
      drawN();
      break; 
    case 'O':
      drawO();
      break; 
    case 'P':
      drawP();
      break; 
    case 'Q':
      drawQ();
      break; 
    case 'R':
      drawR();
      break; 
    case 'S':
      drawS();
      break; 
    case 'T':
      drawT();
      break; 
    case 'U':
      drawU();
      break;
    case 'V':
      drawV();
      break; 
    case 'W':
      drawW();
      break; 
    case 'X':
      drawX();
      break;
    case 'Y':
      drawY();
      break; 
    case 'Z':
      drawZ();
      break;   
  }
}
