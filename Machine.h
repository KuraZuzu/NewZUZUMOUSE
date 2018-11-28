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

class Machine{
public:
    MotorManager& _motor;
    SensorManager& _sensor;
    PositionEstimator& _pe;

    Machine(MotorManager& motor, SensorManager& sensor, PositionEstimator& pe) : _motor(motor), _sensor(sensor), _pe(pe) {
        _motor.init();

    }

//    void fit(double_t v){
//
//        const Position temp = _pe.get_map_position();
//        const Block b = _pe.
//    }

    void move(double_t v, double_t dist){

        const Position temp = _pe.get_position();
        while(true){
            const Position diff = _pe.get_position() - temp;
            const double_t diff_dist = (diff.x * diff.x) + (diff.y * diff.y);
            if (diff_dist > (dist*dist))break;
            _motor.set_left_speed(v);
            _motor.set_right_speed(v);

        }

    }

    void move_p(double_t v){
        MapPosition temp = _pe.get_map_position();
        while (temp == _pe.get_map_position()){
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

    void move_p(double_t v, double_t dist){

        const Position temp = _pe.get_position();
        while(true){
            Position diff = _pe.get_position() - temp;
            if (abs(diff.x) > dist || abs(diff.y) > dist)break;
            p_control(v);
        }
        _motor.reset_counts();
    }

    void move_d(double_t v, double_t dist, bool mode){

        double_t lowest_v = 80;
        double a = ((v - lowest_v) / dist);

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
