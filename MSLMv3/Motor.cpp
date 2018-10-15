//
// Created by 倉澤　一詩 on 2018/09/22.
//
#include "Motor.h"
//コンストラクタ
StepMotor::StepMotor(PinName clock, PinName reset, PinName wise, bool default_wise, PinName m3):
_clock(clock, false), _m3(m3, true), _wise(wise, default_wise), _reset(reset, false)
{
    _forward_wise = default_wise;
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

void StepMotor::set_m3(bool m3) {
    _m3.write(m3);
}


void StepMotor::set_wise(bool wise) {

    if(wise) {
        _wise = _forward_wise;
    }else{
        _wise = !_forward_wise;
    }

}

void StepMotor::reset_count() {
    _pulse_count = 0;
}

MotorManager::MotorManager(StepMotor left, StepMotor right, PinName refout) :
        _left_motor(left), _right_motor(right), RefOut(refout) {

    RefOut.write(static_cast<float>(0.07 / 3.3));
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

//    _l_speed = 20000.0 / l_speed;
//    _l_speed = 180 * 55 / /l_speed;  //180mm進んで欲しい時に55回、回ったらモータが起動してほしい
    _l_speed = 24 * 88 / l_speed;  //タイヤ全周88mmで400パルス欲しい(立ち上がりと立ち下がり分)
}

void MotorManager::set_right_speed(double_t r_speed) {

    r_flag = static_cast<bool>(r_speed);
    if(r_speed < 0.0){
        r_speed = -r_speed;
        _right_motor.set_wise(false);
    } else{
        _right_motor.set_wise(true);
    }

//    _r_speed = 20000.0 / r_speed;
//    _r_speed = 180 * 55 / r_speed;
    _r_speed = 24 * 88 / r_speed;
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

//        l_count++; // サンプリングレート
//        if(l_count == 10){
//            old_l_v = l_v;
//            l_v = l_t / 500000000 / 10 ;    //50msを10回毎に取得している
//            diff_l_v = l_v - old_l_v;
//            l_count = 0;
//        }

    } else {
        l_t++;
    }


    if((_r_speed < r_t) && r_flag) {
        _right_motor.step();
        r_t = 0;

//        r_count++;//サンプリングレート
//        if(r_count == 10){
//            old_r_v = r_v;
//            r_v = r_count / 50000000 / 10 ;
//            diff_r_v = r_v - old_r_v;
//            r_count = 0;
//        }

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

void MotorManager::reset_counts() {
    _left_motor.reset_count();
    _right_motor.reset_count();
}

void MotorManager::motor_on() {
    _left_motor.set_m3(false);
    _right_motor.set_m3(false);
}

void MotorManager::motor_off() {
    _left_motor.set_m3(true);
    _right_motor.set_m3(true);
}

int64_t MotorManager::counts() {
    return (left_distance() + right_distance()) / 2;
}
