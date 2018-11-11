//
// Created by 倉澤　一詩 on 2018/09/22.
//
#include "Motor.h"

#define pi 3.14159265

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

int64_t StepMotor::pulse_counts(){
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
        _left_motor(left), _right_motor(right), RefOut(refout), l_v_log(){

    v_count = 0;
    odometry_watch_count = 0;
    RefOut.write(static_cast<float>(0.05 / 3.3));
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
    return _left_motor.pulse_counts();
}

int64_t MotorManager::right_distance() {
    return _right_motor.pulse_counts();
}

void MotorManager::loop() {

//    if (v_count == 0)
//        odometry_watch_count = 0;

    if ((_l_speed <= l_t) && l_flag) {
        _left_motor.step();   //一回通過で1パルス(立ち上がりor立ち下がりのみなので、1パルスのみでは動いてない)
        l_t = 0;
        l_pulse++;

    } else {
        l_t++;
    }


    if ((_r_speed <= r_t) && r_flag) {
        _right_motor.step();
        r_t = 0;
        r_pulse++;

    } else{
        r_t++;
    }


    v_count++;  //サンプリングレートのためのカウント

    if (v_count == 400) {  // 25us * 400 = 10000us のサンプリングレートとなる (0.01s となる)

        //10000usごとに、どれくらいのパルスが入ったか
        delta_l_pulse = l_pulse - old_l_pulse;
        delta_r_pulse = r_pulse - old_r_pulse;


        if (_left_motor.pulse_counts() < 0)     //もし、モータが逆転していたら、pulse_counts の値は負の値となるので、
            delta_l_pulse = -delta_l_pulse;     //パルスの変化量(delta_pulse)の値が負の値となる

        if (_right_motor.pulse_counts() < 0)
            delta_r_pulse = -delta_r_pulse;


        old_l_pulse = l_pulse;
        old_r_pulse = r_pulse;

        //タイヤのスペックは、直径28.0mm、モーターが1セットのパルス(2pulse)で0.9度回転

        delta_l_distance = (delta_l_pulse) * 28 * pi / 400 / 2;   //　"/ 400"は,(360/0.9)であり、モーター2パルスの1回転に対する割合が "/ 2"  (0.9 or 1.8  ?)
        delta_r_distance = (delta_r_pulse) * 28 * pi / 400 / 2;   //　10ms = 0.01sごとの変化した距離(mm)がわかる.

        v = ( delta_l_distance + delta_r_distance ) * 100 / 2;

        moved_rad += atan2(delta_r_distance - delta_l_distance, 77.7); //WIDTH 77.7  //最初の引数は (角速度)ω * (サンプリングレート)Δt をかけた結果と同様であり、オドメトリのための角度計算で用いる

        //オドメトリの角度は x軸に対しての rad であり、ロボットの初期角度は 90[deg] = 1/2 π　であるので、その差分で計算している.
        //最後の "/ 100"は、走った時間 t が 0.01s なので、秒速である v に対しての係数.
        moved_x_distance += v * cos(3.14159265 / 2 + moved_rad) / 100;  //x軸
        moved_y_distance += v * sin(3.14159265 / 2 + moved_rad) / 100;  //y軸

//        if(odometry_watch_count < 50) {
//            printf("%d \r\n", l_v_log.size()/);
//            l_v_log.push_back(delta_l_distance);
//        }

//        odometry_watch_count = (odometry_watch_count<99)?odometry_watch_count+1:odometry_watch_count;


        //ここの条件分岐がおかしいよー
        if (pi * 1/4 >= moved_rad && moved_rad < pi * 3/4)
            current_machine_direction = 0;  //北

        else if (pi * 3/4 >= moved_rad && moved_rad < pi * 5/4)
            current_machine_direction = 1;  //東

        else if (pi * 5/4 >= moved_rad && moved_rad < pi * 7/4)
            current_machine_direction = 2;  //南

        else
            current_machine_direction = 3;  //西


        odometry_watch_count++;
        v_count = 0;
    }
}

char MotorManager::get_current_machine_direction() {
    return current_machine_direction;
}

void MotorManager::set_coordinates(float x_coordinates, float y_coordinates) {
    moved_x_distance = x_coordinates;
    moved_y_distance = y_coordinates;
}

void MotorManager::set_odometry_watch_count(unsigned int odometry_count) {
    odometry_watch_count = odometry_count;
}

unsigned int MotorManager::get_odometry_watch_count() {
    return odometry_watch_count;
}

float MotorManager::get_v() {
    return v;
}

float MotorManager::get_moved_x() {
    return moved_x_distance;
}

float MotorManager::get_moved_y() {
    return moved_y_distance;
}

float MotorManager::get_moved_rad() {
    return 3.14159265 / 2 + moved_rad;
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

int64_t MotorManager::distance_counts() {
    return (left_distance() + right_distance()) / 2;
}
