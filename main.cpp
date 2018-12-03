#include "new_zuzumouse.h"
#include "Machine.h"
#include "mslm_v3/switch.h"
#include "explore.h"
#include "mslm_v3/PositionEstimator.h"
#include "mslm_v3/map3.h"
#include "mslm_v3/SensorManager.h"
#include "serial_utility.h"
#include "mbed.h"

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
BusOut led(LED4,LED3,LED2,LED1);
Serial pc(USBTX, USBRX);
Switch sw2(p8,PullUp);
Switch select_sw3(p7,PullNone);
Switch plus_sw4(p6,PullUp);
Switch minus_sw5(p5,PullNone);


MotorManager motor(StepMotor(p28, p29, p27, true, p30), StepMotor(p23, p24, p25, false, p26), p18);
SensorManager sensor(p17, p20, p16);
PositionEstimator pe(motor._position,sensor);
Map3 map(16, 16);
Machine me(motor, sensor, pe, map);
Block block;
Explore test(me, map);


int main() {
    uint8_t wait_tima = 1;
    myled1 = 1;
    wait(wait_tima);

    ZUZU::MODE mode = ZUZU::COMMAND_MODE;
    uint8_t mode_i = 0b0000;
    while (true) {

        switch (mode) {

///////////( 0 )//////////////////////////////////////////////////// コマンドモード
            case ZUZU::COMMAND_MODE:
                if (select_sw3.update()){
                    mode = (ZUZU::MODE) mode_i;

                } else if (plus_sw4.update()){

                    if(mode_i < 0b1111) ++mode_i;
                    else mode_i = 0b0000;

                } else if (minus_sw5.update()){

                    if(0 < mode_i) --mode_i;
                    else mode_i = 0b1111;

                }

                led = mode_i;
                break;

///////////( 1 )//////////////////////////////////////////////////// 最初のバージョンの求心法モード

            case ZUZU::ORIGINAL_KYUSIN:
                myled1 = 1;
                myled2 = 1;
                myled3 = 1;
                myled4 = 1;
                wait(wait_tima);
                motor.motor_on();
                wait(wait_tima);
                test.original_kyusin(8, 8, 200, 70);
                wait(wait_tima);
                motor.motor_off();

                mode = ZUZU::COMMAND_MODE;
                break;


                //////)//////////////////////////////////////////////////// 最初のバージョンの求心法モード2222222222

            case ZUZU::ORIGINAL_KYUSIN_2:
                myled1 = 1;
                myled2 = 1;
                myled3 = 1;
                myled4 = 1;
                wait(wait_tima);
                motor.motor_on();
                wait(wait_tima);
                test.original_kyusin(8, 8, 350, 85);
                wait(wait_tima);
                motor.motor_off();

                mode = ZUZU::COMMAND_MODE;
                break;

            case ZUZU::ORIGINAL_KYUSIN_3:
                myled1 = 1;
                myled2 = 1;
                myled3 = 1;
                myled4 = 1;
                wait(wait_tima);
                motor.motor_on();
                wait(wait_tima);
                test.original_kyusin(8, 8, 600, 90);
                wait(wait_tima);
                motor.motor_off();

                mode = ZUZU::COMMAND_MODE;
                break;

//                ///////////( 1.5 )//////////////////////////////////////////////////// 最初のバージョンの求心法モード
//
//            case ZUZU::ORIGINAL_KYUSIN_NEW_SPEED:
//
//            {
//                int i;
//                uint8_t j;
//
//
//
//                if (select_sw3.update())
//                    i += 1;
//                    j += 50;
//
//                } else if (plus_sw4.update()) {
//
//                    i -= 1;
//                    j -= 50;
//
//                } else if (minus_sw5.update()) {
//
//                    if (0 < mode_i) --mode_i;
//                    else mode_i = 0b1111;
//
//                }
//
//                led = mode_i;
//
//
//                wait(wait_tima);
//                motor.motor_on();
//                wait(wait_tima);
//                test.original_kyusin();
//                wait(wait_tima);
//                motor.motor_off();
//            }
//                mode = ZUZU::COMMAND_MODE;
//                break;
//





///////////( 2 )//////////////////////////////////////////////////// もはや意味不明な求心法モード
            case ZUZU::KYUSIN:
                myled1 = 1;
                myled2 = 1;
                myled3 = 1;
                myled4 = 1;
                wait(wait_tima);
                motor.motor_on();
                wait(wait_tima);
                test.kyusin();
                wait(wait_tima);
                motor.motor_off();

                mode = ZUZU::COMMAND_MODE;
                break;

///////////( 3 )//////////////////////////////////////////////////// マップ無し左手(単純左手)法
            case ZUZU::LEFT_HAND_WITHOUT_MAP: //2
                myled1 = 1;
                myled2 = 1;
                myled3 = 1;
                myled4 = 1;
                wait(wait_tima);
                motor.motor_on();
                wait(wait_tima);
                test.marking_exprole();
                wait(wait_tima);
                motor.motor_off();

                mode = ZUZU::COMMAND_MODE;
                break;

///////////( 4 )//////////////////////////////////////////////////// (シリアルモード)
            case ZUZU::SERIAL_MODE: //3
                myled1 = 1;
                myled2 = 1;
                myled3 = 1;
                myled4 = 1;
                serial_map(map);
                for (int i = 0; i < test.log.size(); ++i) printf("X:%.3f Y:%.3f R:%.3f \r\n", test.log.at(i).x/180.0, test.log.at(i).y/180.0, test.log.at(i).rad);

                mode = ZUZU::COMMAND_MODE;
                break;

///////////( 5 )//////////////////////////////////////////////////// (テストモード)
            case ZUZU::TEST_MODE:
                myled1 = 1;
                myled2 = 1;
                myled3 = 1;
                myled4 = 1;
                pe.set_position(90,90,0.0);
                serial_odometry(pe);

                motor.motor_on();
                wait(1);

////                test.mouse.turn(60, ZUZU::TURN_MACHINE);
////                wait(1);
////                test.mouse.turn(60, ZUZU::TURN_MACHINE);
////                wait(1);
////                test.mouse.turn(60, ZUZU::TURN_MACHINE);
////                wait(1);
////                test.mouse.turn(60, ZUZU::TURN_MACHINE);
////                wait(1);
//                test.mouse.old_turn(60, ZUZU::TURN_MACHINE);
//                wait(1);
//                test.mouse.old_turn(60, ZUZU::TURN_MACHINE);
//                wait(1);
//                test.mouse.old_turn(60, ZUZU::TURN_MACHINE);
//                wait(1);
//                test.mouse.old_turn(60, ZUZU::TURN_MACHINE);
//                wait(1);
//                motor.motor_off();
                me.move(60, HALF_BLOCK);
                me.stop();

                mode = ZUZU::COMMAND_MODE;
                break;

///////////( 6 )//////////////////////////////////////////////////// (センサーチェックモード)
            case ZUZU::SENSOR_MODE:
                myled3 = 0;
                myled4 = 0;
                wait(1);
                serial_sensor(sensor);
//                pc.printf("\r\b\r");
//                printf("%d %d %d diff=%d\n\r",
//                       sensor.get_left_wall_distance(),
//                       sensor.get_front_wall_distance(),
//                       sensor.get_right_wall_distance(),
//                       sensor.get_left_wall_distance()-sensor.get_right_wall_distance()
//                );
                mode = ZUZU::COMMAND_MODE;

                break;
        }
    }
}



