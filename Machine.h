//
// Created by 倉澤　一詩 on 2018/11/28.
//

#ifndef NEWZUZUMOUSE_MACHINE_H
#define NEWZUZUMOUSE_MACHINE_H

#include "defines.h"
#include "mslm_v3/deftype.h"
#include "mbed.h"
#include "mslm_v3/motor.h"
#include "mslm_v3/SensorManager.h"
#include "mslm_v3/PositionEstimator.h"
#include "new_zuzumouse.h"
#include "serial_utility.h"
#include "mslm_v3/Point.h"
#include "mslm_v3/map3.h"
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

//    void fit(double_t v){
//
//        const Position temp = _pe.get_map_position();
//        const Block b = _pe.
//    }

    void move(double_t v, double_t dist) {

        const Position temp = _pe.get_position();
        while (true) {
            const Position diff = _pe.get_position() - temp;
            const double_t diff_dist = (diff.x * diff.x) + (diff.y * diff.y);
            if (diff_dist > (dist * dist))break;
            _motor.set_left_speed(v);
            _motor.set_right_speed(v);

        }

    }

    void move_p(double_t v) {
        MapPosition temp = _pe.get_map_position();
        while (temp == _pe.get_map_position()) {
//            odometry_p_control(v);
            p_control(v);
//            _motor.set_left_speed(v);
//            _motor.set_right_speed(v);

        }
        _motor.reset_counts();
    }


//move_d のコンパイルを通す為に 仕方なく move_dを改造
//    void move_p(double_t v, double_t dist, int i=0){
//
//        const Position temp = _pe.get_position();
//        while(true){
//            const Position diff = _pe.get_position() - temp;
//            const double_t diff_dist = (diff.x * diff.x) + (diff.y * diff.y);
//            if (diff_dist > (dist*dist))break;
//            p_control(v);
//        }
//        _motor.reset_counts();
//    }

    void move_p(double_t v, double_t dist) {

        const Position temp = _pe.get_position();
        while (true) {
            Position diff = _pe.get_position() - temp;
            if (abs(diff.x) > dist || abs(diff.y) > dist)break;
            p_control(v);

        }
        _motor.reset_counts();
    }

//    void move_d(double_t v, double_t dist, ZUZU::ACCEL _mode){
//
//        double_t lowest_v = 100;
//        double a = ((v - lowest_v) / dist);
//
//    }

    void move_d(double _speed, double _distance,  ZUZU::ACCEL _mode) {


        _motor.reset_counts();
        double _lowest_speed = 130;

        if (_mode == ZUZU::ACCEL::ACCELERATION) {

            const MapPosition first_block = _pe.get_map_position();
            double next_border;
            double first_position;
            double a;
            const uint8_t _direction = _pe.get_map_position().direction;
            double current_position;

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
            a = (_speed - _lowest_speed) / a_dist;
//            a = (_speed - _lowest_speed) / HALF_BLOCK;

            while (first_block == _pe.get_map_position()) {

//                odometry_p_control(_speed, ZUZU::D_MODE::OUT);
//            p_control(v);

                if (_direction == NORTH_MASK) current_position = _pe.get_position().y;
                else if (_direction == EAST_MASK) current_position = _pe.get_position().x;
                else if (_direction == SOUTH_MASK) current_position = _pe.get_position().y;
                else current_position = _pe.get_position().x;

//                _speed
//a * motor.distance_counts() + _lowest_speed
                double d_speed = a * fabs(current_position - first_position) + _lowest_speed;
                p_control(d_speed);

            }
        }



        if (_mode == ZUZU::ACCEL::DECELERATION) {
            double a = ((_speed - _lowest_speed) / _distance);  //傾き

            while (_distance > _motor.distance_counts()) {
                double d_speed = a * (_distance - _motor.distance_counts()) + _lowest_speed;
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
//                odometry_p_control(d_speed, ZUZU::D_MODE::IN);

            }
        }

        _motor.reset_counts();
    }


    void fit(){

        if(_pe.get_map_position().direction == NORTH_MASK) const double_t fit_dir = PI;  //侵入時にNORTHなら出るときはSOUTH
        else if(_pe.get_map_position().direction == EAST_MASK) const double_t fit_dir = PI/2;  //侵入時にEASTなら出るときにWET
        else if(_pe.get_map_position().direction == SOUTH_MASK) const double_t fit_dir = 0;  //侵入時にSOUTHなら出るときにNORTH
        else const double_t fit_dir = -PI/2;  //侵入時にWESTなら出るときにEAST


        double_t fit_dir;
        double_t fit_x = (_pe.get_map_position().x * 180) + 90;
        double_t fit_y = (_pe.get_map_position().y * 180) + 90;


        old_turn(100, ZUZU::LEFT_MACHINE);
        stop();
        wait_ms(100);
        move(-100, HALF_BLOCK);
        stop();
        wait_ms(100);
        move(100, START_BLOCK);
        stop();
        wait_ms(100);
        old_turn(100, ZUZU::LEFT_MACHINE);
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
//        double_t  target_rad = 0.0;
        while (true) {
            now_rad = _pe.get_position().rad;
            if (abs(now_rad - temp_rad) >= target_rad)break;

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


    void old_turn(double _speed, ZUZU::DIRECTION _direction) {
        if (_direction == ZUZU::LEFT_MACHINE) {
            while (LEFT_TURN > _motor.right_distance()) {
                _motor.set_left_speed(-_speed);
                _motor.set_right_speed(_speed);
            }

        } else if (_direction == ZUZU::TURN_MACHINE) {
            while (HALF_TURN > _motor.left_distance()) {
                _motor.set_left_speed(_speed);
                _motor.set_right_speed(-_speed);
            }

        } else if (_direction == ZUZU::RIGHT_MACHINE) {
            while (RIGHT_TURN > _motor.left_distance()) {
                _motor.set_left_speed(_speed);
                _motor.set_right_speed(-_speed);
            }
        }
        stop();
    }



    void stop() {
        _motor.set_left_speed(0);
        _motor.set_right_speed(0);
        _motor.reset_counts();
    }


//    void odometry_p_control(double _speed, ZUZU::D_MODE _mode=ZUZU::D_MODE::IN) {
//
//        double current_x = _pe.get_position().x;
//        double current_y = _pe.get_position().y;
//        double true_x = (_pe.get_map_position().x * 180) + 90;
//        double true_y = (_pe.get_map_position().y * 180) + 90;
//
////        serial_odometry(_pe);
////        if(ctrl_time.read_ms() > 20) {
//            if (_sensor.get_left_wall_distance() < P_TH && _sensor.get_right_wall_distance() < P_TH) {
//                const int y_t = _sensor.get_left_wall_distance() - _sensor.get_right_wall_distance();
//                const int e_t = 0 - y_t;
//
//                if ((_pe.get_map_position().direction == NORTH_MASK) &&
//                    (_pe.get_map_position().direction == SOUTH_MASK)) {
//                    _motor.set_left_speed(_speed + e_t * KP);
//                    _motor.set_right_speed(_speed - e_t * KP);
//                } else {
//                    _motor.set_left_speed(_speed + e_t * KP);
//                    _motor.set_right_speed(_speed - e_t * KP);
//                }
//
//
//            } else {
//                if ((_pe.get_map_position().direction == NORTH_MASK) ||
//                    (_pe.get_map_position().direction == SOUTH_MASK)) {
////                    const double e_t = (90.0 - current_x);
////
////                    _motor.set_left_speed(_speed + ((e_t * ODOMETRY_KP) - ((e_t - e_t_temp) * 0.8)));
////                    _motor.set_right_speed(_speed - ((e_t * ODOMETRY_KP) - ((e_t - e_t_temp) * 0.8)));
////                    e_t_temp = e_t;
//
//                    const double e_t = (true_y - current_y);
//                    _motor.set_left_speed(_speed - e_t * ODOMETRY_KP);
//                    _motor.set_right_speed(_speed + e_t * ODOMETRY_KP);
//
//                } else {
//                    const double e_t = (true_y - current_y);
//                    _motor.set_left_speed(_speed - e_t * ODOMETRY_KP);
//                    _motor.set_right_speed(_speed + e_t * ODOMETRY_KP);
//                }
//
//            }
////            ctrl_time.reset();
////        }
//
//
//
//    }



//    void odometry_p_control(double _speed, ZUZU::D_MODE _mode) {
//
//        double current_x = _pe.get_position().x;
//        double current_y = _pe.get_position().y;
//        double true_x = (_pe.get_map_position().x * 180) + 90;
//        double true_y = (_pe.get_map_position().y * 180) + 90;
//
//        if(_mode == ZUZU::D_MODE::IN) {
//
//            if (_sensor.get_left_wall_distance() < P_TH && _sensor.get_right_wall_distance() < P_TH) {
//                const int y_t = _sensor.get_left_wall_distance() - _sensor.get_right_wall_distance();
//                const int e_t = 0 - y_t;
//
//                if ((_pe.get_map_position().direction == NORTH_MASK) && (_pe.get_map_position().direction == SOUTH_MASK)) {
//
//                    if (0 < true_y - current_y) {
//                        _motor.set_left_speed(_speed + e_t * KP);
//                        _motor.set_right_speed(_speed - e_t * KP);
//                    } else {
//                        _motor.set_left_speed(0);
//                        _motor.set_right_speed(0);
//                    }
//
//                } else {
//                    if (0 < true_x - current_x) {
//                        _motor.set_left_speed(_speed + e_t * KP);
//                        _motor.set_right_speed(_speed - e_t * KP);
//                    } else {
//                        _motor.set_left_speed(0);
//                        _motor.set_right_speed(0);
//                    }
//                }
//
//
//            } else {
//
//                if ((_pe.get_map_position().direction == NORTH_MASK) ||
//                    (_pe.get_map_position().direction == SOUTH_MASK)) {
//                    const double e_t = (true_x - current_x);
//
//                    if (0 < true_y - current_y) {
//                        _motor.set_left_speed(_speed + e_t * ODOMETRY_KP);
//                        _motor.set_right_speed(_speed - e_t * ODOMETRY_KP);
//                    } else {
//                        _motor.set_left_speed(0);
//                        _motor.set_right_speed(0);
//                    }
//
//
//                } else {
//                    const double e_t = (true_y - current_y);
//
//                    if (0 < true_y - current_y) {
//                        _motor.set_left_speed(_speed - e_t * ODOMETRY_KP);
//                        _motor.set_right_speed(_speed + e_t * ODOMETRY_KP);
//                    } else {
//                        _motor.set_left_speed(0);
//                        _motor.set_right_speed(0);
//                    }
//
//                }
//
//            }
//
//        }else{
//
//            if (_sensor.get_left_wall_distance() < P_TH && _sensor.get_right_wall_distance() < P_TH) {
//                const int y_t = _sensor.get_left_wall_distance() - _sensor.get_right_wall_distance();
//                const int e_t = 0 - y_t;
//
//                if ((_pe.get_map_position().direction == NORTH_MASK) && (_pe.get_map_position().direction == SOUTH_MASK)) {
//
//                        _motor.set_left_speed(_speed + e_t * KP);
//                        _motor.set_right_speed(_speed - e_t * KP);
//
//
//                } else {
//                        _motor.set_left_speed(_speed + e_t * KP);
//                        _motor.set_right_speed(_speed - e_t * KP);
//                }
//
//
//            } else {
//
//                if ((_pe.get_map_position().direction == NORTH_MASK) ||
//                    (_pe.get_map_position().direction == SOUTH_MASK)) {
//                    const double e_t = (true_x - current_x);
//
//                        _motor.set_left_speed(_speed + e_t * ODOMETRY_KP);
//                        _motor.set_right_speed(_speed - e_t * ODOMETRY_KP);
//
//
//                } else {
//                    const double e_t = (true_y - current_y);
//
//                        _motor.set_left_speed(_speed - e_t * ODOMETRY_KP);
//                        _motor.set_right_speed(_speed + e_t * ODOMETRY_KP);
//
//                }
//
//            }
//
//
//        }
//
//    }


    void p_control(double _speed) {

//        _motor.set_left_speed(_speed);
//        _motor.set_right_speed(_speed);

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


//    void odometry_p_control(double _speed) {
//
//            double diff_x;
//            double diff_y;
//
//            _pe.get_position().x =
//                    _pe.get_map_position().y
//
//            _motor.set_left_speed(_speed);
//            _motor.set_right_speed(_speed);
//
//    }
//
    void kyusin_running(double speed, double turn_speed, double wait_time, Point<uint8_t> point, Point<uint8_t> next_center_point, Point<uint8_t> next_left_point, Point<uint8_t> next_right_point) {

        const bool temp_l = _sensor.is_opened_left_wall();
        const bool temp_f = _sensor.is_opened_front_wall();
        const bool temp_r = _sensor.is_opened_right_wall();
        double_t temp_x;
        double_t temp_y;
        double_t temp_dir;

        if ((_sensor.is_opened_front_wall()) &&
            ((_map.at(point).walk_cnt - _map.at(next_center_point).walk_cnt) == 1)) {
            move_p(speed);
        } else if ((_sensor.is_opened_left_wall()) &&
                   (_map.at(point).walk_cnt - _map.at(next_left_point).walk_cnt) == 1) {
            move_d(speed, HALF_BLOCK, ZUZU::DECELERATION);
            stop();
            wait_ms(wait_time);
            turn(turn_speed, ZUZU::LEFT_MACHINE);

//            if (!temp_f && !temp_r) {
//                old_turn(100, ZUZU::LEFT_MACHINE);
//                stop();
//                wait_ms(wait_time);
//                move(-100, HALF_BLOCK);
//                stop();
//                wait_ms(wait_time);
//                move(100, START_BLOCK);
//                old_turn(100, ZUZU::RIGHT_MACHINE);
//                stop();
//                wait_ms(wait_time);
//                move(-100, HALF_BLOCK);
//                stop();
//                wait_ms(wait_time);
//                move(100, START_BLOCK);
//
//            } else
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

//            old_turn(turn_speed, ZUZU::LEFT_MACHINE);
            stop();
            wait_ms(wait_time);
            move_d(speed, 0, ZUZU::ACCELERATION);
        }else if((_sensor.is_opened_right_wall()) && ((_map.at(point).walk_cnt - _map.at(next_right_point).walk_cnt) == 1)){
            move_d(speed, HALF_BLOCK, ZUZU::DECELERATION);
            stop();
            wait_ms(wait_time);
            turn(turn_speed, ZUZU::RIGHT_MACHINE);
//            old_turn(turn_speed, ZUZU::RIGHT_MACHINE);
            stop();
            wait_ms(wait_time);
            move_d(speed, 0, ZUZU::ACCELERATION);
        }else{
            move_d(speed, HALF_BLOCK, ZUZU::DECELERATION);
            stop();
//            wait_ms(wait_time);
//            old_turn(turn_speed, ZUZU::TURN_MACHINE);
//            turn(turn_speed, ZUZU::TURN_MACHINE);
            fit();
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
//            old_turn(turn_speed, ZUZU::LEFT_MACHINE);
            stop();
            wait_ms(wait_time);
            move_d(speed, 0, ZUZU::ACCELERATION);

        }else if((_sensor.is_opened_right_wall()) && ((_map.at(point).walk_cnt - _map.at(next_right_point).walk_cnt) == 1)){
            move_d(speed, HALF_BLOCK, ZUZU::DECELERATION);
            stop();
            wait_ms(wait_time);
            turn(turn_speed, ZUZU::RIGHT_MACHINE);
//            old_turn(turn_speed, ZUZU::RIGHT_MACHINE);
            stop();
            wait_ms(wait_time);
            move_d(speed, 0, ZUZU::ACCELERATION);

        }else{
            move_d(speed, HALF_BLOCK, ZUZU::DECELERATION);
            stop();
//            wait_ms(wait_time);
//            old_turn(turn_speed, ZUZU::TURN_MACHINE);
//            turn(turn_speed, ZUZU::TURN_MACHINE);
            fit();
            stop();
            wait_ms(wait_time);
            move_d(speed, 0, ZUZU::ACCELERATION);
        }
    }
};


#endif //NEWZUZUMOUSE_MACHINE_H
