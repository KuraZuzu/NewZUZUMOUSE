#ifndef NEWZUZUMOUSE_EXPLORE_H
#define NEWZUZUMOUSE_EXPLORE_H

#include "new_zuzumouse.h"
#include "mslm_v3/PositionEstimator.h"
#include "mslm_v3/map3.h"
//class NewZuzumouse;


class Explore {
public:
    NewZuzumouse& mouse;
    PositionEstimator& pe;
    Map3& map;

    Explore(NewZuzumouse& _mouse, PositionEstimator& _pe, Map3& _map):mouse(_mouse), pe(_pe), map(_map){  //コンストラクタ

    }

    void left_hand();

    void center_left_hand();

    void test_center_left_hand();

    void metyakutya();

};

#endif //NEWZUZUMOUSE_EXPLORE_H
