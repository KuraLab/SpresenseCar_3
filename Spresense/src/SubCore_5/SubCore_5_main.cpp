// Written by MAX (Created 03 Mar, 2023)

// Features:    [main.ino] for SubCore_5

//--------------------------------------------------------//

#if (SUBCORE == 5)

#include <IncludeLists.h>

void setup(){
    //---[INITIALIZATION USE]---------------------------------//
    // DO NOT CHANGE OR DELETE THE FOLLOWING CODES
    MP.begin();
    MPLog("SubCore 5 Initialized \n");
    //---[INITIALIZATION FINISHED]----------------------------//

    MPLog("%d \n", SUBCORE);
}

void loop(){

}

#endif