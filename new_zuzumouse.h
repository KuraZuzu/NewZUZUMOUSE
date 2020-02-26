//
// Created by 倉澤　一詩 on 2018/09/22.
//
#ifndef NEWZUZUMOUSE_NEW_ZUZUMOUSE_H
#define NEWZUZUMOUSE_NEW_ZUZUMOUSE_H

#include "defines.h"
#include "mslm_v3/deftype.h"
#include "mbed.h"
#include "mslm_v3/motor.h"
#include "mslm_v3/SensorManager.h"
#include "mslm_v3/PositionEstimator.h"
#include "new_zuzumouse.h"
#include "serial_utility.h"

class NewZuzumouse {
public:
    MotorManager& motor;
    SensorManager& sensor;
    PositionEstimator pe;


    NewZuzumouse(MotorManager& _motor, SensorManager& _sensor, PositionEstimator _pe) : motor(_motor), sensor(_sensor), pe(_pe) {
        motor.init(); //走る準備するよ！(初期値のフラグが0で割り込み開始)

    }

//    ここから走るよ

    void move(double _speed, double _distance) {
        while (_distance > motor.left_distance()) {
            motor.set_left_speed(_speed);
            motor.set_right_speed(_speed);
        }
        stop();
    }

    void test_move(double l_speed, double r_speed, double _distance) {
        motor.set_odometry_watch_count(0);
        while (_distance > motor.left_distance()) {
            motor.set_left_speed(l_speed);
            motor.set_right_speed(r_speed);
        }
        stop();
    }



    void turn(double _speed, ZUZU::DIRECTION _direction) {
        if (_direction == ZUZU::LEFT_MACHINE) {
            while (LEFT_TURN > motor.right_distance()) {
                motor.set_left_speed(-_speed);
                motor.set_right_speed(_speed);
            }

        } else if (_direction == ZUZU::TURN_MACHINE) {
            while (HALF_TURN > motor.left_distance()) {
                motor.set_left_speed(_speed);
                motor.set_right_speed(-_speed);
            }

        } else if (_direction == ZUZU::RIGHT_MACHINE) {
            while (RIGHT_TURN > motor.left_distance()) {
                motor.set_left_speed(_speed);
                motor.set_right_speed(-_speed);
            }
        }
        stop();
    }


    void stop() {
        motor.set_left_speed(0);
        motor.set_right_speed(0);
        motor.reset_counts();
    }


    void p_control(double _speed) {


//        motor.set_left_speed(_speed);
//        motor.set_right_speed(_speed);

        if (sensor.get_front_wall_distance() < CENTER_TH) {
            motor.set_left_speed(_speed);
            motor.set_right_speed(_speed);

        } else if (sensor.get_left_wall_distance() < WALL_TH && sensor.get_right_wall_distance() < WALL_TH) {
            const int y_t = sensor.get_left_wall_distance() - sensor.get_right_wall_distance();
            const int e_t = 0 - y_t;

            motor.set_left_speed(_speed + e_t * KP);
            motor.set_right_speed(_speed - e_t * KP);


        } else if (sensor.get_left_wall_distance() < WALL_TH) {
            const int y_t = (sensor.get_left_wall_distance() - 122);

            motor.set_left_speed(_speed - y_t * KP);
            motor.set_right_speed(_speed + y_t * KP);


        } else if (sensor.get_right_wall_distance() < WALL_TH) {
            const int y_t = (104 - sensor.get_right_wall_distance());

            motor.set_left_speed(_speed - y_t * KP);
            motor.set_right_speed(_speed + y_t * KP);


        } else {
            motor.set_left_speed(_speed);
            motor.set_right_speed(_speed);

        }


    }


    void move_p(double _speed, double _distance) {
//        motor.reset_counts();

        while (_distance > motor.left_distance()) {

                p_control(_speed);
        }

        motor.reset_counts();
        //stop();
    }

    void move_d(double _speed, double _distance, bool _mode) {

        //mode 0 = 走り始め
        //mode 1 = 走り終わり

        double _lowest_speed = 80;
        double a = ((_speed - _lowest_speed) / _distance);  //傾き

//        a = (_mode==0)?a:-a;
        motor.reset_counts();

        while (_distance > motor.distance_counts()) {
            double d_speed = (_mode==0)?a * motor.distance_counts() + _lowest_speed:
                      a * (_distance - motor.distance_counts())+ _lowest_speed;
            p_control(d_speed);
        }
        motor.reset_counts();


    }
};

#endif //NEWZUZUMOUSE_NEW_ZUZUMOUSE_H
