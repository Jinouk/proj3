#include "matrix.h"

void substract(double, int, double*, double*);
void change(int, double*, double*);

/*
**  omat = imat^-1, return ERROR and print out a message if signular
*/
int inverse(int size, double *imat, double *omat) {
double mat[2*MAXSIZE*MAXSIZE];
int i, j, k;
double pivot;

  for (i = 0; i < size; i++)
     for (j = 0; j < size; j++) {
        mat[2*i*size+j] = imat[i*size+j];
        mat[(2*i+1)*size+j] = ((i == j) ? 1 : 0);
     }
  for (i = 0; i < size; i++) {
     if (mat[2*i*size+i] != 0) {
        for (j = 0; j < size; j++) {
     if (j != i) {
        pivot = mat[2*j*size+i] / mat[2*i*size+i];
        if (pivot != 0)
           substract(pivot, size, &mat[2*i*size], &mat[2*j*size]);
     }
        }
        pivot = mat[2*i*size+i];
        for (k = 0; k < 2*size; k++)
     mat[2*i*size+k] /= pivot;
     } else {
        for (k = i+1; k < size; k++) {
     if (mat[2*k*size+i] != 0) {
        change(size, &mat[2*i*size], &mat[2*k*size]);
        i--;
        break;
     }
        } 
        if (k == size) {
     fprintf(stderr, "singular matrix! can't find inverse\n");
     return(ERROR);
        }
     }
  }
  for (i = 0; i< size; i++)
     for (j = 0; j < size; j++)
        omat[i*size+j] = mat[(2*i+1)*size+j];
  return 0;
}


/*
** omat_(col,row) = imat_(row,col)^T
*/
void transpose(int row, int col, double *imat, double *omat) {
int i, j;
double mat[2*MAXSIZE*MAXSIZE];

  for (i = 0; i < col; i++)
     for (j = 0; j < row; j++)
        mat[i*row+j] = imat[j*col+i];
  for (i = 0; i < row; i++)
     for (j = 0; j < col; j++)
        omat[i*col+j] = mat[i*col+j];
}

  
/*
** omat = imat1 + imat2
*/
void addition(int row, int col, double *imat1, double *imat2, double *omat) {
int i, j;

  for (i = 0; i < row; i++)
     for (j = 0; j < col; j++) {
        omat[i*col+j] = *imat1 + *imat2;
        imat1++; imat2++;
     }
}


/*
** omat = imat1 - imat2
*/
void substraction(int row, int col, double *imat1, double *imat2, double *omat)
{
int i, j;

  for (i = 0; i < row; i++)
     for (j = 0; j < col; j++) {
        omat[i*col+j] = *imat1 - *imat2;
        imat1++; imat2++;
     }
}


/*
** omat = imat1 * imat2
*/
void multiplication(int row, int col1, int col2, 
double *imat1, double *imat2, double *omat) {
int i, j, k;
double mat[2*MAXSIZE*MAXSIZE];

  for (i = 0; i < row; i++)
     for ( j = 0; j < col2; j++) {
        mat[i*col2+j] = 0;
        for (k = 0; k < col1; k++)
     mat[i*col2+j] += imat1[i*col1+k]*imat2[k*col2+j];
     }
  for (i = 0; i < row; i++)
     for ( j = 0; j < col2; j++)
        omat[i*col2+j] = mat[i*col2+j];
}


/*
** omat = value * imat (value is a scalar)
*/
void scale_multiplication(int row, int column, double value, 
double *imat, double *omat) {
int i, j;

  for (i = 0; i < row; i++)
     for (j = 0; j < column; j++)
        omat[i*column+j] = value*imat[i*column+j];
}

/*
** ovec = value * ivec (value is a scalar)
*/
void scalar_mult_vec(int size, double value, double *ivec, double *ovec) {
int i;

  for (i = 0; i < size; i ++)
     ovec[i] = value*ivec[i];
}
  
/*
** returns the innerproduct of v1 and v2
*/
double innerproduct(int size, double *v1, double *v2) {
double prod = 0;
int i;

  for (i = 0; i < size; i ++)
     prod += v1[i]*v2[i];
  return(prod);
}


/*
** vout = v1 x v2 (NOTE: v1 and v2 are 3 by 3
*/
void crossproduct(double *v1, double *v2, double *vout) {
double v[3];

  v[0] = v1[1]*v2[2] - v1[2]*v2[1];
  v[1] = v1[2]*v2[0] - v1[0]*v2[2];
  v[2] = v1[0]*v2[1] - v1[1]*v2[0];
  vout[0] = v[0];
  vout[1] = v[1];
  vout[2] = v[2];
}


/*
** retruns |mat| (NOTE: mat is 3 by 3
*/
double determinant(double *mat) {
double scale = 0;

  scale = mat[0]*mat[4]*mat[8] + mat[3]*mat[7]*mat[2] +
    mat[6]*mat[1]*mat[5] - mat[2]*mat[4]*mat[6] -
    mat[0]*mat[5]*mat[7] - mat[1]*mat[3]*mat[8];
  return(scale);
}


/*
** vec2 = vec1
*/
void copyvector(int size, double *vec1, double *vec2) {
int i;

  for (i = 0; i < size; i++)
     vec1[i] = vec2[i];
}


/*
** mat2 = mat1
*/
void copymatrix(int row, int column, double *mat1, double *mat2) {
int i, j;

  for (i = 0; i < row; i++)
     for (j = 0; j < column; j++)
        *mat1++ = *mat2++;
}


/*
** mat = I
*/
void identity(int size, double *mat) {
int i, j;

  for (i = 0; i < size; i++)
     for (j = 0; j < size; j++)
        mat[i*size+j] = (i == j) ? 1 : 0;
}


/*
** make a 4x4 rotational matrix depends on direction ('x', 'y', or 'z')
** and angle (in radian)
*/
void rotate(char direction, double angle, double *mat) {
#define CUTOFF 1e-10
double cosa, sina;
  
  cosa = cos(angle);
  sina = sin(angle);
  if (fabs(cosa) < CUTOFF) cosa = 0;
  if (fabs(sina) < CUTOFF) sina = 0;
  switch (direction) {
     case 'x': mat[5] = cosa;
         mat[6] = sina;
         mat[9] = -mat[6];
         mat[10] = mat[5];
         break;
     case 'y': mat[0] = cosa;
         mat[2] = -sina;
         mat[8] = -mat[2];
         mat[10] = mat[0];
         break;
     case 'z': mat[0] = cosa;
         mat[1] = sina;
         mat[4] = -mat[1];
         mat[5] = mat[0];
         break;
     default: break;
  }
}


/*
** make 4x4 rotational matrix around rx, ry, rz
*/
void rotation(double rx, double ry, double rz, double *imat) {
#define radian(x) (double)(3.14159265358979323846/180.0*x)
double mat[16];

  rx = radian(rx);
  ry = radian(ry);
  rz = radian(rz);
  identity(4, mat);
  if (rx != 0) rotate('x', rx, imat);
  if (ry != 0) rotate('y', ry, mat);
  multiplication(4, 4, 4, imat, mat, imat);
  identity(4, mat);
  if (rz != 0) rotate('z', rz, mat);
  multiplication(4, 4, 4, imat, mat, imat);
}

  
/*
** returns |vec|
*/
#define   sqr(x)  ((x)*(x))
double vectorlength(int size, double *vec) {
double length = 0;
int i;
  for (i =0; i < size; i++) length += sqr(vec[i]);
  length = sqrt(length);
  return(length);
}


/*
** returns distance between pt1 and pt2
*/
double pdist(int size, double *pt1, double *pt2) {
int i;
double length = 0;

  for (i = 0; i < size; i++)
     length += sqr(pt1[i] - pt2[i]);
  return(sqrt(length));
}


/*
** ovec = ivec/|ivec|
*/
void unitvector(int size, double *ivec, double *ovec) {
double length = 0;
int i;

        copyvector(size,ovec,ivec);
  for (i =0; i < size; i++) length += sqr(ivec[i]);
  length = sqrt(length);
  for (i = 0; i < size; i++)
     ovec[i] /= length;
}


/*
** print a matrix
*/
void printmat(int row, int col, double *mat) {
int i, j;

  for (i = 0; i < row; i++) {
     for (j = 0; j < col; j++)
        printf("%f ", mat[i*col+j]);
     printf("\n");
  }
  printf("----------\n");
}

  
/*
** utilities, called by inverse
*/
void substract(double pivot, int size, double *row1, double *row2) {
int i;
  for (i = 0; i < 2*size; i++) {
     *row2 -= *row1 * pivot;
     row1++; row2++;
  }
}


void change(int size, double *row1, double *row2) {
int i;
double temp;
  for (i = 0; i < 2*size; i++) {
     temp = *row1;
     *row1 = *row2;
     *row2 = temp;
     row1++; row2++;
  }
}