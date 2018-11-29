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

class Machine {
public:
    MotorManager &_motor;
    SensorManager &_sensor;
    PositionEstimator &_pe;
    MapPosition _mp;

    Machine(MotorManager &motor, SensorManager &sensor, PositionEstimator &pe, MapPosition mp) : _motor(motor),
                                                                                                 _sensor(sensor),
                                                                                                 _pe(pe), _mp(mp) {
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

    void move_d(double _speed, double _distance, ZUZU::ACCEL _mode) {

        _motor.reset_counts();
        double _lowest_speed = 80;

        if (_mode == ZUZU::ACCEL::ACCELERATION) {

            const MapPosition first_block = _pe.get_map_position();
            double a_dist;
            double next_border;
            double first_position;
            double a;
            const uint8_t _direction = _pe.get_map_position().direction;
            double current_position;

            if (_direction == NORTH_MASK) {
                first_position = _pe.get_position().y;
                next_border = ((_pe.get_map_position().y * ONE_BLOCK) + HALF_BLOCK);
            } else if (_direction == EAST_MASK) {
                first_position = _pe.get_position().x;
                next_border = ((_pe.get_map_position().x * ONE_BLOCK) + HALF_BLOCK);
            } else if (_direction == SOUTH_MASK) {
                first_position = _pe.get_position().y;
                next_border = ((_pe.get_map_position().y * ONE_BLOCK) - HALF_BLOCK);
            } else {
                first_position = _pe.get_position().x;
                next_border = ((_pe.get_map_position().x * ONE_BLOCK) - HALF_BLOCK);
            }

            a_dist = abs(next_border - first_position);
            a = (_speed - _lowest_speed) / a_dist;

            while (first_block == _pe.get_map_position()) {

                if (_direction == NORTH_MASK) current_position = _pe.get_position().y;
                else if (_direction == EAST_MASK) current_position = _pe.get_position().x;
                else if (_direction == SOUTH_MASK) current_position = _pe.get_position().y;
                else current_position = _pe.get_position().x;

                double d_speed = a * abs(current_position - first_position) + _lowest_speed;
                p_control(d_speed);
            }
        }



        if (_mode == ZUZU::ACCEL::DECELERATION) {
            double a = ((_speed - _lowest_speed) / _distance);  //傾き
            while (_distance > _motor.distance_counts()) {

                double d_speed = a * (_distance - _motor.distance_counts()) + _lowest_speed;
                p_control(d_speed);
            }
        }

        _motor.reset_counts();
    }



    void turn(double_t v, ZUZU::DIRECTION _direction){

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
        double_t target_rad = (_direction==ZUZU::TURN_MACHINE)?PI/4.0 + PI/2.0:PI/4.0;
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


    void p_control(double _speed) {

        if (_sensor.get_front_wall_distance() < CENTER_TH) {
            _motor.set_left_speed(_speed);
            _motor.set_right_speed(_speed);

        } else if (_sensor.get_left_wall_distance() < WALL_TH && _sensor.get_right_wall_distance() < WALL_TH) {
            const int y_t = _sensor.get_left_wall_distance() - _sensor.get_right_wall_distance();
            const int e_t = 0 - y_t;

            _motor.set_left_speed(_speed + e_t * KP);
            _motor.set_right_speed(_speed - e_t * KP);


        } else if (_sensor.get_left_wall_distance() < WALL_TH) {
            const int y_t = (_sensor.get_left_wall_distance() - 122);

            _motor.set_left_speed(_speed - y_t * KP);
            _motor.set_right_speed(_speed + y_t * KP);


        } else if (_sensor.get_right_wall_distance() < WALL_TH) {
            const int y_t = (104 - _sensor.get_right_wall_distance());

            _motor.set_left_speed(_speed - y_t * KP);
            _motor.set_right_speed(_speed + y_t * KP);


        } else {
            _motor.set_left_speed(_speed);
            _motor.set_right_speed(_speed);

        }


    }


};


#endif //NEWZUZUMOUSE_MACHINE_H
