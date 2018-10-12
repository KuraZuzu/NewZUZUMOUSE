#ifndef NEWZUZUMOUSE_EXPLORE_H
#define NEWZUZUMOUSE_EXPLORE_H

#include "new_zuzumouse.h"

class Explore {
    NewZuzumouse& mouse;

public:
    Explore(NewZuzumouse& _mouse):mouse(_mouse){

    }

    void left_hand();

    void center_left_hand();

    void metyakutya();

//    void chusya();

};

#endif //NEWZUZUMOUSE_EXPLORE_H
