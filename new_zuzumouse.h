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
    MotorManager motor;
    DistanceSensor left_sensor, center_sensor, right_sensor;

public:

    NewZuzumouse():
    motor(StepMotor (p28, p29, p27, true, p30), StepMotor (p23, p24, p25, false, p26), p18),
    left_sensor(p17), center_sensor(p20), right_sensor(p16)
    {
        //コンストラクタ
        motor.init();
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

    void move(){

    }


};


#endif //NEWZUZUMOUSE_NEW_ZUZUMOUSE_H
