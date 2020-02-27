//
// Created by 倉澤　一詩 on 2018/11/29.
//

#ifndef NEWZUZUMOUSE_SERIAL_UTILITY_H
#define NEWZUZUMOUSE_SERIAL_UTILITY_H

#include "mslm_v3/PositionEstimator.h"
//#include "mslm_v3/map3.h"
#include "mslm_v3/Point.h"
#include "mslm_v3/sensor.h"

/* デバッグにおいて、シリアル通信(USBで、マップの壁情報を見る) */
void serial_map(Map3& map);

/* デバッグにおいて、シリアル通信(USBで、オドメトリの自己位置推定座標を見る) */
void serial_odometry(PositionEstimator& _pe);

/* デバッグにおいて、シリアル通信(USB)で、距離センサによる値を見る */
void serial_sensor(SensorManager& _sensor);

#endif //NEWZUZUMOUSE_SERIAL_UTILITY_H
