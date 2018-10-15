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
        CENTER_LEFT_METHOD,
        D_MODE,
        CHUSYA
    };

    enum DIRECTION{
        LEFT_MACHINE,
        TURN_MACHINE,
        RIGHT_MACHINE
    };
}

//#define LEFT 0x50  //50
#define LEFT 0x50  //60
#define CENTER 0x60   //70
#define RIGHT 0x80
#define CENTER_TH 120
#define WALL_TH 170
//      元は1000パルスで 109mm 前身
#define MM_TO_PULSE (2000/218)
#define ONE_BLOCK (180 * MM_TO_PULSE)
#define HALF_BLOCK (ONE_BLOCK / 2)
#define START_BLOCK 44.2 * MM_TO_PULSE
#define WIDTH 77.7   //変えて76.7　大元は77.7 そして 78.0
#define HALF_TURN (WIDTH * 3.141592 / 2 * MM_TO_PULSE)
#define LEFT_TURN (WIDTH * 3.141592 / 4 * MM_TO_PULSE)
#define RIGHT_TURN (WIDTH * 3.141592 / 4 * MM_TO_PULSE)
#define KP 0.5  //15.0
#endif //NEWZUZUMOUSE_DEFINES_H
