// Written by MAX (Created 06 Mar, 2022)

// Funtions:    Quality-Of-Life Functions

//--------------------------------------------------------//

#ifndef QOL_FUNC_H
#define QOL_FUNC_H

#include "mbed.h"

// Easy Serial Write
void Serial_println();
void Serial_print(const char* msg);
void Serial_println(const char* msg);
void Serial_print(string msg);
void Serial_println(string msg);
void Serial_print(int msg);
void Serial_println(int msg);
void Serial_print(uint16_t msg);
void Serial_println(uint16_t msg);
void Serial_print(uint32_t msg);
void Serial_println(uint32_t msg);
// -> print to 8 decimal points only
void Serial_print(float msg);
// -> print to 8 decimal points only
void Serial_println(float msg);

// Easy Wait
void wait_ms(uint16_t ms);
void wait_s(uint16_t s);

// Easy Angle <=> Radian
float angle_to_radian(float angle);
float radian_to_angle(float radian);

#endif