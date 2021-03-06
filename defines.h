/*!
* @file defines.h v1.0
* @Copyright © 2018 Kazushi Kurasawa
* @date 2018.09.22
*
* Released under the MIT license.
* see https://opensource.org/licenses/MIT
*/

#ifndef NEWZUZUMOUSE_DEFINES_H
#define NEWZUZUMOUSE_DEFINES_H

namespace ZUZU
{

    /**
     * @brief 操作のモード選択
     */
    enum MODE{
        COMMAND_MODE,
        KYUSIN_PARAM1,
        KYUSIN_PARAM2,
        KYUSIN_PARAM3,
        LEFT_HAND_WITHOUT_MAP,
        SERIAL_MODE,
        TEST_MODE,
        SENSOR_MODE,
    };


    /**
     * @fn 機体の旋回方向
     */
    enum DIRECTION{
        LEFT_MACHINE,
        TURN_MACHINE,
        RIGHT_MACHINE
    };

    /**
     * @brief 台形(加減速)制御の加速・減速
     */
    enum ACCEL{
        ACCELERATION,
        DECELERATION
    };
}


#define CENTER_TH 100    // 中央壁検知の閾値
#define WALL_TH 150      // 横壁検知の閾値
#define P_TH 140         // P制御の可否の横壁閾値
#define ONE_BLOCK 180.0  // 1ブロックの距離(mm)
#define HALF_BLOCK (ONE_BLOCK / 2.0) // 半ブロックの距離(mm)
#define START_BLOCK 44.2 // スタート地点へ前進する距離
#define WIDTH 77.7       // 車幅
#define KP 1.5           // P制御の左右モーターの差分に対する速度倍率
#define SINGLE_KP 1.5    // P制御の左右モーターの差分に対する速度倍率

#endif //NEWZUZUMOUSE_DEFINES_H
