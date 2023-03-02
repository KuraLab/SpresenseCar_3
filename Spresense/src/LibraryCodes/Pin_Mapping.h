// Written by MAX (Created 02 Mar, 2023)

/* Features:    Which Spresense pins are used & 
                What are their usages   */
                
// Pin location (Main Board): https://static.developer.sony.com/develop/spresense/docs/images/overview_hardware_mainboard_signal.jpg?t=1653357630769
// Pin location (Extension Board): https://static.developer.sony.com/images/image/s3/uploads/2019/07/overview_hardware_extboard_signal-1.jpg?v=783850&jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ3aGl0ZWxpc3RTaXplcyI6WyIxMjAweEFVVE8iLCIxMDB4NjUiLCIxMDB4QVVUTyIsIjExMHg4MiIsIjc1MHhBVVRPIiwiMTAwMHhBVVRPIiwiMTIwMHhBVVRPIiwiMTIwMHg4MDAiLCIxOTIweEFVVE8iLCIxOTIweDEwMDAiLCIyMDB4MTUwIiwiMjI1eDE3MCIsIjIyNXhBVVRPIiwiMjI5eDMwMCIsIjM2OHhBVVRPIiwiNDUweDM0MCIsIjUwMHhBVVRPIiwiNzUweDUwMCIsIjd4MTAiLCI3eDEyIiwiN3gxNiIsIjd4MyIsIjd4NCIsIjd4NSIsIjd4NiIsIjd4NyIsIjd4OCIsIjd4OSJdLCJpbWFnZVZlcnNpb24iOiJ2NiIsImV4cCI6MTkwNDY4ODAwMDAwMH0.TWmRV6gNzeipUt0QoKyQXGF1gCXiJZEDTmKUYov7hv8

//--------------------------------------------------------//

#ifndef PIN_MAPPING_H
#define PIN_MAPPING_H

// LED defined in official SONY library, duplicated here for reference
// #define LED0
// #define LED1
// #define LED2
// #define LED3

// I2C pins
#define I2C_M_SDA           PIN_D14
#define I2C_M_SCL           PIN_D15

// PikaPika pins
// -> PikaPika LED
#define PIKAPIKA_LED        PIN_D08
// -> PikaPika Light Sensors    (Starts counting from 0 deg (positive x-axis))
#define PIKAPIKA_LIGHT_0    PIN_D00
#define PIKAPIKA_LIGHT_1    PIN_D01
#define PIKAPIKA_LIGHT_2    PIN_D02
#define PIKAPIKA_LIGHT_3    PIN_D03
#define PIKAPIKA_LIGHT_4    PIN_D04
#define PIKAPIKA_LIGHT_5    PIN_D05
#define PIKAPIKA_LIGHT_6    PIN_D06
#define PIKAPIKA_LIGHT_7    PIN_D07

// Power distribution board LED pins
#define BLUE_LED            PIN_D20
#define RED_LED             PIN_D21

// Motor Encoder pins   (Top = side with frontal block plate)
#define M1_HALL             PIN_D25     // M1 = Top Left
#define M2_HALL             PIN_D26     // M2 = Top Right
#define M3_HALL             PIN_D27     // M3 = Bottom Left
#define M4_HALL             PIN_D28     // M4 = Bottom Right

#endif