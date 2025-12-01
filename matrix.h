#ifndef __MATRIX_H
#define __MATRIX_H
       
#define N 100

#endif 

void setValues(double anspp[N][N], double *inp, int r, int c);
void addMatrix(double anspp[N][N], double in1pp[N][N], double in2pp[N][N],int r, int c);
void mulMatrix(double anspp[N][N], double in1pp[N][N], int r1, int c1,double in2pp[N][N], int r2, int c2);
void rowCmulMatrix(double matpp[N][N], int r, int c, int n, double k);
void rowConvertMatrix(double matpp[N][N], int r, int c, int n1, int n2);
void colConvertMatrix(double matpp[N][N], int r, int c, int n1, int n2);
void rowCmulAddMatrix(double matpp[N][N], int r, int c,int n1, double k, int n2);

int inverseMatrix(double anspp[N][N], double inpp[N][N], int n);