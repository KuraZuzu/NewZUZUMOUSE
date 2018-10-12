#include "new_zuzumouse.h"
#include "MSLMv3/switch.h"
#include "explore.h"

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
Serial pc(USBTX, USBRX);
NewZuzumouse me;
Explore test(me);
Switch sw2(p8,PullUp);
Switch sw3(p7,PullNone);
Switch sw4(p6,PullUp);
Switch sw5(p5,PullNone);


int main() {

    myled1.write(1);
    wait(1);
//    me.move(1000, 1000);

    ZUZU::MODE mode = ZUZU::COMMAND_MODE;

    while (true){

//        test.metyakutya();
//        printf("\n\r\n");
//        printf("LEFT:%d, CENTER:%d, RIGHT:%d",me.get_left_wall_distance(),me.get_front_wall_distance(),me.get_right_wall_distance());

        switch (mode){
            case ZUZU::COMMAND_MODE:
                if(sw2.update())
                    mode = ZUZU::TEST_MODE;
                else if(sw4.update())
                    mode = ZUZU::LEFT_HAND_METHOD;
                else if(sw3.update())
                    mode = ZUZU::CENTER_LEFT_METHOD;
//                else if(sw5.update())
//                    mode = ZUZU::
                break;

            case ZUZU::LEFT_HAND_METHOD:
                myled3 = 0;
                myled4 = 0;
                wait(1);
                test.left_hand();
                mode = ZUZU::COMMAND_MODE;

                break;

            case ZUZU::CENTER_LEFT_METHOD:
                myled3 = 0;
                myled4 = 0;
                wait(1);
                test.center_left_hand();
                mode = ZUZU::COMMAND_MODE;

                break;

            case ZUZU::CHUSYA:
                myled3 = 0;
                wait(1);

                break;


            case ZUZU::TEST_MODE:
                myled1 = 1;
                myled2 = 1;

//                {
//                    double turn_speed = 1000;
//                    wait(2);
//                    me.turn(turn_speed, ZUZU::RIGHT_MACHINE);
//
//                }

                pc.printf("\r\b\r");
                printf("%d %d %d diff=%d\n\r",
                       me.get_left_wall_distance(),
                       me.get_front_wall_distance(),
                       me.get_right_wall_distance(),
                       me.get_left_wall_distance()-me.get_right_wall_distance()
                       );

                mode = ZUZU::COMMAND_MODE;
                break;

            default:
                break;

        }

    }

}



