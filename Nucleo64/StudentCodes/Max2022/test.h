// Written by MAX (Created 14-06-2022)

/* Features:  Write test functions here, 
              so main program will not be messy
*/

// *** ONLY CASE WHICH FUNCTIONS ARE DEFINED IN HEADER *** 

//--------------------------------------------------------//

#ifndef MAX2022_TEST_H
#define MAX2022_TEST_H

#include "../../LibraryCodes/QOL_Func/QOL_Func.h"
#include "../../LibraryCodes/Cpp_Main/Cpp_Main_Global_Var.h"
#include "../../LibraryCodes/Motor_Control/Motor_Control.h"

#include "mbed.h"
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <ctime>

//--------------------------------------------------------//

// EXTERN of FUNCTION Declaration

//--------------------------------------------------------//

namespace MAX2022
{
    inline void test_init(){
        Serial_println("now monitor I2C la");

        Curr_Motor_Input.M1_PWM = 1.0;
        Curr_Motor_Input.M1_DIR = 1;
        Curr_Motor_Input.M1_MUL = 1.0;

        Curr_Motor_Input.M2_PWM = 1.0;
        Curr_Motor_Input.M2_DIR = 1;
        Curr_Motor_Input.M2_MUL = 1.0;

        Curr_Motor_Input.M3_PWM = 1.0;
        Curr_Motor_Input.M3_DIR = 1;
        Curr_Motor_Input.M3_MUL = 1.0;

        Curr_Motor_Input.M4_PWM = 1.0;
        Curr_Motor_Input.M4_DIR = 1;
        Curr_Motor_Input.M4_MUL = 1.0;

        Motor_Apply_Input();
    }

    // void test_init(){

    //     Serial_println("now monitor I2C la");

    //     while(1){
    //         // static uint32_t count = 0;

    //         // Serial_println(count);

    //         // if (count >= 50000000) {
    //             I2C_Input* i2c_input = I2C_Read();
    //             if (i2c_input == nullptr) {
    //                 // Serial_println("is null");
    //             } else {
    //                 Serial_println(i2c_input->input_type);
    //                 Serial_println();
    //                 Serial_println(i2c_input->pwm_dir.motor);
    //                 Serial_println(i2c_input->pwm_dir.pwm);
    //                 Serial_println(i2c_input->pwm_dir.dir);
    //                 Serial_println();
    //                 Serial_println(i2c_input->targetXY.target_X);
    //                 Serial_println(i2c_input->targetXY.target_Y);
    //                 Serial_println();
    //                 Serial_println(i2c_input->radian);
    //                 Serial_println();
    //                 Serial_println(i2c_input->encoder.M1_Multiplier);
    //                 Serial_println(i2c_input->encoder.M2_Multiplier);
    //                 Serial_println(i2c_input->encoder.M3_Multiplier);
    //                 Serial_println(i2c_input->encoder.M4_Multiplier);
    //                 Serial_println();
    //             }
    //         //     count = 0;
    //         // } else {
    //         //     count++;
    //         // }

    //         // int addressed = I2C_SLAVE_M->receive();

    //         // // Serial_println(addressed);

    //         // if (addressed == I2CSlave::WriteAddressed) {
    //         //     char buf[32];
    //         //     int data = I2C_SLAVE_M->read(buf, 32);
    //         //     Serial_println(buf);
    //         // }
    //     }

    //     Serial_println("not dead");
    // }

    inline void test_loop(){

        // I2C_Input* i2c_input = I2C_Read();

        // if (i2c_input != nullptr) {
        //     switch (i2c_input->input_type) {
        //         case PWM_DIR:{
        //             PWM_to_Input(i2c_input->pwm_dir);
        //             break;
        //         }
        //         case TargetXY:{
        //             TargetXY_to_Input(i2c_input->targetXY);
        //             break;
        //         }
        //         case Radian:{
        //             Radian_to_Input(i2c_input->radian);
        //             break;
        //         }
        //         case Encoder:{
        //             Encoder_to_Input(i2c_input->encoder);
        //             break;
        //         }
        //         default:break;
        //     }
        // }

        // Serial_println(Motor_HALL_count[0]);
        // for (int i = 0; i < 10; i++) {
        //     Serial_println((uint32_t)(Motor_HALL_time[i]));
        // }
        // Serial_println();
        // Serial_println(Motor_HALL_count[0]);
        // Serial_println(Motor_HALL_count[1]);
        // Serial_println(Motor_HALL_count[2]);
        // Serial_println(Motor_HALL_count[3]);
        // Serial_println(Motor_HALL_count[4]);
        // Serial_println(Motor_HALL_count[5]);
        // Serial_println(Motor_HALL_count[6]);
        // Serial_println(Motor_HALL_count[7]);

        // Serial_println((int)(HAL_GetTick()));

        // for (float f=0.0f; f<1.1f; f+=0.1f) {
        //     Motor_PWM[2]->write(f);
        //     Motor_PWM[3]->write(f);
        //     wait_us(500*1000);
        // }

        // *LED = Button->read();

    }
}

#endif