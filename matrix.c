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

    // 初期化: 左側に元の行列、右側に単位行列をセット
    // ansppのサイズは呼び出し元で [N][N*2] として確保されている必要があります
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            anspp[i][j] = inpp[i][j];
            anspp[i][j + n] = (i == j) ? 1.0 : 0.0;
        }
    }

    // 前進消去（ピボット選択）
    for (j = 0; j < n - 1; j++) {
        int p = j; // ピボットの初期値は j
        double vmax = fabs(anspp[j][j]);
        
        // ピボット検索
        for (i = j + 1; i < n; i++) {
            double v = fabs(anspp[i][j]);
            if (v > vmax) {
                p = i;
                vmax = v;
            }
        }

        // エラー処理
        if (vmax < 1.0e-12) {
            fprintf(stderr, "too small pivot! \n");
            return 1;
        }

        // 行の入れ替え (p行とj行を交換)
        if (p != j) {
            for (k = 0; k < n2; k++) {
                double temp = anspp[j][k];
                anspp[j][k] = anspp[p][k];
                anspp[p][k] = temp;
            }
        }

        // 前進消去
        for (i = j + 1; i < n; i++) {
            // anspp[i][j] を anspp[j][j] を使って消去するための係数 w
            double w = -anspp[i][j] / anspp[j][j];
            
            // i 行を j 行で再計算 (i行 = i行 + w * j行)
            for (k = j; k < n2; k++) {
                anspp[i][k] += w * anspp[j][k];
            }
        }
    }

    // 後退代入（対角成分を1にし、それより上の成分を0にする）
    for (j = n - 1; j >= 0; j--) {
        // anspp[j][j] (対角成分) が 0 に近い場合のチェック（念のため）
        if (fabs(anspp[j][j]) < 1.0e-12) {
             fprintf(stderr, "singular matrix!\n");
             return 1;
        }

        // 正規化: j行全体を anspp[j][j] で割って対角成分を1にする
        double div = 1.0 / anspp[j][j];
        for (k = 0; k < n2; k++) {
            anspp[j][k] *= div;
        }

        // j行より上の行 (i行) から j列目の成分を消去
        for (i = j - 1; i >= 0; i--) {
            double w = -anspp[i][j]; // 既にanspp[j][j]は1なので、消去係数は -anspp[i][j]
            
            // i 行を j 行で再計算
            for (k = 0; k < n2; k++) {
                anspp[i][k] += w * anspp[j][k];
            }
        }
    }

    // 仕上げ: 右半分(逆行列)を左半分に移動（列の交換またはコピー）
    for (j = 0; j < n; j++) {
        // j列目と j+n列目を交換（あるいは単にコピーでも可ですが、元のコメントに従い交換します）
        for (i = 0; i < n; i++) {
             double temp = anspp[i][j];
             anspp[i][j] = anspp[i][j + n];
             anspp[i][j + n] = temp;
        }
    }


    return 0;
}
int solveEquations(double xpp[N][N], double app[N][N], double bpp[N][N], int n) {
    double invA[N][N]; // 逆行列を一時的に保存する場所
    int result;
    int i, j;
    // 1. まず A の逆行列を計算してみる
    // (前の会話のテストコードに基づき、成功=0, 失敗=1 と仮定しているよ！)
    result = inverseMatrix(invA, app, n);

    // もし逆行列が計算できなかったら（戻り値が 1 なら）、
    // 連立方程式も解けないので、ここで諦めて 1 を返す！
    if (result != 0) {
        return 1;
    }
     for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            xpp[i][j] = 0.0;
        }
    }
    // 2. 逆行列ができたら、掛け算をするだけ！
    // x = invA * b
    // 行列 invA (n x n) と、ベクトル b (n x 1) を掛けるよ
    mulMatrix(xpp, invA, n, n, bpp, n, 1);

    // 計算できたので、成功の 0 を返す！
    return 0;
}