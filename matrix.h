#include <stdio.h>
#include <math.h>

#define MAXSIZE  10
#define ERROR   -1

int inverse(int size, double *imat, double *omat);
void transpose(int row, int col, double *imat, double *omat);
void addition(int row, int col, double *imat1, double *imat2, double *omat);
void substraction(int row, int col, double *imat1, double *imat2, double *omat);
void multiplication(int row, int col1, int col2, double *imat1, double *imat2, double *omat); 
void scale_multiplication(int row, int column, double value, double *imat, double *omat);
void scalar_mult_vec(int size, double value, double *ivec, double *ovec);
double innerproduct(int size, double *v1, double *v2);
void crossproduct(double *v1, double *v2, double *vout);
double determinant(double *mat);
void copyvector(int size, double *vec1, double *vec2);
void copymatrix(int row, int column, double *mat1, double *mat2);
void identity(int size, double *mat);
void rotate(char direction, double angle, double *mat);
void rotation(double rx, double ry, double rz, double *imat);
double vectorlength(int size, double *vec);
double pdist(int size, double *pt1, double *pt2);
void unitvector(int size, double *ivec, double *ovec);
void printmat(int row, int col, double *mat);