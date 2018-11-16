//
// Created by 倉澤　一詩 on 2018/11/16.
//

#ifndef NEWZUZUMOUSE_POINT_H
#define NEWZUZUMOUSE_POINT_H

#include <cmath>

struct Point{

public:

    float_t x;
    float_t y;


};


struct Position : public Point{

public:
    float_t rad;

};


#endif //NEWZUZUMOUSE_POINT_H
