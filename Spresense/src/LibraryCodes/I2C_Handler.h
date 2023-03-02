// Written by MAX (Created 02 Mar, 2023)

// Features:    Translator from Variables to I2C Messages for Nucleo64

//--------------------------------------------------------//

#ifndef I2C_HANDLER_H
#define I2C_HANDLER_H

// Use this instead of [Wire.beginTransmission()]
void I2C_Start_Send();

// Use this instead of [Wire.endTransmission()]
void I2C_End_Send();

/**
 *  Input validation:
 *      pwm: no -ve, >0 part (left-hand side) will be omitted
 *      dir: only 0,1,2(2=no change in directions)
 * 
 *  For pwm: will only send first 8 decimal places
 */
bool I2C_Send_PWM_DIR (Motor motor, float pwm, uint8_t dir);

/**
 *  Input validation:
 *      tar_X, tar_Y: no -ve
 * 
 *  For tar_X, tar_Y: will send 9 digits
 */
bool I2C_Send_Target_XY (int tar_X, int tar_Y);

/**
 *  Input validation:
 *      radian: limit to [0,2pi]
 * 
 *  For radian: will only send first 8 decimal places
 */
bool I2C_Send_Radian (float radian);

/**
 *  Input validation:
 *      m1_mul, m2_mul, m3_mul, m4_mul: scale down w.r.t slowest motor please (mul of slowest motor = 1.0), , no -ve, >0 part will be omitted
 * 
 *  For m1_mul, m2_mul, m3_mul, m4_mul: will only send first 6 decimal places
 */
bool I2C_Send_Encoder (float m1_mul, float m2_mul, float m3_mul, float m4_mul);

#endif