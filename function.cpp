#include "function.h"
#include <list> 

const int window_size = 601;

typedef struct vectex {
  double x;
  double y;
  double z;
} vertex;

typedef struct edge {
  vertex v1;
  vertex v2;
} edge;

list < edge > polygon_tri; 
list < edge > polygon_quad;

list <vertex> globalPoints;

double nearK, farK; 

char color = 'b';

int previous_vertex;
int counter;
int leftOverFlow, rightOverFlow, topOverFlow, bottomOverFlow;
vertex first;
vertex previous;

double viewingMatrix[16];
double rotationMatrix[16];
double modelMatrix[16]; 
double stack[32][16];
double rotateMatrixStack[32][16];

type polygonType;
int stackCounter;

int finalPixel[window_size][window_size];
int tempTable[window_size][window_size];
double zbuffer[window_size][window_size];

void clipping(list <edge>& polygon);
void lineDrawing(list <edge>& polygon);
void polygonFilling(list <edge>& polygon);
void findZ(list <edge> & polygon); 
void normalize(double * vector, int count);
void translate(double * matrix, double x, double y, double z);
void rotate(double * matrix, double angle, double x, double y, double z);

void viewNormalization(double * eye, double * center, double * up, 
                       double right, double left, double top, double bottom,
                       double near, double far) {
  nearK = near;
  farK = far;
  
  for ( int i = 0; i < window_size; i++){
    for ( int j = 0; j < window_size; j++){
      zbuffer[i][j] = 10000.0;
    }
  }

  double w[3], u[3], v[3];
  double projectionMatrix[16], resultMatrix[16];
  
  // projection transform matrix
  cout << "Projection Matrix" << endl;
  projectionMatrix[0] = ( 2 * near ) / ( right -  left);
  projectionMatrix[1] = 0;
  projectionMatrix[2] = ( right + left ) / ( right - left);
  projectionMatrix[3] = 0;
  projectionMatrix[4] = 0;
  projectionMatrix[5] = ( 2 * near ) / ( top - bottom );  
  projectionMatrix[6] = ( top + bottom ) / ( top - bottom );
  projectionMatrix[7] = 0;
  projectionMatrix[8] = 0;
  projectionMatrix[9] = 0;
  projectionMatrix[10] = ( -1 * ( far + near ) ) / ( far - near );
  projectionMatrix[11] =  ( -2 * far * near ) / ( far - near );
  projectionMatrix[12] = 0;
  projectionMatrix[13] = 0;
  projectionMatrix[14] = -1;
  projectionMatrix[15] = 0; 
  
  // viewing transform matrix
  w[0] = eye[0] - center[0];
  w[1] = eye[1] - center[1];
  w[2] = eye[2] - center[2];

  normalize(w, 3);

  crossproduct(up, w, u);
  
  normalize(u, 3);

  crossproduct(w, u, v);

  rotationMatrix[0] = u[0];
  rotationMatrix[1] = u[1];
  rotationMatrix[2] = u[2];
  rotationMatrix[3] = 0;

  rotationMatrix[4] = v[0];
  rotationMatrix[5] = v[1];
  rotationMatrix[6] = v[2];
  rotationMatrix[7] = 0;

  rotationMatrix[8] = w[0];
  rotationMatrix[9] = w[1];
  rotationMatrix[10] = w[2];
  rotationMatrix[11] = 0;

  rotationMatrix[12] = 0;
  rotationMatrix[13] = 0;
  rotationMatrix[14] = 0;
  rotationMatrix[15] = 1;

  

  identity(4, viewingMatrix);
  translate(viewingMatrix, -eye[0], -eye[1], -eye[2]);
  multiplication(4,4,4, viewingMatrix, rotationMatrix, resultMatrix);
  copymatrix(4, 4, viewingMatrix, resultMatrix);
  


  multiplication(4,4,4, projectionMatrix, viewingMatrix, resultMatrix);
  copymatrix(4,4, viewingMatrix, resultMatrix);
  
  
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

  multiplication(4,4,4, tempMatrix, rotationMatrix, resultMatrix);
  copymatrix(4,4, rotationMatrix, resultMatrix);
  //cout << "model: " << endl; 
  //printmat(4,4,modelMatrix);
}

void JLRotate(double angle, int xAxis, int yAxis, int zAxis) {
  double tempMatrix[16], resultMatrix[16];
  identity(4, tempMatrix);
  
  double newAngle = 3.14159265358979323846 / 180.0 * angle;

  if(xAxis)
    rotate('x', newAngle, tempMatrix);
  if(yAxis)
    rotate('y', newAngle, tempMatrix);
  if(zAxis)
    rotate('z', newAngle, tempMatrix);

  cout << "rotate" << endl;
  printmat(4,4, tempMatrix);

  multiplication(4, 4, 4, modelMatrix, tempMatrix, resultMatrix);
  copymatrix(4, 4, modelMatrix, resultMatrix);

  multiplication(4,4,4, tempMatrix, rotationMatrix, resultMatrix);
  copymatrix(4,4, rotationMatrix, resultMatrix);
}

void JLScale(double xScale, double yScale, double zScale) {
  double tempMatrix[16], resultMatrix[16];
  identity(4, tempMatrix);

  tempMatrix[0] = xScale;
  tempMatrix[5] = yScale;
  tempMatrix[10] = zScale;

  multiplication(4, 4, 4, modelMatrix, tempMatrix, resultMatrix);
  copymatrix(4, 4, modelMatrix, resultMatrix);

  multiplication(4,4,4, tempMatrix, rotationMatrix, resultMatrix);
  copymatrix(4,4, rotationMatrix, resultMatrix);
}

void JLPushMatrix() {
  for(int i= 0; i < 4; i++){
    for (int j = 0; j< 4; j++){
      stack[stackCounter][i*4+j] = modelMatrix[i*4+j];
      rotateMatrixStack[stackCounter][i*4+j] = rotationMatrix[i*4+j];
    }
  }
  
  stackCounter++;
}

void JLPopMatrix() {
  for(int i= 0; i < 4; i++){
    for (int j = 0; j< 4; j++){
      modelMatrix[i*4+j] = stack[stackCounter - 1][i*4+j];
      rotationMatrix[i*4+j] = rotateMatrixStack[stackCounter-1][i*4+j];
    }
  }
  stackCounter--;
}

void JLColor(char c) {
  color = c;
}

void JLBegin(type m) {
  polygonType = m;
}

void JLEnd() {
  
  list <vertex> ::iterator iterator;

  double v1[3],v2[3],v3[3];
  double coefficient[3]; 
  

  if(polygonType == triangle){
    
    int counter = 1;
    for(iterator = globalPoints.begin(); iterator != globalPoints.end(); ++iterator) {
      if(counter == 1){
        v1[0] = iterator->x;
        v1[1] = iterator->y;
        v1[2] = iterator->z;
      }
      else if(counter == 2){
        v2[0] = iterator->x;
        v2[1] = iterator->y;
        v2[2] = iterator->z;
      }
      else{
        v3[0] = iterator->x;
        v3[1] = iterator->y;
        v3[2] = iterator->z;
      }

      counter++;
    }

    double A[] = {v1[0], v1[1], 1, v2[0], v2[1], 1, v3[0], v3[1], 1};
    double z[] = {v1[2], v2[2], v3[2]};
    
    cout << "A" << endl;
    printmat(3,3, A);
    
    cout << "z values: " << endl;
    printmat(3,1, z);
    
    double inv[9], aTran[9], result1[9], result2[9];
    transpose(3,3,A , aTran);
    
    // transpost * A
    multiplication(3,3,3, aTran, A, result1);
    // inverse of (x^t * x)
    inverse(3, result1, result2);
    //
    multiplication(3,3,3, result2, aTran, result1);
    multiplication(3,3,1, result1, z, coefficient);
    
    //multiplication(3,3,1, inv, z, coefficient);
    
    cout << "inv" << endl;
    printmat(3,1, inv);

    //clipping(polygon_tri);   
    lineDrawing(polygon_tri);
    polygonFilling(polygon_tri);
  }
  else {

    int counter = 1;
    for(iterator = globalPoints.begin(); iterator != globalPoints.end(); ++iterator) {
      //cout << iterator->v1.x << " " << iterator->v1.y << " " << iterator->v1.z << endl;
      //cout << iterator->v2.x << " " << iterator->v2.y << " " << iterator->v2.z << endl;

      if(counter == 1){
        v1[0] = iterator->x;
        v1[1] = iterator->y;
        v1[2] = iterator->z;

        
      }
      else if(counter == 2){
        v2[0] = iterator->x;
        v2[1] = iterator->y;
        v2[2] = iterator->z;
      }

      else if(counter == 3){
        v3[0] = iterator->x;
        v3[1] = iterator->y;
        v3[2] = iterator->z;
      }
      counter++;
    }
    
    
    double A[] = {v1[0], v1[1], 1, v2[0], v2[1], 1, v3[0], v3[1], 1};
    double z[] = {v1[2], v2[2], v3[2]};
    
    cout << "A" << endl;
    printmat(3,3, A);
    
    cout << "z values: " << endl;
    printmat(3,1, z);
    
    double inv[9], aTran[9], result1[9], result2[9];
    transpose(3,3,A , aTran);
    
    // transpost * A
    multiplication(3,3,3, aTran, A, result1);
    // inverse of (x^t * x)
    inverse(3, result1, result2);
    //
    multiplication(3,3,3, result2, aTran, result1);
    multiplication(3,3,1, result1, z, coefficient);
    
    //multiplication(3,3,1, inv, z, coefficient);
    
    cout << "inv" << endl;
    printmat(3,1, inv);
    
    //clipping(polygon_quad);
    lineDrawing(polygon_quad);
    polygonFilling(polygon_quad);
  }
  
  for(int i = window_size -1 ; i >= 0; i--){
    for(int j = 0; j < window_size; j++){
      if(tempTable[i][j] == 1){
        
        // find z buffer and compare
        
        // case triangle 
        //cout << "j(x): " << j << "i(y): " << i << endl;
        double z = coefficient[0] * (j - 300) / 300 + coefficient[1] * (i - 300) / 300 + coefficient[2];
        
        // case quad
        
        //cout << (double) z << endl;
        if(zbuffer[i][j] > z){
          //cout << "come" << endl;
          if(color == 'b')
            finalPixel[i][j] = 1;
          else
            finalPixel[i][j] = 2;
          zbuffer[i][j] = z;
        }
        tempTable[i][j] = 0;
      }
    }
  }
  if(polygonType == triangle)
    polygon_tri.clear();
  else
    polygon_quad.clear();

  globalPoints.clear();
}

void JLVertex(double x, double y, double z) {
    

  cout << "modelMatrix" << endl;
  printmat(4,4, modelMatrix);  
  double coord[] = {x, y, z, 1};
  double finalv[4];
  double resultMatrix[16];
  multiplication(4, 4, 4, viewingMatrix, modelMatrix, resultMatrix);
  multiplication(4, 4, 1, resultMatrix, coord, finalv);

  
  // Geometric transform
  double globalCoord[4];
  cout << "printing rotationMatrix" << endl;
  printmat(4,4,rotationMatrix);
  //multiplication(4,4,4, modelMatrix, rotationMatrix, resultMatrix);
  multiplication(4,4,1, rotationMatrix, coord, globalCoord);
  //multiplication(4,4,1, tetete, temp, globalCoord);
  vertex global = {globalCoord[0], globalCoord[1], globalCoord[2]};
  globalPoints.push_back(global);
  
  cout << "globalCoord" << endl;
  printmat(4,1,globalCoord);
  //printmat(4,1,finalv);
  
  
  vertex v;
  v.x = finalv[0];
  v.y = finalv[1]; 
  v.z = finalv[2]; 
  cout << "vertex: " << v.x << " " << v.y << " " << v.z << endl;
    
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
        
        //cout << "edge v1 = { " << previous.x << ", " << previous.y << ", " << previous.z << "}" << endl;
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
        
        //cout << "edge v1 = { " << previous.x << ", " << previous.y << ", " << previous.z << "}" << endl;
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

void printFinal() {
  for(int i = window_size - 1; i >= 0; i--){
    for (int j = 0; j < window_size; j++){
      if(finalPixel[i][j] == 1)
        cout << "@";
      else if(finalPixel[i][j] == 2)
        cout << " ";
      else
        cout << ".";
    }
    cout << endl;
  }

  cout << "done" << endl;
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
  double denominator = 0;

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
  double verticestri[3][6];
  double verticesquad[4][6];
  int counter = 0;

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
    if(polygonType == triangle){
      verticestri[counter][0] = point1x;
      verticestri[counter][1] = point1y;
      verticestri[counter][2] = point1z;
      verticestri[counter][3] = point2x;
      verticestri[counter][4] = point2y;
      verticestri[counter][5] = point2z;
    }
    else {
      verticesquad[counter][0] = point1x;
      verticesquad[counter][1] = point1y;
      verticesquad[counter][2] = point1z;
      verticesquad[counter][3] = point2x;
      verticesquad[counter][4] = point2y;
      verticesquad[counter][5] = point2z;
    }
    counter++;
  }


  counter = 0;
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
      // check through x
      // horizontal check
      if(start != end){
        if( (point1x - point2x) < 0)
          deltaX = 1;
        else
          deltaX = -1;
        //cout << deltaX << endl;
        //cout << "Start: " << start << " End: " << end <<endl;
        while(start != end) {
          //cout << "start: " << deltaX << " end: " << end << endl;
          int yPixel = slope * start + yIntercept;
          
          tempTable[yPixel + 300][start + 300] = 1;
          
          //cout << "x: " << start + 300 << " y: " << yPixel << endl;
          start += deltaX;
        }
        
        int deltaY;
        start = round(point1y);
        end = round(point2y);
        
        if(start != end) {
          if( (start - end) < 0)
            deltaY = 1;
          else
            deltaY = -1;
          //cout << "start: " << start << " end: " << end << endl;
          //cout << "deltaY: " << deltaY << " yinter: " << yIntercept << " slope: " << slope << endl;
          while(start != end) {
            int xPixel = (start - yIntercept) / slope;
            //cout << "x: " << xPixel << endl;
            
            tempTable[start + 300][xPixel + 300] = 1;
            start += deltaY; 
          }
        }  
      }
      
      
      // vertical check 
      else {
      //cout << " yinter: " << yIntercept << " slope: " << slope << endl;
        start = round(point1y);
        end = round(point2y);
        
        if( (point1y - point2y) < 0)
          deltaX = 1;
        else
          deltaX = -1;
     
        while(start != end) {
          //cout << "start: " << deltaX << " end: " << end << endl;
          
          tempTable[start + 300][(int) point1x + 300] = 1;
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
  
  //cout << minY << "               " << maxY << endl;
  
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
        
        //cout << "new: " << newPoint.x << " " << newPoint.y << endl;
      }
    }
    
    //cout << "num point: " << numPoints << endl;
    /*if(numPoints == 1){
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
    */
    
    edge e = { points.front(), points.back() };
    points.clear();
    
    for(int i = e.v1.x; i <= e.v2.x; i++){
      tempTable[y][i] = 1;
    }
    numPoints = 0;
  }
}

void rotate(double * matrix, double angle, double x, double y, double z) {
 
  double theta = 3.14159265358979323846 / 180.0 * angle;
  
  matrix[0] = x * x * (1 - cos(theta)) + cos(theta);
  matrix[1] = x * y * (1 - cos(theta)) - z * sin(theta);
  matrix[2] = x * z * (1 - cos(theta)) + y * sin(theta);
  matrix[3] = 0; 
  matrix[4] = y * x * (1 - cos(theta)) + z * sin(theta); 
  matrix[5] = y * y * (1 - cos(theta)) + cos(theta);
  matrix[6] = y * z * (1 - cos(theta)) - x * sin(theta);
  matrix[7] = 0;
  matrix[8] = x * z * (1 - cos(theta)) - y * sin(theta);
  matrix[9] = y * z * (1 - cos(theta)) + x * sin(theta);
  matrix[10] = z * z * (1 -cos(theta)) + cos(theta);
  matrix[11] = 0;
  matrix[12] = 0;
  matrix[13] = 0;
  matrix[14] = 0;
  matrix[15] = 1;
  
  
}

