// Written by MAX (Created 31-08-2022)

/* Features :   Code for Spresense SubCore 1
                SubCore 1 -> General Tasks
*/
//--------------------------------------------------------//

#if (SUBCORE == 1)

//--------------------------------------------------------//

#include "Sub1_main.h"
#include "Sub1_TaskList.h"
#include <IncludeLists.h>

//--------------------------------------------------------//

// Functions Declaration

//--------------------------------------------------------//

namespace MAX2022
{
    void Sub1_setup(void){
        // MP.begin();
    }
    
    void Sub1_loop(void){
        int8_t msgid;
        uint32_t msgdata;
    
        MP.Recv(&msgid, &msgdata);
    
        switch (msgid)
        {
        case C1_T0_COMMU_TEST:
            MP.Send(msgid, msgdata+100);
            break;
        case C1_T1_PIKAPIKA_LED:{
            uint64_t endtime = millis()+(uint64_t)msgdata;
            digitalWrite(PIKAPIKA_LED, HIGH);
            while (millis() < endtime){};
            digitalWrite(PIKAPIKA_LED, LOW);
            break;
        }
        case C1_T2_INSIDE_LED:{
            digitalWrite(BLUE_LED, HIGH);
            uint64_t endtime = millis()+(uint64_t)msgdata;
            while (millis() < endtime){};
            digitalWrite(BLUE_LED, LOW);
            break;
        }
        case C1_T3_OUTSIDE_LED:{
            digitalWrite(RED_LED, HIGH);
            uint64_t endtime = millis()+(uint64_t)msgdata;
            while (millis() < endtime){};
            digitalWrite(RED_LED, LOW);
            break;
        }
        default:
            break;
        }
    }
    void Sub1_loop2(void){
        int8_t msgid;
        int u_2;
        int ret_sub1;
        int v_sub1;
        MP.RecvTimeout(0);
        MP.Recv(&msgid,&u_2);
        //MP.Recv(&msgid,&v_sub1);
        //u_2=100;
        int u3[2];
        double* ptr2; 
        //ptr2= CBF1Dasym(u_2,v_sub1);
        for (int i = 0; i < 2; ++i) {
            u3[i]=ptr2[i];
        }
        //Serial.print(u_2);
        //Serial.print("\r\n");
        //Serial.print(u3[0]);
        //Serial.print("\r\n");
        ret_sub1=MP.Send(msgid,u3[0]);
        if(ret_sub1==0){
            MP.Send(msgid,u3[1]);
        }
    }
}

#endif