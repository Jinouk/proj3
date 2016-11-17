// Number.c
// Definition of All Number functions
#include "number.h"

void drawZero() {
  JLPushMatrix();
    drawRingPart(1.0, 2.0, 0.5, 1, 0, 360);
  JLPopMatrix();
}
void drawOne(){
  JLScale(1.1, 1.1, 1);
  JLPushMatrix();
    JLScale(1, 0.25, 0.5);
    JLTranslate(0, -8, 0);
    drawbox();
  JLPopMatrix();

  JLPushMatrix();
    JLScale(0.25, 1.5, 0.5);
    JLTranslate(0, -0.25, 0);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLScale(1.25, 1.25, 1);
    JLTranslate(0.25, 0.75, 0.5);

    
    // Front Triangle
    JLBegin(triangle);   
      JLVertex(0,0,0);
      JLVertex(0,1,0);
      JLVertex(-1, 0, 0);
    JLEnd();
    
    // Back Trianlge
    ;
    JLBegin(triangle);
      JLVertex(-1, 0, -1);
      JLVertex(0, 1, -1);
      JLVertex(0, 0, -1);
    JLEnd();
    
    // Side
    
    JLBegin(triangle);
      //JLVertex(-1, 0, -1);
      JLVertex(0, 0, -1);
      JLVertex(0, 1, 0);
      JLVertex(0, 0, 0);
    JLEnd();

    JLBegin(triangle);
      //JLVertex(-1, 0, -1);
      JLVertex(0, 0, -1);
      JLVertex(0, 1, 0);
      JLVertex(0, 1, -1);
    JLEnd();

    
    // Bottom
    
    JLBegin(triangle);
      JLVertex(0, 1, 0);
      JLVertex(0, 0, 0);
      JLVertex(-1, 0, -1);
      JLVertex(-1, 0, 0);
    JLEnd();

    // Top
    ;
    JLBegin(triangle);
      JLVertex(0,1,0);
      JLVertex(-1, 0, 0);
      JLVertex(-1, 0, -1);
      //JLVertex(0, 1, -1);
    JLEnd();

    JLBegin(triangle);
      JLVertex(0,1,0);
      JLVertex(-1, 0, -1);
      JLVertex(0, 1, -1);
      //JLVertex(0, 1, -1);
    JLEnd();
    
  JLPopMatrix();
}
void drawTwo(){
  JLTranslate(0, 1, 0);
  JLPushMatrix();
    drawRingPart(1,1,0.5,1, 315, 180);
  JLPopMatrix();
  
  JLPushMatrix();
    JLRotate(45, 0, 0, 1);
    JLScale(1.5, 0.25, 0.5);
    JLTranslate(-1, -5, 0);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLScale(1.4, 0.25, 0.5);
    JLTranslate(0, -12.25, 0);
    drawbox();
  JLPopMatrix();
}
void drawThree(){
  JLScale(1, 0.9, 1);
  JLPushMatrix();
    JLTranslate(0, 1.25, 0);
    drawRingPart(1,1,0.5, 1, 270, 135);
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(0, -1.25, 0);
    drawRingPart(1,1,0.5, 1, 225, 90);
  JLPopMatrix();
}
void drawFour(){
  JLTranslate(0.5, -0.5, 0);
  JLScale(0.7, 0.7, 1);

  JLPushMatrix();
    JLScale(0.5, 3.5, 0.5);
    JLTranslate(1, 0.25, 0);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLScale(2, 0.5, 0.5);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLRotate(65, 0, 0, 1);
    JLScale(2.25, 0.5, 0.5);
    JLTranslate(0.75, 2.75, 0);
    drawbox(); 
  JLPopMatrix();
}
void drawFive(){
  JLTranslate(0,-0.8, 0);
  JLScale(1, 1.025, 1);
  JLPushMatrix();
    JLScale(1.1, 0.25, 0.5);
    JLTranslate(0.11, 12, 0);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLScale(0.25, 1.0, 0.5);
    JLTranslate(-2.90, 2, 0);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    drawRingPart(1,1,0.5, 1, 225, 135);
  JLPopMatrix();
}
void drawSix(){
  JLPushMatrix();
    drawRingPart(1, 2, 0.5, 1, 50, 315);
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(0, -1.02, 0);
    drawRingPart(0.7, 1, 0.5, 1, 315, 180);
  JLPopMatrix();
}
void drawSeven(){
  JLTranslate(0.5, 0, 0);
  JLPushMatrix();
    JLTranslate(1, -2.5, 0);
    drawRingPart(1.5, 4, 0.5, 1, 90, 180);
  JLPopMatrix();
  JLPushMatrix();
    
    JLTranslate(-0.25, 2, 0);
    JLScale(1.25, 0.25, 0.5);
    drawbox();
  JLPopMatrix();
}
void drawEight(){
  JLPushMatrix();
    JLTranslate(0, 1, 0);
    drawRingPart(0.8, 0.8, 0.5, 1, 0, 360);
  JLPopMatrix();
  
  JLPushMatrix();
    JLTranslate(0, -1.25, 0);
    drawRingPart(1, 0.9, 0.5, 1, 0, 360);
  JLPopMatrix();
}
void drawNine(){
  JLPushMatrix();
    JLTranslate(0, 0.75, 0);
    drawRingPart(0.8, 1, 0.5, 1, 0, 360);
  JLPopMatrix();
  
  JLPushMatrix();
    JLRotate(-5, 0, 0, 1);
    JLTranslate(-0.1, 0, 0);
    drawRingPart(0.9, 2, 0.5, 1, 220, 30);
  JLPopMatrix();
}

void drawNumber(int num){
  switch (num) {
    case 1:
      drawOne();
      break;  
    case 2:
      drawTwo();
      break;  
    case 3:
      drawThree();
      break;  
    case 4:
      drawFour();
      break;  
    case 5:
      drawFive();
      break;  
    case 6:
      drawSix();  
      break;  
    case 7:
      drawSeven();
      break;  
    case 8:
      drawEight();
      break;  
    case 9:
      drawNine();
      break;  
    default:
      drawZero();
      break;   
  }
}
