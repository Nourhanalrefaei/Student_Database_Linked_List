/*
 * std_types.h
 *
 * Created: 3/27/2022 5:55:17 PM
 *  Author: NourhanAlrefaei
 */

#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_
#include <stdio.h>
#include <stdlib.h>

#define ZERO_INIT 0
#define TRUE 1
#define FALSE 0


typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

typedef signed int sint32_t;
typedef signed char sint8_t;
typedef signed short sint16_t;


extern uint8_t Counter_of_elements;
typedef enum return_status{
  R_NOK,
  R_OK
}return_status_t;


#endif // _STD_TYPES_H_
