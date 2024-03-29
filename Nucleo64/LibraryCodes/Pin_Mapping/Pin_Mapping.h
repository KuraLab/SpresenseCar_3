// Written by MAX (Created 06 Mar, 2022)

/* Features:    Which Nucleo64 pins are used & 
                What are their usages   */

// Pin location: https://os.mbed.com/platforms/ST-Nucleo-F446RE/

//--------------------------------------------------------//

#ifndef PIN_MAPPING_H
#define PIN_MAPPING_H

// PIN defined in library, duplicated here for reference
// #define LED1         PA_5
// #define BUTTON1      PC_13
// #define CONSOLE_TX   PA_2
// #define CONSOLE_RX   PA_3

// I2C pins
#define I2C_M_SDA_PIN   PB_9
#define I2C_M_SCL_PIN   PB_8

// Motor pins
// -> DIR_1 -> forward
// -> DIR_2 -> backward

//  M1 = Top Left   (Top = side with frontal block plate)
#define M1_PWM_PIN      PA_8
#define M1_DIR_1_PIN    PC_4
#define M1_DIR_2_PIN    PB_13
// #define M1_HALL_1_PIN   PB_14
// #define M1_HALL_2_PIN   PB_15

//  M2 = Top Right
#define M2_PWM_PIN      PA_0
#define M2_DIR_1_PIN    PC_3
#define M2_DIR_2_PIN    PC_2
// #define M2_HALL_1_PIN   PH_1
// #define M2_HALL_2_PIN   PD_2

//  M3 = Bottom Left
#define M3_PWM_PIN      PA_6
#define M3_DIR_1_PIN    PC_8
#define M3_DIR_2_PIN    PC_6
// #define M3_HALL_1_PIN   PC_5
// #define M3_HALL_2_PIN   PA_12

//  M4 = Bottom Right
#define M4_PWM_PIN      PB_6
#define M4_DIR_1_PIN    PC_10
#define M4_DIR_2_PIN    PC_12
// #define M4_HALL_1_PIN   PA_13
// #define M4_HALL_2_PIN   PC_11

#endif