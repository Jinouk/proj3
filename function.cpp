#include "function.h"
#include <list> 

typedef struct vectex {
  double x;
  double y;
  double z;
} vertex;

typedef struct edge {
  vertex v1;
  vertex v2;
} edge;

list < list <edge> > triangle_strip;
list < list <edge> > quad_strip;

list < edge > polygon_tri; 
list < edge > polygon_quad;

int previous_vertex;
int counter;
int leftOverFlow, rightOverFlow, topOverFlow, bottomOverFlow;
vertex first;
vertex previous;

double viewingMatrix[16];
double modelMatrix[16]; 
double stack[32][16];

type polygonType;
int stackCounter;

int finalPixel[600][600];
int tempTable[600][600];
double zbuffer[600][600];

void clipping(list <edge>& polygon);
void lineDrawing(list <edge>& polygon);
void polygonFilling(list <edge>& polygon); 
void normalize(double * vector, int count);
void translate(double * matrix, double x, double y, double z);



void viewNormalization(double * eye, double * center, double * up, 
                       double right, double left, double top, double bottom,
                       double near, double far) {
  
  double w[3], u[3], v[3];
  double matrix2[16], resultMatrix[16];
  double a, b; 

  w[0] = eye[0] - center[0];
  w[1] = eye[1] - center[1];
  w[2] = eye[2] - center[2];

  printmat(3,1,w);

  normalize(w, 3);

  printmat(3,1,w);

  crossproduct(up, w, u);
  
  normalize(u, 3);

  crossproduct(w, u, v);

  matrix2[0] = u[0];
  matrix2[1] = u[1];
  matrix2[2] = u[2];
  matrix2[3] = 0;

  matrix2[4] = v[0];
  matrix2[5] = v[1];
  matrix2[6] = v[2];
  matrix2[7] = 0;

  matrix2[8] = w[0];
  matrix2[9] = w[1];
  matrix2[10] = w[2];
  matrix2[11] = 0;

  matrix2[12] = 0;
  matrix2[13] = 0;
  matrix2[14] = 0;
  matrix2[15] = 1;

  printmat(4, 4, matrix2);

  identity(4, viewingMatrix);
  translate(viewingMatrix, -eye[0], -eye[1], -eye[2]);

  printmat(4,4, viewingMatrix);
  multiplication(4,4,4, viewingMatrix, matrix2, resultMatrix);
  copymatrix(4, 4, viewingMatrix, resultMatrix);

  printmat(4, 4, viewingMatrix);

  /**
  // shear
  a = ((width[0] + width[1]) / 2) / length[0];
  b = ((height[0] + height[1]) / 2) / length[0];

  cout << "a: " << a << " b: " << b << endl;
  identity(4, matrix2); 
  matrix2[2] = a;
  matrix2[6] = b;

  printmat(4, 4, matrix2); 

  multiplication(4, 4, 4, viewingMatrix, matrix2, resultMatrix);
  copymatrix(4, 4, viewingMatrix, resultMatrix);

  // scale in x and y
  identity(4, matrix2);
  matrix2[0] = length[0] / ( (width[0] - width[1]) / 2);  // near / (right - left) / 2
  matrix2[5] = length[0] / ( (height[0] - height[1]) / 2);  // near / (top - bottom) / 2

  printmat(4, 4, matrix2);

  multiplication(4, 4, 4, viewingMatrix, matrix2, resultMatrix);
  copymatrix(4, 4, viewingMatrix, resultMatrix);

  // scale in z
  identity(4, matrix2);
  matrix2[0] = 1 / length[1];
  matrix2[5] = 1 / length[1];
  matrix2[10] = 1 / length[1];

  printmat(4, 4, matrix2);

  multiplication(4, 4, 4, viewingMatrix, matrix2, resultMatrix);
  copymatrix(4, 4, viewingMatrix, resultMatrix);

  printmat(4, 4, viewingMatrix);
  **/
  
  
  matrix2[0] = ( 2 * near ) / ( right -  left);
  matrix2[1] = 0;
  matrix2[2] = ( right + left ) / ( right - left);
  matrix2[3] = 0;
  matrix2[4] = 0;
  matrix2[5] = ( 2 * near ) / ( top - bottom );  
  matrix2[6] = ( top + bottom ) / ( top - bottom );
  matrix2[7] = 0;
  matrix2[8] = 0;
  matrix2[9] = 0;
  matrix2[10] = ( -1 * ( far + near ) ) / ( far - near );
  matrix2[11] =  ( -2 * far * near ) / ( far - near );
  matrix2[12] = 0;
  matrix2[13] = 0;
  matrix2[14] = -1;
  matrix2[15] = 0; 
  
  printmat(4,4, matrix2);
  
  multiplication(4, 4, 4, matrix2, viewingMatrix, resultMatrix);
  copymatrix(4, 4, viewingMatrix, resultMatrix);
  
  printmat(4,4, viewingMatrix);
 
}

void JLLoadIdentity() {
  identity(4, modelMatrix);
}

void JLTranslate(double x, double y, double z) {
  double tempMatrix[16], resultMatrix[16];
  identity(4, tempMatrix);

  tempMatrix[3]  = x;
  tempMatrix[7]  = y;
  tempMatrix[11] = z;

  multiplication(4,4,4, modelMatrix, tempMatrix, resultMatrix);
  copymatrix(4, 4, modelMatrix, resultMatrix);
}

void JLRotate(double angle, double xAxis, double yAxis, double zAxis) {
  double tempMatrix[16], resultMatrix[16];
  identity(4, tempMatrix);

  if(xAxis)
    rotate('x', angle, tempMatrix);
  if(yAxis)
    rotate('y', angle, tempMatrix);
  if(zAxis)
    rotate('z', angle, tempMatrix);

  multiplication(4, 4, 4, modelMatrix, tempMatrix, resultMatrix);
  copymatrix(4, 4, modelMatrix, resultMatrix);
}

void JLScale(double xScale, double yScale, double zScale) {
  double tempMatrix[16], resultMatrix[16];
  identity(4, tempMatrix);

  tempMatrix[0] = xScale;
  tempMatrix[5] = yScale;
  tempMatrix[10] = zScale;

  multiplication(4, 4, 4, modelMatrix, tempMatrix, resultMatrix);
  copymatrix(4, 4, modelMatrix, resultMatrix);
}

void JLPushMatrix() {
  for(int i= 0; i < 4; i++)
    for (int j = 0; j< 4; j++)
      stack[stackCounter][i*4+j] = modelMatrix[i*4+j];
  
  stackCounter++;
}

void JLPopMatrix() {
  for(int i= 0; i < 4; i++)
    for (int j = 0; j< 4; j++)
      modelMatrix[i*4+j] = stack[stackCounter - 1][i*4+j];
  stackCounter--;
}

void JLBegin(type m) {
  polygonType = m;
}

void JLEnd() {
  
  list <edge> ::iterator iterator;

  if(polygonType == triangle){
    for(iterator = polygon_tri.begin(); iterator != polygon_tri.end(); ++iterator) {
      cout << "edge: \nv1 = { x: " << iterator->v1.x << ", y: " << iterator->v1.y << ", z: " << iterator->v1.z << "}, v2 = { x: " << iterator->v2.x << ", y: " << iterator->v2.y << ", z: " << iterator->v2.z << " } " <<endl; 
    }

    clipping(polygon_tri);

    for(iterator = polygon_tri.begin(); iterator != polygon_tri.end(); ++iterator) {
      cout << "edge: \nv1 = { x: " << iterator->v1.x << ", y: " << iterator->v1.y << ", z: " << iterator->v1.z << "}, v2 = { x: " << iterator->v2.x << ", y: " << iterator->v2.y << ", z: " << iterator->v2.z << "} " << endl; 
    }
    
    lineDrawing(polygon_tri);
    //polygonFilling(polygon_tri);
  }
  
  
  else {
    for(iterator = polygon_quad.begin(); iterator != polygon_quad.end(); ++iterator) {
      cout << "edge: \nv1 = { x: " << iterator->v1.x << ", y: " << iterator->v1.y << ", z: " << iterator->v1.z << "}, v2 = { x: " << iterator->v2.x << ", y: " << iterator->v2.y << ", z: " << iterator->v2.z << " } " <<endl; 
    }

    clipping(polygon_quad);

    for(iterator = polygon_quad.begin(); iterator != polygon_quad.end(); ++iterator) {
      cout << "edge: \nv1 = { x: " << iterator->v1.x << ", y: " << iterator->v1.y << ", z: " << iterator->v1.z << "}, v2 = { x: " << iterator->v2.x << ", y: " << iterator->v2.y << ", z: " << iterator->v2.z << "} " << endl; 
    }
    
    lineDrawing(polygon_quad);
    polygonFilling(polygon_quad);
  }
  
  for(int i = 599; i >= 0; i--){
    for(int j = 0; j < 600; j++){
      if(tempTable[i][j] == 1){
        finalPixel[i][j] = 1;
        tempTable[i][j] = 0;
        cout << "@";
      }
      else
        cout << ".";
    }
    cout << endl;
  }

  triangle_strip.push_back(polygon_tri);
  polygon_tri.clear();
  
  cout << triangle_strip.front().front().v1.x << endl;
  
}

void JLVertex(double x, double y, double z) {
  
  double coord[] = {x, y, z, 1};
  double final[4];
  double resultMatrix[16];
  multiplication(4, 4, 4, viewingMatrix, modelMatrix, resultMatrix);
  multiplication(4, 4, 1, resultMatrix, coord, final);

  printmat(4,1,final);
  printf("x: %f, y: %f, z: %f\n", final[0], final[1], final[2]);

  vertex v;
  v.x = final[0];
  v.y = final[1]; 
  v.z = final[2]; 
   
  switch(polygonType) {
    case triangle:
      counter++;
      if(!previous_vertex){
        first = v;
        previous = v;
        previous_vertex = 1;
      }
      else{
        edge e = {previous, v};
        polygon_tri.push_back(e);
        
        cout << "edge v1 = { " << previous.x << ", " << previous.y << ", " << previous.z << "}" << endl;
        previous = v;
      }
      
      if(counter == 3) {
        edge e = { v, first };
        polygon_tri.push_back(e);
        
        previous_vertex = 0;
        counter = 0;
      }
      
      break;
    case quad:
    
      counter++;
      if(!previous_vertex){
        first = v;
        previous = v;
        previous_vertex = 1;
      }
      else{
        edge e = {previous, v};
        polygon_quad.push_back(e);
        
        cout << "edge v1 = { " << previous.x << ", " << previous.y << ", " << previous.z << "}" << endl;
        previous = v;
      }
      
      if(counter == 4) {
        edge e = { v, first };
        polygon_quad.push_back(e);
        
        previous_vertex = 0;
        counter = 0;
      }
      break;
    default: 
      cout << "nothing" << endl;
      break;
  }
}

void printMatrix() {
  printmat(4, 4, modelMatrix);
}
// Helper Method
void translate(double * matrix, double x, double y, double z) {
  double tempMatrix[16], resultMatrix[16];
  identity(4, tempMatrix);

  tempMatrix[3]  = x;
  tempMatrix[7]  = y;
  tempMatrix[11] = z;

  multiplication(4, 4, 4, matrix, tempMatrix, resultMatrix);
  copymatrix(4, 4, matrix, resultMatrix);
}

void normalize(double * vector, int count) {
  double denominator;

  for (int i = 0; i < count; i++) {
    denominator += (vector[i] * vector[i]);
  }

  denominator = sqrt(denominator);

  for(int i = 0; i < count; i++) {
    vector[i] = vector[i] / denominator;
  }
}

void clipping(list <edge>& polygon) {
  
  list <edge>::iterator iterator;

  for(iterator = polygon.begin(); iterator != polygon.end(); ++iterator) {
    
    double point1x = iterator->v1.x;
    double point1y = iterator->v1.y;
    double point1z = iterator->v1.z;
    double point2x = iterator->v2.x;
    double point2y = iterator->v2.y;
    double point2z = iterator->v1.z;

    double slopeXY = (point1y - point2y) / (point1x - point2x);
    double yIntercept = point1y - slopeXY * point1x;

    double slopeXZ  = (point1z - point2z) / (point1x - point2x);
    double zIntercept = point1z - slopeXZ * point1x;

    double slopeYZ = (point1y - point2y) / (point1z - point2z); 
    double yInterceptYZ = point1y - slopeYZ * point1z;

    // check right

    // both points outside
    if (point1x > 1 && point2x > 1) {
      //discard this edge
      //polygon.erase(iterator);
    }

    // only first point
    else if (point1x > 1) {
      // find point where x  = 1
      rightOverFlow = 1;
      double newY = slopeXY + yIntercept;
      double newZ = slopeXZ + zIntercept;
      vertex newVertex = {1, newY, newZ};
      iterator->v1 = newVertex;
    }

    // only second point
    else if (point2x > 1) {
      rightOverFlow = 1;
      double newY = slopeXY + yIntercept;
      double newZ = slopeXZ + zIntercept;
      vertex newVertex = {1, newY, newZ};
      iterator->v2 = newVertex;
    }

    // both points inside
    else {
      // do nothing?
    }

    // check bottom

    // both points outside
    if (point1y < -1 && point2y < -1) {
      //discard this edge
      //polygon.erase(iterator);
    }

    // only first point
    else if (point1y < -1) {
      bottomOverFlow = 1;
      double newX = (-1 - yIntercept) / slopeXY;
      double newZ = (-1 - yInterceptYZ) / slopeYZ;
      vertex newVertex = {newX, -1,newZ};
      iterator->v1 = newVertex;
    }

    // only second point
    else if (point2y < -1) {
      bottomOverFlow = 1;
      double newX = (-1 - yIntercept) / slopeXY;
      double newZ = (-1 - yInterceptYZ) / slopeYZ;
      vertex newVertex = {newX, -1,newZ};
      iterator->v2 = newVertex;
    }

    // both points inside
    else {
      // do nothing?
    }

    // check left 

    // both points outside
    if (point1x < -1 && point2x < -1) {
      //discard this edge
      //polygon.erase(iterator);
    }

    // only first point
    else if (point1x < -1) {
      leftOverFlow = 1;
      double newY = -slopeXY + yIntercept;
      double newZ = -slopeXZ + zIntercept;
      vertex newVertex = {-1, newY,newZ};
      iterator->v1 = newVertex;
    }

    // only second point
    else if (point2x < -1) {
      leftOverFlow = 1;
      double newY = -slopeXY + yIntercept;
      double newZ = -slopeXZ + zIntercept;
      vertex newVertex = {-1, newY,newZ};
      iterator->v2 = newVertex;
    }

    // both points inside
    else {
      // do nothing?
    }

    // check top

    // both points outside
    if (point1y > 1 && point2y > 1) {
      //discard this edge
      //polygon.erase(iterator);
    }

    // only first point
    else if (point1y > 1) {
      topOverFlow = 1;
      double newX = (1 - yIntercept) / slopeXY;
      double newZ = (1 - yInterceptYZ) / slopeYZ;
      vertex newVertex = {newX, 1,newZ};
      iterator->v1 = newVertex;
    }

    // only second point
    else if (point2y > 1) {
      topOverFlow = 1;
      double newX = (1 - yIntercept) / slopeXY;
      double newZ = (1 - yInterceptYZ) / slopeYZ;
      vertex newVertex = {newX, 1,newZ};
      iterator->v2 = newVertex;
    }

    // both points inside
    else {
      // do nothing?
    } 
  }
}

void lineDrawing(list <edge>& polygon) {
  list <edge>::iterator iterator;

  for(iterator = polygon.begin(); iterator != polygon.end(); ++iterator) {
    double point1x = iterator->v1.x * 300;
    double point1y = iterator->v1.y * 300;
    
    double point2x = iterator->v2.x * 300;
    double point2y = iterator->v2.y * 300;

    double slope = (point1y - point2y) / (point1x - point2x);
    double yIntercept = point1y - slope * point1x;

    int start = round(point1x);
    int end = round(point2x);
    int deltaX;
    
    if( !(point1x > 300 && point2x > 300) && !(point1x < -300 && point2x < -300) &&
        !(point1y > 300 && point2y > 300) && !(point1y < -300 && point2y < -300)){
      cout << " yinter: " << yIntercept << " slope: " << slope << endl;
      // check through x
      // horizontal check
      if(start != end){
        if( (point1x - point2x) < 0)
          deltaX = 1;
        else
          deltaX = -1;
        cout << deltaX << endl;
        cout << "Start: " << start << " End: " << end <<endl;
        while(start != end) {
          //cout << "start: " << deltaX << " end: " << end << endl;
          int yPixel = slope * start + yIntercept;
          
          tempTable[yPixel + 299][start + 299] = 1;
          
          cout << "x: " << start + 299 << " y: " << yPixel << endl;
          start += deltaX;
        }
        /*
        int deltaY;
        start = round(point1y);
        end = round(point2y);
        
        if(start != end) {
          if( (start - end) < 0)
            deltaY = 1;
          else
            deltaY = -1;
          cout << "start: " << start << " end: " << end << endl;
          cout << "deltaY: " << deltaY << " yinter: " << yIntercept << " slope: " << slope << endl;
          while(start != end) {
            int xPixel = (start - yIntercept) / slope;
            cout << "x: " << xPixel << endl;
            
            tempTable[start + 299][xPixel + 299] = 1;
            start += deltaY; 
          }
        }  */
      }
      
      
      // vertical check 
      else {
      cout << " yinter: " << yIntercept << " slope: " << slope << endl;
        start = round(point1y);
        end = round(point2y);
        
        if( (point1y - point2y) < 0)
          deltaX = 1;
        else
          deltaX = -1;
     
        while(start != end) {
          //cout << "start: " << deltaX << " end: " << end << endl;
          
          tempTable[start + 299][(int) point1x + 299] = 1;
          start += deltaX;
        }  
      }      
    }
  }
  
}

void polygonFilling(list <edge>& polygon){
  
  
  int numPoints = 0;
  double maxY = -1, minY = 1;
  list <vertex> points; 
  
  list <edge> ::iterator iterator;
  for(iterator = polygon.begin(); iterator != polygon.end(); ++iterator) {
    if(iterator->v1.y > maxY)
      maxY = iterator->v1.y;
    if(iterator->v2.y > maxY)
      maxY = iterator->v2.y;
    if(iterator->v1.y < minY)
      minY = iterator->v1.y;
    if(iterator->v1.y > maxY)
      minY = iterator->v2.y;
  }
  
  minY = minY * 300 + 299;
  maxY = maxY * 300 + 299;
  
  cout << minY << "               " << maxY << endl;
  
  if(maxY > 600) 
    maxY = 599;
  if(minY < -600)
    minY = 0;  
  
  
  for(int y = maxY; y >= minY; y--){
    for(int j = 0; j < 600; j++){
      if(tempTable[y][j] == 1){
        vertex newPoint = {j, y, 0};
        points.push_back(newPoint);
        numPoints++;
        
        cout << "new: " << newPoint.x << " " << newPoint.y << endl;
      }
    }
    
    cout << "num point: " << numPoints << endl;
    if(numPoints == 1){
      cout << "number okay? " << endl;
      if(rightOverFlow == 1){
        cout << "front: " << points.front().x << " back: " << points.back().x << endl;
        vertex borderPoint = {599, y, 0};
        points.push_back(borderPoint);
        
         
        cout << "front: " << points.front().x << " back: " << points.back().x << endl;
      }
     
      else{
        
        vertex borderPoint = {0, y, 0};
        points.push_front(borderPoint);
        cout << "front: " << points.front().x << " back: " << points.back().x << endl;
      }     
      
    }
    
    edge e = { points.front(), points.back() };
    points.clear();
    
    for(int i = e.v1.x; i <= e.v2.x; i++){

      tempTable[y][i] = 1;
    }
    numPoints = 0;
  }
}


