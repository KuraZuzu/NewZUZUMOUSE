#ifndef NEWZUZUMOUSE_EXPLORE_H
#define NEWZUZUMOUSE_EXPLORE_H


#include "Machine.h"
#include "mslm_v3/PositionEstimator.h"
#include "mslm_v3/map3.h"
#include "mslm_v3/vector.h"
#include "mslm_v3/Point.h"


class Explore {
public:

    Machine& mouse;
    Map3& map;
    Vector<Position> log;

    Explore(Machine& _mouse, Map3& _map):mouse(_mouse), map(_map){  //コンストラクタ
    }

    void kyusin(uint8_t _x, uint8_t _y, double_t _speed, double_t _turn_speed); // ゴール座標に向かって制御する。マップを参照。

    void left_hand(uint8_t _x, uint8_t _y, double_t _speed, double_t _turn_speed); // 古典的な左手方で走る。マップは参照しない。

    void make_walkmap(Map3 &map, uint8_t x, uint8_t y); // 歩数情報を更新。更新した壁情報を反映。

};

#endif //NEWZUZUMOUSE_EXPLORE_H
