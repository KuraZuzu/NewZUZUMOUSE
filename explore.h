#ifndef NEWZUZUMOUSE_EXPLORE_H
#define NEWZUZUMOUSE_EXPLORE_H

#include "Machine.h"
#include "mslm_v3/PositionEstimator.h"
#include "mslm_v3/map3.h"
#include "mslm_v3/vector.h"
#include "mslm_v3/Point.h"


class Explore {
public:
    Machine& mouse;
    Map3& map;
    Vector<Position> log;

    Explore(Machine& _mouse, Map3& _map):mouse(_mouse), map(_map){  //コンストラクタ
    }

    void make_walkmap(Map3 &map, uint8_t x, uint8_t y){
        int tmp_cnt = 0;
        Point<uint8_t > v_point, c_point;
        Block tmp_block;
        bool change_flg=false;
        c_point.x=x;
        c_point.y=y;
        map.set_walk_cnt(c_point, 0);
        do {
            change_flg = false;
            for(uint8_t i=0; i<map.size().x; i++){
                for(uint8_t j=0; j<map.size().y; j++){
                    v_point.x=i;
                    v_point.y=j;
                    tmp_block = map.at(v_point);
                    tmp_cnt = tmp_block.walk_cnt;
                    if(map.at(v_point).walk_cnt==255) continue;

                    if(j<map.size().y-1 && ((tmp_block.get_wall() & NORTH_MASK) != NORTH_MASK)){
                        v_point.y++;
                        if(map.at(v_point).walk_cnt == 255){
                            map.set_walk_cnt(v_point, tmp_cnt+1);
                            change_flg = true;
                        }
                        v_point.y--;
                    }
                    if(i<map.size().x-1 &&((tmp_block.get_wall() & EAST_MASK) != EAST_MASK)){
                        v_point.x++;
                        if(map.at(v_point).walk_cnt == 255){
                            map.set_walk_cnt(v_point, tmp_cnt+1);
                            change_flg = true;
                        }
                        v_point.x--;
                    }
                    if(0<j&&((tmp_block.get_wall() & SOUTH_MASK) != SOUTH_MASK)){
                        v_point.y--;
                        if(map.at(v_point).walk_cnt == 255){
                            map.set_walk_cnt(v_point, tmp_cnt+1);
                            change_flg = true;
                        }
                        v_point.y++;
                    }
                    if(0<i&&((tmp_block.get_wall() & WEST_MASK) != WEST_MASK)){
                        v_point.x--;
                        if(map.at(v_point).walk_cnt == 255){
                            map.set_walk_cnt(v_point, tmp_cnt+1);
                            change_flg = true;
                        }
                        v_point.x++;
                    }
                }
            }

        }while(change_flg);

    }

    void left_hand(){};

    void center_left_hand(){};

    void test_center_left_hand(){};

    void metyakutya(){};

    void marking_exprole();

    void kyusin();



};

#endif //NEWZUZUMOUSE_EXPLORE_H
