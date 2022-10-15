/*!
* @file serial_utility.h v1.0
* @Copyright © 2018 Kazushi Kurasawa
* @date 2018.11.16
*
* Released under the MIT license.
* see https://opensource.org/licenses/MIT
*/

#ifndef NEWZUZUMOUSE_SERIAL_UTILITY_H
#define NEWZUZUMOUSE_SERIAL_UTILITY_H

#include "MSLMv3/position_estimator.h"
#include "MSLMv3/point.h"
#include "MSLMv3/sensor.h"

/**
 * @fn デバッグにおいて、シリアル通信(USBで、マップの壁情報を見る)
 */
void serial_map(Map3& map);

/**
 * @fn デバッグにおいて、シリアル通信(USBで、オドメトリの自己位置推定座標を見る)
 */
void serial_odometry(PositionEstimator& _pe);

/**
 * @fn デバッグにおいて、シリアル通信(USB)で、距離センサによる値を見る
 */
void serial_sensor(SensorManager& _sensor);

#endif //NEWZUZUMOUSE_SERIAL_UTILITY_H
