//
// Created by 倉澤　一詩
//

#include "serial_utility.h"
#include "MSLMv3/vector.h"

void serial_map(Map3 &map) {

    Point <uint8_t > a;
    for (int i = map.size().y-1; 0 <= i; --i) {
        a.y = i;
        for (int j = 0; j < map.size().x; ++j) {
            a.x = j;
            printf("%d, ",map.at(a).get_wall()); //各ビットごとに壁情報が記録されている

        }
        printf("\r\n");
    }

    for (int i = map.size().y-1; 0 <= i; --i) {
        a.y = i;
        for (int j = 0; j < map.size().x; ++j) {
            a.x = j;
            printf("%d, ",map.at(a).walk_cnt);  //各ビットごとに歩数情報が記録されている

        }
        printf("\r\n");
    }


}

void serial_odometry(PositionEstimator &_pe) {
    double_t rad = _pe.get_position().rad;
    double_t deg = rad * 180.0/3.1415;

    //(ブロックx, ブロックy,  座標x, 座標y,  角度rad, 角度deg) が表示される
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
    }

    int32_t max_diff = 0;
    int32_t min_diff = 0;
    int32_t mean= 0;
    for (int j = 0; j < ls.size(); ++j) {
        int32_t diff = ls.at(j)-rs.at(j);

        // (左センサ, 中央センサ, 右センサ, 左右センサの差分)といったように、センサで読み取った距離[cm]が表示される
        printf("%ld %ld %ld diff=%ld\n\r",
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
    printf("Mean: %ld Max: %ld Min: %ld \r\n",mean ,max_diff,min_diff);

}
