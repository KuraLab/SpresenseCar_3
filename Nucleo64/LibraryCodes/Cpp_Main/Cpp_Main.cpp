// Written by MAX (Created 06 Mar, 2022)

// Features:    THE TRUE Main program for Nucleo64

//--------------------------------------------------------//

#include "../../IncludeLists.h"

//--------------------------------------------------------//

// GLOBAL VARIABLES

// Position Variables
// -> Coordinates
uint32_t            X, Y;
uint32_t            target_X, target_Y;

// PIN Variables
// -> onboard LED & Button
DigitalOut*         LED;
DigitalIn*          Button;     //Pressed=0, NOT Pressed=1
// -> I2C
I2CSlave*           I2C_SLAVE_M;
// -> Motor pins
PwmOut*             Motor_PWM[4];
DigitalOut*         Motor_DIR[2*4];
// InterruptIn*        Motor_HALL[2*4];

// Motor Related
// -> Motor enum (PLACEHOLDER)
// enum Motor { Motor_TL, Motor_TR, Motor_BL, Motor_BR };
// -> Motor Current Input
Motor_Input         Curr_Motor_Input;
// -> Motor Hall Sensors Count
// uint16_t            Hotor_HALL_count[2*4] = {0,0,0,0,0,0,0,0};

// Serial communication
BufferedSerial*     Serial_M;

//--------------------------------------------------------//

// THE REAL main() for mbed
// main() runs in its own thread in the OS
int main()
{
    Init();
    setup();
    while (true) {
        loop();
    }
}
