#include "new_zuzumouse.h"
#include "MSLMv3/switch.h"

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
Serial pc(USBTX, USBRX);

NewZuzumouse me;
Switch sw2(p8,PullUp);
Switch sw3(p7,PullNone);
Switch sw4(p6,PullUp);
Switch sw5(p5,PullNone);


int main() {

    wait(1);

    myled1.write(1);
    wait(0.5);
    myled2.write(1);
    wait(0.5);
    myled3.write(1);
    wait(0.5);
    myled4.write(1);
    wait(0.5);

    ZUZU::MODE mode = ZUZU::COMMAND_MODE;

    while (true){
        switch (mode){
            case ZUZU::COMMAND_MODE:
                if(sw2.update())
                    mode = ZUZU::TEST_MODE;
                else if(sw4.update())
                    mode = ZUZU::LEFT_HAND_METHOD;

                break;

            case ZUZU::LEFT_HAND_METHOD:



                break;

            case ZUZU::TEST_MODE:
                myled1 = 0;
                myled2 = 0;

                mode = ZUZU::COMMAND_MODE;
                break;

            default:
                break;

        }
    }
}