// Written by MAX (Created 06 Mar, 2022)

// Features:    Nucleo64-related Global Variables

//--------------------------------------------------------//

#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include "mbed.h"

// Position Variables
// -> Coordinates
extern uint32_t         X, Y;
extern uint32_t         target_X, target_Y;

// PIN Variables
// -> onboard LED & Button
extern DigitalOut*      LED;
extern DigitalIn*       Button;     //Pressed=0, NOT Pressed=1
// -> I2C
extern I2CSlave*        I2C_SLAVE_M;
// -> Motor pins
extern PwmOut*          Motor_PWM[4];
extern DigitalOut*      Motor_DIR[2*4];
// extern InterruptIn*     Motor_HALL[2*4];

// Motor Related
// -> Motor Current Input
class Motor_Input { // DIR : True = forward, False = backward
    public:
    bool    is_available;    // use mutex with this if want to update with timer interrupt, don't forget to implement checking tho
    //
    float   M1_PWM;
    bool    M1_DIR;
    float   M1_MUL;
    //
    float   M2_PWM;
    bool    M2_DIR;
    float   M2_MUL;
    //
    float   M3_PWM;
    bool    M3_DIR;
    float   M3_MUL;
    //
    float   M4_PWM;
    bool    M4_DIR;
    float   M4_MUL;
};
extern Motor_Input      Curr_Motor_Input;
// -> Motor Hall Sensors Count
// extern uint16_t         Hotor_HALL_count[2*4] = {0,0,0,0,0,0,0,0};

// Serial communication
extern BufferedSerial*  Serial_M;

#endif