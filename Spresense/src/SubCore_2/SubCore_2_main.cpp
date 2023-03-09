// Written by MAX (Created 03 Mar, 2023)

// Features:    [main.ino] for SubCore_2

//--------------------------------------------------------//

#if (SUBCORE == 2)

#include <IncludeLists.h>

using namespace MAX2022;

void setup(){
    //---[INITIALIZATION USE]---------------------------------//
    // DO NOT CHANGE OR DELETE THE FOLLOWING CODES
    MP.begin();
    MPLog("SubCore 2 Initialized \n");
    //---[INITIALIZATION FINISHED]----------------------------//

    MPLog("%d \n", SUBCORE);

    Sub2_setup();
}

void loop(){
    Sub2_loop();
}

#endif