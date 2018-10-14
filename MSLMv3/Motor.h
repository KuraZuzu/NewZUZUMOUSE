//
// Created by 倉澤　一詩 on 2018/09/22.
//
//#ifndef BLINKLED_MOTOR_H
//#define BLINKLED_MOTOR_H

#ifndef NEWZUZUMOUSE_MOTOR_H
#define NEWZUZUMOUSE_MOTOR_H

#include "mbed.h"

class StepMotor{

    DigitalOut _clock;
    DigitalOut _m3;
    DigitalOut _wise;
    DigitalOut _reset;
    int64_t _pulse_count;
    bool _forward_wise;

public:
    StepMotor(PinName clock, PinName reset, PinName wise, bool default_wise, PinName m3);

    void set_m3(bool m3);

    void step();

    void reset_count();

    void pulse_counter();

    int64_t counts();


    void set_wise(bool wise);

};


class MotorManager{

    AnalogOut RefOut;
    StepMotor _left_motor;
    StepMotor _right_motor;
    Ticker run;
    double_t _l_speed{0.0};
    double_t _r_speed{0.0};
    timestamp_t l_t{0};
    timestamp_t r_t{0};
    bool l_flag{false};
    bool r_flag{false};
    int32_t old_l_v;
    int32_t l_v;
    int32_t diff_l_v;
    int32_t old_r_v;
    int32_t r_v;
    int32_t diff_r_v;
    int l_count = 0;
    int r_count = 0;


public:

    MotorManager(StepMotor left, StepMotor right, PinName refout); //呼び出し

    void set_left_speed(double_t l_speed);

    void set_right_speed(double_t r_speed);

    int64_t  counts();

    int64_t left_distance();
    int64_t right_distance();

    void reset_counts();

    void loop();
    void init(timestamp_t tick_speed=50);
    void kill();

    void motor_on();
    void motor_off();


};

//#endif //BLINKLED_MOTOR_H
#endif //NEWZUZUMOUSE_MOTOR_H