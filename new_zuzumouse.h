//
// Created by 倉澤　一詩 on 2018/09/22.
//
#ifndef NEWZUZUMOUSE_NEW_ZUZUMOUSE_H
#define NEWZUZUMOUSE_NEW_ZUZUMOUSE_H

#include "defines.h"
#include "mbed.h"
#include "MSLMv3/Motor.h"
#include "MSLMv3/sensor.h"



class NewZuzumouse {

//public:   //センサ見たい時
private:

    MotorManager motor;
    DistanceSensor left_sensor, front_sensor, right_sensor;  //この値のまま使いたかったらpublicで書けよ！


public:

    NewZuzumouse() :
            motor(StepMotor(p28, p29, p27, true, p30), StepMotor(p23, p24, p25, false, p26), p18),
            left_sensor(p17), front_sensor(p20), right_sensor(p16) {

        motor.init(); //走る準備するよ！(初期値のフラグが0で割り込み開始)

    }


    inline void disp_odometry(){
        for(int i = 0; i < 30; i++){
            printf("%d00[ms]  左速度:%d[m/s]  右輪速度:%d[m/s]  左距離:%d[mm]  右距離:%d[mm]  速度:%d  変角:%.2f[rad], 総変角:%.2f[rad]  \n\r",
                    i,
                    motor.wathc_v[0][i],
                    motor.wathc_v[1][i],
                    motor.wathc_v[2][i],
                    motor.wathc_v[3][i],
                    motor.wathc_v[4][i],
                    motor.watch_rad[i],
                    motor.watch_total_rad[i]
            );
        }
    }


    inline bool is_opened_left_wall() {
        return left_sensor >= WALL_TH;
    }

    inline bool is_opened_center_wall() {
        return front_sensor >= WALL_TH;
    }

    inline bool is_opened_right_wall() {
        return right_sensor >= WALL_TH;
    }

    inline int get_front_wall_distance() {
        return front_sensor;
    }

    inline int get_left_wall_distance() {
        return left_sensor;
    }

    inline int get_right_wall_distance() {
        return right_sensor;
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
        motor.watch_count = 0;
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


//    void slalom_turn(double _speed, ZUZU::DIRECTION _direction){
//        if(_direction == ZUZU::LEFT_MACHINE) {
//            while (LEFT_TURN > motor.right_distance()) {
//                motor.set_left_speed(-_speed);
//                motor.set_right_speed(_speed);
//            }
//
//        }else if(_direction == ZUZU::TURN_MACHINE) {
//            while (HALF_TURN > motor.left_distance()) {
//                motor.set_left_speed(_speed);
//                motor.set_right_speed(-_speed);
//            }
//
//        }else if(_direction == ZUZU::RIGHT_MACHINE) {
//            while (RIGHT_TURN > motor.left_distance()) {
//                motor.set_left_speed(_speed);
//                motor.set_right_speed(-_speed);
//            }
//        }
//        stop();
//    }


    void stop() {
        motor.set_left_speed(0);
        motor.set_right_speed(0);
        motor.reset_counts();
    }


    void p_control(double _speed) {

        if (front_sensor < CENTER_TH) {
            motor.set_left_speed(_speed);
            motor.set_right_speed(_speed);

        } else if (left_sensor < WALL_TH && right_sensor < WALL_TH) {
            const int y_t = left_sensor - right_sensor;
            const int e_t = 0 - y_t;

            motor.set_left_speed(_speed + e_t * KP);
            motor.set_right_speed(_speed - e_t * KP);


        } else if (left_sensor < WALL_TH) {
            const int y_t = (left_sensor - 122);

            motor.set_left_speed(_speed - y_t * KP);
            motor.set_right_speed(_speed + y_t * KP);


        } else if (right_sensor < WALL_TH) {
            const int y_t = (104 - right_sensor);

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

        double _lowest_speed = 350;
        double a = ((_speed - _lowest_speed) / _distance);  //傾き

//        a = (_mode==0)?a:-a;
        motor.reset_counts();

        while (_distance > motor.counts()) {
            double d_speed = (_mode==0)?a * motor.counts() + _lowest_speed:
                      a * (_distance - motor.counts())+ _lowest_speed;
            p_control(d_speed);
        }
        motor.reset_counts();

    }
};

#endif //NEWZUZUMOUSE_NEW_ZUZUMOUSE_H
