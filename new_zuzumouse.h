//
// Created by 倉澤　一詩 on 2018/09/22.
//
#ifndef NEWZUZUMOUSE_NEW_ZUZUMOUSE_H
#define NEWZUZUMOUSE_NEW_ZUZUMOUSE_H

#include "defines.h"
#include "mbed.h"
#include "MSLMv3/Motor.h"
#include "MSLMv3/sensor.h"



class NewZuzumouse{

public:
private:

    MotorManager motor;
    DistanceSensor left_sensor, center_sensor, right_sensor;  //この値のまま使いたかったらpublicで書けよ！
    double diffirence_sensor = 0;


public:

    NewZuzumouse():
    motor(StepMotor (p28, p29, p27, true, p30), StepMotor (p23, p24, p25, false, p26), p18),
    left_sensor(p17), center_sensor(p20), right_sensor(p16){
        //コンストラクタ
        motor.init(); //レイジするよ！
    }


    inline bool is_opened_left_wall() {
        return left_sensor >= WALL_TH;
    }

    inline bool is_opened_center_wall() {
        return center_sensor >= WALL_TH;
    }

    inline bool is_opened_right_wall() {
        return right_sensor >= WALL_TH;
    }

//    ここから走るよ

    void move(double _speed, double _distance){
        while(_distance > motor.left_distance()){
            motor.set_left_speed(_speed);
            motor.set_right_speed(_speed);
        }
        stop();
    }


//    void move_p(double _speed, double _distance){
//        while(_distance > motor.left_distance()){
//            motor.set_left_speed(_speed);
//            motor.set_right_speed(_speed);
//        }
//        stop();
//    }



    void turn(double _speed, ZUZU::DIRECTION _direction){
        if(_direction == ZUZU::LEFT_MACHINE) {
            while (LEFT_TURN > motor.right_distance()) {
                motor.set_left_speed(-_speed);
                motor.set_right_speed(_speed);
            }

        }else if(_direction == ZUZU::TURN_MACHINE) {
            while (HALF_TURN > motor.left_distance()) {
                motor.set_left_speed(_speed);
                motor.set_right_speed(-_speed);
            }

        }else if(_direction == ZUZU::RIGHT_MACHINE) {
            while (RIGHT_TURN > motor.left_distance()) {
                motor.set_left_speed(_speed);
                motor.set_right_speed(-_speed);
            }
        }
        stop();



    }

    void stop(){
        motor.set_left_speed(0);
        motor.set_right_speed(0);
        motor.reset_counts();
    }



    void left_hand(){

        int _speed = 1000;
        move(1000, START_BLOCK + HALF_BLOCK);
        wait(0.5);

        while (true){
            if(is_opened_left_wall()){
                move(_speed, HALF_BLOCK);
                wait(0.5);
                turn(_speed, ZUZU::LEFT_MACHINE);
                wait(0.5);
                move(_speed, HALF_BLOCK);
                wait(0.5);
            }else if(is_opened_center_wall()){
                wait(0.5);
                move(_speed, ONE_BLOCK);
                wait(0.5);
            }else if(is_opened_right_wall()){
                move(_speed, HALF_BLOCK);
                wait(0.5);
                turn(_speed, ZUZU::RIGHT_MACHINE);
                wait(0.5);
                move(_speed, HALF_BLOCK);
                wait(0.5);
            }else{
                wait(0.5);
                turn(_speed, ZUZU::TURN_MACHINE);
                wait(0.5);
            }
        }

    }


//    void move_p(double _speed, double _distance){
//        diffirence_sensor = left_sensor.get_val() - right_sensor.get_val();
//        while(_distance > motor.left_distance()){
//            if (diffirence_sensor < 0) {
//                motor.set_left_speed(_speed);
//                motor.set_right_speed(_speed);
//            } else if (diffirence_sensor > 0) {
//                motor.set_left_speed(_speed);
//                motor.set_right_speed(_speed);
//            }else{
//                motor.set_left_speed(_speed);
//                motor.set_right_speed(_speed);
//            }
//        }
//        stop();
//    }



};


#endif //NEWZUZUMOUSE_NEW_ZUZUMOUSE_H
