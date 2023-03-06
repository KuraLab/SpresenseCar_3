// Written by MAX (Created 06 Mar, 2023)

// Features:    Motor Control Functions

//--------------------------------------------------------//

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "mbed.h"
#include "../Global_Constant/Global_Constant.h"
#include "../Cpp_Main/Cpp_Main_Global_Var.h"

void Motor_Apply_Input();

void Motor_Apply_Input(Motor_Input input);

void Motor_Apply_Input(Motor motor, float pwm, bool dir, float mul);

#endif