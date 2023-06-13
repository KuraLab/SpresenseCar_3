// Written by MAX (Created 03 Mar, 2023)

// Features:    [main.ino] for SubCore_3

//--------------------------------------------------------//

#if (SUBCORE == 3)

#include <IncludeLists.h>

using namespace MAX2022;
int count[4]={0,0,0,0};
int speed[4]={0,0,0,0};
uint64_t curr_time;
uint64_t curr_time_1;
void Count1UP(){
    count[0]++;
 }
void Count2UP(){
    count[1]++;
 }
void Count3UP(){
    count[2]++;
 }
void Count4UP(){
    count[3]++;
 }
void setup(){
    //---[INITIALIZATION USE]---------------------------------//
    // DO NOT CHANGE OR DELETE THE FOLLOWING CODES
    MP.begin();
    MPLog("SubCore 3 Initialized \n");
    //---[INITIALIZATION FINISHED]----------------------------//+
    MPLog("%d \n", SUBCORE);

    Serial.begin(115200);
    pinMode (PIN_D25,INPUT);
    pinMode (PIN_D26,INPUT);
    pinMode (PIN_D27,INPUT);
    pinMode (PIN_D28,INPUT);
    attachInterrupt(digitalPinToInterrupt(PIN_D25), Count1UP, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_D26), Count2UP, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_D27), Count3UP, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_D28), Count4UP, CHANGE);
    // Sub3_setup();
}

void loop(){
    // Sub3_loop();
    curr_time=millis();
    if(curr_time-curr_time_1>=50){
        speed[0]=80*PI*count[0]*1000/450/(curr_time-curr_time_1);
        speed[1]=80*PI*count[1]*1000/450/(curr_time-curr_time_1);
        speed[2]=80*PI*count[2]*1000/450/(curr_time-curr_time_1);
        speed[3]=80*PI*count[3]*1000/450/(curr_time-curr_time_1);
        count[0]=0;
        count[1]=0;
        count[2]=0;
        count[3]=0;
        Serial.print(speed[0]);
        Serial.print(",");
        Serial.print(speed[1]);
        Serial.print(",");
        Serial.print(speed[2]);
        Serial.print(",");
        Serial.print(speed[3]);
        Serial.print(",\r\n");
        curr_time_1=curr_time;
    }
}

#endif