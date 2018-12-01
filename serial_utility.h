//
// Created by 倉澤　一詩 on 2018/11/29.
//

#ifndef NEWZUZUMOUSE_SERIAL_UTILITY_H
#define NEWZUZUMOUSE_SERIAL_UTILITY_H

#include "mslm_v3/PositionEstimator.h"
#include "mslm_v3/map3.h"
#include "mslm_v3/Point.h"
#include "mslm_v3/sensor.h"


void serial_map(Map3& map);

void serial_odometry(PositionEstimator& _pe);

void serial_sensor(SensorManager& _sensor);

#endif //NEWZUZUMOUSE_SERIAL_UTILITY_H
