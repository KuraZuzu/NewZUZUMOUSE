#include "new_zuzumouse.h"
#include "mslm_v3/switch.h"
#include "explore.h"
#include "mslm_v3/PositionEstimator.h"
#include "mslm_v3/map3.h"

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
PositionEstimator pe(motor._position);
NewZuzumouse me(motor);
Map3 map(16, 16);
Block block;
Explore test(me, pe, map);



int main() {

    myled1.write(1);
    wait(1);


    ZUZU::MODE mode = ZUZU::COMMAND_MODE;
    uint8_t mode_i = 0;
    while (true) {

//        test.metyakutya();
//        printf("\n\r\n");
//        printf("LEFT:%d, CENTER:%d, RIGHT:%d",me.get_left_wall_distance(),me.get_front_wall_distance(),me.get_right_wall_distance());

        switch (mode) {
            case ZUZU::COMMAND_MODE:
                if (select_sw3.update())
                    mode = (ZUZU::MODE) mode_i;
                else if (plus_sw4.update())
                    ++mode_i;
                else if (minus_sw5.update())
                    --mode_i;

                led = mode_i;
                break;

            case ZUZU::LEFT_HAND_METHOD:
                myled3 = 0;
                myled4 = 0;
                wait(1);
                motor.motor_on();
                test.left_hand();
                motor.motor_off();
                mode = ZUZU::COMMAND_MODE;

                break;

            case ZUZU::CENTER_LEFT_METHOD:
                myled3 = 0;
                myled4 = 0;
                wait(1);
                motor.motor_on();
                test.center_left_hand();
                motor.motor_off();
                mode = ZUZU::COMMAND_MODE;

                break;


            case ZUZU::SENSOR_MODE:
                myled3 = 0;
                myled4 = 0;
                wait(1);
                pc.printf("\r\b\r");
                printf("%d %d %d diff=%d\n\r",
                       me.get_left_wall_distance(),
                       me.get_front_wall_distance(),
                       me.get_right_wall_distance(),
                       me.get_left_wall_distance()-me.get_right_wall_distance()
                       );


                break;


            case ZUZU::TEST_CENTER_LEFT_METHOD:
                myled3 = 0;
                myled4 = 0;
                wait(1);
                motor.motor_on();
                test.test_center_left_hand();
                motor.motor_off();
                mode = ZUZU::COMMAND_MODE;

                break;


            case ZUZU::TEST_MODE:
                wait(1);
                myled1 = 1;
//                motor.l_v_log.push_back(123);

//                pe.set_position(90,90,0.0);
                motor.motor_on();
                me.move_p(150, 180.0);
                me.turn(150,ZUZU::RIGHT_MACHINE);
                me.move_p(150, 180);
                printf("X=%d Y=%d \r\n",pe.get_map_position().x, pe.get_map_position().y);
//                printf("X=%.3f Y=%.3f Theta=%.3f \r\n",pe.get_position().x, pe.get_position().y, pe.get_position().rad*(180.0/PI));

                me.stop();

                mode = ZUZU::COMMAND_MODE;
                break;

            case ZUZU::D_MODE:

                wait(1);
                motor.motor_on();
                me.move(1000, HALF_BLOCK);
//                me.move(3000, ONE_BLOCK);
                me.stop();
                wait(10);
                me.move_d(1000, HALF_BLOCK, 1);
                me.stop();
                wait(1);
                motor.motor_off();

                mode = ZUZU::COMMAND_MODE;
                break;

            default:
                break;
        }
    }

}


