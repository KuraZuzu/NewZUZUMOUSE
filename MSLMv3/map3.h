//
// Created by 倉澤　一詩 on 2018/11/11.
//

#ifndef NEWZUZUMOUSE_MAP_3_H
#define NEWZUZUMOUSE_MAP_3_H

#include "block.h"
#include "deftype.h"

class Map3 {

private:

    Block **_block;
    uint8_t _x_size = 0;
    uint8_t _y_size = 0;



public:

    Map3(uint8_t x_size, uint8_t y_size) {
        _x_size = x_size;
        _y_size = y_size;
        _block = new Block* [x_size];
        for (int i = 0; i < y_size; ++i) {
            _block[i] = new Block;
        }
    }
    ~Map3(){
        for (int i = 0; i < _y_size; ++i) {
            delete _block[i];
        }
        delete [] _block;
    }


private:

    void map_init();



};


#endif //NEWZUZUMOUSE_MAP_3_H
