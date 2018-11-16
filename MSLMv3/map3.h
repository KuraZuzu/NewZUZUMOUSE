//
// Created by 倉澤　一詩 on 2018/11/11.
//

#ifndef NEWZUZUMOUSE_MAP_3_H
#define NEWZUZUMOUSE_MAP_3_H

#include "block.h"
#include "deftype.h"
#include "Point.h"


class Map3 {

private:

    Block **_block;
    uint8_t _x_size = 0;
    uint8_t _y_size = 0;
    Point _point;

public:

    Map3(uint8_t x_size, uint8_t y_size);

    ~Map3();

private:

    void map_init();

    void set_wall(Block _wall_info){
        _block[(int)point.x][(int)point.y] = _wall_info;
    }

};


#endif //NEWZUZUMOUSE_MAP_3_H
