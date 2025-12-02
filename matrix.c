#include "matrix.h"
#include <stdio.h>


void setValues(double anspp[N][N], double *inp, int r, int c) {
// コメントがないと自動整形されてくっついてしまう。
int i, j;
for (i = 0; i < r; i++) {
for (j = 0; j < c; j++) {
anspp[i][j] = *inp++;
}
}
}
void addMatrix(double anspp[N][N], double in1pp[N][N], double in2pp[N][N],int r, int c){
    int i, j;
for (i = 0; i < r; i++) {
for (j = 0; j < c; j++) {
anspp[i][j] =  in1pp[i][j]+in2pp[i][j];
}
}
}
void mulMatrix(double anspp[N][N], double in1pp[N][N], int r1, int c1, double in2pp[N][N], int r2, int c2) {
    int i, j, k;

 
    if (c1 != r2) {
        printf("error\n");
        return;
    }

    for (i = 0; i < r1; i++) {           
        for (j = 0; j < c2; j++) {       
            
            anspp[i][j] = 0.0;          
            
            for (k = 0; k < c1; k++) {  
                anspp[i][j] += in1pp[i][k] * in2pp[k][j];
            }
        }
    }
}
void rowCmulMatrix(double matpp[N][N], int r, int c, int n, double k) {
    int j;
    
    for (j = 0; j < c; j++) {
        matpp[n-1][j] *= k;  
    }
}
void rowConvertMatrix(double matpp[N][N], int r, int c, int n1, int n2){
    double matsub[c];
    int i ;
    for(i=0;i<c;i++){
        matsub[i] = matpp[n1-1][i];
    }
    for(i=0;i<c;i++){
        matpp[n1-1][i] =  matpp[n2-1][i];
        matpp[n2-1][i] = matsub[i];
    }

}
void colConvertMatrix(double matpp[N][N], int r, int c, int n1, int n2){
    double matsub[c];
    int i ;
    for(i=0;i<r;i++){
        matsub[i] = matpp[i][n1-1];
    }
    for(i=0;i<r;i++){
        matpp[i][n1-1] =  matpp[i][n2-1];
        matpp[i][n2-1] = matsub[i];
    }

}
void rowCmulAddMatrix(double matpp[N][N], int r, int c,int n1, double k, int n2){
 double matsub[c];
    int i ;
    for(i=0;i<c;i++){
        matsub[i] = matpp[n1-1][i]*k;
    }
    for(i=0;i<c;i++){
        
        matpp[n2-1][i] += matsub[i];
    }
}


int inverseMatrix(double anspp[N][N], double inpp[N][N], int n) {
    int i, j, k, n2;
    n2 = n * 2;


    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            anspp[i][j] = inpp[i][j];
            anspp[i][j + n] = (i == j) ? 1.0 : 0.0;
        }
    }


    for (j = 0; j < n - 1; j++) {
        int p = j; 
        double vmax = fabs(anspp[j][j]);
        
      
        for (i = j + 1; i < n; i++) {
            double v = fabs(anspp[i][j]);
            if (v > vmax) {
                p = i;
                vmax = v;
            }
        }

    
        if (vmax < 1.0e-12) {
            fprintf(stderr, "too small pivot! \n");
            return 1;
        }

     
        if (p != j) {
            for (k = 0; k < n2; k++) {
                double temp = anspp[j][k];
                anspp[j][k] = anspp[p][k];
                anspp[p][k] = temp;
            }
        }

  
        for (i = j + 1; i < n; i++) {
         
            double w = -anspp[i][j] / anspp[j][j];
            
            
            for (k = j; k < n2; k++) {
                anspp[i][k] += w * anspp[j][k];
            }
        }
    }

    
    for (j = n - 1; j >= 0; j--) {
        
        if (fabs(anspp[j][j]) < 1.0e-12) {
             fprintf(stderr, "singular matrix!\n");
             return 1;
        }

        double div = 1.0 / anspp[j][j];
        for (k = 0; k < n2; k++) {
            anspp[j][k] *= div;
        }

        
        for (i = j - 1; i >= 0; i--) {
            double w = -anspp[i][j]; 
            

            for (k = 0; k < n2; k++) {
                anspp[i][k] += w * anspp[j][k];
            }
        }
    }
    for (j = 0; j < n; j++) {
     
        for (i = 0; i < n; i++) {
             double temp = anspp[i][j];
             anspp[i][j] = anspp[i][j + n];
             anspp[i][j + n] = temp;
        }
    }

    return 0;
}