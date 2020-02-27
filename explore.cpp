#include "explore.h"


/* 方向が合っているか実機でのデバッグ */
void debug(const Explore &_t) {
    printf("X=%d Y=%d \r\n",_t.mouse._pe.get_map_position().x, _t.mouse._pe.get_map_position().y);

    if (_t.mouse._pe.get_map_position().direction == NORTH_MASK) printf("Direction:NORTH");
    else if (_t.mouse._pe.get_map_position().direction == EAST_MASK) printf("DirectionEAST");
    else if (_t.mouse._pe.get_map_position().direction == SOUTH_MASK) printf("DirectionSOUTH");
    else printf("Direction:WEST");

    printf("\n");
}


void Explore::kyusin(uint8_t _x, uint8_t _y, double_t _speed, double_t _turn_speed) {

    /* 目標となる座標(x,y)に対しての情報を、引数より代入する */
    MapPosition stop_point;
    stop_point.x = _x;
    stop_point.y = _y;

    /* 各種パラメータを引数より代入 */
    const double speed = _speed;
    const double turn_speed = _turn_speed;
    int wait_time = 150;

    /* マウスの初期位置に移動する、指令
       これは、P制御などは用いない。   */
    mouse.move(50 , START_BLOCK);
    mouse.stop();
    wait_ms(wait_time);
    mouse._pe.set_position(90.0, 90.0, 0.0);
    mouse.move_d(speed, 0, ZUZU::ACCELERATION);


    /* 求心の手法での探索開始 */
    while (true){

        Point<uint8_t> target_front_point; // 前方の隣り合ったブロックの座標
        Point<uint8_t> target_left_point;  // 　左の隣り合ったブロックの座標
        Point<uint8_t> target_right_point; // 　右の隣り合ったブロックの座標

        const Point<uint8_t> first_point = mouse._pe.get_map_position(); // 現在の座標を取得

        mouse._pe.update_map(map); // マップの壁情報を、動く都度に更新
        make_walkmap(map,_x,_y);   // 上記で更新したマップ情報をもとに、歩数情報を生成

        /* 自己位置推定による現在位置ブロックが、目的ブロックに到達していたら、求心手法のアルゴリズムから抜ける */
        if(mouse._pe.get_map_position() == stop_point) break;

        /* 東西南北の向いている向きによって、目的となるブロックの座標が変わるので、それを分岐して処理している */
        if(mouse._pe.get_map_position().direction == NORTH_MASK){ // 機体が北方向を向いていた時

            target_front_point.x = first_point.x;
            target_front_point.y = first_point.y + (uint8_t)1;

            if (target_left_point.x != 0) {
                target_left_point.x = first_point.x - (uint8_t) 1;
                target_left_point.y = first_point.y;
            }

            target_right_point.x = first_point.x + (uint8_t)1;
            target_right_point.y = first_point.y;


        }else if(mouse._pe.get_map_position().direction == EAST_MASK){

            target_front_point.x = first_point.x + (uint8_t)1;
            target_front_point.y = first_point.y;

            target_left_point.x = first_point.x;
            target_left_point.y = first_point.y + (uint8_t)1;

            if (target_right_point.y != 0) {
                target_right_point.x = first_point.x;
                target_right_point.y = first_point.y - (uint8_t) 1;
            }


        }else if(mouse._pe.get_map_position().direction == SOUTH_MASK){

            if (target_front_point.y != 0) {
                target_front_point.x = first_point.x;
                target_front_point.y = first_point.y - (uint8_t) 1;
            }

            target_left_point.x = first_point.x + (uint8_t)1;
            target_left_point.y = first_point.y;

            if (target_right_point.x != 0 ) {
                target_right_point.x = first_point.x - (uint8_t) 1;
                target_right_point.y = first_point.y;
            }

        }else{ //west

            if (target_front_point.x != 0) {
                target_front_point.x = first_point.x - (uint8_t) 1;
                target_front_point.y = first_point.y;
            }

            if (target_left_point.y != 0 ) {
                target_left_point.x = first_point.x;
                target_left_point.y = first_point.y - (uint8_t) 1;
            }

            target_right_point.x = first_point.x;
            target_right_point.y = first_point.y + (uint8_t)1;

        }

        mouse.kyusin_method(speed, turn_speed, wait_time, first_point, target_front_point, target_left_point,
                            target_right_point);

    }

    mouse.move(speed, HALF_BLOCK); //ゴールに到達した時、半ブロック進むことで、ゴール座標に入れる
    mouse.stop(); //ゴールに到達したので、制御停止

}


void Explore::left_hand(uint8_t _x, uint8_t _y, double_t _speed, double_t _turn_speed) {

    MapPosition stop_point;
    stop_point.x = _x;
    stop_point.y = _y;

    const double speed = _speed;
    const double turn_speed = _turn_speed;
    const int wait_time = 300;

    mouse.move(_speed/10 , START_BLOCK);
    mouse.stop();
    wait_ms(wait_time);
    mouse._pe.set_position(90.0, 90.0, 0.0);
    mouse.move_d(_speed, 0, ZUZU::ACCELERATION);


    while (true){

        mouse._pe.update_map(map);
        make_walkmap(map,8,8);
        if(mouse._pe.get_map_position()==stop_point) break;

        if(mouse._sensor.is_opened_left_wall()){

            mouse.move_d(speed, HALF_BLOCK, ZUZU::DECELERATION);
            mouse.stop();
            wait_ms(wait_time);
            mouse.turn(turn_speed, ZUZU::LEFT_MACHINE);
            mouse.stop();
            wait_ms(wait_time);
            mouse.move_d(speed, 0, ZUZU::ACCELERATION);


        }else if(mouse._sensor.is_opened_front_wall()){

            mouse.move_p(speed);

        }else if(mouse._sensor.is_opened_right_wall()){

            mouse.move_d(speed, HALF_BLOCK, ZUZU::DECELERATION);
            mouse.stop();
            printf("X=%.3f Y=%.3f Direction=%.3f \r\n", mouse._pe.get_position().x, mouse._pe.get_position().y, mouse._pe.get_position().rad);
            wait_ms(wait_time);
            mouse.turn(turn_speed, ZUZU::RIGHT_MACHINE);
            mouse.stop();
            wait_ms(wait_time);
            mouse.move_d(speed, 0, ZUZU::ACCELERATION);


        }else {

            mouse.move_d(speed, HALF_BLOCK, ZUZU::DECELERATION);
            mouse.stop();
            printf("X=%.3f Y=%.3f Direction=%.3f \r\n", mouse._pe.get_position().x, mouse._pe.get_position().y, mouse._pe.get_position().rad);
            wait_ms(wait_time);
            mouse.turn(turn_speed, ZUZU::TURN_MACHINE);
            mouse.stop();
            wait_ms(wait_time);
            mouse.move_d(speed, 0, ZUZU::ACCELERATION);

        }
    }
    mouse.stop();
    wait_ms(wait_time);
    mouse.move(speed, HALF_BLOCK);
//    debug(*this);
}


void Explore::make_walkmap(Map3 &map, uint8_t x, uint8_t y) {
    int tmp_cnt = 0;
    Point<uint8_t > v_point, c_point;
    Block tmp_block;
    bool change_flg=false;
    c_point.x=x;
    c_point.y=y;
    map.set_walk_cnt(c_point, 0);
    for(uint8_t i=0; i<map.size().x; i++) {
        for (uint8_t j = 0; j < map.size().y; j++) {
            v_point.x=i;
            v_point.y=j;
            if(!(i==x&&j==y))map.set_walk_cnt(v_point, 255);
        }
    }
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
