// Written by MAX (Created 02 Mar, 2023)

// Features:    Spresense-related Global Variables

//--------------------------------------------------------//

#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

// PI
#define PI                              3.14

// Serial Baud Rate
#define DEFAULT_BAUD_RATE               115200

// SubCore ID
#define SUBCORE_1                       1
#define SUBCORE_2                       2
#define SUBCORE_3                       3

// I2C
// -> Address of all components
#define NUCLEO_I2C_ADDR                 0x45>>1
// -> Message Length
#define I2C_MSG_LENGTH                  32

// PikaPika
// -> Sensor Count
#define PIKA_SENSOR_COUNT               8
// -> Blink Duration
#define DEFAULT_PIKA_BLINK_TIME         100     // LED点灯時間[回-dt]
// -> Light Sensor Lifetime
#define DEFAULT_PIKA_LIFETIME           10      // [タイマー割り込み回数]
// -> Minimum Interval between Interrupts
#define DEFAULT_PIKA_MIN_INTERRUPT_INTERVAL 0   // [ms]

// Motors
// -> Motor name    (Top = side with frontal block plate)
enum Motor { Motor_TL, Motor_TR, Motor_BL, Motor_BR };
// -> Encoder Ticks VS Real-life Distance
#define MOTOR_MM_PER_TICK               80*PI/150   // mm/tick (~1.6755)
// -> Related Info
// #define WHEEL_DIAMETER                  80      // mm
// #define ENCODER_TICK_PER_ROTATION       150
// Robotic Car Base Manual: https://osoyoo.com/2019/11/08/omni-direction-mecanum-wheel-robotic-kit-v1/
// Motor Spec: https://osoyoo.com/2019/11/08/how-to-test-motor-encoder-with-arduino/

#endif