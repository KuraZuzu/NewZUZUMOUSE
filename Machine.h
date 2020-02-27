//
// Created by 倉澤　一詩 on 2018/11/28.
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

/* P制御。自機と左右の壁の距離から、直進に補正させる制御 */
    void p_control(double _speed) {
        if(_sensor.get_front_wall_distance() < CENTER_TH) {
            _motor.set_left_speed(_speed);
            _motor.set_right_speed(_speed);

        } else if (_sensor.get_left_wall_distance() < P_TH && _sensor.get_right_wall_distance() < P_TH) {
            const int y_t = _sensor.get_left_wall_distance() - _sensor.get_right_wall_distance();
            const int e_t = 0 - y_t;

            _motor.set_left_speed(_speed + e_t * KP);
            _motor.set_right_speed(_speed - e_t * KP);

        } else if (_sensor.get_left_wall_distance() < P_TH) {
            const int y_t = (_sensor.get_left_wall_distance() - 122);

            _motor.set_left_speed(_speed - y_t * SINGLE_KP);
            _motor.set_right_speed(_speed + y_t * SINGLE_KP);

        } else if (_sensor.get_right_wall_distance() < P_TH) {
            const int y_t = (104 - _sensor.get_right_wall_distance());

            _motor.set_left_speed(_speed - y_t * SINGLE_KP);
            _motor.set_right_speed(_speed + y_t * SINGLE_KP);

        } else {
            _motor.set_left_speed(_speed);
            _motor.set_right_speed(_speed);

        }
    }


/* P制御を使わず、まっすぐ前進 */
    void move(double_t v, double_t dist) {
        const Position temp = _pe.get_position();
        while (true) {
            const Position diff = _pe.get_position() - temp;
            const double_t diff_dist = (diff.x * diff.x) + (diff.y * diff.y);
            if (diff_dist > (dist * dist)) break;
            _motor.set_left_speed(v);
            _motor.set_right_speed(v);
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

    /// 指定した分の距離を前進。自己位置を参照しないでの制御
    void move_p(double_t v, double_t dist) {
        const Position temp = _pe.get_position();
        while (true) {
            Position diff = _pe.get_position() - temp;
            if (abs(diff.x) > dist || abs(diff.y) > dist) break;  //左右どちらかの回転数が、指定の距離を満たすまで "true"
            p_control(v);  //P制御の関数呼び出し
        }
        _motor.reset_counts(); // モーターの回転数のカウントリセット
    }


/* 台形制御。加減速を制御する */
    void move_d(double _speed, double _distance,  ZUZU::ACCEL _mode) {

        _motor.reset_counts(); // モーターの回転数のカウントリセット
        constexpr double _lowest_speed = 80;

        if (_mode == ZUZU::ACCEL::ACCELERATION) {

            const MapPosition first_block = _pe.get_map_position();
            double next_border;
            double first_position;
            double accel;
            const uint8_t _direction = _pe.get_map_position().direction;
            double current_position;

            //進行方向のブロックに対して、適正な目標座標をセットさせる
            if (_direction == NORTH_MASK) {
                first_position = _pe.get_position().y;
                next_border = (_pe.get_map_position().y * ONE_BLOCK);
            } else if (_direction == EAST_MASK) {
                first_position = _pe.get_position().x;
                next_border = (_pe.get_map_position().x * ONE_BLOCK);
            } else if (_direction == SOUTH_MASK) {
                first_position = _pe.get_position().y;
                next_border = ((_pe.get_map_position().y - 1) * ONE_BLOCK);
            } else {
                first_position = _pe.get_position().x;
                next_border = ((_pe.get_map_position().x - 1) * ONE_BLOCK);
            }

            const double a_dist = fabs(next_border - first_position);
            accel = (_speed - _lowest_speed) / a_dist;

            while (first_block == _pe.get_map_position()) {
                if (_direction == NORTH_MASK) current_position = _pe.get_position().y;
                else if (_direction == EAST_MASK) current_position = _pe.get_position().x;
                else if (_direction == SOUTH_MASK) current_position = _pe.get_position().y;
                else current_position = _pe.get_position().x;

                double d_speed = accel * fabs(current_position - first_position) + _lowest_speed;
                p_control(d_speed);

            }
        }


        if (_mode == ZUZU::ACCEL::DECELERATION) {
            double accel = ((_speed - _lowest_speed) / _distance);  // ブロック間の距離に応じて線形加速させる

            while (_distance > _motor.distance_counts()) {
                double d_speed = accel * (_distance - _motor.distance_counts()) + _lowest_speed; // 速度 = (加速度 * 加速距離) + 初速度
//                if(_sensor.get_v_front_wall_distance() < EMR_TH){
//                    stop();
//                    if(_pe.get_map_position().direction == NORTH_MASK) _pe.set_position(_pe.get_position().x, (_pe.get_map_position().y * 180) - 90, _pe.get_position().rad);
//                    else if(_pe.get_map_position().direction == EAST_MASK) _pe.set_position((_pe.get_map_position().x * 180) - 90, _pe.get_position().y, _pe.get_position().rad);
//                    else if(_pe.get_map_position().direction == SOUTH_MASK) _pe.set_position(_pe.get_position().x, (_pe.get_map_position().y * 180) + 90, _pe.get_position().rad);
//                    else _pe.set_position((_pe.get_map_position().x * 180) - 90, _pe.get_position().y, _pe.get_position().rad);
//
//                    break;
//                }
                p_control(d_speed);

            }
        }

        _motor.reset_counts(); // モーターの回転数のカウントリセット
    }


/* 自己位置推定の積算誤差が発生してしまうので、それを修正させる制御 */
    void fit(){
        if(_pe.get_map_position().direction == NORTH_MASK) const double_t fit_dir = PI;        //侵入時にNORTHなら出るときはSOUTH
        else if(_pe.get_map_position().direction == EAST_MASK) const double_t fit_dir = PI/2;  //侵入時にEASTなら出るときにWET
        else if(_pe.get_map_position().direction == SOUTH_MASK) const double_t fit_dir = 0;    //侵入時にSOUTHなら出るときにNORTH
        else const double_t fit_dir = PI*3/2;                                                  //侵入時にWESTなら出るときにEAST

        double_t fit_dir;
        double_t fit_x = (_pe.get_map_position().x * 180) + 90;
        double_t fit_y = (_pe.get_map_position().y * 180) + 90;

        stop();
        wait_ms(100);
        move(-100, HALF_BLOCK);
        stop();
        wait_ms(100);
        move(100, START_BLOCK);
        stop();
        wait_ms(100);

        _pe.set_position(fit_x, fit_y, fit_dir);
    }


    void turn(double_t v, ZUZU::DIRECTION _direction){
        serial_odometry(_pe);
        const uint8_t  temp_dir = _pe.get_map_position().direction;
        double_t now_rad;
        double_t temp_rad;
        while(true){
            uint8_t current_dir = _pe.get_map_position().direction;
            if(temp_dir != current_dir){
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


    void kyusin_running(double speed, double turn_speed, double wait_time, Point<uint8_t> point, Point<uint8_t> next_center_point, Point<uint8_t> next_left_point, Point<uint8_t> next_right_point) {

        const bool temp_l = _sensor.is_opened_left_wall();
        const bool temp_f = _sensor.is_opened_front_wall();
        const bool temp_r = _sensor.is_opened_right_wall();
        double_t temp_x;
        double_t temp_y;
        double_t temp_dir;

        if ((_sensor.is_opened_front_wall()) && ((_map.at(point).walk_cnt - _map.at(next_center_point).walk_cnt) == 1)) {
            move_p(speed);

        } else if ((_sensor.is_opened_left_wall()) &&
                   (_map.at(point).walk_cnt - _map.at(next_left_point).walk_cnt) == 1) {
            move_d(speed, HALF_BLOCK, ZUZU::DECELERATION);
            stop();
            wait_ms(wait_time);
            turn(turn_speed, ZUZU::LEFT_MACHINE);

                if (!temp_r) {
                move(-100, HALF_BLOCK);
                stop();
                wait_ms(wait_time);
                move(100, START_BLOCK);
                stop();
                wait_ms(wait_time);
            }

            if (_pe.get_map_position().direction == NORTH_MASK) {
                temp_x = _pe.get_map_position().x * 180 - 90;
                temp_y = _pe.get_map_position().y * 180 + 90;
                temp_dir = 0;

            } else if (_pe.get_map_position().direction == EAST_MASK) {
                temp_x = _pe.get_map_position().x * 180 - 90;
                temp_y = _pe.get_map_position().y * 180 + 90;
                temp_dir = -PI/2;

            } else if (_pe.get_map_position().direction == SOUTH_MASK){
                temp_x = _pe.get_map_position().x * 180 - 90;
                temp_y = _pe.get_map_position().y * 180 + 90;
                temp_dir = PI/2;

            }else{
                temp_x =_pe.get_map_position().x * 180 + 90;
                temp_y = _pe.get_map_position().y * 180 - 90;
                temp_dir = PI;

            }

            _pe.set_position(temp_x, temp_y, temp_dir);

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
            move_d(speed, 0, ZUZU::ACCELERATION);

        }
    }


    void original_kyusin_running(double speed, double turn_speed, double wait_time, Point<uint8_t> point, Point<uint8_t> next_center_point, Point<uint8_t> next_left_point, Point<uint8_t> next_right_point) {

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
