//
// Created by 倉澤　一詩 on 2018/11/11.
//

#ifndef NEWZUZUMOUSE_BLOCK_H
#define NEWZUZUMOUSE_BLOCK_H


#include "deftype.h"

class Block {

private:
                  //         NESW <- mask (North, East, South, West)//
    uint8_t _b;  // 0b 0000 0000                                   //

public:

    void is_barriered_north_wall();
    void is_barriered_east_wall();
    void is_barriered_south_wall();
    void is_barriered_west_wall();

    bool is_opened_north_wall();
    bool is_opened_east_wall();
    bool is_opened_south_wall();
    bool is_opened_west_wall();

};


#endif //NEWZUZUMOUSE_BLOCK_H
