#ifndef NEWZUZUMOUSE_CALC_H
#define NEWZUZUMOUSE_CALC_H


/*********************************************
 * 台形則による定積分
 *********************************************/

#include <iostream>  // for cout
#include <math.h>    // for sqrt
#include <stdio.h>   // for printf()

# define f(x) sqrt(4-x*x)  // 被積分関数

using namespace std;

/*
 * 計算クラス
 */

class Calc {

    // 各種定数
    static const int m = 100;  // 積分区間分割数

    // 各種変数
    double h;     // １区間の幅
    double x;     // X 値
    double s;     // 面積
    int k;        // ループインデックス

public:
    // 定積分計算
    void calcIntegral(double a, double b);
};

/*
 * 定積分計算
 */
void Calc::calcIntegral(double a, double b) {
    // １区間の幅
    h = (b - a) / m;

    // 初期化
    x = a;  // X 値を a で初期化
    s = 0;  // 面積初期化

    // 計算
    for (k = 1; k <= m-1; k++) {
        x = x + h;
        s = s + f(x);
    }
    s = h * ((f(a) + f(b)) / 2 + s);

    // 結果表示
    printf("  /%f\n",b);
    printf("  |  f(x)dx = %f\n", s);
    printf("  /%f\n",a);
}

/*
 * メイン処理
 */
int main()
{
    // 積分区間
    double a, b;

    try {
        // データ入力
        cout << "積分区間 A, B ：";
        scanf("%lf %lf", &a, &b);

        // 計算クラスインスタンス化
        Calc objCalc;

        // 定積分計算
        objCalc.calcIntegral(a, b);
    }
    catch (...) {
        cout << "例外発生！" << endl;
        return -1;
    }

    // 正常終了
    return 0;
}


#endif //NEWZUZUMOUSE_CALC_H
