// Written by MAX (Created 03 Mar, 2023)

// Features:    [main.ino] for SubCore_3

//--------------------------------------------------------//

#if (SUBCORE == 3)

#include <IncludeLists.h>


void setup(){
    //---[INITIALIZATION USE]---------------------------------//
    // DO NOT CHANGE OR DELETE THE FOLLOWING CODES
    MP.begin();
    MPLog("SubCore 3 Initialized \n");
    //---[INITIALIZATION FINISHED]----------------------------//+
    MPLog("%d \n", SUBCORE);

    // Sub3_setup();

}

void loop(){
    // Sub3_loop();
   
}

#endif