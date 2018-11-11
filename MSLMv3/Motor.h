//
// Created by 倉澤　一詩 on 2018/09/22.
//
//#ifndef BLINKLED_MOTOR_H
//#define BLINKLED_MOTOR_H

#ifndef NEWZUZUMOUSE_MOTOR_H
#define NEWZUZUMOUSE_MOTOR_H

#include "mbed.h"
#include "vector.h"

class StepMotor{

private:
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

    int64_t pulse_counts();

    void set_wise(bool wise);

};



class MotorManager{


private:

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


    int32_t old_l_pulse;
    int32_t old_r_pulse;
    int32_t delta_l_pulse;
    int32_t delta_r_pulse;
    int32_t l_pulse;
    int32_t r_pulse;
    float delta_l_distance;
    float delta_r_distance;
    float v;
    float moved_x_distance;
    float moved_y_distance;
    float moved_rad;
    unsigned int odometry_watch_count;
    char current_machine_direction = 0;  //0:北  1:東  2:南  3:西  4:南
    Vector<int> l_v_log;
    int v_count;

public:

    MotorManager(StepMotor left, StepMotor right, PinName refout); //呼び出し

    void set_left_speed(double_t l_speed);
    void set_right_speed(double_t r_speed);
    void set_coordinates(float x_coordinates, float y_coordinates);
    void set_odometry_watch_count(unsigned int odometry_count);

    char get_current_machine_direction();
    float get_v();
    float get_moved_x();
    float get_moved_y();
    float get_moved_rad();
    unsigned int get_odometry_watch_count();


    int64_t  distance_counts();

    int64_t left_distance();
    int64_t right_distance();

    void reset_counts();

    void loop();
    void init(timestamp_t tick_speed=25);  //元は50us　次に10us(10usは早すぎて無理だった)
    void kill();

    void motor_on();
    void motor_off();

};

#endif //NEWZUZUMOUSE_MOTOR_H