//
// Created by 倉澤　一詩 on 2018/11/29.
//
#include "serial_utility.h"


void serial_map(Map3 &map) {

    Point <uint8_t > a;
    for (int i = map.size().y-1; 0 <= i; --i) {
        a.y = i;
        for (int j = 0; j < map.size().x; ++j) {
            a.x = j;
            printf("%d, ",map.at(a).get_wall());

        }
        printf("\r\n");
    }

    for (int i = map.size().y-1; 0 <= i; --i) {
        a.y = i;
        for (int j = 0; j < map.size().x; ++j) {
            a.x = j;
            printf("%d, ",map.at(a).walk_cnt);

        }
        printf("\r\n");
    }


}

void serial_odometry(PositionEstimator &_pe) {
    printf("x:%d y:%d  x:%.3f y:%.3f rad:%.3f\r\n", _pe.get_map_position().x,
           _pe.get_map_position().y,
           _pe.get_position().x,
           _pe.get_position().y,
           _pe.get_position().rad);
}
