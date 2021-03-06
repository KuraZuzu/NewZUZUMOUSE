/*!
* @file explore.h v1.0
* @Copyright © 2018 Kazushi Kurasawa
* @date 2018.11.16
*
* Released under the MIT license.
* see https://opensource.org/licenses/MIT
*/

#ifndef NEWZUZUMOUSE_EXPLORE_H
#define NEWZUZUMOUSE_EXPLORE_H


#include "machine.h"


class Explore {
public:

    machine& mouse;
    Map3& map;
    Vector<Position> log;

    Explore(machine& _mouse, Map3& _map): mouse(_mouse), map(_map){
    }

/* 求心手法(ゴール座標へ最短で向かう) */
    void kyusin(uint8_t _x, uint8_t _y, double_t _speed, double_t _turn_speed);


/* 左手法。マップは参照せずに、古典的な手法。 */
    void left_hand(uint8_t _x, uint8_t _y, double_t _speed, double_t _turn_speed);


/* 歩数情報を更新。更新した壁情報を反映。 */
    void make_walkmap(Map3 &map, uint8_t x, uint8_t y);

};

#endif //NEWZUZUMOUSE_EXPLORE_H
