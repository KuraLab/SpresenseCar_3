// Written by MAX (Created 06 Mar, 2023)

// Features:    Translator to Motor Input

//--------------------------------------------------------//

#ifndef MOTOR_INPUT_TRANSLATE_H
#define MOTOR_INPUT_TRANSLATE_H

#include "mbed.h"
#include "../Motor_Control/Motor_Control.h"
#include "../I2C_Handler/I2C_Handler.h"

void PWM_to_Input(I2C_PWM_DIR_Input input);

void TargetXY_to_Input(I2C_Target_XY_Input input);

void Radian_to_Input(float input);

void Encoder_to_Input(I2C_Encoder_Input input);

#endif