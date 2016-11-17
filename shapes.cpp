#import "shapes.h"

void drawbox() {
  // front 
  JLBegin(quad);
    JLVertex(-1,-1,1);
    JLVertex(1,-1,1);
    JLVertex(1,1,1);
    JLVertex(-1,1,1);
  JLEnd();

  // back
  JLBegin(quad);
    JLVertex(-1,-1,-1);
    JLVertex(1,-1,-1);
    JLVertex(1,1,-1);
    JLVertex(-1,1,-1);
  JLEnd();

  // right
  JLBegin(quad);
    JLVertex(1,1,1);
    JLVertex(1,-1,1);
    JLVertex(1,-1,-1);
    JLVertex(1,1,-1);
  JLEnd();

  // left
  JLBegin(quad);
    JLVertex(-1,1,1);
    JLVertex(-1,-1,1);
    JLVertex(-1,-1,-1);
    JLVertex(-1,1,-1);
  JLEnd();

  // top
  JLBegin(quad);
    JLVertex(-1,1,1);
    JLVertex(1,1,1);
    JLVertex(1,1,-1);
    JLVertex(-1,1,-1);
  JLEnd();

  // bottom
  JLBegin(quad);
    JLVertex(-1,-1,1);
    JLVertex(1,-1,1);
    JLVertex(1,-1,-1);
    JLVertex(-1,-1,-1);
  JLEnd();
}

void drawboxWithEave() {
  JLColor('w');
  drawbox();

  JLColor('b');
  JLPushMatrix();
    JLScale(0.1,0.1, 1);
    JLTranslate(11, 11, 0);
    drawbox();
    
    JLTranslate(0,-22, 0);
    drawbox();
    
    JLTranslate(-22,0,0) ;
    drawbox();
    
    JLTranslate(0,22,0) ;
    drawbox();
  JLPopMatrix(); 

  JLPushMatrix();
    JLScale(1, 0.1, 0.1);
    JLTranslate(0,11,11);
    drawbox(); 
    
    JLTranslate(0, -22, 0);
    drawbox(); 
    
    JLTranslate(0, 0, -22);
    drawbox(); 
    
    JLTranslate(0, 22, 0);
    drawbox();
  JLPopMatrix();
  
  JLPushMatrix();
    JLScale(0.1, 1.2, 0.1);
    JLTranslate(11, 0, 11);
    drawbox();
    
    JLTranslate(-22, 0, 0);
    drawbox();
    
    JLTranslate(0, 0, -22);
    drawbox();
    
    JLTranslate(22, 0, 0);
    drawbox();
  JLPopMatrix(); 
}

void drawRingPart(double radiusX, double radiusY, double width, double thickness , int start, int end) {
  int vertexCount;
  int theta = start;

  if(start > end) {
    vertexCount = 360 - start + end;
  }
  
  else {
    vertexCount = end - start;
  }

  if(vertexCount == 360){ 
    vertexCount++;
    end++; 
  } 

  double frontInnerCord[vertexCount][2];
  double frontOuterCord[vertexCount][2];
  
  double backInnerCord[vertexCount][2];
  double backOuterCord[vertexCount][2];

  double innerX, innerY, outerX, outerY;

  double radian;
  
  JLPushMatrix();
    for(int i = 0; i < vertexCount; i++) {
      if (theta == 360) {
        theta = 0; 
      }
      radian =  theta * PI / 180.0;

      // Inner Circle
      innerX = radiusX * cos(radian);
      innerY = radiusY * sin(radian);
    
      // Outer Circle
      outerX = (radiusX + width) * cos(radian);
      outerY = (radiusY + width) * sin(radian);
      
              
      frontInnerCord[i][0] = innerX;
      frontInnerCord[i][1] = innerY;
      
      frontOuterCord[i][0] = outerX;
      frontOuterCord[i][1] = outerY;

      backInnerCord[i][0] = innerX;
      backInnerCord[i][1] = innerY;
      
      backOuterCord[i][0] = outerX;
      backOuterCord[i][1] = outerY;
      
      theta++;
    }
    
    
    theta = start;

    
    for(int i = 0; i < vertexCount-1; i++) {
      if (theta == 360) {
        theta = 0;
      }
      // front           
      JLBegin(triangle);
        JLVertex(frontInnerCord[i][0], frontInnerCord[i][1], -thickness/2.0); 
        JLVertex(frontOuterCord[i][0], frontOuterCord[i][1], -thickness/2.0);
        JLVertex(frontOuterCord[i+1][0], frontOuterCord[i+1][1], -thickness/2.0);
      JLEnd();

      JLBegin(triangle);
        JLVertex(frontInnerCord[i][0], frontInnerCord[i][1], -thickness/2.0); 
        JLVertex(frontOuterCord[i][0], frontOuterCord[i][1], -thickness/2.0);
        JLVertex(frontOuterCord[i+1][0], frontOuterCord[i+1][1], -thickness/2.0);
      JLEnd();

      //back
      JLBegin(triangle);
        JLVertex(frontInnerCord[i][0], frontInnerCord[i][1], thickness/2.0); 
        JLVertex(frontOuterCord[i][0], frontOuterCord[i][1], thickness/2.0);
        JLVertex(frontOuterCord[i+1][0], frontOuterCord[i+1][1], -thickness/2.0);
      JLEnd();

      JLBegin(triangle);
        JLVertex(frontInnerCord[i][0], frontInnerCord[i][1], thickness/2.0); 
        JLVertex(frontOuterCord[i][0], frontOuterCord[i][1], thickness/2.0);
        JLVertex(frontOuterCord[i+1][0], frontOuterCord[i+1][1], thickness/2.0);
      JLEnd();
      theta++;
    }
    
    
    // Inner & Outer surface
    theta = start;
    for(int i = 0; i < vertexCount-1; i++) {
      if(theta == 360) {
        theta = 0;
      }
      // Inner
      
      JLBegin(triangle);
        JLVertex(frontInnerCord[i][0], frontInnerCord[i][1], thickness/2.0); 
        JLVertex(backInnerCord[i+1][0], backInnerCord[i+1][1], thickness/2.0);
        JLVertex(frontInnerCord[i][0], frontInnerCord[i][1], -thickness/2.0);  
      JLEnd();

      JLBegin(triangle);
        JLVertex(frontInnerCord[i][0], frontInnerCord[i][1], -thickness/2.0); 
        JLVertex(backInnerCord[i+1][0], backInnerCord[i+1][1], -thickness/2.0);
        JLVertex(frontInnerCord[i+1][0], frontInnerCord[i+1][1], thickness/2.0);  
      JLEnd();

      // Outer
      
      JLBegin(triangle);
        JLVertex(frontOuterCord[i][0], frontOuterCord[i][1], thickness/2.0); 
        JLVertex(backOuterCord[i+1][0], backOuterCord[i+1][1], thickness/2.0);
        JLVertex(frontOuterCord[i][0], frontOuterCord[i][1], -thickness/2.0); 
      JLEnd();

      JLBegin(triangle);
        JLVertex(frontOuterCord[i][0], frontOuterCord[i][1], -thickness/2.0); 
        JLVertex(backOuterCord[i+1][0], backOuterCord[i+1][1], -thickness/2.0);
        JLVertex(frontOuterCord[i+1][0], frontOuterCord[i+1][1], thickness/2.0); 
      JLEnd();
      theta++;
    }
    
    JLBegin(quad);
      JLVertex(frontInnerCord[0][0], frontInnerCord[0][1], thickness/2.0);
      JLVertex(backInnerCord[0][0], backInnerCord[0][1], -thickness/2.0);
      JLVertex(frontOuterCord[0][0], frontOuterCord[0][1], thickness/2.0);
      JLVertex(backOuterCord[0][0], backOuterCord[0][1], -thickness/2.0);
    JLEnd();

    JLBegin(quad);
      JLVertex(frontInnerCord[vertexCount-1][0], frontInnerCord[vertexCount-1][1], thickness/2.0);
      JLVertex(backInnerCord[vertexCount-1][0], backInnerCord[vertexCount-1][1], -thickness/2.0);
      JLVertex(frontOuterCord[vertexCount-1][0], frontOuterCord[vertexCount-1][1], thickness/2.0);
      JLVertex(backOuterCord[vertexCount-1][0], backOuterCord[vertexCount-1][1], -thickness/2.0);
    JLEnd();

  JLPopMatrix();
}