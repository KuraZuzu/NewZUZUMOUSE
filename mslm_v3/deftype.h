#ifndef DEF_TYPE_H
#define DEF_TYPE_H

#include "mbed.h"

#define pi 3.14159265


//Public Function Relation
#define INT_MODE		0   /* Return mode select */
#define BOOL_MODE		1

//Map Relation
#define FRONT_MACHINE	0
#define NORTH			0x08
#define EAST			0x04
#define SOUTH           0x02
#define WEST			0x01

#define NORTH_MASK 8 //0b 0000 1000
#define EAST_MASK 4  //0b 0000 0100
#define SOUTH_MASK 2 //0b 0000 0010
#define WEST_MASK 1  //0b 0000 0001

//Base Define
#define HIGH            true
#define LOW             false
#define STOP            0
#define BOOL_ERROR      false
#define BOOL_SUCCESS    true


#endif
