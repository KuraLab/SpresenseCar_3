// Written by MAX (Created 02 Mar, 2023)

// Features:    [main.ino] for MainCore

//--------------------------------------------------------//

#ifndef SUBCORE

#include <IncludeLists.h>
#include <SDHCI.h>
#include <File.h>

using namespace MAX2022;
int* speed_admain;
int8_t msgid_main;
double wheel_PWM[4]={0.3,0.3,0.3,0.3};
int v=300;
//int v=0;
int houkou;
SDClass SD;
File myFile;
int endcount=0;
int end=0;
inline void test_init4(){
    int u=50;
    //int u=0;
    int u2[4];
    int v_mean;
    int ret;
    double feedback[4];
    int8_t msgid;
    double* ptr2; 
    v_mean=(*(speed_admain+0)+*(speed_admain+1)+*(speed_admain+2)+*(speed_admain+3))/4;  
    ptr2= CBF1Dasym(u,v_mean,houkou);
    //ptr2= CBF1D(u,houkou);
    for (int i = 0; i < 4; ++i) {
        u2[i]=ptr2[i];
    }
   
    //ret = MP.Send(msgid,u,1);
    //if(ret==0){
    //  MP.Send(msgid,v,1);
    //}
    ///MP.RecvTimeout(0);
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
    Serial.print(",");
    Serial.print(u2[0]);
    Serial.print(",");
    Serial.print(u2[2]);
    Serial.print(",");
    Serial.print(u2[3]);
    Serial.print("\r\n");
    Serial.print(wheel_PWM[0]);
    Serial.print(",");
    Serial.print(wheel_PWM[1]);
    Serial.print(",");
    Serial.print(wheel_PWM[2]);
    Serial.print(",");
    Serial.print(wheel_PWM[3]);
    Serial.print("\r\n");
    Serial.print(*(speed_admain+0)-v);
    Serial.print(",");
    Serial.print(*(speed_admain+1)-v);
    Serial.print(",");
    Serial.print(*(speed_admain+2)-v);
    Serial.print(",");
    Serial.print(*(speed_admain+3)-v);
    Serial.print("\r\n");
    Serial.print(v_mean);
    Serial.print(",");
    Serial.print(v);
    Serial.print("\r\n");
    v=v+0.1*u2[0];
    if(v<0){
      houkou=0;
    }
    else{
      houkou=1;
    }
    
    I2C_Start_Send();
    if(end==1){
      I2C_Send_Encoder(0.0, 0.0, 0.0, 0.0);
    }
    else{
      for (int i = 0; i < 19; i++){
        feedback[0]=abs(v)-*speed_admain;
        feedback[1]=abs(v)-*(speed_admain+1);
        feedback[2]=abs(v)-*(speed_admain+2);
        feedback[3]=abs(v)-*(speed_admain+3);
        wheel_PWM[0]+=feedback[0]/4000;
        wheel_PWM[1]+=feedback[1]/4000;
        wheel_PWM[2]+=feedback[2]/4000;
        wheel_PWM[3]+=feedback[3]/4000;
        I2C_Send_Encoder(1.0, 1.0, 1.0, 1.0);
        for(int i = 0; i < 4; i++){
          if(wheel_PWM[i]>1.0){
            wheel_PWM[i]=1.0;
          }
          else if(wheel_PWM[i]<0.0){
            wheel_PWM[i]=0.0;
            I2C_Send_Encoder(0.0, 0.0, 0.0, 0.0);
          }
        }
      
        I2C_Send_PWM_DIR(Motor_TL, abs(wheel_PWM[0]), houkou);
        I2C_Send_PWM_DIR(Motor_TR, abs(wheel_PWM[1]), houkou);
        I2C_Send_PWM_DIR(Motor_BL, abs(wheel_PWM[2]), houkou);
        I2C_Send_PWM_DIR(Motor_BR, abs(wheel_PWM[3]), houkou);
        }
    }
    if(*(speed_admain+0)<10 && *(speed_admain+1)<10 && *(speed_admain+2)<10 && *(speed_admain+3)<10){
      endcount +=1;
    }
    else{
      endcount=0;
    }
    if(endcount>=100){
      end=1;
    }
    
    myFile = SD.open("Lidar/350-4mm.txt", FILE_WRITE);
    if (myFile && !(end==1)) {
    //Serial.print("Writing to test_ground.txt...");
    myFile.printf("%d,%d\r\n", u2[2],u2[3]);
    //myFile.println(speed[1]);
    //myFile.println(speed[2]);
    //myFile.println(speed[3]);
    //Close the file 
    myFile.close();
    //Serial.println("done.");
    }
  else {
    //If the file didn't open, print an error 
    //Serial.println("error opening test_ground.txt");
  }
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
  Serial2.begin(115200);
  while (!Serial) {
   ; /* wait for serial port to connect. Needed for native USB port only */
  }
  /* Initialize SD */
  Serial.print("Insert SD card.\r\n");
  //while (!SD.begin()) {
   //; /* wait until SD card is mounted. */
  //}
  /* Create a new directory */
  SD.mkdir("Lidar/");
  MP.RecvTimeout(0);
  MP.Recv(&msgid_main,&speed_admain,1);
  myFile = SD.open("Lidar/350-4mm.txt", FILE_WRITE);
  if (myFile && !(end==1)) {
  myFile.printf("------------\r\n");
  myFile.close();
  }
  Serial2.write("MD0118063616001\r\n");
  delay(100);
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