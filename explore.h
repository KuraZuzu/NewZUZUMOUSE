#ifndef NEWZUZUMOUSE_EXPLORE_H
#define NEWZUZUMOUSE_EXPLORE_H

#include "new_zuzumouse.h"
//class NewZuzumouse;


class Explore {

private:
    NewZuzumouse& mouse;

public:
    Explore(NewZuzumouse& _mouse):mouse(_mouse){  //コンストラクタ

    }

    void left_hand();

    void center_left_hand();

    void metyakutya();

};

#endif //NEWZUZUMOUSE_EXPLORE_H
