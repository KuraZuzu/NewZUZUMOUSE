#include "explore.h"

void Explore::left_hand() {

    double _speed = 300;
    double _turn_speed = 150;
    int wait_time = 1000;
    mouse.move(80 , START_BLOCK);
    mouse.set_init_coordinates();
    mouse.set_init_odometry_watch_count();
    wait_ms(wait_time);
    mouse.disp_odometry();
    wait_ms(wait_time);
    mouse.move_d(_speed, HALF_BLOCK, 0);

    while (true){

        int i;

        if(5 < i) break;

        if(mouse.is_opened_left_wall()){
            mouse.move_d(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            mouse.disp_odometry();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::LEFT_MACHINE);
            wait_ms(wait_time);
            mouse.move_d(_speed, HALF_BLOCK, 0);

            i++;

        }else if(mouse.is_opened_center_wall()){

            mouse.move_p(_speed, ONE_BLOCK);

        }else if(mouse.is_opened_right_wall()){
            mouse.move_d(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::RIGHT_MACHINE);
            wait_ms(wait_time);
            mouse.disp_odometry();
            wait_ms(wait_time);
            mouse.move_d(_speed, HALF_BLOCK, 0);

            i++;

        }else {
            mouse.move_d(_speed, HALF_BLOCK, 1);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(_turn_speed, ZUZU::TURN_MACHINE);
            wait_ms(wait_time);
            mouse.disp_odometry();
            wait_ms(wait_time);
            mouse.stop();
            wait_ms(wait_time);
            mouse.move_d(_speed, HALF_BLOCK, 0);

            i++;

        }
    }

    printf("終了");
    mouse.disp_odometry();
}


void Explore::center_left_hand() {

    double _speed = 450;
    double _turn_speed = 250;
    int wait_time = 300;
    mouse.move_d(450, START_BLOCK + HALF_BLOCK, 0);

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


void Explore::test_center_left_hand() {

    double _speed = 740;
    double _turn_speed = 250;
    int wait_time = 300;
    mouse.move_p(350, START_BLOCK + HALF_BLOCK);

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