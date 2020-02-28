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

class Machine {
    double_t e_t_temp;
    Timer ctrl_time;
public:
    MotorManager &_motor;
    SensorManager &_sensor;
    PositionEstimator &_pe;
    Map3& _map;

    Machine(MotorManager &motor, SensorManager &sensor, PositionEstimator &pe, Map3& map) : _motor(motor),
                                                                                                 _sensor(sensor),
                                                                                                 _pe(pe),
                                                                                                 _map(map)
                                                                                                 {
        ctrl_time.start();
        _motor.init();

    }

/* P制御。自機と左右の壁の距離から、直進に補正させる制御
   左右の距離センサを元に、その差分から両方のモータの速度比を調整する
   KP値という倍率を用いて、速度に対しての差分の重みを設定する       */
    void p_control(double _speed) {

        // 前方センサの値が一定以下の時、P制御はしない
        if(_sensor.get_front_wall_distance() < CENTER_TH) {
            _motor.set_left_speed(_speed);
            _motor.set_right_speed(_speed);

        // 両方の距離せんさが閾値以下の時、両方の値を参考にP制御
        } else if (_sensor.get_left_wall_distance() < P_TH && _sensor.get_right_wall_distance() < P_TH) {
            const int y_t = _sensor.get_left_wall_distance() - _sensor.get_right_wall_distance();
            const int e_t = 0 - y_t;

            _motor.set_left_speed(_speed + e_t * KP);
            _motor.set_right_speed(_speed - e_t * KP);

        // 左の距離せんさが閾値以下の時、両方の値を参考にP制御
        } else if (_sensor.get_left_wall_distance() < P_TH) {
            const int y_t = (_sensor.get_left_wall_distance() - 122); //122とは、左のセンサの中央からの距離(個体差を考慮)

            _motor.set_left_speed(_speed - y_t * SINGLE_KP);
            _motor.set_right_speed(_speed + y_t * SINGLE_KP);

        // 左の距離せんさが閾値以下の時、両方の値を参考にP制御
        } else if (_sensor.get_right_wall_distance() < P_TH) {
            const int y_t = (104 - _sensor.get_right_wall_distance()); //104とは、左のセンサの中央からの距離(個体差を考慮)

            _motor.set_left_speed(_speed - y_t * SINGLE_KP);
            _motor.set_right_speed(_speed + y_t * SINGLE_KP);

        //両方のセンサ距離が閾値以下だと、P制御はしない
        } else {
            _motor.set_left_speed(_speed);
            _motor.set_right_speed(_speed);

        }
    }


/* P制御を使わず、まっすぐ前進 */
    void move(double_t v, double_t dist) {
        const Position first_pos = _pe.get_position(); //初期位置(走りはじめの位置)の保存
        while (true) {
            const Position diff = _pe.get_position() - first_pos; //現在位置と初期位置の差分算出
            const double_t diff_dist = (diff.x * diff.x) + (diff.y * diff.y); //メネラウスの定理と同じ要領で、進んだ距離算出
            if (diff_dist > (dist * dist)) break; //上で算出した距離が、指定した距離を上回るまで "true"
            _motor.set_left_speed(v);  //左モータの速度指令
            _motor.set_right_speed(v); //右モータの速度指令
        }
    }


/*  "move_p()" はP制御を用いての前進
     オーバーロードを用いて、2種類の制御手法の確率*/

    /// ブロックを超えるまで走行させる。走らせる距離を引数にいれる必要がない。自己位置推定を利用しての制御
    void move_p(double_t v) {
        MapPosition temp = _pe.get_map_position();
        while (temp == _pe.get_map_position()) {  //走り出しの瞬間と同じブロックにいる間のみ "true"
            p_control(v);
        }
        _motor.reset_counts(); // モーターの回転数のカウントリセット
    }

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
    void move_d(double _speed, double _distance,  ZUZU::ACCEL _mode) {

        _motor.reset_counts(); // モーターの回転数のカウントリセット
        constexpr double _lowest_speed = 80;

        if (_mode == ZUZU::ACCEL::ACCELERATION) { //マシンが加速する場合

            const MapPosition first_block = _pe.get_map_position();
            double target_dist;
            double first_dist;
            double accel;
            const uint8_t _direction = _pe.get_map_position().direction;
            double current_position;

            //進行方向のブロックに対して、適正な目標座標をセットさせる。
            //この場合は、加速を行うので、ブロック同士の間の座標となる
            if (_direction == NORTH_MASK) {
                first_dist = _pe.get_position().y;
                target_dist = (_pe.get_map_position().y * ONE_BLOCK); //マップ座標単位 * 1ブロックの距離
            } else if (_direction == EAST_MASK) {
                first_dist = _pe.get_position().x;
                target_dist = (_pe.get_map_position().x * ONE_BLOCK);
            } else if (_direction == SOUTH_MASK) {
                first_dist = _pe.get_position().y;
                target_dist = ((_pe.get_map_position().y - 1) * ONE_BLOCK);
            } else {
                first_dist = _pe.get_position().x;
                target_dist = ((_pe.get_map_position().x - 1) * ONE_BLOCK);
            }

            const double a_dist = fabs(target_dist - first_dist); //目的座標までの距離を絶対値で確保する
            accel = (_speed - _lowest_speed) / a_dist;                //距離をもとに、加速度を確保

            while (first_block == _pe.get_map_position()) {
                if (_direction == NORTH_MASK) current_position = _pe.get_position().y;
                else if (_direction == EAST_MASK) current_position = _pe.get_position().x;
                else if (_direction == SOUTH_MASK) current_position = _pe.get_position().y;
                else current_position = _pe.get_position().x;

                double d_speed = accel * fabs(current_position - first_dist) + _lowest_speed; //距離をもとに速度算出
                p_control(d_speed); //座標を移動するまで前進

            }
        }


        if (_mode == ZUZU::ACCEL::DECELERATION) { //マシンが減速するばいい
            double accel = ((_speed - _lowest_speed) / _distance);  // ブロック間の距離に応じて線形加速させる

            while (_distance > _motor.distance_counts()) {
                double d_speed = accel * (_distance - _motor.distance_counts()) + _lowest_speed; // 速度 = (加速度 * 加速距離) + 初速度
                p_control(d_speed);

            }
        }

        _motor.reset_counts(); // モーターの回転数のカウントリセット
    }


/* 自己位置推定の積算誤差が発生してしまうので、それを修正させる制御 */
    void fit(){

        double_t fit_dir;
        if(_pe.get_map_position().direction == NORTH_MASK) fit_dir = PI;        //侵入時にNORTHなら出るときはSOUTH
        else if(_pe.get_map_position().direction == EAST_MASK) fit_dir = PI/2;  //侵入時にEASTなら出るときにWET
        else if(_pe.get_map_position().direction == SOUTH_MASK) fit_dir = 0;    //侵入時にSOUTHなら出るときにNORTH
        else fit_dir = PI*3/2;                                                  //侵入時にWESTなら出るときにEAST

        double_t fit_x = (_pe.get_map_position().x * ONE_BLOCK) + HALF_BLOCK; //機体はブロックの中心点にいるので、HALF_BLOCK を足す
        double_t fit_y = (_pe.get_map_position().y * ONE_BLOCK) + HALF_BLOCK; // 同上

        /////この一連の動作により、自機を正確なマップの中心にセットする
        stop();
        wait_ms(100);
        move(-100, HALF_BLOCK);
        stop();
        wait_ms(100);
        move(100, START_BLOCK);
        stop();
        wait_ms(100);
        /////
        _pe.set_position(fit_x, fit_y, fit_dir); //実際に自己位置をセットする
    }


/* 指定の方向に機体を旋回 */
    void turn(double_t v, ZUZU::DIRECTION _direction){
        //serial_odometry(_pe);  //シリアル通信を用いてのデバッグ用
        const uint8_t  first_dir = _pe.get_map_position().direction; //初期の向いている方向
        double_t now_rad;
        double_t temp_rad;
        while(true){
            const uint8_t current_dir = _pe.get_map_position().direction; //現在の向いている方向
            if(first_dir != current_dir){ //向いている方向が変わらないうちは"true"
                temp_rad = _pe.get_position().rad;
                break;
            }

            if(_direction == ZUZU::LEFT_MACHINE || _direction == ZUZU::TURN_MACHINE) {
                _motor.set_left_speed(-v);
                _motor.set_right_speed(v);
            }else if(_direction == ZUZU::DIRECTION::RIGHT_MACHINE){
                _motor.set_left_speed(v);
                _motor.set_right_speed(-v);

            }
        }

        double_t target_rad = (_direction==ZUZU::TURN_MACHINE)?PI/4.0 + PI/2.0: PI/4.0;

        while (true) {
            now_rad = _pe.get_position().rad;
            if (abs(now_rad - temp_rad) >= target_rad) break;

            if(_direction == ZUZU::DIRECTION::LEFT_MACHINE || _direction == ZUZU::TURN_MACHINE) {
                _motor.set_left_speed(-v);
                _motor.set_right_speed(v);
            }else if(_direction == ZUZU::DIRECTION::RIGHT_MACHINE){
                _motor.set_left_speed(v);
                _motor.set_right_speed(-v);
            }
        }
        stop();
    }

/* モーター制御をストップさせる */
    void stop() {
        _motor.set_left_speed(0);
        _motor.set_right_speed(0);
        _motor.reset_counts(); // モーターの回転数のカウントリセット
    }


/* 求心(目的座標に最短で向かう)手法のルールベースの基礎アルゴリズム */
    void kyusin_method(double speed, double turn_speed, double wait_time, Point<uint8_t> point, Point<uint8_t> next_center_point, Point<uint8_t> next_left_point, Point<uint8_t> next_right_point) {


        /*前方の壁が空いていた時、そして、マップの数情報で、マップが隣り合ってて通行可能な時
          といったような処理を、見える壁全てに対して行う。
          この機体では、曲がらずに前進することの重みが1番重要となるように、1番上に前進処理が書かれている*/
        if ((_sensor.is_opened_front_wall()) &&
            ((_map.at(point).walk_cnt - _map.at(next_center_point).walk_cnt) == 1)) {
            move_p(speed);

        } else if ((_sensor.is_opened_left_wall()) && (_map.at(point).walk_cnt - _map.at(next_left_point).walk_cnt) == 1) {
            move_d(speed, HALF_BLOCK, ZUZU::DECELERATION);
            stop();
            wait_ms(wait_time);
            turn(turn_speed, ZUZU::LEFT_MACHINE);
            stop();
            wait_ms(wait_time);
            move_d(speed, 0, ZUZU::ACCELERATION);

        }else if((_sensor.is_opened_right_wall()) && ((_map.at(point).walk_cnt - _map.at(next_right_point).walk_cnt) == 1)){
            move_d(speed, HALF_BLOCK, ZUZU::DECELERATION);
            stop();
            wait_ms(wait_time);
            turn(turn_speed, ZUZU::RIGHT_MACHINE);
            stop();
            wait_ms(wait_time);
            move_d(speed, 0, ZUZU::ACCELERATION);

        }else{
            move_d(speed, HALF_BLOCK, ZUZU::DECELERATION);
            stop();
            wait_ms(wait_time);
             turn(turn_speed, ZUZU::TURN_MACHINE);
            stop();
            wait_ms(wait_time);
            move_d(speed, 0, ZUZU::ACCELERATION);
        }
    }
};


#endif //NEWZUZUMOUSE_MACHINE_H
