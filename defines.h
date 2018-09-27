//
// Created by 倉澤　一詩 on 2018/09/22.
//

#ifndef NEWZUZUMOUSE_DEFINES_H
#define NEWZUZUMOUSE_DEFINES_H

namespace ZUZU{
    enum MODE{
        COMMAND_MODE,
        LEFT_HAND_METHOD,
        TEST_MODE,
        TEST_MODE2,
        TEST_MODE3,
        TEST_MODE4
    };

    enum DIRECTION{
        LEFT_MACHINE,
        TURN_MACHINE,
        RIGHT_MACHINE
    };
}

//#define LEFT 0x50  //50
//#define LEFT 0x50  //60
//#define CENTER 0x60   //70
//#define RIGHT 0x80
#define WALL_TH 170
//      1000パルスで 109mm 前身
#define MM_TO_PULSE (1000/109)
#define ONE_BLOCK (180 * MM_TO_PULSE)
#define HALF_BLOCK (ONE_BLOCK / 2)
#define START_BLOCK 43.5 * MM_TO_PULSE
#define WIDTH 76.7
#define HALF_TURN (WIDTH * 3.141592 / 2 * MM_TO_PULSE)
#define LEFT_TURN (WIDTH * 3.141592 / 4 * MM_TO_PULSE)
#define RIGHT_TURN (WIDTH * 3.141592 / 4 * MM_TO_PULSE)
#define KP 0.10//仮置き

#endif //NEWZUZUMOUSE_DEFINES_H
