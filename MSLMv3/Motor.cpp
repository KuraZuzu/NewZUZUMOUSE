//
// Created by 倉澤　一詩 on 2018/09/22.
//
#include "Motor.h"
//コンストラクタ
StepMotor::StepMotor(PinName clock, PinName reset, PinName wise, bool default_wise, PinName m3):
_clock(clock, false), _m3(m3, false), _wise(wise, default_wise), _reset(reset, false)
{
    _forward_wise = default_wise;
    _m3.write(0);
    _pulse_count = 0;
}

void StepMotor::step(){
    _clock = !_clock;
    pulse_counter();
}

void StepMotor::pulse_counter(){
    if(_forward_wise == _wise.read())
        _pulse_count++;
    else
        _pulse_count--;
}

int64_t StepMotor::counts(){
    return _pulse_count;
}

void StepMotor::set_wise(bool wise) {

    if(wise) {
        _wise = _forward_wise;
    }else{
        _wise = !_forward_wise;
    }

}

MotorManager::MotorManager(StepMotor left, StepMotor right, PinName refout) :
        _left_motor(left), _right_motor(right), RefOut(refout)
{
    RefOut.write(static_cast<float>(0.06 / 3.3));
    l_flag = false;
    r_flag = false;
}

void MotorManager::set_left_speed(double_t l_speed) {

    l_flag = static_cast<bool>(l_speed);
    if(l_speed < 0.0){
        l_speed = -l_speed;
        _left_motor.set_wise(false);
    } else{
        _left_motor.set_wise(true);
    }

    _l_speed = 20000.0 / l_speed;
}

void MotorManager::set_right_speed(double_t r_speed) {

    r_flag = static_cast<bool>(r_speed);
    if(r_speed < 0.0){
        r_speed = -r_speed;
        _right_motor.set_wise(false);
    } else{
        _right_motor.set_wise(true);
    }

    _r_speed = 20000.0 / r_speed;
}

int64_t MotorManager::left_distance() {
    return _left_motor.counts();
}

int64_t MotorManager::right_distance() {

    return _right_motor.counts();
}

void MotorManager::loop() {

    if ((_l_speed < l_t) && l_flag) {
        _left_motor.step();
        l_t = 0;
    } else {
        l_t++;
    }


    if((_r_speed < r_t) && r_flag) {
        _right_motor.step();
        r_t = 0;
    } else{
        r_t++;
    }

}

void MotorManager::init(timestamp_t tick_speed) {
    run.attach_us(this, &MotorManager::loop, tick_speed);
}

void MotorManager::kill() {
    run.detach();
}
