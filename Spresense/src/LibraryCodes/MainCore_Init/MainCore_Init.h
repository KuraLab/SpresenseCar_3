// Written by MAX (Created 02 Mar, 2023)

// Features:    Initialization code for MainCore

//--------------------------------------------------------//

#ifndef SUBCORE

#ifndef MAINCORE_INIT_H
#define MAINCORE_INIT_H

// Init ALL Components
void MainCore_Init();

// Init the 4 onboard LED
void Onboard_LED_Init();

// Init Serial Communication
void Serial_Init();

// Init PikaPika pins & variables
// -> Input your custom PikaPika Interrupt Handler here, input can be [nullptr]
void PIKAPIKA_Set_Custom_Handler(
    void (*Custom_Handler_0)(void), void (*Custom_Handler_1)(void), 
    void (*Custom_Handler_2)(void), void (*Custom_Handler_3)(void), 
    void (*Custom_Handler_4)(void), void (*Custom_Handler_5)(void), 
    void (*Custom_Handler_6)(void), void (*Custom_Handler_7)(void));
void PIKAPIKA_Set_Custom_Handler();
void PIKAPIKA_Init();

// Init Power Distribution Board LED pins
void PowerDistBoard_LED_Init();

// Init I2C
void I2C_Init();

// Init SubCores
void MP_Init();

// Init Timer Interrupt
// -> Input your custom Timer Interrupt period here
void Timer_Interrupt_Set_Period(unsigned int new_timer_int_period);
void Timer_Interrupt_Set_Period();
// -> getter for Timer_Interrupt_Period
unsigned int get_Timer_Interrupt_Period();
void Timer_Interrupt_Init();

//--------------------------------------------------------//

void Finish_Init_LED_Flash();

#endif

#endif