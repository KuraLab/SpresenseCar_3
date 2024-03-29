// Written by MAX (Created 06 Mar, 2023)

// Features:    Nucleo64-related Global Constant

//--------------------------------------------------------//

#ifndef GLOBAL_CONSTANT_H
#define GLOBAL_CONSTANT_H

// I2C
// -> Address of Nucleo-64
#define NUCLEO_I2C_ADDR 0x45
// -> I2C Message Length
#define I2C_MSG_LENGTH  32

// PI
#define PI_M            3.14159265358979323846f

// MAX Motor Speed Ratio
#define MAX_MOTOR_SPD   0.95f

// MIN Distance to trigger Motor Movement
#define MIN_MOVE_DIST   0   

// Motor Related
// -> Motor name
enum                    Motor { Motor_TL, Motor_TR, Motor_BL, Motor_BR };

// Motor Physical Properties
// -> According to: https://osoyoo.com/2019/11/08/how-to-test-motor-encoder-with-arduino/
// #define RATED_V         6   //V
// #define WHEEL_D         80  //mm
// -> Circumference for half wheel (for hall sensor feedback)
// #define WHEEL_HALF_C    80/2*PI_M  //mm
// #define MOTOR_GEAR_RATIO    75 //1:75
// #define MOTOR_SPEC_SPEED    11500 //rpm

// MIN Time for next SAME Interrupt to be handled
// #define HALL_UPDATE_PERIOD  1  //ms

#endif