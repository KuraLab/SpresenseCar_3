// Written by MAX (Created 06 Mar, 2023)

// Features:    Translator from I2C Messages from Spresense to Variables

//--------------------------------------------------------//

#ifndef I2C_HANDLER_H
#define I2C_HANDLER_H

#include "mbed.h"
#include "../Global_Constant/Global_Constant.h"
#include <cstdint>

class I2C_PWM_DIR_Input {
    public:
    Motor motor;
    float pwm;      // <0.0 = no change
    uint8_t dir;    // 3 = no change
};
I2C_PWM_DIR_Input I2C_Receive_PWM_DIR(char* input);


class I2C_Target_XY_Input {
    public:     // if no change, dont send
    uint32_t target_X;
    uint32_t target_Y;
};
I2C_Target_XY_Input I2C_Receive_TargetXY(char* input);


float I2C_Receive_Radian(char* input);


class I2C_Encoder_Input {
    public:
    float M1_Multiplier;
    float M2_Multiplier;
    float M3_Multiplier;
    float M4_Multiplier;
};
I2C_Encoder_Input I2C_Receive_Encoder(char* input);


enum I2C_Input_Type { PWM_DIR, TargetXY, Radian, Encoder };
class I2C_Input{
    public:
    I2C_Input_Type          input_type;
    I2C_PWM_DIR_Input       pwm_dir;
    I2C_Target_XY_Input     targetXY;
    float                   radian;
    I2C_Encoder_Input       encoder;
};
I2C_Input* I2C_Receive();

#endif