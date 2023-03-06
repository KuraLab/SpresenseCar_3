// Written by MAX (Created 02 Mar, 2023)

// Features:    Initialization code for MainCore

//--------------------------------------------------------//

#ifndef SUBCORE

#include "MainCore_Init.h"
#include <IncludeLists.h>

// Init ALL Components
void MainCore_Init(){
    Onboard_LED_Init();
    Serial_Init();
    PIKAPIKA_Init();
    PowerDistBoard_LED_Init();
    I2C_Init();
    MP_Init();
    Timer_Interrupt_Init();

    Finish_Init_LED_Flash();
    Serial.println("Initialization Finished");
}

// Init the 4 onboard LED
void Onboard_LED_Init(){
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
}

// Init Serial Communication
void Serial_Init(){
    Serial.begin(DEFAULT_BAUD_RATE);
}

// Init PikaPika pins & variables
static void (*Custom_PIKAPIKA_Handler_0)(void);
static void (*Custom_PIKAPIKA_Handler_1)(void);
static void (*Custom_PIKAPIKA_Handler_2)(void);
static void (*Custom_PIKAPIKA_Handler_3)(void);
static void (*Custom_PIKAPIKA_Handler_4)(void);
static void (*Custom_PIKAPIKA_Handler_5)(void);
static void (*Custom_PIKAPIKA_Handler_6)(void);
static void (*Custom_PIKAPIKA_Handler_7)(void);
// -> Input your custom PikaPika Interrupt Handler here, input can be [nullptr]
void PIKAPIKA_Set_Custom_Handler(
    void (*Custom_Handler_0)(void), void (*Custom_Handler_1)(void), 
    void (*Custom_Handler_2)(void), void (*Custom_Handler_3)(void), 
    void (*Custom_Handler_4)(void), void (*Custom_Handler_5)(void), 
    void (*Custom_Handler_6)(void), void (*Custom_Handler_7)(void))
    {
        Custom_PIKAPIKA_Handler_0 = Custom_Handler_0;
        Custom_PIKAPIKA_Handler_1 = Custom_Handler_1;
        Custom_PIKAPIKA_Handler_2 = Custom_Handler_2;
        Custom_PIKAPIKA_Handler_3 = Custom_Handler_3;
        Custom_PIKAPIKA_Handler_4 = Custom_Handler_4;
        Custom_PIKAPIKA_Handler_5 = Custom_Handler_5;
        Custom_PIKAPIKA_Handler_6 = Custom_Handler_6;
        Custom_PIKAPIKA_Handler_7 = Custom_Handler_7;
    }
void PIKAPIKA_Set_Custom_Handler(){
    PIKAPIKA_Set_Custom_Handler(nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr);
}
void PIKAPIKA_Init(){
    pinMode(PIKAPIKA_LED, OUTPUT);

    pinMode(PIKAPIKA_LIGHT_0, INPUT);
    pinMode(PIKAPIKA_LIGHT_1, INPUT);
    pinMode(PIKAPIKA_LIGHT_2, INPUT);
    pinMode(PIKAPIKA_LIGHT_3, INPUT);
    pinMode(PIKAPIKA_LIGHT_4, INPUT);
    pinMode(PIKAPIKA_LIGHT_5, INPUT);
    pinMode(PIKAPIKA_LIGHT_6, INPUT);
    pinMode(PIKAPIKA_LIGHT_7, INPUT);

    if (Custom_PIKAPIKA_Handler_0 != nullptr){
        attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_0), Custom_PIKAPIKA_Handler_0, FALLING);
    } else {
        attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_0), Default_Pika_Int_Handler_0, FALLING);
    }
    if (Custom_PIKAPIKA_Handler_1 != nullptr){
        attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_1), Custom_PIKAPIKA_Handler_1, FALLING);
    } else {
        attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_1), Default_Pika_Int_Handler_1, FALLING);
    }
    if (Custom_PIKAPIKA_Handler_2 != nullptr){
        attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_2), Custom_PIKAPIKA_Handler_2, FALLING);
    } else {
        attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_2), Default_Pika_Int_Handler_2, FALLING);
    }
    if (Custom_PIKAPIKA_Handler_3 != nullptr){
        attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_3), Custom_PIKAPIKA_Handler_3, FALLING);
    } else {
        attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_3), Default_Pika_Int_Handler_3, FALLING);
    }
    if (Custom_PIKAPIKA_Handler_4 != nullptr){
        attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_4), Custom_PIKAPIKA_Handler_4, FALLING);
    } else {
        attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_4), Default_Pika_Int_Handler_4, FALLING);
    }
    if (Custom_PIKAPIKA_Handler_5 != nullptr){
        attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_5), Custom_PIKAPIKA_Handler_5, FALLING);
    } else {
        attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_5), Default_Pika_Int_Handler_5, FALLING);
    }
    if (Custom_PIKAPIKA_Handler_6 != nullptr){
        attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_6), Custom_PIKAPIKA_Handler_6, FALLING);
    } else {
        attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_6), Default_Pika_Int_Handler_6, FALLING);
    }
    if (Custom_PIKAPIKA_Handler_7 != nullptr){
        attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_7), Custom_PIKAPIKA_Handler_7, FALLING);
    } else {
        attachInterrupt(digitalPinToInterrupt(PIKAPIKA_LIGHT_7), Default_Pika_Int_Handler_7, FALLING);
    }    
}

// Init Power Distribution Board LED pins
void PowerDistBoard_LED_Init(){
    pinMode(BLUE_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, HIGH);

    delay(500);

    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, LOW);
}

// Init I2C
void I2C_Init(){
    Wire.begin();
    Wire.setClock(TWI_FREQ_400KHZ);
}

// Init SubCores
void MP_Init(){
    int ret;

    ret = MP.begin(SUBCORE_1_ID);
    if (ret<0) {
        MPLog("MP.begin(%d) error = %d\n", SUBCORE_1_ID, ret);
    }
    ret = MP.begin(SUBCORE_2_ID);
    if (ret<0) {
        MPLog("MP.begin(%d) error = %d\n", SUBCORE_2_ID, ret);
    }
    ret = MP.begin(SUBCORE_3_ID);
    if (ret<0) {
        MPLog("MP.begin(%d) error = %d\n", SUBCORE_3_ID, ret);
    }
    ret = MP.begin(SUBCORE_4_ID);
    if (ret<0) {
        MPLog("MP.begin(%d) error = %d\n", SUBCORE_4_ID, ret);
    }
    ret = MP.begin(SUBCORE_5_ID);
    if (ret<0) {
        MPLog("MP.begin(%d) error = %d\n", SUBCORE_5_ID, ret);
    }
}

// Init Timer Interrupt
static unsigned int Timer_Interrupt_Period = DEFAULT_TIMER_INT_INTERVAL;
// -> Input your custom Timer Interrupt period here
void Timer_Interrupt_Set_Period(unsigned int new_timer_int_period_us){
    Timer_Interrupt_Period = new_timer_int_period_us;
}
void Timer_Interrupt_Set_Period(){
    Timer_Interrupt_Set_Period(DEFAULT_TIMER_INT_INTERVAL);
}
// -> getter for Timer_Interrupt_Period
unsigned int Timer_Interrupt_Get_Period(){
    return Timer_Interrupt_Period;
}
extern unsigned int Timer_Interrupt_Routine();
void Timer_Interrupt_Init(){
    attachTimerInterrupt(&Timer_Interrupt_Routine, Timer_Interrupt_Period);
}

//--------------------------------------------------------//

void Finish_Init_LED_Flash(){
    digitalWrite(LED0, HIGH);
    delay(50);
    digitalWrite(LED1, HIGH);
    delay(50);
    digitalWrite(LED2, HIGH);
    delay(50);
    digitalWrite(LED3, HIGH);
    delay(500);

    digitalWrite(LED0, LOW);
    delay(50);
    digitalWrite(LED1, LOW);
    delay(50);
    digitalWrite(LED2, LOW);
    delay(50);
    digitalWrite(LED3, LOW);
    // delay(500);
}

#endif