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

    void set_north_wall();
    void set_east_wall();
    void set_south_wall();
    void set_west_wall();

    bool is_opened_north_wall();
    bool is_opened_east_wall();
    bool is_opened_south_wall();
    bool is_opened_west_wall();

};


#endif //NEWZUZUMOUSE_BLOCK_H
