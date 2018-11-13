//
// Created by 倉澤　一詩 on 2018/11/11.
//

#include "map3.h"

void Map3::map_init() {

    for(int i = 0; i < 15; i++){
        _block[15][i].set_west_wall();
        _block[0][i].set_east_wall();
    }

    for(int i = 0; i < 15; i++){
        _block[i][0].set_south_wall();
        _block[i][15].set_north_wall();
    }
}

