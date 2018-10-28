#include "new_zuzumouse.h"
#include "MSLMv3/switch.h"
#include "explore.h"

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
BusOut led(LED4,LED3,LED2,LED1);
Serial pc(USBTX, USBRX);
NewZuzumouse me;
MotorManager motor(StepMotor(p28, p29, p27, true, p30), StepMotor(p23, p24, p25, false, p26), p18);
Explore test(me);
Switch sw2(p8,PullUp);
Switch select_sw3(p7,PullNone);
Switch plus_sw4(p6,PullUp);
Switch minus_sw5(p5,PullNone);


int main() {

    myled1.write(1);
    wait(1);

//    me.move(1000, 1000);


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

            case ZUZU::CHUSYA:
                myled3 = 0;
                wait(1);

                break;


            case ZUZU::TEST_MODE:
                wait(1);
                myled1 = 1;
//                motor.l_v_log.push_back(123);
                motor.motor_on();
                motor.watch_count = 0;
//                me.move(180, ONE_BLOCK*5);
//                me.turn(180, ZUZU::TURN_MACHINE);
                me.test_move(100, 200, ONE_BLOCK * 2);

                me.stop();

                motor.motor_off();

                me.disp_odometry();


//                for(int i = 0; i < 100; i++) {
//                    printf("l_v:%d  r_v:%d  moved_l_distance:%d   moved_r_distance:%d  count:%d \n\r",
//                            motor.disp_l_v(),
//                            motor.disp_r_v(),
//                            motor.disp_moved_l_pulse(),
//                            motor.disp_moved_r_pulse(),
//                            i
//                    );
//                }

//
//                printf("log_size = %d \r\n",motor.l_v_log.size());
//                for(int i = 0; i < motor.l_v_log.size(); i++) {
//                    printf("l_v:%d  r_v:%d  moved_l_distance:%d  moved_r_distance%d %d\n\r",
//                           motor.l_v_log.at(i),
//                           motor.wathc_v[1][i],
//                           motor.wathc_v[2][i],
//                           motor.wathc_v[3][i],
//                           motor.watch_count
//                    );
//                }

//                for (int i = 0; i < 100; i++) {
//                    printf("l_v:%d  r_v:%d  moved_l_distance:%d  moved_r_distance%d  %d\n\r",
//                           motor.wathc_v[0][i],
//                           motor.wathc_v[1][i],
//                           motor.wathc_v[2][i],
//                           motor.wathc_v[3][i],
//                           motor.watch_count
//                    );
//                }


//                pc.printf("\r\b\r");
//                printf("%d %d %d diff=%d\n\r",
//                       me.get_left_wall_distance(),
//                       me.get_front_wall_distance(),
//                       me.get_right_wall_distance(),
//                       me.get_left_wall_distance()-me.get_right_wall_distance()
//                       );

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


