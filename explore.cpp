#include "explore.h"

void Explore::left_hand() {

    double _speed = 180;
    double _turn_speed = 300;
    int wait_time = 300;
    mouse.move_p(250 , START_BLOCK + HALF_BLOCK);

    while (true){
        if(mouse.is_opened_left_wall()){
            mouse.move_p(_speed, HALF_BLOCK);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::LEFT_MACHINE);
            wait_ms(wait_time);
            mouse.move_p(_speed, HALF_BLOCK);
        }else if(mouse.is_opened_center_wall()){
            mouse.move_p(_speed, ONE_BLOCK);

        }else if(mouse.is_opened_right_wall()){
            mouse.move_p(_speed, HALF_BLOCK);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::RIGHT_MACHINE);
            wait_ms(wait_time);
            mouse.move_p(_speed, HALF_BLOCK);

        }else{
            mouse.move_p(_speed, HALF_BLOCK);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::TURN_MACHINE);
            wait_ms(wait_time);
            mouse.move_p(_speed, HALF_BLOCK);

        }
    }
}


void Explore::center_left_hand() {

    double _speed = 800;
    double _turn_speed = 400;
    int wait_time = 300;
    mouse.move_p(250, START_BLOCK + HALF_BLOCK);

    while (true){

        if(mouse.is_opened_center_wall()){
                mouse.move_p(_speed, ONE_BLOCK);

        }else if(mouse.is_opened_left_wall()){

            mouse.move_d(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::LEFT_MACHINE);
            wait_ms(wait_time);
            mouse.move_d(_speed, HALF_BLOCK, 0);

        }else if(mouse.is_opened_right_wall()){
            mouse.move_d(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::RIGHT_MACHINE);
            wait_ms(wait_time);
            mouse.move_d(_speed, HALF_BLOCK, 0);

        }else{
            mouse.move_d(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::TURN_MACHINE);
            wait_ms(wait_time);
            mouse.move_d(_speed, HALF_BLOCK, 0);

        }
    }
}


void Explore::metyakutya() {

    int i;
    double _speed = 2000;
    wait_us(100000);


        while (true){

            if(i%5 != 0){
                if(mouse.is_opened_left_wall()){
                    mouse.move_p(_speed, HALF_BLOCK);
                    wait_us(1000);
                    mouse.turn(_speed, ZUZU::LEFT_MACHINE);
                    wait_us(1000);
                    mouse.move_p(_speed, HALF_BLOCK);
                    wait_us(1000);
                }else if(mouse.is_opened_center_wall()){
                    mouse.move_p(_speed, ONE_BLOCK);
                    wait_us(1000);
                }else if(mouse.is_opened_right_wall()){
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


                if(mouse.is_opened_right_wall()){
                    mouse.move_p(_speed, HALF_BLOCK);
                    wait_us(1000);
                    mouse.turn(_speed, ZUZU::RIGHT_MACHINE);
                    wait_us(1000);
                    mouse.move_p(_speed, HALF_BLOCK);
                    wait_us(1000);
                }else if(mouse.is_opened_center_wall()){
                    mouse.move_p(_speed, ONE_BLOCK);
                    wait_us(1000);
                }else if(mouse.is_opened_left_wall()){
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