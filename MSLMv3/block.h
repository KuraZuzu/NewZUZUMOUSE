//
// Created by 倉澤　一詩 on 2018/11/11.
//

#ifndef NEWZUZUMOUSE_BLOCK_H
#define NEWZUZUMOUSE_BLOCK_H


#include <sys/types.h>
#include "deftype.h"

class Block {

private:
                  //         NESW <- mask (North, East, South, West)//
    u_int8_t _b;  // 0b 0000 0000                                   //

public:

    void is_nothing_north_wall();
    void is_nothing_east_wall();
    void is_nothing_south_wall();
    void is_nothing_west_wall();

    bool is_opened_north_wall();
    bool is_opened_east_wall();
    bool is_opened_south_wall();
    bool is_opened_west_wall();

};


#endif //NEWZUZUMOUSE_BLOCK_H
