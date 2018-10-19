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

//    _l_speed = 180 * 55 / /l_speed;  //180mm進んで欲しい時に55回、回ったらモータが起動してほしい
//    _l_speed = 24 * 88 / l_speed;  //タイヤ全周88mmで400パルス欲しい(立ち上がりと立ち下がり分) 50usの時
//    _l_speed = 125 * 88 / l_speed; //10usの時
    _l_speed = 50 * 88 / l_speed;

}

void MotorManager::set_right_speed(double_t r_speed) {

    r_flag = static_cast<bool>(r_speed);
    if(r_speed < 0.0){
        r_speed = -r_speed;
        _right_motor.set_wise(false);
    } else{
        _right_motor.set_wise(true);
    }

//    _r_speed = 25 * 88 / r_speed;  //25回　タイヤの全周88mm　1(結果2)パルスで1.8度　一周400パルス 50us
//    _r_speed = 125 * 88 / r_speed;  //1 0us時
    _r_speed = 50 * 88 / r_speed;   //計算結果の参考として、set_left_spped(180)とした時には 24となる

}


int64_t MotorManager::left_distance() {
    return _left_motor.counts();
}

int64_t MotorManager::right_distance() {

    return _right_motor.counts();
}

void MotorManager::loop() {

    if ((_l_speed <= l_t) && l_flag) {
        _left_motor.step();   //一回通過で1パルス(立ち上がりor立ち下がりのみなので動いてない)
        l_t = 0;
        l_pulse++;

    } else {
        l_t++;
    }


    if((_r_speed <= r_t) && r_flag) {
        _right_motor.step();
        r_t = 0;
        r_pulse++;

    } else{
        r_t++;
    }


    v_count++;  //サンプリングレートのためのカウント


    if (v_count == 100000) {  // 10us * 100000 = 100000us のサンプリングレートとなる (0.1s となる)

        moved_l_pulse = l_pulse - old_l_pulse;  //100000us1ごとに、どれくらいのパルスが入ったか
        moved_r_pulse = r_pulse - old_r_pulse;

        old_l_pulse = l_pulse;
        old_r_pulse = r_pulse;

        //タイヤのスペックは、直径28.0mm、モーターが1セットのパルス(2pulse)で1.8度回転

        l_v = (moved_l_pulse / 2) * 28 * 3.14159265 / 200 * 100000;  //200は,(360/1.8)であり、モーター2パルスの1回転に対する割合
        r_v = (moved_r_pulse / 2) * 28 * 3.14159265 / 200 * 100000;  //これで、100000us = 0.1s毎に、その時の mm/s が分かる

        moved_l_distance += l_v / 10;
        moved_r_distance += r_v /10;   //0.1s毎に進んだ距離を足している

        v_count = 0;
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
