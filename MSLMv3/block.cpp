//
// Created by 倉澤　一詩 on 2018/11/11.
//

#include "block.h"

// open = true 1
// close = false 0


void Block::set_north_wall() {
    _b += NORTH_MASK;
}

void Block::set_east_wall() {
    _b += EAST_MASK;
}

void Block::set_south_wall() {
    _b += SOUTH_MASK;
}

void Block::set_west_wall() {
    _b += WEST_MASK;
}



bool Block::is_opened_north_wall() {
    return (NORTH_MASK & _b)==NORTH_MASK;
}

bool Block::is_opened_east_wall() {
    return (EAST_MASK & _b)==EAST_MASK;
}

bool Block::is_opened_south_wall() {
    return (SOUTH_MASK & _b)==SOUTH_MASK;
}

bool Block::is_opened_west_wall() {
    return (WEST_MASK & _b) == WEST_MASK;
}