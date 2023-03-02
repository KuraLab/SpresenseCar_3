// Written by MAX (Created 02 Mar, 2023)

// Features:    [main.ino] for MainCore

//--------------------------------------------------------//

#include "IncludeLists.h"

void setup() {
  // [INITIALIZATION USE] DO NOT DELETE THE FOLLOWING CODES
  // -> Put your custom handler for PikaPika Interrupts here, leave it empty if you are not using PikaPika
  PIKAPIKA_Set_Custom_Handler();
  // -> Put your custom period for Timer Interrupt here, default = 100us(->10kHz)
  Timer_Interrupt_Set_Period();
  // -> [IMPORTANT] DO NOT DELETE OR MODIFY THIS LINE
  MainCore_Init();
  // [INITIALIZATION FINISHED] Feel free to add your codes below
  //--------------------------------------------------------//

  // put your setup code here, to run once:
  // Serial.begin(115200);
  // Serial.println(asdf);

  // pinMode(LED0, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED0, HIGH);
  delay(1000);
  digitalWrite(LED0, LOW);
  delay(1000);
}

unsigned int Timer_Interrupt_Routine(){

  return get_Timer_Interrupt_Period();
}