// Written by MAX (Created 03 Mar, 2023)

// Features:    [main.ino] for SubCore_1

//--------------------------------------------------------//
#if (SUBCORE == 1)

#include <IncludeLists.h>

using namespace MAX2022;
void setup(){
    //---[INITIALIZATION USE]---------------------------------//
    // DO NOT CHANGE OR DELETE THE FOLLOWING CODES
    MP.begin();
    MPLog("SubCore 1 Initialized \n");
    //---[INITIALIZATION FINISHED]----------------------------//
    Serial2.begin(115200);
    Serial.begin(115200);
    MPLog("%d \n", 1);
    //Sub1_setup();
}

void loop(){
    //Sub1_loop();
    int8_t msgid;
    int u_2;
    int ret;
    MP.RecvTimeout(0);
    MP.Recv(&msgid,&u_2);
    //u_2=100;
    int u3[2];
    double* ptr2; 
    ptr2= CBF1D(u_2);
    for (int i = 0; i < 2; ++i) {
        u3[i]=ptr2[i];
    }
    //Serial.print(u_2);
    //Serial.print("\r\n");
    //Serial.print(u3[0]);
    //Serial.print("\r\n");
    ret=MP.Send(msgid,u3[0]);
    if(ret==0){
        MP.Send(msgid,u3[1]);
    }
}

#endif