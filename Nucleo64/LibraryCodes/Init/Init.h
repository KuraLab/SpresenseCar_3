// Written by MAX (Created 06 Mar, 2023)

// Features:    Initialization code for Nucleo64

//--------------------------------------------------------//

#ifndef INIT_H
#define INIT_H

#include "mbed.h"
#include <cstdint>

// Init ALL Components
void Init();

// Init the 2 onboard components, simply that
void Onboard_LED_Init(DigitalOut*& LED);
void Onboard_Button_Init(DigitalIn*& Button);

// Init I2C pins & I2C
void I2C_Init(I2CSlave*& I2C_SLAVE_M);

// Init static Motor_Input object
void Motor_Input_Init();

// Init the pins for Motor Control
void Motor_PWM_Pin_Init(PwmOut* motor_PWM[]);       //1x4 pins
void Motor_DIR_Pin_Init(DigitalOut* motor_DIR[]);   //2x4 pins
// void Motor_HALL_Pin_Init(InterruptIn* motor_HALL[]);//2x4 pins

// Init Serial Communication
void Serial_Init(BufferedSerial*& Serial_M);

//--------------------------------------------------------//

//HALL Pin Interrupt Handler
// void M1_HALL_1_handler();
// void M1_HALL_2_handler();
// void M2_HALL_1_handler();
// void M2_HALL_2_handler();
// void M3_HALL_1_handler();
// void M3_HALL_2_handler();
// void M4_HALL_1_handler();
// void M4_HALL_2_handler();

//--------------------------------------------------------//

void Nucleo64_Init_Finished_Successfully(DigitalOut* LED);

#endif