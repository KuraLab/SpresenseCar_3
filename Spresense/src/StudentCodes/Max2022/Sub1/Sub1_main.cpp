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
        MP.begin();
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
}

#endif