#include "explore.h"


void debug(const Explore &_t) {
    printf("X=%d Y=%d \r\n",_t.mouse._pe.get_map_position().x, _t.mouse._pe.get_map_position().y);

    if (_t.mouse._pe.get_map_position().direction == NORTH_MASK) printf("Direction:NORTH");
    else if (_t.mouse._pe.get_map_position().direction == EAST_MASK) printf("DirectionEAST");
    else if (_t.mouse._pe.get_map_position().direction == SOUTH_MASK) printf("DirectionSOUTH");
    else printf("Direction:WEST");

    printf("\n");
//    printf("X=%.3f Y=%.3f rad=%.3f \r\n",_t.log.push_back(), _t.p, _t.pe.get_position().rad*(180.0/PI));
}

void Explore::marking_exprole() {

    MapPosition stop_point;
    stop_point.x = 3;
    stop_point.y = 8;

    double _speed = 150;
    double _turn_speed = 80;
    int wait_time = 300;

    mouse.move(_speed , START_BLOCK);
//    mouse._pe.update_map(map);
    mouse._pe.set_position(90.0, 90.0, 0.0);
    mouse.move_p(_speed);


    while (true){

        mouse._pe.update_map(map);
//        log.push_back(mouse._pe.get_position());
        if(mouse._pe.get_map_position()==stop_point)break;

        if(mouse._sensor.is_opened_left_wall()){

//            mouse.move_p(_speed, HALF_BLOCK);
            mouse.move_d(_speed, HALF_BLOCK, ZUZU::DECELERATION);
            mouse.stop();
            printf("X=%.3f Y=%.3f Direction=%.3f \r\n", mouse._pe.get_position().x, mouse._pe.get_position().y, mouse._pe.get_position().rad);
            wait_ms(wait_time);
//            mouse.turn(_turn_speed, ZUZU::LEFT_MACHINE);
            mouse.old_turn(_turn_speed, ZUZU::LEFT_MACHINE);
            mouse.stop();
            wait_ms(wait_time);
            mouse.move_p(_speed);
//            mouse.stop();
//            wait_ms(wait_time);


        }else if(mouse._sensor.is_opened_center_wall()){

            mouse.move_p(_speed);
//            mouse.stop();
//            wait_ms(wait_time);

        }else if(mouse._sensor.is_opened_right_wall()){

//            mouse.move_p(_speed, HALF_BLOCK);
            mouse.move_d(_speed, HALF_BLOCK, ZUZU::DECELERATION);
            mouse.stop();
            printf("X=%.3f Y=%.3f Direction=%.3f \r\n", mouse._pe.get_position().x, mouse._pe.get_position().y, mouse._pe.get_position().rad);
            wait_ms(wait_time);
//            mouse.turn(_turn_speed, ZUZU::RIGHT_MACHINE);
            mouse.old_turn(_turn_speed, ZUZU::RIGHT_MACHINE);
            mouse.stop();
            wait_ms(wait_time);
//            mouse.move(_speed,HALF_BLOCK);
            mouse.move_p(_speed);
//            mouse.stop();
//            wait_ms(wait_time);


        }else {

//            mouse.move_p(_speed, HALF_BLOCK);
            mouse.move_d(_speed, HALF_BLOCK, ZUZU::DECELERATION);
            mouse.stop();
            printf("X=%.3f Y=%.3f Direction=%.3f \r\n", mouse._pe.get_position().x, mouse._pe.get_position().y, mouse._pe.get_position().rad);
            wait_ms(wait_time);
//            mouse.turn(_turn_speed, ZUZU::TURN_MACHINE);
            mouse.old_turn(_turn_speed, ZUZU::TURN_MACHINE);
            mouse.stop();
            wait_ms(wait_time);
            mouse.move_p(_speed);
//            mouse.stop();
//            wait_ms(wait_time);


        }
    }
    mouse.stop();
    wait_ms(wait_time);
    mouse.move(_speed, HALF_BLOCK);
//    debug(*this);


}
