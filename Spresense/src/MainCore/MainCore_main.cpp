// Written by MAX (Created 02 Mar, 2023)

// Features:    [main.ino] for MainCore

//--------------------------------------------------------//

#ifndef SUBCORE

#include <IncludeLists.h>

using namespace MAX2022;
int* speed_admain;
int8_t msgid_main;
int wheelspeed[4];


inline void test_init4(){
    int u=10;
    int u2[2];
    int houkou;
    int v=0;
    int speed[4];
    int ret;
    int8_t msgid;

    v=(*(speed_admain+0)+*(speed_admain+1)+*(speed_admain+2)+*(speed_admain+3))/4;  
    ret = MP.Send(msgid,u,1);
    if(ret==0){
      MP.Send(msgid,v,1);
    }
    //MP.RecvTimeout(0);
    //MP.Recv(&msgid,&u2[0],1);
    //MP.Recv(&msgid,&u2[1],1);
    if(u2[1]==1){
      digitalWrite(LED0, HIGH);
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
    }
    else{
      digitalWrite(LED0, LOW);
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
    }
    Serial.print(u);
    Serial.print("\r\n");
    Serial.print(u2[0]);
    Serial.print("\r\n");
    Serial.print(v);
    Serial.print("\r\n");
    //v=v+0.2*u2[0];
    v=300;
    if(v<0){
      houkou=0;
    }
    else{
      houkou=1;
    }
    
    I2C_Start_Send();
    //for (int i = 0; i < 1; i++){
      //wheelspeed[0]+=(abs(v)-*speed_admain)/1000;
      //wheelspeed[1]+=(abs(v)-*(speed_admain+1))/1000;
      //wheelspeed[2]+=(abs(v)-*(speed_admain+2))/1000;
      //wheelspeed[3]+=(abs(v)-*(speed_admain+3))/1000;
      I2C_Send_Encoder(1.0, 1.0, 1.0, 1.0);
      I2C_Send_PWM_DIR(Motor_TL, 0.3, houkou);
      I2C_Send_PWM_DIR(Motor_TR, 0.3, houkou);
      I2C_Send_PWM_DIR(Motor_BL, 0.3, houkou);
      I2C_Send_PWM_DIR(Motor_BR, 0.3, houkou);
      delay(50);
      //}
    }


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
  MP.RecvTimeout(0);
  MP.Recv(&msgid_main,&speed_admain,3);
}

void loop() {

  // put your main code here, to run repeatedly:
  // digitalWrite(LED0, HIGH);
  // delay(1000);
  // digitalWrite(LED0, LOW);
  // delay(1000);
  //test_init2();
  test_init4();
  //Sub3_loop();
  //MainCore_loop();
}



unsigned int Timer_Interrupt_Routine(){

  FFT_PikaPika_Routine();

  // PLEASE DO NOT CHANGE THIS RETURN, USE SETTER TO CHANGE PERIOD
  return Timer_Interrupt_Get_Period();
}
#endif