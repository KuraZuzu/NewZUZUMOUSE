#ifndef NEWZUZUMOUSE_EXPLORE_H
#define NEWZUZUMOUSE_EXPLORE_H

#include "Machine.h"
#include "mslm_v3/PositionEstimator.h"
#include "mslm_v3/map3.h"
#include "mslm_v3/vector.h"
#include "mslm_v3/Point.h"
//class NewZuzumouse;


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

    void kyusin(){

        MapPosition stop_point;
        stop_point.x = 8;
        stop_point.y = 3;

        const double _speed = 300;
        const double _turn_speed = 80;
        const int wait_time = 300;

        mouse.move(_speed/10 , START_BLOCK);
        mouse.stop();
        wait_ms(wait_time);
        mouse._pe.set_position(90.0, 90.0, 0.0);
        mouse.move_d(_speed, 0, ZUZU::ACCELERATION);


        while (true){
            Point<uint8_t> point;
            Point<uint8_t> next_point;

            point.x = mouse._pe.get_map_position().x;
            point.y = mouse._pe.get_map_position().y;

            mouse._pe.update_map(map);
            make_walkmap(map,2,2);
//        log.push_back(mouse._pe.get_position());
            if(mouse._pe.get_map_position() == stop_point)break;



            if(mouse._sensor.is_opened_center_wall() && ((map.at(point).walk_cnt - map.at(next_point).walk_cnt) == 1)){
                next_point.x = point.x ;
                next_point.y = point.y + (uint8_t)1;

                mouse.move_p(_speed);

            }else if((mouse._sensor.is_opened_left_wall()) && ((map.at(point).walk_cnt - map.at(next_point).walk_cnt) == 1)){

                mouse.move_d(_speed, HALF_BLOCK, ZUZU::DECELERATION);
                mouse.stop();
                printf("X=%.3f Y=%.3f Direction=%.3f \r\n", mouse._pe.get_position().x, mouse._pe.get_position().y, mouse._pe.get_position().rad);
                wait_ms(wait_time);
//            mouse.turn(_turn_speed, ZUZU::LEFT_MACHINE);
                mouse.old_turn(_turn_speed, ZUZU::LEFT_MACHINE);
                mouse.stop();
                wait_ms(wait_time);
                mouse.move_d(_speed, 0, ZUZU::ACCELERATION);


            }else if((mouse._sensor.is_opened_right_wall()) && ((map.at(point).walk_cnt - map.at(next_point).walk_cnt) == 1)){

                mouse.move_d(_speed, HALF_BLOCK, ZUZU::DECELERATION);
                mouse.stop();
                printf("X=%.3f Y=%.3f Direction=%.3f \r\n", mouse._pe.get_position().x, mouse._pe.get_position().y, mouse._pe.get_position().rad);
                wait_ms(wait_time);
//            mouse.turn(_turn_speed, ZUZU::RIGHT_MACHINE);
                mouse.old_turn(_turn_speed, ZUZU::RIGHT_MACHINE);
                mouse.stop();
                wait_ms(wait_time);
                mouse.move_d(_speed, 0, ZUZU::ACCELERATION);

            }else{

                mouse.move_d(_speed, HALF_BLOCK, ZUZU::DECELERATION);
                mouse.stop();
                printf("X=%.3f Y=%.3f Direction=%.3f \r\n", mouse._pe.get_position().x, mouse._pe.get_position().y, mouse._pe.get_position().rad);
                wait_ms(wait_time);
//            mouse.turn(_turn_speed, ZUZU::TURN_MACHINE);
                mouse.old_turn(_turn_speed, ZUZU::TURN_MACHINE);
                mouse.stop();
                wait_ms(wait_time);
                mouse.move_d(_speed, 0, ZUZU::ACCELERATION);
            }
        }
        mouse.stop();
        wait_ms(wait_time);
        mouse.move(_speed, HALF_BLOCK);
    }



};

#endif //NEWZUZUMOUSE_EXPLORE_H
