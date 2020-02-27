#include "mslm_v3/switch.h"
#include "explore.h"

BusOut led(LED4,LED3,LED2,LED1);
Serial pc(USBTX, USBRX);
Switch sw2(p8,PullUp);
Switch select_sw3(p7,PullNone);
Switch plus_sw4(p6,PullUp);
Switch minus_sw5(p5,PullNone);

MotorManager motor(StepMotor(p28, p29, p27, true, p30), StepMotor(p23, p24, p25, false, p26), p18);
SensorManager sensor(p17, p20, p16);
PositionEstimator pe(motor._position,sensor);
Map3 map(4, 4);
Machine me(motor, sensor, pe, map);
Explore explore(me, map);


int main() {
    constexpr uint8_t wait_time = 1;
    wait(wait_time);
    ZUZU::MODE mode = ZUZU::COMMAND_MODE;
    uint8_t mode_i = 0b0000; // マイコンに付いているLEDを2進数トレラントで管理。1(点灯), 0(消灯)
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

            case ZUZU::KYUSIN_PARAM1:
                led = 0b1111;
                wait(wait_time);
                motor.motor_on();
                wait(wait_time);
                explore.kyusin(3, 3, 200, 70);
                motor.motor_off();

                mode = ZUZU::COMMAND_MODE;
                break;


                //////)//////////////////////////////////////////////////// 最初のバージョンの求心法モード2222222222

            case ZUZU::KYUSIN_PARAM2:
                led = 0b1111;
                wait(wait_time);
                motor.motor_on();
                wait(wait_time);
                explore.kyusin(3, 3, 650, 150);
                wait(wait_time);
                motor.motor_off();

                mode = ZUZU::COMMAND_MODE;
                break;

            case ZUZU::KYUSIN_PARAM3:
                led = 0b1111;
                wait(wait_time);
                motor.motor_on();
                wait(wait_time);
                explore.kyusin(8, 8, 600, 90);
                wait(wait_time);
                motor.motor_off();

                mode = ZUZU::COMMAND_MODE;
                break;



///////////( 2 )//////////////////////////////////////////////////// マップ無し左手(単純左手)法
            case ZUZU::LEFT_HAND_WITHOUT_MAP: //2
                led = 0b1111;
                wait(wait_time);
                motor.motor_on();
                wait(wait_time);
                explore.left_hand(7, 7, 400, 60);
                wait(wait_time);
                motor.motor_off();

                mode = ZUZU::COMMAND_MODE;
                break;

///////////( 3 )//////////////////////////////////////////////////// (シリアルモード)
            case ZUZU::SERIAL_MODE: //3
                led = 0b1111;
                serial_map(map);
                for (int i = 0; i < explore.log.size(); ++i) printf("X:%.3f Y:%.3f R:%.3f \r\n", explore.log.at(i).x / 180.0, explore.log.at(i).y / 180.0, explore.log.at(i).rad);

                mode = ZUZU::COMMAND_MODE;
                break;

///////////( 4 )//////////////////////////////////////////////////// (テストモード) 任意のコードを挿入
            case ZUZU::TEST_MODE:
                led = 0b1111;
                pe.set_position(90,90,0.0);
                serial_odometry(pe);

                motor.motor_on();
                wait(1);

                me.move(60, HALF_BLOCK);
                me.stop();

                mode = ZUZU::COMMAND_MODE;
                break;

///////////( 5 )//////////////////////////////////////////////////// (センサーチェックモード)
            case ZUZU::SENSOR_MODE:
                led = 0b1100;
                wait(1);
                // serial_sensor(sensor);
                while(1){
                   pc.printf("\r\b\r");
                   printf("%d %d %d diff=%d\n\r",
                          sensor.get_left_wall_distance(),
                          sensor.get_front_wall_distance(),
                          sensor.get_right_wall_distance(),
                          sensor.get_left_wall_distance()-sensor.get_right_wall_distance()
                   );
                }
                mode = ZUZU::COMMAND_MODE;

                break;
        }
    }
}
