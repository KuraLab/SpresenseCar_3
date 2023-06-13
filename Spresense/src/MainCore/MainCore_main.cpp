// Written by MAX (Created 02 Mar, 2023)

// Features:    [main.ino] for MainCore

//--------------------------------------------------------//

#ifndef SUBCORE

#include <IncludeLists.h>

using namespace MAX2022;
void setup() {
  //---[INITIALIZATION USE]---------------------------------//
  // DO NOT DELETE THE FOLLOWING CODES
  // -> Put your custom handler for PikaPika Interrupts here, leave it empty if you are not using PikaPika
  //PIKAPIKA_Set_Custom_Handler();
  // -> Put your custom period for Timer Interrupt here, default = 100us(->10kHz)
  Timer_Interrupt_Set_Period();
  // -> [IMPORTANT] DO NOT DELETE OR MODIFY THIS LINE
  MainCore_Init();
  //---[INITIALIZATION FINISHED]----------------------------//
  MainCore_setup();
  //Sub3_setup();
}

void loop() {

  // put your main code here, to run repeatedly:
  // digitalWrite(LED0, HIGH);
  // delay(1000);
  // digitalWrite(LED0, LOW);
  // delay(1000);
  //test_init2();
  test_init3();
  //Sub3_loop();
  //MainCore_loop();
}

unsigned int Timer_Interrupt_Routine(){

  FFT_PikaPika_Routine();

  // PLEASE DO NOT CHANGE THIS RETURN, USE SETTER TO CHANGE PERIOD
  return Timer_Interrupt_Get_Period();
}
#endif