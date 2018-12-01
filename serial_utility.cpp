//
// Created by 倉澤　一詩 on 2018/11/29.
//
#include "serial_utility.h"
#include "mslm_v3/vector.h"

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
    double_t rad = _pe.get_position().rad;
    double_t deg = rad * 180.0/3.1415;
    printf("x:%d y:%d  x:%.3f y:%.3f rad:%.3f deg:%.3f \r\n", _pe.get_map_position().x,
           _pe.get_map_position().y,
           _pe.get_position().x,
           _pe.get_position().y,
           rad,
           deg);
}

void serial_sensor(SensorManager &_sensor) {
    Vector<int32_t> ls,rs,fs;
        wait(3);
        for (int i = 0; i < 10; ++i) {
            ls.push_back(_sensor.get_left_wall_distance());
            rs.push_back(_sensor.get_right_wall_distance());
            fs.push_back(_sensor.get_front_wall_distance());
//            wait_ms(5);
    }

    int32_t max_diff = 0;
    int32_t min_diff = 0;
    int32_t mean= 0;
    for (int j = 0; j < ls.size(); ++j) {
        int32_t diff = ls.at(j)-rs.at(j);
        printf("%d %d %d diff=%d\n\r",
               ls.at(j),
               fs.at(j),
               rs.at(j),
               diff
        );
        mean += diff;
    }
    mean = mean/ls.size();
    for (int k = 0; k < ls.size(); ++k) {
        int diff = (ls.at(k)-rs.at(k)) - mean;
        if (max_diff < diff)max_diff = diff;
        if (min_diff > diff)min_diff = diff;
    }
    printf("Mean: %d Max: %d Min: %d \r\n",mean ,max_diff,min_diff);


//                                                              printf("\r\b\r");
//    printf("%d %d %d diff=%d\n\r",
//           _sensor.get_left_wall_distance(),
//           _sensor.get_front_wall_distance(),
//           _sensor.get_right_wall_distance(),
//           _sensor.get_left_wall_distance()-_sensor.get_right_wall_distance()
//    );
}
