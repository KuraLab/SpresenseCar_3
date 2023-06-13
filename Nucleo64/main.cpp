// Written by MAX (Created 06 Mar, 2022)

// Features:    Main program for Nucleo64

//--------------------------------------------------------//

#include "main.h"
#include "IncludeLists.h"

// using namespace MAX2022;

void setup(){
    Serial_println("here");
    //Curr_Motor_Input.M1_DIR = 1;
    //Curr_Motor_Input.M2_DIR = 1;
    //Curr_Motor_Input.M3_DIR = 1;
    //Curr_Motor_Input.M4_DIR = 1;
}

void loop(){
    // I2C_Receive is needed for receiving new motor input from Spresense
    I2C_Receive_Routine();

    //Curr_Motor_Input.M1_PWM = 1.0;
    //Curr_Motor_Input.M2_PWM = 1.0;
    //Curr_Motor_Input.M3_PWM = 1.0;
    //Curr_Motor_Input.M4_PWM = 1.0;
    //Motor_Apply_Input();

    //wait_s(3);

    //Curr_Motor_Input.M1_PWM = 0.0;
    //Curr_Motor_Input.M2_PWM = 0.0;
    //Curr_Motor_Input.M3_PWM = 0.0;
    //Curr_Motor_Input.M4_PWM = 0.0;
    //Motor_Apply_Input();

    //wait_s(3);
}

void I2C_Receive_Routine(){
    I2C_Input* i2c_input = I2C_Receive();

    if (i2c_input != nullptr) {
        switch (i2c_input->input_type) {
            case PWM_DIR:{
                PWM_to_Input(i2c_input->pwm_dir);
                break;
            }
            case TargetXY:{
                TargetXY_to_Input(i2c_input->targetXY);
                break;
            }
            case Radian:{
                Radian_to_Input(i2c_input->radian);
                break;
            }
            case Encoder:{
                Encoder_to_Input(i2c_input->encoder);
                break;
            }
            default:break;
        }

        Motor_Apply_Input();

        delete i2c_input;
    }
}