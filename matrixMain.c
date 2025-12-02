#include <stdio.h>
#include <math.h>

#define N 100 // 行列の最大サイズ

// プロトタイプ宣言 (matrix.c にある関数)
void setValues(double anspp[N][N], double *inp, int r, int c);
int solveEquations(double xpp[N][N], double app[N][N], double bpp[N][N], int n);

// 結果を表示するための補助関数
void printCurrent(char *label, double v_start, double v_end, double r) {
    double current = fabs(v_start - v_end) / r;
    printf("%s: %.6f A\n", label, current);
}

int main() {
    double A[N][N], b[N][N], x[N][N];
    
    // ==========================================
    // 問題 i: 抵抗を取り外した回路 (節点5, 6の電圧を求める)
    // ==========================================
    printf("--- Problem i ---\n");

    // 1. まずは回路のパラメータ（抵抗値・電圧）を変数にするよ！
    double R56 = 1.0;
    double R67 = 2.0;
    // double R78 = 3.0; // 今回の計算式には直接出てこないけど定義しておくね
    double R58 = 4.0;
    double E = 1.0;     // 電源電圧 (V7)

    // 2. キルヒホッフの法則を行列の要素としてプログラムで計算するよ
    // 未知数: V5, V6
    
    // 行列 A の係数計算 (コンダクタンス 1/R の和になるよ)
    // 式1 (Node 5): V5 * (1/R56 + 1/R58) - V6 * (1/R56) = V8/R58 (V8=0なので右辺0)
    // 式2 (Node 6): -V5 * (1/R56) + V6 * (1/R56 + 1/R67) = V7/R67 (V7=E)
    
    double vals_A1[] = {
        (1.0/R56 + 1.0/R58),   -(1.0/R56),           // 1行目 (Node 5の式)
       -(1.0/R56),             (1.0/R56 + 1.0/R67)   // 2行目 (Node 6の式)
    };
    
    // ベクトル b の計算 (右辺)
    double vals_b1[] = {
        0.0,                   // Node 5の右辺 (GNDにつながる項は0)
        E / R67                // Node 6の右辺 (電源Eにつながる項)
    };

    // 値をセット
    setValues(A, vals_A1, 2, 2);
    setValues(b, vals_b1, 2, 1);

    // 解く
    if (solveEquations(x, A, b, 2) == 0) {
        double v5 = x[0][0];
        double v6 = x[1][0];
        printCurrent("Current between Node 5 and 6", v5, v6, R56);
    } else {
        printf("Failed to solve equations for Problem i.\n");
    }

    printf("\n");

    // ==========================================
    // 問題 ii: 立方体回路 (節点1～6の電圧を求める)
    // ==========================================
    printf("--- Problem ii ---\n");

    // 1. パラメータ定義
    double R = 1.0; // 全ての抵抗は 1オーム
    double E_cube = 1.0; // 電源電圧

    // 2. 行列の要素を計算式で定義
    // 各節点は3つの抵抗(R)で他とつながっているから、対角成分は常に 3/R
    // 隣接する節点の成分は -1/R
    
    double G_self = 3.0 / R; // 自己コンダクタンス (対角成分)
    double G_mut  = -1.0 / R; // 相互コンダクタンス (非対角成分)
    
    double vals_A2[] = {
        // V1,      V2,      V3,      V4,      V5,      V6
        G_self,  G_mut,    0.0,   G_mut,   G_mut,    0.0,  // Node 1 (接続: 2,4,5)
         G_mut, G_self,  G_mut,     0.0,     0.0,  G_mut,  // Node 2 (接続: 1,3,6)
           0.0,  G_mut, G_self,   G_mut,     0.0,    0.0,  // Node 3 (接続: 2,4,7)
         G_mut,    0.0,  G_mut,  G_self,     0.0,    0.0,  // Node 4 (接続: 1,3,8)
         G_mut,    0.0,    0.0,     0.0,  G_self,  G_mut,  // Node 5 (接続: 1,6,8)
           0.0,  G_mut,    0.0,     0.0,   G_mut, G_self   // Node 6 (接続: 2,5,7)
    };

    // ベクトル b (右辺) の計算
    // 電源(V7=E)につながっている節点には E/R の項が右辺に来る
    double val_E = E_cube / R;

    double vals_b2[] = {
        0.0,    // Node 1
        0.0,    // Node 2
        val_E,  // Node 3 (V7と接続) -> 係数は -(-1/R)*E = E/R
        0.0,    // Node 4
        0.0,    // Node 5
        val_E   // Node 6 (V7と接続)
    };

    // 値をセット
    setValues(A, vals_A2, 6, 6);
    setValues(b, vals_b2, 6, 1);

    // 解く
    if (solveEquations(x, A, b, 6) == 0) {
        double v1 = x[0][0];
        double v2 = x[1][0];
        printCurrent("Current between Node 1 and 2", v1, v2, R);
    } else {
        printf("Failed to solve equations for Problem ii.\n");
    }

    return 0;
}