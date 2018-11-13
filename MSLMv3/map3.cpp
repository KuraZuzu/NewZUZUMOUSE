//
// Created by 倉澤　一詩 on 2018/11/11.
//

#include "map3.h"

void Map3::map_init() {

    for(int i = 0; i < 15; i++){
        _block[15][i].is_barriered_west_wall();
        _block[0][i].is_barriered_east_wall();
    }

    for(int i = 0; i < 15; i++){
        _block[i][0].is_barriered_south_wall();
        _block[i][15].is_barriered_north_wall();
    }
}

