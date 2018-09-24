#ifndef DEF_TYPE_H
#define DEF_TYPE_H

#include "mbed.h"

//Public Function Relation
#define INT_MODE		0   /* Return mode select */
#define BOOL_MODE		1

//Map Relation
#define FRONT_MACHINE	0
#define LEFT_MACHINE	1
#define RIGHT_MACHINE	2
#define TURN_MACHINE	3
#define NORTH			0x08
#define EAST			0x04
#define SOUTH           0x02
#define WEST			0x01

//Base Define
#define HIGH            true
#define LOW             false
#define STOP            0
#define BOOL_ERROR      false
#define BOOL_SUCCESS    true


#endif
