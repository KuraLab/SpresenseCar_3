// Written by MAX (Created 03 Mar, 2023)

// Features:    [main.ino] for SubCore_1

//--------------------------------------------------------//

#if (SUBCORE == 1)

#include <IncludeLists.h>

void setup(){
    //---[INITIALIZATION USE]---------------------------------//
    // DO NOT CHANGE OR DELETE THE FOLLOWING CODES
    MP.begin();
    MPLog("SubCore 1 Initialized \n");
    //---[INITIALIZATION FINISHED]----------------------------//

    MPLog("%d \n", SUBCORE);
}

void loop(){

}

#endif