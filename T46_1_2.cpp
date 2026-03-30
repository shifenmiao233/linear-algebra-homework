#include <iostream>
using namespace std;

int main() {
    double t[6] = {0, 2, 4, 6, 8, 10};
    double F[6] = {0, 2.90, 14.8, 39.6, 74.3, 119};

    // 如果要进行三次多项式拟合的话，那么列出的方程就是超定方程，且不相容，所以选择通过超定方程的最小二乘法来进行拟合
    //计算正则方程 A^T A 和 A^T F
    double A[6][4] = {0};
    for (int i = 0; i < 6; i++) {
        A[i][0] = 1;
        A[i][1] = t[i];
        A[i][2] = t[i] * t[i];
        A[i][3] = t[i] * t[i] * t[i];
    }

    // 计算 A^T * A 和 A^T * F
    double AtA[4][4] = {0}, AtF[4] = {0};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 6; k++)
                AtA[i][j] += A[k][i] * A[k][j];

        for (int k = 0; k < 6; k++)
            AtF[i] += A[k][i] * F[k];
    }

    // 构造增广矩阵，进行高斯消元
    double aug[4][5];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) aug[i][j] = AtA[i][j];
        aug[i][4] = AtF[i];
    }

    // 高斯消元
    for (int col = 0; col < 4; col++) {
        double div = aug[col][col];
        for (int j = col; j <= 4; j++) aug[col][j] /= div;

        for (int row = 0; row < 4; row++)
            if (row != col) {
                double factor = aug[row][col];
                for (int j = col; j <= 4; j++)
                    aug[row][j] -= factor * aug[col][j];
            }
    }

    // 得到最小二乘解
    double a0 = aug[0][4], a1 = aug[1][4], a2 = aug[2][4], a3 = aug[3][4];

    // 预测 t=7.5
    double t_test = 7.5;
    double res = a0 + a1 * t_test + a2 * t_test * t_test + a3 * t_test * t_test * t_test;

    // 输出
    cout << "最小二乘解：\n";
    cout << "a0 = " << a0 << endl;
    cout << "a1 = " << a1 << endl;
    cout << "a2 = " << a2 << endl;
    cout << "a3 = " << a3 << endl;
    cout << "\nt=7.5 阻力 = " << res << " (100 lb)\n";

    return 0;
}