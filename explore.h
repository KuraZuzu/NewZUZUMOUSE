#ifndef NEWZUZUMOUSE_EXPLORE_H
#define NEWZUZUMOUSE_EXPLORE_H

#include "Machine.h"
#include "mslm_v3/PositionEstimator.h"
#include "mslm_v3/map3.h"
#include "mslm_v3/vector.h"
#include "mslm_v3/algorithm.h"
//class NewZuzumouse;


class Explore {
public:
    Machine& mouse;
    Map3& map;
    Vector<Position> log;

    Explore(Machine& _mouse, Map3& _map):mouse(_mouse), map(_map){  //コンストラクタ

    }

    void left_hand(){};

    void center_left_hand(){};

    void test_center_left_hand(){};

    void metyakutya(){};

    void marking_exprole();



};

#endif //NEWZUZUMOUSE_EXPLORE_H
