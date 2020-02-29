//
// Created by 倉澤　一詩
//

#ifndef NEWZUZUMOUSE_MACHINE_H
#define NEWZUZUMOUSE_MACHINE_H

#include "defines.h"
#include "mslm_v3/deftype.h"
#include "mslm_v3/motor.h"
#include "mslm_v3/SensorManager.h"
#include "serial_utility.h"

class machine {

private:
    Timer ctrl_time;

public:
    MotorManager &_motor;
    SensorManager &_sensor;
    PositionEstimator &_pe;
    Map3& _map;

    machine(MotorManager &motor, SensorManager &sensor, PositionEstimator &pe, Map3& map);

/* P制御。自機と左右の壁の距離から、直進に補正させる制御
   左右の距離センサを元に、その差分から両方のモータの速度比を調整する
   KP値という倍率を用いて、速度に対しての差分の重みを設定する       */
    void p_control(double _speed);


/* P制御を使わず、まっすぐ前進 */
    void move(double_t v, double_t dist);


/*  "move_p()" はP制御を用いての前進
     オーバーロードを用いて、2種類の制御手法の確率*/

    /// ブロックを超えるまで走行させる。走らせる距離を引数にいれる必要がない。自己位置推定を利用しての制御
    void move_p(double_t v);

    /// 指定した分の距離を前進。自己位置を参照しない制御
    void move_p(double_t v, double_t dist) {
        const Position first_pos = _pe.get_position();  //初期位置の座標取得
        while (true) {
            Position diff = _pe.get_position() - first_pos;  //初期位置から現在位置の差分をとり、進んだ距離算出
            if (abs(diff.x) > dist || abs(diff.y) > dist) break;  //左右どちらかの回転数が、指定の距離を満たすまで "true"
            p_control(v);  //P制御の関数呼び出し
        }
        _motor.reset_counts(); // モーターの回転数のカウントリセット
    }


/* 台形制御。加減速を制御する */
    void move_d(double _speed, double _distance,  ZUZU::ACCEL _mode);


/* 自己位置推定の積算誤差が発生してしまうので、それを修正させる制御 */
    void fit();


/* 指定の方向に機体を旋回 */
    void turn(double_t v, ZUZU::DIRECTION _direction);

/* モーター制御をストップさせる */
    void stop() {
        _motor.set_left_speed(0);
        _motor.set_right_speed(0);
        _motor.reset_counts(); // モーターの回転数のカウントリセット
    }


/* 求心(目的座標に最短で向かう)手法のルールベースの基礎アルゴリズム */
    void kyusin_method(double speed, double turn_speed, double wait_time, Point<uint8_t> point, Point<uint8_t> next_center_point, Point<uint8_t> next_left_point, Point<uint8_t> next_right_point);
};


#endif //NEWZUZUMOUSE_MACHINE_H
