#include <stdio.h>
#include "matrix.h" // testCommon.h にも書かれているので書かなくても動く
#include "testCommon.h"

void testSetValues() {
    double ans[N][N];
    double correct[] = { 3.1, 4.1, 5.9, 2.6, 5.3, 5.8 };
    testStart("testSetValues");
    setValues(ans, correct, 2, 1); // 列ベクトルの設定
    assertEqualsMatrixAndValues(ans, correct, 2, 1);
    setValues(ans, correct, 1, 3); // 行ベクトルの設定
    assertEqualsMatrixAndValues(ans, correct, 1, 3);
    setValues(ans, correct, 2, 3); // 行列の設定
    assertEqualsMatrixAndValues(ans, correct, 2, 3);
}

void testAddMatrix() {
double in1[N][N], in2[N][N], ans[N][N];
double in1Values[] = { 3.1, 4.1, 5.9, 2.6, 5.3, 5.8 };
double in2Values[] = { 9.7, 9.3, 2.3, 8.4, 6.2, 6.4 };
testStart("addMatrix");
setValues(in1, in1Values, 2, 3);
setValues(in2, in2Values, 2, 3);
addMatrix(ans, in1, in2, 2, 3);
double correct1[] = { 3.1+9.7, 4.1+9.3, 5.9+2.3, 2.6+8.4, 5.3+6.2, 5.8+6.4 };
assertEqualsMatrixAndValues(ans, correct1, 2, 3);
addMatrix(ans, in1, in2, 2, 1);
double correct2[] = { 3.1+9.7, 2.6+8.4 };
assertEqualsMatrixAndValues(ans, correct2, 2, 1);
}
void testMulMatrix() {
double in1[N][N], in2[N][N], ans[N][N];
double in1Values[] = { 3.1, 4.1, 5.9, 2.6, 5.3, 5.8 };
double in2Values[] = { 7.9, 3.2, 3.8, 4.6, 2.6, 4.3 };
testStart("mulMatrix");
setValues(in1, in1Values, 2, 3);
setValues(in2, in2Values, 3, 2);
mulMatrix(ans, in1, 2, 3, in2, 3, 2);
double correct1[] = {
0.0 + 3.1*7.9 + 4.1*3.8 + 5.9*2.6, 0.0 + 3.1*3.2 + 4.1*4.6 + 5.9*4.3,
0.0 + 2.6*7.9 + 5.3*3.8 + 5.8*2.6, 0.0 + 2.6*3.2 + 5.3*4.6 + 5.8*4.3 };
assertEqualsMatrixAndValues(ans, correct1, 2, 2);
mulMatrix(ans, in2, 3, 2, in1, 2, 3);
double correct2[] = {
0.0 + 7.9*3.1 + 3.2*2.6, 0.0 + 7.9*4.1 + 3.2*5.3, 0.0 + 7.9*5.9 + 3.2*5.8,
0.0 + 3.8*3.1 + 4.6*2.6, 0.0 + 3.8*4.1 + 4.6*5.3, 0.0 + 3.8*5.9 + 4.6*5.8,
0.0 + 2.6*3.1 + 4.3*2.6, 0.0 + 2.6*4.1 + 4.3*5.3, 0.0 + 2.6*5.9 + 4.3*5.8 };
assertEqualsMatrixAndValues(ans, correct2, 3, 3);
}
void testCmul() {
double in1[N][N], in2[N][N], ans[N][N];
double in1Values[] = { 3.1, 4.1, 5.9, 2.6, 5.3, 5.8 };
double in2Values[] = { 7.9, 3.2, 3.8, 4.6, 2.6, 4.3 };
double k = 2;
int n = 2;
testStart("testCmul");
setValues(in1, in1Values, 2, 3);
setValues(in2, in2Values, 3, 2);
rowCmulMatrix(in1, 2, 3, n, k);
rowCmulMatrix(in2, 3, 2, n, k);
double correct1[] = { 3.1, 4.1, 5.9, 2.6*2, 5.3*2, 5.8*2 };
assertEqualsMatrixAndValues(in1, correct1, 2, 3);

double correct2[] = { 7.9, 3.2, 3.8*2, 4.6*2, 2.6, 4.3 };
assertEqualsMatrixAndValues(in2, correct2, 3, 2);
}
void testrCon() {
double in1[N][N], in2[N][N], ans[N][N];
double in1Values[] = { 3.1, 4.1, 5.9, 2.6, 5.3, 5.8 };
double in2Values[] = { 7.9, 3.2, 3.8, 4.6, 2.6, 4.3 };

int n1 = 1;
int n2 = 2;
testStart("testCon");
setValues(in1, in1Values, 2, 3);
setValues(in2, in2Values, 3, 2);
rowConvertMatrix(in1, 2, 3, n1, n2);
rowConvertMatrix(in2, 3, 2, n1, n2);
double correct1[] = { 2.6, 5.3, 5.8, 3.1, 4.1, 5.9 };
assertEqualsMatrixAndValues(in1, correct1, 2, 3);

double correct2[] = { 3.8, 4.6, 7.9, 3.2,  2.6, 4.3 };
assertEqualsMatrixAndValues(in2, correct2, 3, 2);
}
void testcCon() {
double in1[N][N], in2[N][N], ans[N][N];
double in1Values[] = { 3.1, 4.1, 5.9, 2.6, 5.3, 5.8 };
double in2Values[] = { 7.9, 3.2, 3.8, 4.6, 2.6, 4.3 };

int n1 = 1;
int n2 = 2;
testStart("testrCon");
setValues(in1, in1Values, 2, 3);
setValues(in2, in2Values, 3, 2);
colConvertMatrix(in1, 2, 3, n1, n2);
colConvertMatrix(in2, 3, 2, n1, n2);
double correct1[] = { 4.1, 3.1, 5.9, 
                    5.3,2.6,  5.8 };
assertEqualsMatrixAndValues(in1, correct1, 2, 3);

double correct2[] = {  3.2,7.9, 
                      4.6, 3.8,
                     4.3 ,2.6};
assertEqualsMatrixAndValues(in2, correct2, 3, 2);
}

void testrCmuladd() {
double in1[N][N], in2[N][N];
double in1Values[] = { 3.1, 4.1, 5.9, 2.6, 5.3, 5.8 };
double in2Values[] = { 7.9, 3.2, 3.8, 4.6, 2.6, 4.3 };
double k = 2;
int n1 = 1;
int n2 = 2;
testStart("testrCmuladd");
setValues(in1, in1Values, 2, 3);
setValues(in2, in2Values, 3, 2);
rowCmulAddMatrix(in1, 2, 3, n1,k, n2);
rowCmulAddMatrix(in2, 3, 2, n1,k, n2);
double correct1[] = { 3.1, 4.1, 5.9, 2.6+3.1*2, 5.3+4.1*2, 5.8+5.9*2 };
assertEqualsMatrixAndValues(in1, correct1, 2, 3);

double correct2[] = { 7.9, 3.2, 3.8+7.9*2, 4.6+3.2*2, 2.6, 4.3 };
assertEqualsMatrixAndValues(in2, correct2, 3, 2);
}

void testInverseMatrix() {
    double in1[N][N], in2[N][N], ans[N][N];
    
    // in1: 逆行列がないパターン (Det = 0)
    double in1Values[] = { 1, 1, 1, 1 }; 
    
    // in2: 逆行列があるパターン (Det = 3)
    // 値を {2, 1, 1, 2} に変更したよ。これなら期待値と合う！
    double in2Values[] = { 2, 1, 1, 2 }; 

    // 重要！ .0 をつけて double として計算させる
    double correct1[] = { 2.0/3.0, -1.0/3.0, -1.0/3.0, 2.0/3.0 };
    
    int k = 2; // 行列のサイズ

    // 戻り値の想定 (1:成功, 0:失敗 と仮定)
    int success = 0;
    int failure = 1;

    testStart("testInverseMatrix");
    
    setValues(in1, in1Values, 2, 2);
    setValues(in2, in2Values, 2, 2);

    // in1 は逆行列がないので、失敗(0)が返るのが正しい
    assertEqualsInt(inverseMatrix(ans, in1, k), failure);

    // in2 は逆行列があるので、成功(1)して、結果をチェックする
    assertEqualsInt(inverseMatrix(ans, in2, k), success);
    
    // ここは ans をチェック！サイズは 2, 2 で！
    assertEqualsMatrixAndValues(ans, correct1, 2, 2);
}
void testSolveEquations() {
    double xpp[N][N], app[N][N], bpp[N][N];
    
    // --- ケース1: 解ける場合 (Success) ---
    // A = {{1, 2}, {2, 1}}
    double aValues[] = { 1, 2, 2, 1 };
    
    // b = {{3}, {3}} 
    // ※引数が[N][N]なので、1列目に値が入るように {3, 0, 3, 0} と設定するよ
    // (setValuesが左上から順に埋めると仮定)
    double bValues[] = { 3, 0, 3, 0 };
    
    // 期待する解 x = {{1}, {1}} (1列目が1, 1になればOK)
    double correctX[] = { 1, 0, 1, 0 };

    // --- ケース2: 解けない場合 (Failure) ---
    // A = {{1, 1}, {1, 1}} (行列式が0)
    double aSingular[] = { 1, 1, 1, 1 };

    int n = 2;
    int success = 0; // 画像の仕様通り、成功は 0
    int failure = 1; // 失敗は 1

    testStart("testSolveEquations");

    // 1. 解けるパターンのテスト
    setValues(app, aValues, 2, 2);
    setValues(bpp, bValues, 2, 2);
    
    // 戻り値が 0 (成功) であることを確認
    assertEqualsInt(solveEquations(xpp, app, bpp, n), success);
    
    // 計算された x が正しいか確認 (サイズは2x2で渡すけど、実質見るのは1列目)
    assertEqualsMatrixAndValues(xpp, correctX, 2, 2);

    // 2. 解けないパターンのテスト
    setValues(app, aSingular, 2, 2);
    setValues(bpp, bValues, 2, 2); // bは何でもいい

    // 戻り値が 1 (失敗) であることを確認
    assertEqualsInt(solveEquations(xpp, app, bpp, n), failure);
}


int main() {
    testSetValues(); // 関数の呼び出しを追加
    testAddMatrix();
    testMulMatrix();
    testCmul();
    testrCon();
    testcCon();
    testrCmuladd();
    testInverseMatrix();
    testSolveEquations();
    testErrorCheck(); // この行は絶対に消さないこと
   
    return 0;
}