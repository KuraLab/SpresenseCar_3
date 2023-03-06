// Written by MAX (Created 05-01-2023)

/* Features :   Code for Spresense SubCore 3
                SubCore 3 -> Motor Encoders Feedback Tracking
*/
//--------------------------------------------------------//

#if (SUBCORE == 3)

//--------------------------------------------------------//

#ifndef MAX2022_SUB_3_MAIN_H
#define MAX2022_SUB_3_MAIN_H

#include <Arduino.h>

namespace MAX2022
{
    // Functions Declaration
    void Interrupt_Tick_Update(uint8_t motor_num);
    void M1_Int_Handler();
    void M2_Int_Handler();
    void M3_Int_Handler();
    void M4_Int_Handler();

    // Speed in tick/s
    float get_Speed_Since_Last_Access(uint8_t motor_num);

    //--------------------------------------------------------//

    void Sub3_setup(void);
    void Sub3_loop(void);
}

#endif

#endif