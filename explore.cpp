#include "explore.h"


void debug(const Explore &_t) {
    printf("X=%d Y=%d \r\n",_t.mouse._pe.get_map_position().x, _t.mouse._pe.get_map_position().y);
    if (_t.mouse._pe.get_map_position().direction == NORTH_MASK) printf("Direction:NORTH");
    else if (_t.mouse._pe.get_map_position().direction == EAST_MASK) printf("DirectionEAST");
    else if (_t.mouse._pe.get_map_position().direction == SOUTH_MASK) printf("DirectionSOUTH");
    else printf("Direction:WEST");
//    printf("X=%.3f Y=%.3f Theta=%.3f \r\n",_t.pe.get_position().x, _t.pe.get_position().y, _t.pe.get_position().rad*(180.0/PI));
}

void disp_map(Map3& map){

    Point <uint8_t > a;
    for (int i = map.size().y-1; 0 <= i; --i) {
        a.y = i;
        for (int j = 0; j < map.size().x; ++j) {
            a.x = j;
            printf("%d, ",map.at(a).get_wall());

        }
        printf("\r\n");
    }
}

void Explore::left_hand() {

    double _speed = 300;
    double _turn_speed = 150;
    int wait_time = 1000;
    debug(*this);
    mouse.move(80 , START_BLOCK);
    wait_ms(wait_time);
    mouse._pe.set_position(90.0, 90.0, 0.0);
    debug(*this);
    wait_ms(wait_time);
    mouse.move_p(_speed, HALF_BLOCK, 0);

    while (true){

        int i;

        if(5 < i) break;

        if(mouse._sensor.is_opened_left_wall()){
            mouse.move_p(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            debug(*this);
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::LEFT_MACHINE);
            wait_ms(wait_time);
            mouse.move_p(_speed, HALF_BLOCK, 0);

            i++;

        }else if(mouse._sensor.is_opened_center_wall()){

            mouse.move_p(_speed, ONE_BLOCK);

        }else if(mouse._sensor.is_opened_right_wall()){
            mouse.move_p(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::RIGHT_MACHINE);
            wait_ms(wait_time);
            debug(*this);
            wait_ms(wait_time);
            mouse.move_p(_speed, HALF_BLOCK, 0);

            i++;

        }else {
            mouse.move_p(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::TURN_MACHINE);
            wait_ms(wait_time);
            debug(*this);
            wait_ms(wait_time);
            mouse.stop();
            wait_ms(wait_time);
            mouse.move_p(_speed, HALF_BLOCK, 0);

            i++;

        }
    }

    printf("終了");
    debug(*this);
}


void Explore::center_left_hand() {

    double _speed = 450;
    double _turn_speed = 250;
    int wait_time = 300;
    mouse.move_p(450, START_BLOCK + HALF_BLOCK, 0);

    while (true){

        if(mouse._sensor.is_opened_center_wall()){
                mouse.move_p(_speed, ONE_BLOCK);

        }else if(mouse._sensor.is_opened_left_wall()){

            mouse.move_p(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::LEFT_MACHINE);
            wait_ms(wait_time);
            mouse.move_p(_speed, HALF_BLOCK, 0);

        }else if(mouse._sensor.is_opened_right_wall()){
            mouse.move_p(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::RIGHT_MACHINE);
            wait_ms(wait_time);
            mouse.move_p(_speed, HALF_BLOCK, 0);

        }else{
            mouse.move_p(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::TURN_MACHINE);
            wait_ms(wait_time);
            mouse.move_p(_speed, HALF_BLOCK, 0);

        }
    }
}


void Explore::test_center_left_hand() {

    double _speed = 740;
    double _turn_speed = 250;
    int wait_time = 300;
    mouse.move_p(350, START_BLOCK + HALF_BLOCK);

    while (true){

        if(mouse._sensor.is_opened_center_wall()){
            mouse.move_p(_speed, ONE_BLOCK);

        }else if(mouse._sensor.is_opened_left_wall()){

            mouse.move_p(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::LEFT_MACHINE);
            wait_ms(wait_time);
            mouse.move_p(_speed, HALF_BLOCK, 0);

        }else if(mouse._sensor.is_opened_right_wall()){
            mouse.move_p(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::RIGHT_MACHINE);
            wait_ms(wait_time);
            mouse.move_p(_speed, HALF_BLOCK, 0);

        }else{
            mouse.move_p(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::TURN_MACHINE);
            wait_ms(wait_time);
            mouse.move_p(_speed, HALF_BLOCK, 0);

        }
    }
}

void Explore::metyakutya() {

    int i;
    double _speed = 2000;
    wait_us(100000);


        while (true){

            if(i%5 != 0){
                if(mouse._sensor.is_opened_left_wall()){
                    mouse.move_p(_speed, HALF_BLOCK);
                    wait_us(1000);
                    mouse.turn(_speed, ZUZU::LEFT_MACHINE);
                    wait_us(1000);
                    mouse.move_p(_speed, HALF_BLOCK);
                    wait_us(1000);
                }else if(mouse._sensor.is_opened_center_wall()){
                    mouse.move_p(_speed, ONE_BLOCK);
                    wait_us(1000);
                }else if(mouse._sensor.is_opened_right_wall()){
                    mouse.move_p(_speed, HALF_BLOCK);
                    wait_us(1000);
                    mouse.turn(_speed, ZUZU::RIGHT_MACHINE);
                    wait_us(1000);
                    mouse.move_p(_speed, HALF_BLOCK);
                    wait_us(1000);
                }else{
                    mouse.turn(_speed, ZUZU::TURN_MACHINE);
                    wait_us(1000);
                }

                i++;

            }else{


                if(mouse._sensor.is_opened_right_wall()){
                    mouse.move_p(_speed, HALF_BLOCK);
                    wait_us(1000);
                    mouse.turn(_speed, ZUZU::RIGHT_MACHINE);
                    wait_us(1000);
                    mouse.move_p(_speed, HALF_BLOCK);
                    wait_us(1000);
                }else if(mouse._sensor.is_opened_center_wall()){
                    mouse.move_p(_speed, ONE_BLOCK);
                    wait_us(1000);
                }else if(mouse._sensor.is_opened_left_wall()){
                    mouse.move_p(_speed, HALF_BLOCK);
                    wait_us(1000);
                    mouse.turn(_speed, ZUZU::LEFT_MACHINE);
                    wait_us(1000);
                    mouse.move_p(_speed, HALF_BLOCK);
                    wait_us(1000);
                }else{
                    mouse.turn(_speed, ZUZU::TURN_MACHINE);
                    wait_us(1000);
                }

                i++;
            }
        }
}

void Explore::marking_exprole() {


    double _speed = 100;
    double _turn_speed = 80;
    int wait_time = 1000;

    mouse.move(_speed , START_BLOCK);
    mouse._pe.update_map(map);
    mouse._pe.set_position(90.0, 90.0, 0.0);
    mouse.move(_speed, HALF_BLOCK);

    int i;

    while (i < 5){

        mouse._pe.update_map(map);


        if(mouse._sensor.is_opened_left_wall()){

            mouse.move_p(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::LEFT_MACHINE);
            mouse.stop();
            wait_ms(wait_time);
            mouse.move_p(_speed);


        }else if(mouse._sensor.is_opened_center_wall()){
            mouse.move_p(_speed);

        }else if(mouse._sensor.is_opened_right_wall()){

            mouse.move_p(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::RIGHT_MACHINE);
            mouse.stop();
            wait_ms(wait_time);
            wait_ms(wait_time);
            mouse.move_p(_speed);


        }else {

            mouse.move_p(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::TURN_MACHINE);
            mouse.stop();
            wait_ms(wait_time);
            wait_ms(wait_time);
            mouse.stop();
            wait_ms(wait_time);
            mouse.move_p(_speed);


        }

        i++;
    }
    mouse.stop();
    wait_ms(wait_time);
    debug(*this);
    disp_map(map);

}
